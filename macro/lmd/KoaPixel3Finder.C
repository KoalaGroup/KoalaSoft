///  Method="Follow" - Track-following method, Method="CA" - Cellular Automaton
///  missPl=true - use "missing plane" algorithm
int KoaPixel3Finder(const int nEvents = 1000, const int startEvent = 0,
		TString storePath = "tmpOutput", const int verboseLevel = 0,
		TString Method = "CA", const bool missPl = true, const bool mergedHits =
		      false, const bool trkcuts = true, double mom = 3.2) {
	// ========================================================================
	TString RecoMergedFile = storePath + "/Koala_recoMerged_";
	RecoMergedFile += startEvent;
	RecoMergedFile += ".root";
	TString RecoFile = storePath + "/Koala_reco_";
	RecoFile += startEvent;
	RecoFile += ".root";
	// Parameter file
	TString parFile = storePath + "/Koala_Params_";
	parFile += startEvent;
	parFile += ".root";

	// Output file
	TString outFile = storePath + "/Koala_TCand_";
	outFile += startEvent;
	outFile += ".root";

	std::cout << "RecoFile: " << RecoFile.Data() << std::endl;
	std::cout << "TCandFile: " << outFile.Data() << std::endl;

	// -----   Timer   --------------------------------------------------------
	TStopwatch timer;
	timer.Start();
	// ------------------------------------------------------------------------

	// -----   Reconstruction run   -------------------------------------------
	FairRunAna *fRun = new FairRunAna();
	FairFileSource input_source(RecoFile);
	if (mergedHits)
		input_source.AddFriend(RecoMergedFile);
	fRun->SetSource(&input_source);
	fRun->SetOutputFile(outFile);

	// ------------------------------------------------------------------------

	// -----  Parameter database   --------------------------------------------
	FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
	FairParRootFileIo* parInput1 = new FairParRootFileIo(kTRUE);
	parInput1->open(parFile.Data(), "UPDATE");
	rtdb->setFirstInput(parInput1);

	// =========================================================================
	// ======                       Track Finder                          ======
	// =========================================================================

	// -----  LMD collections names & importain parameters --------------------------------------------

	TString inHits = "LMDHitsPixel";
	int nsensors = 40;
	int nplanes = 4;
	double accurF = 0.01;  //parameter for trk-finder corridor
	double accurCA;  //parameter for CA neigboring search (breaking angle)
	// //set accurCA for diff Pbeam cases ---------------------------------------------
	double accCAv[7] = { 5e-6, 4.5e-6, 2e-6, 1e-6, 9e-7, 8e-7, 8e-7 }; //1.5, 2.0, 3.2, 4.06, 8.9, 11.91, 15
	double delta_mom(0.1);
	if (1.5 - delta_mom < mom && mom < 1.5 + delta_mom)
	  accurCA = accCAv[0];
	else if (2.0 - delta_mom < mom && mom < 2.0 + delta_mom)
	  accurCA = accCAv[1];
	else if (3.2 - delta_mom < mom && mom < 3.2 + delta_mom)
	  accurCA = accCAv[2];
	else if (4.06 - delta_mom < mom && mom < 4.06 + delta_mom)
		accurCA = accCAv[3];
	else if (8.9 - delta_mom < mom && mom < 8.9 + delta_mom)
		accurCA = accCAv[4];
	else if (11.91 - delta_mom < mom && mom < 11.91 + delta_mom)
		accurCA = accCAv[5];
	else if (15.0 - delta_mom < mom && mom < 15.0 + delta_mom)
		accurCA = accCAv[6];
	else {
		accurCA = 1e-5;
		cout
				<< "! CA algorithm needs to know beam momentum for choose of proper cut !";
	}
	// //------------------------------------------------------------------------------------------

// //------------------------------------------------------------------------------------------
	if (trkcuts != true)
		accurCA = 1e-3; //misalignment sensors case (TODO: study it in multiple trks case)
	if (mergedHits) {
		inHits = "LMDHitsMerged";
		nplanes = 4;
	}

	if (Method == "Follow") {
		PndLmdTrackFinderTask* lmdfinder = new PndLmdTrackFinderTask(missPl, inHits,
				nsensors);
		lmdfinder->SetInaccuracy(accurF);
		lmdfinder->SetSensPixelFlag(true);

		lmdfinder->SetVerbose(verboseLevel);
		fRun->AddTask(lmdfinder);
	} else {
		if (Method == "CA") {
			cout << "CA is going to use cut=" << accurCA << endl;
			PndLmdTrackFinderCATask* lmdfinder = new PndLmdTrackFinderCATask(missPl,
					accurCA, nsensors, nplanes, inHits); //for merged hits
			lmdfinder->SetSensPixelFlag(true);
			lmdfinder->SetTrkCandCutsFlag(trkcuts); //value=false for misaligned sensors only
			//  lmdfinder->SetTrkCandCutsFlag(true);

			lmdfinder->SetVerbose(verboseLevel);
			fRun->AddTask(lmdfinder);
		} else {
			cout << "Method " << Method.Data() << " doesn't exist!" << endl;
		}
	}

	rtdb->setOutput(parInput1);
	rtdb->print();
	// =====                 End of TrackFinding                           =====
	// =========================================================================

	// -----   Intialise and run   --------------------------------------------
	fRun->Init();

	fRun->Run(0, nEvents);
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
