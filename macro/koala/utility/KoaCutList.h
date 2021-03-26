#ifndef KOACUTLIST_H
#define KOACUTLIST_H

#include "KoaUtility.h"

namespace KoaUtility
{

// Map of popular cut name to cut entry list name saved in root file
std::map<std::string, std::string> koalaCuts = {
  {"fwdhit", "fwdhit_elist"},
  {"tof window", "tofwindow_elist"}
};

// Get the list name of a cut condition
std::string getCutListName(const char* name)
{
  auto search = koalaCuts.find(name);
  if(search != koalaCuts.end())
    return search->second;

  return std::string(name);
}

// write a map of elists to a directory
template<typename T>
void writeElists(TDirectory* eDir, T &eLists, const char* option = "Overwrite")
{
  for ( const auto& list : eLists ) {
    eDir->WriteTObject(&list.second, "", option);
  }
}
};

#endif
