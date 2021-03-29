#include "KoaEmsStreamSource.h"
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <cstdlib>

// server string is combination of hostname + port like: hostname:port
// hostname can be IP address string or a domain name like "ikp078"
// port is the numeric port number of the event distributor server
Bool_t KoaEmsStreamSource::SetupInput(const char* server)
{
  // 1. get hostname and port number
  std::string fullname(server);
  auto n = fullname.find(":");
  if ( n == std::string::npos ) {
    LOG(fatal) << "KoaEmsStreamSource::SetupInput : incorrect server address, no port number provided."
               << "\n Correct format is x.x.x.x:port";
    exit(EXIT_FAILURE);
  }
  std::string ip = fullname.substr(0, n);
  std::string port = fullname.substr(n+1);

  return SetupInput(ip, port);
}

// ip is the hostname
// port is the port number
Bool_t KoaEmsStreamSource::SetupInput(std::string ip, std::string port)
{
  LOG(INFO) << "Input Stream from host: " << ip << ", port: " << port;

  // 1. check and convert hostname and port string
  struct addrinfo hints;
  struct addrinfo *result, *rp;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0; // any protocol is acceptted
  hints.ai_family = AF_INET; // ipv4

  int status = getaddrinfo(ip.c_str(), port.c_str(), &hints, &result);
  if ( status != 0 ) {
    LOG(fatal) << "KoaEmsStreamSource::SetupInput : " << gai_strerror(status);
    exit(EXIT_FAILURE);
  }

  // try each [host, port] returned by getaddrinfo until success
  for ( rp = result; rp != NULL; rp = rp->ai_next ) {
    fInput = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

    if ( fInput == -1 )
      continue;

    status = connect(fInput, rp->ai_addr, rp->ai_addrlen);
    if ( status == 0 ) {
      if ( errno == EINPROGRESS || errno == EINTR ) {
        // TODO ? what about non-block connection
      }
      break;
    }

    close(fInput);
  }

  // not connection is established
  if ( rp == NULL ) {
    LOG(fatal) << "KoaEmsStreamSource::SetupInput : can't establish connection with input stream";
    exit(EXIT_FAILURE);
  }

  //
  freeaddrinfo(result);

  return true;
}

void KoaEmsStreamSource::Close()
{
  shutdown(fInput, SHUT_RDWR);

  KoaEmsSource::Close();
}

ClassImp(KoaEmsStreamSource)
