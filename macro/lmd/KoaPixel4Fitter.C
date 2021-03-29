int KoaPixel4Fitter(const int nEvents = 100000, const int startEvent = 0,
		TString storePath = "tmpOutput", const int verboseLevel = 0,
		const TString Method = "Minuit", const bool mergedHits = false,
		const double radlen = 0.31) {
	// ========================================================================
	TString RecoFile = storePath;
	if (mergedHits)
		RecoFile += "/Koala_recoMerged_";
	else
		RecoFile += "/Koala_reco_";
	RecoFile += startEvent;
	RecoFile += ".root";
	// TCand file
	TString CandFile = storePath + "/Koala_TCand_";
	CandFile += startEvent;
	CandFile += ".root";
	// Parameter file
	TString parFile = storePath + "/Koala_Params_";
	parFile += startEvent;
	parFile += ".root";

	// Output file
	TString outFile = storePath + "/Koala_Track_";
	outFile += startEvent;
	outFile += ".root";

	std::cout << "RecoFile: " << RecoFile.Data() << std::endl;
	std::cout << "TCandFile: " << CandFile.Data() << std::endl;
	std::cout << "TrackFile: " << outFile.Data() << std::endl;

	// -----   Timer   --------------------------------------------------------
	TStopwatch timer;
	timer.Start();
	// ------------------------------------------------------------------------

	// -----   Reconstruction run   -------------------------------------------
	FairRunAna *fRun = new FairRunAna();
	FairFileSource input_source(RecoFile);
	input_source.AddFriend(CandFile);
	fRun->SetSource(&input_source);
	fRun->SetOutputFile(outFile);
	// ------------------------------------------------------------------------

	// -----  Parameter database   --------------------------------------------
	FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
	FairParRootFileIo* parInput1 = new FairParRootFileIo(kTRUE);
	parInput1->open(parFile.Data(), "UPDATE");
	rtdb->setFirstInput(parInput1);

	// =========================================================================
	// ======                       Track Fitter                          ======
	// =========================================================================

	// -----  LMD collections names & importain parameters --------------------------------------------

		// // ----- Prepare GEANE --------------------------------------------
		// // this will load Geant3 and execute setup macros to initialize geometry:
		// FairGeane *Geane = new FairGeane();
		// fRun->AddTask(Geane);
		// // ------------------------------------------------------------------------
		// double scaleP=1;
		// double scaleM=1;
		// PndLmdKalmanTask* lmdkalmanfitter = new PndLmdKalmanTask(inHits,inTrks);
		// lmdkalmanfitter->SetVerbose(verboseLevel);
		// lmdkalmanfitter->SetScalePError(scaleP);
		// lmdkalmanfitter->SetScaleMError(scaleM);
		// lmdkalmanfitter->SetFilterFlag(false);
		// if(Method=="KalmanGeane"){

		//   lmdkalmanfitter->SetGeaneTrkRep();
		//   fRun->AddTask(lmdkalmanfitter);
		// }
		// else{
		//   if(Method=="KalmanRK"){
		// 	lmdkalmanfitter->SetRKTrkRep();
		// 	fRun->AddTask(lmdkalmanfitter);
		//   }
		//   else{
		// 	cout<<"Method "<<Method.Data()<<" doesn't exist!"<<endl;
		// 	break;
		//   }
		// }

	TString inTrks = "LMDTrackCand";
	TString inHits = "LMDHitsPixel";
	if (mergedHits) {
		inHits = "LMDHitsMerged";
	}
	if (Method == "Minuit") {
		PndLmdLinFitTask* lmdfit = new PndLmdLinFitTask(inTrks, inHits);
		//  TString tTCandBranchName, TString tRecoBranchName
		lmdfit->SetRadLen(1e-2 * radlen);
		lmdfit->SetVerbose(verboseLevel);
		//  lmdfit->SetFilterFlag(false);
		fRun->AddTask(lmdfit);
	} else {
		cout
				<< "I'm very sorry, but Kalman-Filter option for LMD is currently switched off :("
				<< endl;
	}
	rtdb->setOutput(parInput1);
	rtdb->print();
	// =====                 End of TrackFinding                           =====
	// =========================================================================

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
