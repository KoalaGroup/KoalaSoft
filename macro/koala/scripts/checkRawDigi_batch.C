#include "checkRawDigi.C"

void checkRawDigi_batch(const char* indir)
{
  TString filelist [] ={
    "analog_0.3" ,
    "analog_0.4" ,
    "analog_0.5" ,
    "analog_0.6" ,
    "analog_0.8" ,
    "analog_1.0" ,
    "analog_1.2" ,
    "analog_1.4" ,
    "analog_1.6" ,
    "analog_1.8" ,
    "analog_2.0" ,
    "analog_2.2" ,
    "analog_2.4" ,
    "analog_2.6" ,
    "analog_2.8"
  };

  TString infile;
  for (int i=0;i<15;i++) {
    infile = indir + filelist[i] + ".root";

    checkRecRawDigi(infile.Data(),
                    "koalasim"
                    );
  }

  return;
}
