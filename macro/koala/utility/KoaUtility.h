#ifndef KOAUTILITY_H
#define KOAUTILITY_H

namespace KoaUtility
{
  // get a directory from file. create it if not existing.
  TDirectory* getDirectory(TFile* f, const char* dir_name)
  {
    TDirectory* hdir;
    if(!(hdir=f->GetDirectory(dir_name)))
      hdir = f->mkdir(dir_name);

    return hdir;
  };
};

#endif
