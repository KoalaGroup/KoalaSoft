#include "drawClusterEnergy.C"

void drawClusterEnergy_batch(const char* indir, const char* suffix = "_cluster.root")
{
  TString filelist [] ={
    "P_2.6_2019_Aug_30_22_22_25" ,
    "P_2.6_2019_Aug_31_00_06_22" ,
    "P_2.6_2019_Aug_31_03_10_45" ,
    "P_2.6_2019_Aug_31_07_44_18" ,
    "P_2.6_2019_Aug_31_10_46_07" ,
    "P_2.6_2019_Aug_31_12_59_13" ,
    "P_2.6_2019_Aug_31_13_44_43" ,
    "P_2.6_2019_Aug_31_15_53_04" ,
    "P_2.6_2019_Aug_31_18_19_13" ,
    "P_2.6_2019_Aug_31_20_02_15" ,
    "P_2.6_2019_Sep_01_00_00_15" ,
    "P_2.6_2019_Sep_01_09_37_57" ,
    "P_2.6_2019_Sep_01_11_44_27" ,
    "P_2.6_2019_Sep_01_15_55_52" ,
    "P_2.6_2019_Sep_01_18_19_04" ,
    "P_2.6_2019_Sep_01_21_57_45"
  };

  TString infile;
  TString outfile;
  TString fwdhit_file;
  for (int i=0;i<16;i++) {
    infile = indir + filelist[i] + suffix;
    outfile = infile; outfile.ReplaceAll(".root","_result.root");
    fwdhit_file = indir + filelist[i] + "_FwdHit.root";
    drawClusterEnergy(infile.Data(),
                      outfile.Data(),
                      "koalasim",
                      "KoaRecCluster",
                      false
                      );
  }

  return;
}
