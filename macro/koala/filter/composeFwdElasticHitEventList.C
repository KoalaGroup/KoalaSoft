#include "KoaUtility.h"
using namespace KoaUtility;

void composeFwdElasticHitEventList(const char* filename)
{
  auto fin = new TFile(filename, "update");
  auto eDir = getDirectory(fin, "fwd");
  auto eList = getObject<TEventList>(eDir, "elist_fwdhit");
  auto amp_main = getObject<TEventList>(eDir, "elist_FwdAmpMain");
  auto elastic_list = (*eList) * (*amp_main);
  elastic_list.SetName("elist_fwdhit_elastic");
  elastic_list.SetTitle("List of events with elastic forward hit");

  std::cout << "Fwd Total Hits: " << eList->GetN() << std::endl;
  std::cout << "Fwd Amp Hits: " << amp_main->GetN() << std::endl;
  std::cout << "Fwd Elastic Hits: " << elastic_list.GetN() << std::endl;

  eDir->WriteTObject(&elastic_list, "", "Overwrite");

  delete fin;
}
