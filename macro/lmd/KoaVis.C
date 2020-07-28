int KoaVis(const int nEvents = 10, const int startEvent = 0,
		TString storePath = "tmpOutput", const int verboseLevel = 0, bool misalign =
				false) {
	// ========================================================================
	TString CompFile = storePath + "/Koala_comp_"; //"/Lumi_digi_noise_";//"/Lumi_digi_";
	CompFile += startEvent;
	CompFile += ".root";

	TString RecoFile = storePath + "/Koala_reco_"; //"/Lumi_digi_noise_";//"/Lumi_digi_";
	RecoFile += startEvent;
	RecoFile += ".root";



	// Parameter file
	TString parFile = storePath + "/Koala_Params_";
	parFile += startEvent;
	parFile += ".root";



	//std::cout << "MCFile  : " << MCFile.Data()<< std::endl;
	//std::cout << "DigiFile: " << DigiFile.Data() << std::endl;
	//std::cout << "RecoFile: " << outFile.Data() << std::endl;

	// -----   Timer   --------------------------------------------------------
	TStopwatch timer;
	timer.Start();
	// ------------------------------------------------------------------------

	// -----   Reconstruction run   -------------------------------------------
	FairRunAna *fRun = new FairRunAna();
	FairFileSource input_source(CompFile);
	input_source.AddFriend(RecoFile);
	fRun->SetSource(&input_source);
	// ------------------------------------------------------------------------

	// -----  Parameter database   --------------------------------------------
	FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
	FairParRootFileIo* parInput1 = new FairParRootFileIo(kTRUE);
	parInput1->open(parFile.Data(), "UPDATE");
//   FairParAsciiFileIo* parInput1 = new FairParAsciiFileIo();
//   parInput1->open(parFile.Data(),"in");
	rtdb->setFirstInput(parInput1);

	// alignment parameter file
	//  TString alignparFile = "lumi.align.par";//perfect! OLD
	//  TString alignparFile = "lumi.misalign.par";//misalignment!  OLD
	//  TString alignparFile = "lumi.align_pixel_ideal.par";//perfect
	/* TString alignparFile;
	 if(misalign){
	 alignparFile = storePath+"/lumi.misalign_pixel.par";//misalign
	 }
	 else{
	 alignparFile = "LMD_alignment/lumi.align_pixel_ideal.par";//perfect
	 }

	 FairParAsciiFileIo* parInput2 = new FairParAsciiFileIo();
	 parInput2->open(alignparFile.Data(),"in");
	 rtdb->setSecondInput(parInput2);*/

	/*Bool_t kParameterMerged=kTRUE;
	 FairParRootFileIo* output=new FairParRootFileIo(kParameterMerged);
	 output->open(parOutFile);
	 rtdb->setOutput(output);
	 */
// fRun->LoadGeometry();
	// ------------------------------------------------------------------------
	// =========================================================================
	// ======                       Hit Producers                         ======
	// =========================================================================
	// -----    LMD hit producer   --------------------------------------------
	KoaPloti* koaPanda = new KoaPloti();
	koaPanda->SetVerbose(verboseLevel);
	fRun->AddTask(koaPanda);

        
	rtdb->print();
	// =====                 End of HitProducers                           =====
	// =========================================================================

	// -----   Intialise and run   --------------------------------------------
	fRun->Init();

	fRun->Run(0, nEvents);
	// ------------------------------------------------------------------------

	
	rtdb->print();
	// -----   Finish   -------------------------------------------------------
	timer.Stop();
	Double_t rtime = timer.RealTime();
	Double_t ctime = timer.CpuTime();
	cout << endl << endl;
	cout << "Macro finished succesfully." << endl;

	cout << "Parameter file is " << parFile << endl;
	cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << endl;
	cout << endl;
	// ------------------------------------------------------------------------

	// temporary fix to avoid double frees at the destruction of te program for pandaroot/fairroot with root6


	return 0;
}
