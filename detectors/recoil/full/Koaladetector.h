// -------------------------------------------------------------------------
// -----                         PndLmdDetector header file -----
// -----                  Created 6/04/06  by T. Stockmanns            -----
// -----                          Based on PndMvdDetector -----
// -------------------------------------------------------------------------

/**  PndLmdDetector.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 *@author M.Michel <michel@kph.uni-mainz.de>
 *@author h.xu <h.xu@fz-juelich.de>
 **
 ** Defines the active detector PndLmdDetector. Constructs the geometry and
 ** registers MCPoints.
 ** Notes on Jun 30,2010 by Huagen:
 ** To construct detector geometry from ASCII file the detector name shall be
 ** defined by users. The function of ConstructASCIIGeometry() should be
 *reloaded
 ** by user who wants to define the DetName freely.Without reloading this
 *function
 ** the detector name was defined by PndSdsGeo class anyway.
 **/

#ifndef KOALADETECTOR_H
#define KOALADETECTOR_H

#include "PndSdsDetector.h"

class Koaladetector : public PndSdsDetector {

 public:
  /** Default constructor **/
  Koaladetector();

  /** Standard constructor.
   *@param name    detetcor name
   *@param active  sensitivity flag
   **/
 Koaladetector(const char* name, Bool_t active);

  /** Destructor **/
  virtual ~Koaladetector();

  virtual void SetBranchNames(char* outBranchname, char* folderName);
  virtual void SetBranchNames();
  virtual void SetDefaultSensorNames();

  virtual void Initialize() { PndSdsDetector::Initialize(); };
  // virtual void ConstructASCIIGeometry();


  ClassDef(Koaladetector, 7);
};

#endif
