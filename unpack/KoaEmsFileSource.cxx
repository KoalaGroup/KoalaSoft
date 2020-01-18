#include "KoaEmsFileSource.h"
#include "TSystem.h"

Bool_t KoaEmsFileSource::SetupInput(const char* filename)
{
  fFileName = gSystem->ExpandPathName(filename);
  fInput = open(fFileName.c_str(), O_RDONLY);
  if ( fInput < 0 ) {
    LOG(ERROR) << "KoaEmsFileSource::SetInput : can't open file " << fFileName;
    return false;
  }

  LOG(INFO) << "KoaEmsFileSource::SetInput : open file " << fFileName;
  return true;
}

ClassImp(KoaEmsFileSource, 1)
