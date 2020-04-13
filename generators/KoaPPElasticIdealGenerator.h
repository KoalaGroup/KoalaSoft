/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                    KoaPPElasticIdealGenerator header file                   -----
// -----          Created 16/10/2019  by Y.Zhou
// -------------------------------------------------------------------------


/** KoaPPElasticIdealGenerator.h
 *@author Y.Zhou <y.zhou@fz-juelich.de>
 *
The KoaPPElasticIdealGenerator is the an generator for proton-proton elastic scattering.
It is based on the analytic calculation of elastic kinematics, with a specified recoil angle range.
The distribution within the range is flat, i.e. uniform.
**/


#ifndef KOA_PPELASTICIDEALGENERATOR_H
#define KOA_PPELASTICIDEALGENERATOR_H

#include "FairGenerator.h"


class FairPrimaryGenerator;

class KoaPPElasticIdealGenerator : public FairGenerator
{

  public:

    /** Default constructor. **/
    KoaPPElasticIdealGenerator();


    /** Constructor with name and title **/
    KoaPPElasticIdealGenerator(Double_t mom, Bool_t isGeantino = kFALSE);


    /** Destructor. **/
    virtual ~KoaPPElasticIdealGenerator();

    /** Modifiers. **/
    void SetMomentum(Double_t mom) // in GeV
    { fP = mom; }
    void SetGeantino() // generate geantino instead of proton
    { fIsGeantino = kTRUE; }
    void SetAlphaRange(Double_t min, Double_t max) // in degree
    { fAlphaMin = min; fAlphaMax = max; }
    void SetPhiRange(Double_t min, Double_t max) // in degree
    { fPhiMin = min; fPhiMax = max; }

    /** Abstract method ReadEvent must be implemented by any derived class.
        It has to handle the generation of input tracks (reading from input
        file) and the handing of the tracks to the FairPrimaryGenerator. I
        t is called from FairMCApplication.
        *@param pStack The stack
        *@return kTRUE if successful, kFALSE if not
    **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);


    /**Initialize the generator if needed */
    virtual Bool_t Init();

    /** Clone this object (used in MT mode only) */
    virtual KoaPPElasticIdealGenerator* CloneGenerator() const;

  protected:
    /** Copy constructor */
    KoaPPElasticIdealGenerator(const KoaPPElasticIdealGenerator&);
    /** Assignment operator */
    KoaPPElasticIdealGenerator& operator= (const KoaPPElasticIdealGenerator&);

 private:
    void Calculate(Double_t alpha, Double_t phi);

 private:
    Bool_t   fIsGeantino; // flag, use proton or geantino

    Double_t fMass; // rest mass of proton in GeV, from PDG2018
    Double_t fP; // beam proton momentum
    Double_t fAlphaMin, fAlphaMax; // angle alpha of recoil proton (with respect to x-axis)
    Double_t fPhiMin, fPhiMax; // angle phi of recoil proton
    Double_t fKappa;

    Double_t fRecoilPx, fRecoilPy, fRecoilPz;
    Double_t fScatPx, fScatPy, fScatPz;
    ClassDef(KoaPPElasticIdealGenerator,1);
};

#endif


