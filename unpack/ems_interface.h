#ifndef KOA_EMS_INTERFACE_H
#define KOA_EMS_INTERFACE_H

#include <stdint.h>
#include <poll.h>
#include <cstring>
#include "FairLogger.h"

typedef uint32_t ems_u32;
typedef char ems_byte;

// Macro for swap the byte order
#define SWAP_32(n) (((n & 0xff000000) >> 24) |  \
                    ((n & 0x00ff0000) >>  8) |  \
                    ((n & 0x0000ff00) <<  8) |  \
                    ((n & 0x000000ff) << 24))

constexpr Int_t HEADERSIZE = 2*sizeof(ems_u32);

// ems cluster buffer
struct ems_buffer {
  size_t capacity; // capacity of this buffer
  ems_byte* data; // pointer to the read heap for storage

  ems_buffer() : capacity(8192) {
    data = (ems_byte*)malloc(sizeof(ems_byte)*capacity);
    if ( data == 0 ) {
      printf("error: malloc data (8192): %s\n", strerror(errno));
    }
  }
  ~ems_buffer() {
    if (data) {
      delete data;
    }
  }
};

class ems_cluster
{
 public:
  ems_cluster() : valid (false), initialized(false), size(0), position(0)
  {
    pfd.fd = -1;
    pfd.events = POLLIN;
    timeout = 1000;
  }

  ~ems_cluster() {}

  // set the file descriptor for input 
  void set_input(int finput)
  {
    pfd.fd = finput;
  }
  // set the polling timeout value (ms)
  void set_timeout(int time)
  {
    timeout = time;
  }
  inline int read_header(); // read the headers words, set the 'initialized' flag when header is ready for use
  inline int read_body(); // read the body words, set the 'valid' flag when body is ready for use

  inline void create_buffer(); // create a buffer with 'size' words, reuse the existing buffer if 'size' <= 'capacity' otherwise delete the old and create the new on with 'size' capacity
  inline void clear_buffer(); // reset flags, position and size
  inline void delete_buffer(); // delete the underlying buffer space and reset all members

  bool is_valid() { return valid; }
  bool is_initialized() { return initialized; };

private:
  friend class KoaEmsSource; // Ems Source should be able to access the data buffer directly
  
  pollfd pfd; // polling file descriptor for the input
  int    timeout; // polling timeout, 0 for immediately, -1 for blocking

  ems_u32 head[2]; // header words of cluster: 1. length of cluster from second word,  2. + 0x12345678
  size_t  size; // size of the whole cluster, including 2 header words
  size_t  position; // pointer position for the next R/W in the buffer
  ems_buffer buffer; // buffer for storing the data of this cluster

  bool valid; // whether a full cluster is ready or not
  bool initialized; // whether the header words have been read or not
};

void ems_cluster::create_buffer()
{
  if ( !buffer.data ) {
    buffer.capacity = size;
    buffer.data = (ems_byte*)malloc(sizeof(ems_byte)*size);
    if ( buffer.data == 0 ) {
      printf("error: malloc data (%llu byte): %s\n", (unsigned long long)size, strerror(errno));
    }
    return;
  }

  if ( buffer.capacity < size ) {
    free(buffer.data);

    buffer.capacity = size;
    buffer.data = (ems_byte*)malloc(sizeof(ems_byte)*size);
    if ( buffer.data == 0 ) {
      printf("error: malloc data (%llu byte): %s\n", (unsigned long long)size, strerror(errno));
    }
  }
  return;
}

void ems_cluster::clear_buffer()
{
  size = 0;
  position = 0;
  valid = false;
  initialized = false;
}

void ems_cluster::delete_buffer()
{
  free(buffer.data);
  buffer.capacity = 0;

  clear_buffer();
}

int ems_cluster::read_header()
{
  if ( !initialized ) {
    while ( position < HEADERSIZE ) {
      int res = poll(&pfd, 1, timeout);
      if ( res < 0 ) {
        LOG(error) << "ems_cluster::read_header : polling input stream error, " << strerror(errno);
        return -1;
      }
      else if ( res > 0 ) {
        res = read(pfd.fd, ((char*)head)+position, HEADERSIZE-position);
        if ( res <= 0 ) {
          LOG(error) << "ems_cluster::read_header : reading input stream error, " << strerror(errno);
          return -1;
        }
        position += res;
      }
    }

    //
    switch (head[1]) {
    case 0x12345678:
      size = head[0];
      break;
    case 0x78563412:
      size = SWAP_32(head[0]);
      break;
    default:
      LOG(fatal) << "ems_cluster::read_body : unknown endian " << std::hex << head[1] << std::dec;
      return -1;
    }

    size = (size+1)*sizeof(ems_u32);

    create_buffer();

    memcpy(buffer.data, (char*)head, HEADERSIZE);

    initialized = true;
  }
  else {
    LOG(fatal) << "ems_cluster::read_header : header already available!";
    return -1;
  }

  return 0;
}

int ems_cluster::read_body()
{
  if ( !initialized ) {
    LOG(fatal) << "ems_cluster::read_body : read header first!";
    return -1;
  }

  if ( !valid ) {
    while ( position < size ) {
      int res = poll(&pfd, 1, timeout);
      if ( res < 0 ) {
        LOG(error) << "ems_cluster::read_body : polling input stream error, " << strerror(errno);
        return -1;
      }
      else if ( res > 0 ) {
        res = read(pfd.fd, buffer.data+position, size-position);
        if ( res <= 0 ) {
          LOG(error) << "ems_cluster::read_body : reading input stream error, " << strerror(errno);
          return -1;
        }
        position += res;
      }
    }

    //
    if ( head[1] == 0x78563412 ) {
      int n = SWAP_32(head[0]);
      ems_u32* b = reinterpret_cast<ems_u32*>(buffer.data);
      for(int i=n;n>=0;i--){
        ems_u32 v = b[i];
        b[i] = SWAP_32(v);
      }
    }

    valid = true;
  }
  else {
    LOG(fatal) << "ems_cluster::read_body : body already available!";
    return -1;
  }

  return 0;
}
#endif
