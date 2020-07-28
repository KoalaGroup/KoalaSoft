/** CbmStsMapsHitInfo header file
 ** Class for additional information about PndSdsHit
 *@author Michael Deveaux <m.deveaux@gsi.de>
 ** Acknowledgements to M. Al-Turany, D. Bertini, G. Gaycken
 ** Version beta 0.1 (02.02.2005)
 ** Slight modifications by V. Friese to match coding conventions
 **/

#ifndef PNDSSDHITINFO_H
#define PNDSSDHITINFO_H 1


#include "TObject.h"


class PndSdsHitInfo: public TObject 
{

 public:

  /** Default constructor **/
  PndSdsHitInfo();


  /** Constructor with all parameters **/
  PndSdsHitInfo(Int_t fileNumber, Int_t eventNumber, Int_t trackID,
		Int_t pointID, Int_t nMerged, Bool_t isFake);


  /** Destructor **/
  virtual ~PndSdsHitInfo();  


  /** Accessors **/
  Int_t  GetFileNumber()  const { return fFileNumber;  };
  Int_t  GetEventNumber() const { return fEventNumber; };
  Int_t  GetTrackID()     const { return fTrackID;     }; 
  Int_t  GetPointID()     const { return fPointID;     };
  Int_t  GetNMerged()     const { return fNMerged;     };
  Bool_t IsFake()         const { return fIsFake;      };


  /** Modifiers **/
  void SetNMerged(Int_t nMerged)  { fNMerged = nMerged;  };


  /** Reset data members **/
  void Clear();


 private:

  /** Indicates the file to which the corresponding point belongs.
   ** -1    => no file (fake hit)
   **  0    => data file
   **  1    => pileup file
   ** else => reserved for future use
   **/
  Int_t fFileNumber;


  /** Event number of the corresponding MCPoint.  Important to 
   ** find it in background files due to the random access.
   ** -1 => no corresponding MCPoint (fake hit)
   **  0 => current event in data file
   **  n => event in pileup file
   **/
  Int_t fEventNumber;


  /** Index of the corresponding MCTrack in its TClonesArray.
   ** Also true for background files.
   ** -1 for fake hits
   **/
  Int_t fTrackID;


  /** Index of the corresponding MCPoint in its TClonesArray.
   ** Also true for background files.
   ** -1 for fake hits
   **/
  Int_t fPointID;


  /** Number of other hits this one is merged with
   ** -1 => Hit was created without checking for merging
   **  0 => Hit was not merged
   **  n => Hit was merged with n other hits
   **/
  Int_t fNMerged;


  /** Indicator for fake flag **/
  Bool_t fIsFake;



  ClassDef(PndSdsHitInfo,1);

};


#endif
