{
	std::cout<<"processing rootlogon.C...\n";
	std::string koalasoft_dir(getenv("VMCWORKDIR"));
	gROOT->ProcessLine((std::string(".include ")+koalasoft_dir).c_str());
	gSystem->Load("libLmd");
}
