//////////////////////////////////////////////////////////////////////////
//                                                                      //
// VAbsMicroCandidate	                                                //
//                                                                      //
// Definition of an abstract interface to a micro candidate.	        //
//                                                                      //
// Author: Sascha Berger and Marcel Kunze, RUB, March 1999		//
// Copyright (C) 1999-2001, Ruhr-University Bochum.			//
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TVector3.h"
#include "PndRecoCandidate.h"

ClassImp(PndRecoCandidate);

TBuffer &operator>>(TBuffer &buf, PndRecoCandidate *&obj)
{
   obj = (PndRecoCandidate *) buf.ReadObject(PndRecoCandidate::Class());
   return buf;
}

#include <iostream>
using namespace std;

void PndRecoCandidate::PrintOn(std::ostream &o) const 
{
    o << " ======= Fit Params ======= " << endl; 
    TVector3 r = GetPosition();
    TVector3 p = GetMomentum();
	o << " Position              : (" << r.X() << ";" << r.Y() << ";" << r.Z() << ")" << endl;
	o << " Momentum              : (" << p.X() << ";" << p.Y() << ";" << p.Z() << ")" << endl;
	o << " Momentum.mag          : " << p.Mag() << endl;
	o << " Charge                : " << GetCharge() << endl;
	o << " Energy                : " << GetEnergy() << endl;
    
    if (GetCharge() != 0) {
	o << " ======= Track Quality ======= " 
	  << "\n Fit quality         : Ndof " << GetDegreesOfFreedom()<< " chi2 " << GetChiSquared() 
	  << endl;//"\n track length        : " << GetTrackLength()<<endl; 
    }
          
} 

std::ostream&  operator << (std::ostream& o, const PndRecoCandidate& a) { a.PrintOn(o); return o; }
