#include "KoaEmsFileSource.h"
#include "TSystem.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/socket.h>

Bool_t KoaEmsFileSource::SetupInput(const char* filename)
{
  fFileName = gSystem->ExpandPathName(filename);
  fInput = open(fFileName.c_str(), O_RDONLY);
  if ( fInput < 0 ) {
    LOG(fatal) << "KoaEmsFileSource::SetInput : can't open file " << fFileName;
    exit(EXIT_FAILURE);
  }

  LOG(INFO) << "KoaEmsFileSource::SetInput : open file " << fFileName;
  return true;
}

void KoaEmsStreamSource::Close()
{
  shutdown(fInput, SHUT_RDWR);

  KoaEmsSource::Close();
}

ClassImp(KoaEmsFileSource, 1)
