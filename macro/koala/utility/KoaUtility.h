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

// get list of file name for batch processing
std::vector<std::string> getFileList(const char* fileconfig, const char* outdir, const char* suffix)
{
  std::ifstream flist;
  flist.open(gSystem->ExpandPathName(fileconfig));
  if (!flist.is_open()) {
    cout << "Can't open file : " << fileconfig << '\n';
  }

  vector<string> outlist;

  string line, file, dir;
  while (!flist.eof()) {
    getline(flist, line);
    stringstream ss(line);

    ss >> file >> dir;

    TString filename(file.data());
    filename.ReplaceAll(".cl", suffix);

    // outlist.emplace_back(gSystem->ConcatFileName(outdir, filename.Data()));
    outlist.emplace_back(gSystem->ConcatFileName(gSystem->ExpandPathName(outdir), filename.Data()));
  }
  flist.close();
  return outlist;
}

};

#endif
