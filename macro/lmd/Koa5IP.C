int Koa5IP(const int nEvents = 100000, const int startEvent = 0,
		TString storePath = "tmpOutput", const int verboseLevel = 1,
		const bool mergedHits = false, const bool SkipFilt = false,
		const bool XthFilt = true, const bool YphFilt = true, const bool BoxFilt =
				false, const double dX = 0, const double dY = 0) {
	// ========================================================================
  // MC file
	TString MCFile = storePath + "/Koala_MC_";
	MCFile += startEvent;
	MCFile += ".root";
	// TCand file
	TString CandFile = storePath + "/Koala_TCand_";
	CandFile += startEvent;
	CandFile += ".root";
	// Track file
	TString TrkFile = storePath + "/Koala_Track_";
	TrkFile += startEvent;
	TrkFile += ".root";

	// Parameter file
	TString parFile = storePath + "/Koala_Params_";
	parFile += startEvent;
	parFile += ".root";

	// Output file
	TString outFile = storePath + "/Koala_TrackEff_";
	outFile += startEvent;
	outFile += ".root";

	std::cout << "TCandFile: " << CandFile.Data() << std::endl;
	std::cout << "TrackInFile: " << TrkFile.Data() << std::endl;
	std::cout << "TrackOutFile: " << outFile.Data() << std::endl;

	// -----   Timer   --------------------------------------------------------
	TStopwatch timer;
	timer.Start();
	// ------------------------------------------------------------------------

	// -----   Reconstruction run   -------------------------------------------
	FairRunAna *fRun = new FairRunAna();
	FairFileSource input_source(TrkFile);
	input_source.AddFriend(CandFile);
	fRun->SetSource(&input_source);
	fRun->SetOutputFile(outFile);

	// ------------------------------------------------------------------------

	// -----  Parameter database   --------------------------------------------
	FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
	FairParRootFileIo* parInput1 = new FairParRootFileIo(kTRUE);
	parInput1->open(parFile.Data(), "UPDATE");
	rtdb->setFirstInput(parInput1);

	// ======================================
	// ======                       Track Filter                          ======
	// ======================================

	// -----  LMD collections names & importain parameters --------------------------------------------


	TString inHits = "LMDHitsPixel";
	if (mergedHits) {
		inHits = "LMDHitsMerged";
	}
        
	KoaBackProp* lmdfilt = new KoaBackProp();

	
	lmdfilt->SetVerbose(verboseLevel);
	fRun->AddTask(lmdfilt);

	rtdb->setOutput(parInput1);
	rtdb->print();
	// =====                 End of Track Filter                          =====
	// ======================================

	// -----   Intialise and run   --------------------------------------------
	fRun->Init();

	fRun->Run(0, nEvents);
	cout << "fRun->Run(0, " << nEvents << ") was done!" << endl;
	// ------------------------------------------------------------------------

	rtdb->saveOutput();
	rtdb->print();
	// -----   Finish   -------------------------------------------------------
	timer.Stop();
	Double_t rtime = timer.RealTime();
	Double_t ctime = timer.CpuTime();
	cout << endl << endl;
	cout << "Macro finished succesfully." << endl;
	cout << "Output file is " << outFile << endl;
	cout << "Parameter file is " << parFile << endl;
	cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << endl;
	cout << endl;
	// ------------------------------------------------------------------------

	// temporary fix to avoid double frees at the destruction of te program for pandaroot/fairroot with root6
	gGeoManager->GetListOfVolumes()->Delete();
	gGeoManager->GetListOfShapes()->Delete();
	delete gGeoManager;

	return 0;
}
