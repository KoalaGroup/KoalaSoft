#include <iostream>
#include "PndLmdAlignPar.h"
#include "FairParamList.h"
#include "TMath.h"
#include "TString.h"
PndLmdAlignPar::PndLmdAlignPar(const char* name, const char* title, const char* context)
  : FairParGenericSet(name,title,context),fshift_x(0),fshift_y(0),fshift_z(0),frotate_x(0),frotate_y(0),frotate_z(0)
{
  clear();
}

void PndLmdAlignPar::putParams(FairParamList* list)
{
  if(!list) return;
  list->add("num_halfs", (Int_t)fhalfs);
  list->add("num_planes", (Int_t)fplanes);
  list->add("num_modules", (Int_t)fmodules);
  list->add("num_sensors", (Int_t)fsensors);
  list->add("num_sides", (Int_t)fsides);
  for (int ihalf = 0; ihalf < fhalfs; ihalf++){ // loop over detector halves
    for (int iplane = 0; iplane < fplanes; iplane++){ // loop over planes
      for (int imodule = 0; imodule < fmodules; imodule++){ // loop over modules
	int curpos = (ihalf*fplanes*fmodules)+(iplane*fmodules)+imodule;
	TString name_shx = "shift_x_";
	name_shx +=ihalf;
	name_shx +="_";
	name_shx +=iplane;
	name_shx +="_";
	name_shx +=imodule;
	list->add(name_shx, (Double_t)fshift_x[curpos]);
	TString name_shy = "shift_y_";
	name_shy +=ihalf;
	name_shy +="_";
	name_shy +=iplane;
	name_shy +="_";
	name_shy +=imodule;
	list->add(name_shy, (Double_t)fshift_y[curpos]);
	TString name_shz = "shift_z_";
	name_shz +=ihalf;
	name_shz +="_";
	name_shz +=iplane;
	name_shz +="_";
	name_shz +=imodule;
	list->add(name_shz, (Double_t)fshift_z[curpos]);
	TString name_rotx = "rotate_x_";
	name_rotx +=ihalf;
	name_rotx +="_";
	name_rotx +=iplane;
	name_rotx +="_";
	name_rotx +=imodule;
	list->add(name_rotx, (Double_t)frotate_x[curpos]);
	TString name_roty = "rotate_y_";
	name_roty +=ihalf;
	name_roty +="_";
	name_roty +=iplane;
	name_roty +="_";
	name_roty +=imodule;
	list->add(name_roty, (Double_t)frotate_y[curpos]);
	TString name_rotz = "rotate_z_";
	name_rotz +=ihalf;
	name_rotz +="_";
	name_rotz +=iplane;
	name_rotz +="_";
	name_rotz +=imodule;
	list->add(name_rotz, (Double_t)frotate_z[curpos]);
      }
    }
  }
}

Bool_t PndLmdAlignPar::getParams(FairParamList* list)
{
  if (!list) return kFALSE;
  if (!list->fill("num_halfs", &fhalfs)) return kFALSE; 
  if (!list->fill("num_planes", &fplanes)) return kFALSE;
  if (!list->fill("num_modules", &fmodules)) return kFALSE;
  if (!list->fill("num_sensors", &fsensors)) return kFALSE;
  if (!list->fill("num_sides", &fsides)) return kFALSE;

  fshift_x.resize(fhalfs*fplanes*fmodules,0);
  fshift_y.resize(fhalfs*fplanes*fmodules,0);
  fshift_z.resize(fhalfs*fplanes*fmodules,0);
  frotate_x.resize(fhalfs*fplanes*fmodules,0);
  frotate_y.resize(fhalfs*fplanes*fmodules,0);
  frotate_z.resize(fhalfs*fplanes*fmodules,0);

  for (int ihalf = 0; ihalf < fhalfs; ihalf++){ // loop over detector halves
    for (int iplane = 0; iplane < fplanes; iplane++){ // loop over planes
      for (int imodule = 0; imodule < fmodules; imodule++){ // loop over modules
	int curpos = (ihalf*fplanes*fmodules)+(iplane*fmodules)+imodule;
	TString name_shx = "shift_x_";
	name_shx +=ihalf;
	name_shx +="_";
	name_shx +=iplane;
	name_shx +="_";
	name_shx +=imodule;

	TString name_shy = "shift_y_";
	name_shy +=ihalf;
	name_shy +="_";
	name_shy +=iplane;
	name_shy +="_";
	name_shy +=imodule;

	TString name_shz = "shift_z_";
	name_shz +=ihalf;
	name_shz +="_";
	name_shz +=iplane;
	name_shz +="_";
	name_shz +=imodule;

	TString name_rotx = "rotate_x_";
	name_rotx +=ihalf;
	name_rotx +="_";
	name_rotx +=iplane;
	name_rotx +="_";
	name_rotx +=imodule;

	TString name_roty = "rotate_y_";
	name_roty +=ihalf;
	name_roty +="_";
	name_roty +=iplane;
	name_roty +="_";
	name_roty +=imodule;

	TString name_rotz = "rotate_z_";
	name_rotz +=ihalf;
	name_rotz +="_";
	name_rotz +=iplane;
	name_rotz +="_";
	name_rotz +=imodule;

	if (!list->fill(name_shx, &fshift_x[curpos])) return kFALSE;
	if (!list->fill(name_shy, &fshift_y[curpos])) return kFALSE;
	if (!list->fill(name_shz, &fshift_z[curpos])) return kFALSE;
	if (!list->fill(name_rotx, &frotate_x[curpos])) return kFALSE;
	if (!list->fill(name_roty, &frotate_y[curpos])) return kFALSE;
	if (!list->fill(name_rotz, &frotate_z[curpos])) return kFALSE;
      }
    }
  }
  return kTRUE;
}

ClassImp(PndLmdAlignPar);

void PndLmdAlignPar::Print()
{
  std::cout<<"LUMI Alignment Parameters for geometry with :"<<std::endl;
  std::cout<<"   Halfs         = "<<fhalfs<<std::endl;
  std::cout<<"   Planes        = "<<fplanes<<std::endl;
  std::cout<<"   Modules        = "<<fmodules<<std::endl;
  std::cout<<"   fshift_x.size() = "<< fshift_x.size()<<std::endl;
  std::cout<<"   fshift_y.size() = "<< fshift_z.size()<<std::endl;
  std::cout<<"   fshift_z.size() = "<< fshift_z.size()<<std::endl;
  std::cout<<"   frotate_x.size() = "<< frotate_x.size()<<std::endl;
  std::cout<<"   frotate_y.size() = "<< frotate_y.size()<<std::endl;
  std::cout<<"   frotate_z.size() = "<< frotate_z.size()<<std::endl;

  for(size_t ix=0; ix<fshift_x.size();ix++){
    if(fshift_x[ix]!=0) cout<<"fshift_x["<<ix<<"]="<<fshift_x[ix]<<endl;
    if(fshift_y[ix]!=0) cout<<"fshift_y["<<ix<<"]="<<fshift_y[ix]<<endl;
    if(fshift_z[ix]!=0) cout<<"fshift_z["<<ix<<"]="<<fshift_z[ix]<<endl;
    if(frotate_x[ix]!=0) cout<<"frotate_x["<<ix<<"]="<<frotate_x[ix]<<endl;
    if(frotate_y[ix]!=0) cout<<"frotate_y["<<ix<<"]="<<frotate_y[ix]<<endl;
    if(frotate_z[ix]!=0) cout<<"frotate_z["<<ix<<"]="<<frotate_z[ix]<<endl;
  }
  return;
}
