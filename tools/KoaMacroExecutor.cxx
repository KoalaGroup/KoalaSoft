#include "TROOT.h"
#include "TSystem.h"
#include "TString.h"
#include "FairLogger.h"

void Usage(const char *cmd)
{
	printf("Usage: %s macro_script arg1 arg2 ...\n", cmd);

	exit(-1);
}

/*
 * An executable used to load macro and pass the command line arguments to the macro.
 * The loaded macro script need to have the same name as the macro to be executed.
 */
int main(int argc, char *argv[])
{
  if (argc < 2) {
    LOG(FATAL) << "Provide at least the macro script as arguments";
    Usage(argv[0]);
  }

  // Add include path
  TString configm(gSystem->Getenv("VMCWORKDIR"));
  gROOT->ProcessLine(Form(".include %s/macro/koala/utility", configm.Data()));
  gROOT->ProcessLine(Form(".include %s/macro/koala", configm.Data()));
  // gSystem->AddIncludePath(Form(".include %s/macro/koala/utility", configm.Data()));
  // gSystem->AddIncludePath(Form(".include %s/macro/koala", configm.Data()));

  // get macro file path
  TString macro(argv[1]);
  gSystem->ExpandPathName(macro);

  // add arguments string to macro, like:
  // root[0] .x func.C++(arg1,arg2);
  macro.Prepend(".x ");
  macro.Append("(");
  for (auto index = 2; index < argc; ++index) {
    TString arg(argv[index]);
    if( arg.IsFloat() ) {
      macro.Append(arg);
    }
    else {
      macro.Append("\"");
      macro.Append(arg);
      macro.Append("\"");
    }

    if(index == (argc-1))
      break;
    macro.Append(",");
  }
  macro.Append(");");

  // load and execute the macro
  // LOG(INFO) << macro.Data();
  gROOT->ProcessLine(Form("%s",macro.Data()));

  return 0;
}
