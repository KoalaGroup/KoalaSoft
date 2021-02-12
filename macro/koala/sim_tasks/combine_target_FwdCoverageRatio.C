#include "combineFwdCoverageRatio_Imp.C"

void combine_target_FwdCoverageRatio(const char* component_1,
                                     const char* component_2,
                                     const char* outfilename, 
                                     double fwd_offset = 0,
                                     double frac1 = 0.75,
                                     double frac2 = 1.0)
{
  map<string, double> list_file = {{component_1, frac1}, {component_2, frac2}};
  combineFwdCoverageRatio_Imp(list_file, outfilename, Form("fwd_offset_%.1fmm",fwd_offset));
}
