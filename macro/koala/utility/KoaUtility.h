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
}

  // get an object from a directory
template<typename T>
T* getObject(TDirectory* dir, const char* name)
{
  T* object = nullptr;
  dir->GetObject(name, object);
  if ( !object ) {
    std::cerr << "Error: no object named " << name << " found in directory: " << dir->GetName() <<  std::endl;
  }

  return object;
}

};

#endif
