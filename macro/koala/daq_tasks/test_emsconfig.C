/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void test_emsconfig()
{

  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;

  // -----   Decoding run   -------------------------------------------
  TString dir = getenv("VMCWORKDIR");

  TString param_dir = dir+"/parameters/";
  TString config_module_table = param_dir + "mxdc32.config";
  TString config_amplitude_map = param_dir + "mxdc32_amplitude_map.config";
  TString config_time_map = param_dir + "mxdc32_time_map.config";
  TString config_scalor_map = param_dir + "scalor_map.config";

  // KoaRunOnline *fRun = new KoaRunOnline(); // without this line, the macro could not run. library loading error

  KoaEmsRawEvent ems_event;

  // Setup ems configuration, it's owned by user himself
  KoaEmsConfig* emsConfig = new KoaEmsConfig();
  emsConfig->SetEmsConfigFile(config_module_table.Data());
  emsConfig->PrintModuleTable();

  emsConfig->SetAmplitudeChannelMap(config_amplitude_map.Data());
  emsConfig->PrintAmplitudeChannelMap();

  emsConfig->SetTimeChannelMap(config_time_map);
  emsConfig->PrintTimeChannelMap();

  emsConfig->SetScalorChannelMap(config_scalor_map);
  emsConfig->PrintScalorChannelMap();

  // KoaEmsConfig is owned and managed by user himself
  delete emsConfig;

  cout << endl << endl;

  // Extract the maximal used memory an add is as Dart measurement
  // This line is filtered by CTest and the value send to CDash
  FairSystemInfo sysInfo;
  Float_t maxMemory=sysInfo.GetMaxMemory();
  cout << "<DartMeasurement name=\"MaxMemory\" type=\"numeric/double\">";
  cout << maxMemory;
  cout << "</DartMeasurement>" << endl;

  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();

  Float_t cpuUsage=ctime/rtime;
  cout << "<DartMeasurement name=\"CpuLoad\" type=\"numeric/double\">";
  cout << cpuUsage;
  cout << "</DartMeasurement>" << endl;

  cout << endl << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime
       << "s" << endl << endl;
  cout << "Macro finished successfully." << endl;

  // ------------------------------------------------------------------------
}
