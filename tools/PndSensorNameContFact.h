#ifndef PNDSENSORNAMECONTFACT_H
#define PNDSENSORNAMECONTFACT_H

#include "FairContFact.h"

#include <vector>
#include <string>

class FairContainer;
//class FairParIo;

class PndSensorNameContFact : public FairContFact {
public:
  PndSensorNameContFact();
  ~PndSensorNameContFact();
  FairParSet* createContainer(FairContainer* c);
  TList* GetSensorParNames() {return fSensorParNames;};
private:
  void setAllContainers();
  TList* fSensorParNames; //!
  std::vector<std::string> fContainerNames;

  PndSensorNameContFact(const  PndSensorNameContFact& L);
  PndSensorNameContFact& operator= (const  PndSensorNameContFact&) {return *this;}

  ClassDef( PndSensorNameContFact,1); // Factory for all SensorName parameter containers
};

#endif  /* !MVDCONTFACT_H */
