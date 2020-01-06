#ifndef KOA_EMS_INTERFACE_H
#define KOA_EMS_INTERFACE_H

#include <stdint.h>>
typedef uint32_t ems_u32;
typedef char ems_byte;

// Macro for swap the byte order
#define SWAP_32(n) (((n & 0xff000000) >> 24) |  \
                    ((n & 0x00ff0000) >>  8) |  \
                    ((n & 0x0000ff00) <<  8) |  \
                    ((n & 0x000000ff) << 24))

struct ems_buffer {
  size_t capacity; // capacity of this buffer
  ems_byte* data; // pointer to the read heap for storage

  ems_buffer() : capacity(8192) {
    data = (ems_byte*)malloc(sizeof(ems_byte)*size);
    if ( data == 0 ) {
      printf("error: malloc data (8192): %s\n", strerror(errno));
    }
  }
};

class ems_cluster
{
 public:
  ems_cluster() : fd(-1), valid (false), initialized(false), size(0), position(0) {}
  ~ems_cluster() {}

  void set_input(int finput) { fd = finput; } // set the file descriptor for input
  inline int read_header(); // read the headers words, set the 'initialized' flag when header is ready for use
  inline int read_body(); // read the body words, set the 'valid' flag when body is ready for use

  inline void create_buffer(size_t size); // create a buffer with 'size' words, reuse the existing buffer if 'size' <= 'capacity' otherwise delete the old and create the new on with 'size' capacity
  inline void clear_buffer(); // reset flags, position and size
  inline void delete_buffer(); // delete the underlying buffer space and reset all members

  bool is_valid() { return valid; }
  bool is_initialized() ( return initialized; );

private:
  friend class KoaEmsSource; // Ems Source should be able to access the data buffer directly
  
  int fd; // file descriptor for the input

  ems_u32 head[2]; // header words of cluster: 1. length of cluster from second word,  2. + 0x12345678
  size_t  size; // size of the whole cluster, including 2 header words
  size_t  position; // pointer position for the next R/W in the buffer
  ems_buffer buffer; // buffer for storing the data of this cluster

  bool valid; // whether a full cluster is ready or not
  bool initialized; // whether the header words have been read or not
};

void ems_cluster::create_buffer(size_t size)
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
  
}

int ems_cluster::read_body()
{
  
}
#endif
