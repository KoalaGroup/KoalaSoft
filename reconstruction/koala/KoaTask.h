#ifndef KOATASK_H
#define KOATASK_H

class KoaTask : public FairTask
{
public:
public:
  /** Initiliazation of task at the beginning of a run **/
  virtual InitStatus Init();
  void SetInputDigiName(const char* name) {
    fInputName = name;
  }
  void SetOutputDigiName(const char* name) {
    fOutputName = name;
  }
  void SaveOutputDigi(bool flag = true) {
    fSaveOutput = flag;
  }
  
private:
  // Input digit branch name
  std::string fInputName;
  // Output digit branch name
  std::string fOutputName;
  // Flag indicate save output branch to file or in memory
  bool fSaveOutput;
};

#endif
