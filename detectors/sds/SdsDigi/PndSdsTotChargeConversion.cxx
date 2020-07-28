#include "PndSdsTotChargeConversion.h"
#include "TMath.h"

///Default constructor
PndSdsTotChargeConversion::PndSdsTotChargeConversion(Int_t VerboseLevel) : PndSdsChargeConversion(kToT),
fthreshold(0.),
Qt(0.),
t1e(0.),
t2e(0.),
ftimestep(0.),
fstarttime(0.),
fstoptime(0.),
ftimeoffset(0.),
ftimewalk(0.),
fVerboseLevel(0),
fRand()
{
  SetParameter("ftr", 100.); //todo take data from Database
  SetParameter("fa", 60.);
  SetParameter("fth", 3000.);
  SetParameter("fclk", 156.);
  ftimestep = 1. / GetParameter("fclk") * 1000.;
  fVerboseLevel = VerboseLevel;
  StartExecute();
  Warning("constructor","default constructor used");
  if (fVerboseLevel>0){
    std::cout<<"Tot parameter "<<std::endl;
    std::cout<<"  charge time: "<<GetParameter("ftr")<<" ns"<<std::endl;
    std::cout<<"  const. current: "<<GetParameter("fa")<<" e/ns"<<std::endl;
    std::cout<<"  threshold: "<<GetParameter("fth")<<" e"<<std::endl;
    std::cout<<"  clock frequency: "<<GetParameter("fclk")<<" MHz"<<std::endl;
  }
};

///Main constructor
PndSdsTotChargeConversion::PndSdsTotChargeConversion(Double_t tr, Double_t a, Double_t threshold, Double_t clockfrequency, Int_t VerboseLevel) : PndSdsChargeConversion(kToT),
fthreshold(0.),
Qt(0.),
t1e(0.),
t2e(0.),
ftimestep(0.),
fstarttime(0.),
fstoptime(0.),
ftimeoffset(0.),
ftimewalk(0.),
fVerboseLevel(0),
fRand()
{
  SetParameter("ftr", tr);				//charge time [ns]
  SetParameter("fa", a);					//const. curren [e/ns]
  SetParameter("fth", threshold);
  SetParameter("fclk", clockfrequency); 	//the frequency the readout chip works with
  ftimestep = 1. / clockfrequency * 1000.;
  fVerboseLevel = VerboseLevel;
  if (fVerboseLevel>0){
    std::cout<<"Tot parameter "<<std::endl;
    std::cout<<"  charge time: "<<GetParameter("ftr")<<" ns"<<std::endl;
    std::cout<<"  const. current: "<<GetParameter("fa")<<" e/ns"<<std::endl;
    std::cout<<"  threshold: "<<GetParameter("fth")<<" e"<<std::endl;
    std::cout<<"  clock frequency: "<<GetParameter("fclk")<<" MHz"<<std::endl;
  }
  StartExecute();
};

Double_t PndSdsTotChargeConversion::ChargeToDigiValue(Double_t charge){ //returns the TOT in ns
	if (GetParameter("fa") <= 0){
		if (fVerboseLevel>0) 
      Error("ConvertChargeToDigiValue(Double_t charge)","const. current is less or equal zero -> now set to 60 e/ns");
		SetParameter("fa",60.);
	}
  
	Double_t Q = charge;
	Qt = GetParameter("fth");
  //Error handling: if there is a parameter leading to a division by zero Q=Qt=1 is set to prevent this
  
	if (Qt < 0){
		if (fVerboseLevel>0)
      Error("ConvertChargeToDigiValue(Double_t charge)","threshold is less than zero -> now set to 0 eV");
		Qt = 0.;
	}
  
	if ((Q <= Qt) or (Q <= 0)){
		if (fVerboseLevel>0)
      Warning("ConvertChargeToDigiValue(Double_t charge)","charge (%g) is equal or less than threshold (%g) -> zero TOT",Q,Qt);
		Q = 1.;
		Qt = 1.;
	}
  
	t1e = (GetParameter("ftr")*Qt/Q+ftimeoffset);							//exact time when signal is over threshold
	t2e = (Q-Qt)/GetParameter("fa")+ftimeoffset+GetParameter("ftr");		//exact time when signal is again below threshold
  
	//return (t2e-t1e);						//turn off clock
	return GetTotWC();
}

Double_t PndSdsTotChargeConversion::GetRelativeError(Double_t Charge)
{
  // formula from D.Pohl/FZJ his sources?
  // dQ_rec     a             /               (Q_t - a*t_c)/2  +  (Q - Q_t)(t_c/Q - 1/a)*a/2              \.
  // ------  =  - * dt_max * | 1 + ----------------------------------------------------------------------  |
  //  Q_rec     2             \    sqrt{ [ (Q_t - a*t_c)/2 + (Q - Q_t)(t_c/Q - 1/a)*a/2 ]^2 + a*Q_t*t_c } /
  //
  //            a     1      /           2Qt - Qt*Qc/Q - Q                \.
  //         =  - * ----- * | 1 + ---------------------------------------  |
  //            2   f_clk    \    sqrt{ [2Qt - Qt*Qc/Q - Q]^2 + 4*Qc*Qt } /
  //
  
	Double_t Q = Charge;
	Qt = GetParameter("fth"); // threshold
  Double_t a = GetParameter("fa"); // const current
  Double_t tc = GetParameter("ftr");// time to load capacitor fully
  Double_t Qc = a*tc; // storable capacitor charge
  Double_t temp = 2.*Qt - Qt*Qc/Q - Q;
  temp = temp/(sqrt(temp*temp + 4*Qc*Qt));
  temp = 0.5*a*(1+temp)/GetParameter("fclk");
  return temp;
}

//Int_t PndSdsTotChargeConversion::GetTimeStamp(Double_t time)
//{
//  Int_t temp = (Int_t)(time / ftimestep); // [clockcycles]
//  time = temp*ftimestep + ftimestep; //[ns] to the following clock tick
//  return (Int_t)TMath::Ceil(time); // [ns] with 1 ns number precision, casting cuts trailing digits, like floor()
//}

Double_t PndSdsTotChargeConversion::GetTimeStamp(Double_t time, Double_t Charge,Double_t MCEventTime)
{
	ftimewalk=GetTimeWalk(Charge);
  
	Double_t totaltime = ftimewalk;
	Double_t eventtime =  MCEventTime;
	Double_t flighttime = time;
  
	totaltime += flighttime; // [ns]
	totaltime += eventtime;  // [ns]
  
	Double_t digitizedtime = DigitizeTime(totaltime);
  
  if (fVerboseLevel>2){
    std::cout<<"  +++threshold: "<< Qt <<" "<<std::endl;
    std::cout<<"  charge: "<< Charge <<" "<<std::endl;
    std::cout<<"  time since event: "<< time <<" "<<std::endl;
    std::cout<<"  event time: "<< MCEventTime << std::endl;
    std::cout<<"  timewalk: "<< ftimewalk <<std::endl;
    std::cout<<"  total time: "<< totaltime <<std::endl;
    std::cout<<"  time step: "<< ftimestep<<std::endl;
    std::cout<<"  digitized total time:"<< digitizedtime << "+++"<<std::endl;
  }
  return digitizedtime ; //digitalisiert
  //	 return totaltime; // nicht digitalisiert
}


Double_t PndSdsTotChargeConversion::DigitizeTime(Double_t time)
{
	Int_t temp = (Int_t)((time) / ftimestep);
	time =  temp *ftimestep + ftimestep;
  
  if (fVerboseLevel>2) std::cout << "temp " << temp << " time " << time << std::endl;
  
	return time;
}

Double_t PndSdsTotChargeConversion::GetTimeWalk(Double_t Charge) { // [ns]
	if (GetParameter("fa") <= 0){
    if (fVerboseLevel>0)
      Error("GetTimeWalk(Double_t charge)","const. current is less or equal zero -> now set to 60 e/ns");
    SetParameter("fa",60.);
  }

	Double_t Q = Charge;

	if (Qt < 0){
		if (fVerboseLevel>0)
      Error("GetTimeWalk(Double_t charge)","threshold is less than zero -> now set to 0 eV");
		Qt = 0.;
	}
  
	if ((Q <= Qt) or (Q <= 0)){
		if (fVerboseLevel>0)
      Warning("GetTimeWalk(Double_t charge)","charge is equal or less than threshold -> zero TOT -> infinity TimeWalk");
		Q = 1.;
		Qt = 100000.;
		ftimewalk = GetParameter("ftr");
		return ftimewalk;
	}
  

	Qt = GetParameter("fth");
	ftimewalk = (GetParameter("ftr")*Qt/Q);
//	ftimewalk += ftimestep;
	return ftimewalk;
}

Double_t PndSdsTotChargeConversion::GetTotWC(){ //calculates start time, stop time with a clock
	fstarttime = (Int_t) ( t1e / ftimestep ) * ftimestep + ftimestep; //quantization of the start signal
	fstoptime = (Int_t) ( t2e / ftimestep ) * ftimestep + ftimestep; //quantization of the stop signal
  /*
   std::cout<<"  start point exact: "<<t1e<<std::endl;
   std::cout<<"  stop point exact: "<<t2e<<std::endl;
   std::cout<<"  time step is: "<<ftimestep<<" ns"<<std::endl;
   std::cout<<"  fclockfrequency is: "<<GetParameter("fclk")<<" MHz"<<std::endl;
   std::cout<<"  time offset is: "<<ftimeoffset<<" ns"<<std::endl;
   std::cout<<"  start point is: "<<fstarttime<<" ns"<<std::endl;
   std::cout<<"  stop point is: "<<fstoptime<<" ns"<<std::endl;
   */
	return (fstoptime-fstarttime);
}

void PndSdsTotChargeConversion::StartExecute(){	//function called for different events to set different time offsets
	ftimeoffset = fRand.Uniform(ftimestep);
}

Double_t PndSdsTotChargeConversion::GetPileUpTime(Double_t fcharge){	//returns the time the detector is not sensitive for other events
	return (GetParameter("ftr") + fcharge / GetParameter("fa"));
}

Double_t PndSdsTotChargeConversion::DigiValueToCharge(Double_t digivalue){ //returns the charge for the given tot value
	if (digivalue<0){
		if (fVerboseLevel>0)
      Error("ConvertDigiValueToELoss(Double_t digi)","charge digitization value not calculated properly");
		return -1;
	}
	return (-GetParameter("fa")*GetParameter("ftr")+GetParameter("fth")+digivalue*GetParameter("fa"))/2.+sqrt( pow( (GetParameter("fa")*GetParameter("ftr")-GetParameter("fth")-digivalue*GetParameter("fa")),2) / 4. + GetParameter("fa")* GetParameter("fth") * GetParameter("ftr"));
}

ClassImp(PndSdsTotChargeConversion);

