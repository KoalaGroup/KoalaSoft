int KoaPixel1Digi(const int nEvents = 10, const int startEvent = 0,
		TString storePath = "tmpOutput", const int verboseLevel = 0,
		const int pitch = 1) {
	// -----   Timer   --------------------------------------------------------
	TStopwatch timer;
	timer.Start();

	// Input file (MC events)
	TString inFile = storePath + "/Koala_MC_";
	inFile += startEvent;
	inFile += ".root";
	// Parameter file
	TString parFile = storePath + "/Koala_Params_";
	parFile += startEvent;
	parFile += ".root";

	// Parameter file
	TString digiparFile = "../../parameters/koala.digi.par";
        

	// Output file
	TString outFile = storePath + "/Koala_digi_";
	outFile += startEvent;
	outFile += ".root";
	std::cout << "DigiFileName: " << outFile.Data() << std::endl;

	// -----   Reconstruction run   -------------------------------------------
	FairRunAna *fRun = new FairRunAna();

	FairFileSource *input_source = new FairFileSource(inFile);
	// input_source->SetEventMeanTime(50);//[ns] 50= interaction rate 20 MHz;
	input_source->SetEventMeanTime(80);  //[ns] 80= interaction rate 12.5 MHz;
	// example: cross-section(DPM el+inlel, 1.5 GeV/c)= 125 mb, L=10^32 -> interaction rate 12.5 MHz
	// input_source->SetEventMeanTime(400);//[ns] 400= interaction rate 5 MHz; //15 GeV
	fRun->SetSource(input_source);
	fRun->SetOutputFile(outFile);

	// -----  Parameter database   --------------------------------------------
	FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
	FairParRootFileIo* parInput1 = new FairParRootFileIo(kTRUE);
	parInput1->open(parFile.Data(), "UPDATE");
	rtdb->setFirstInput(parInput1);
	FairParAsciiFileIo* parInput2 = new FairParAsciiFileIo();
	parInput2->open(digiparFile.Data(), "in");
	rtdb->setSecondInput(parInput2);

		KoaHybridHitProducer* lmdStripProd = new KoaHybridHitProducer();
	//  PndLmdStripHitProducerDif* ssdStripProd = new PndLmdStripHitProducerDif(); //TEST
	lmdStripProd->SetVerbose(verboseLevel);
	fRun->AddTask(lmdStripProd);

	PndLmdHybridHitProducer* lumiStripProd = new PndLmdHybridHitProducer();
	//  PndLmdStripHitProducerDif* ssdStripProd = new PndLmdStripHitProducerDif(); //TEST
	lumiStripProd->SetVerbose(verboseLevel);
	fRun->AddTask(lumiStripProd);
	

        

	rtdb->setOutput(parInput1);
	rtdb->print();
	// =====                 End of HitProducers                           =====
	// =========================================================================
	PndSdsGeoPar* geoPar = (PndSdsGeoPar*) (rtdb->getContainer("PndSdsGeoPar"));

	// -----   Intialise and run   --------------------------------------------
	fRun->Init();
	fRun->Run(0, nEvents);
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
	cout << "Real time " << rtime << " s, CPU time " << ctime << " s\a\a" << endl;
	cout << endl;

	// temporary fix to avoid double frees at the destruction of te program for pandaroot/fairroot with root6
	gGeoManager->GetListOfVolumes()->Delete();
	gGeoManager->GetListOfShapes()->Delete();
	delete gGeoManager;

	return 0;
}
