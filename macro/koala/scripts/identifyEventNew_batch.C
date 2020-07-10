#include "identifyEventNew.C"

void identifyEventNew_batch(const char* indir, const char* geoFile)
{
  TString filelist [] ={
    // "P_2.6_2019_Aug_30_22_22_25" ,
    // "P_2.6_2019_Aug_31_00_06_22" ,
    // "P_2.6_2019_Aug_31_03_10_45" ,
    "P_2.6_2019_Aug_31_07_44_18" ,
    // "P_2.6_2019_Aug_31_10_46_07" ,
    // "P_2.6_2019_Aug_31_12_59_13" ,
    // "P_2.6_2019_Aug_31_13_44_43" ,
    // "P_2.6_2019_Aug_31_15_53_04" ,
    // "P_2.6_2019_Aug_31_18_19_13" ,
    // "P_2.6_2019_Aug_31_20_02_15" ,
    // "P_2.6_2019_Sep_01_00_00_15" ,
    // "P_2.6_2019_Sep_01_09_37_57" ,
    // "P_2.6_2019_Sep_01_11_44_27" ,
    // "P_2.6_2019_Sep_01_15_55_52" ,
    // "P_2.6_2019_Sep_01_18_19_04" ,
    // "P_2.6_2019_Sep_01_21_57_45"
  };

  TString cluster_file;
  TString elist_file;
  for (int i=0;i<16;i++) {
    cluster_file = indir + filelist[i] + "_calib_7sigma.root";
    elist_file = indir + filelist[i] + "_EntryList.root";

    identifyEventNew(cluster_file.Data(),
                     2.6,
                     elist_file.Data(),
                     "fwd",
                     "elist_fwdhit",
                     33,
                     5,
                     0.3,
                     0.9,
                     3,
                     2,
                     geoFile,
                     true
                     );
  }

  return;
}
