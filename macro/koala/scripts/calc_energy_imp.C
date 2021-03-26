using namespace TMath;

static Double_t proton_mass=0.938272081;//GeV, from PDG2018

Double_t get_beta(Double_t Plab)//unit: GeV
{
  Double_t Elab=TMath::Sqrt(Plab*Plab+proton_mass*proton_mass);
  TLorentzVector mom(0,0,Plab,Elab);
  TLorentzVector v(0,0,0,0);

  TParticle proton(2212,1,0,0,0,0,mom,v);
  Double_t beta=proton.P()/proton.Energy();
  return beta;
}

Double_t get_energy(Double_t Plab)//unit: GeV
{
  Double_t Elab=TMath::Sqrt(Plab*Plab+proton_mass*proton_mass);
  return Elab;
}

Double_t get_gamma(Double_t Plab)//unit: GeV
{
  Double_t gamma=get_energy(Plab)/proton_mass;
  return gamma;
}

Double_t get_kappa(Double_t Plab)
{
  Double_t E_beam=TMath::Sqrt(Plab*Plab+proton_mass*proton_mass);
  return (E_beam+proton_mass)/(E_beam-proton_mass);
}

// alpha in degree
// return in MeV
Double_t GetRecTByAlpha_Imp(Double_t* alpha, Double_t *Plab)
{
  Double_t T;
  Double_t E_beam=TMath::Sqrt(Plab[0]*Plab[0]+proton_mass*proton_mass);
  Double_t Kappa=(E_beam+proton_mass)/(E_beam-proton_mass);
  Double_t sin_alpha=Sin(alpha[0]/180*Pi());
  T=2*proton_mass*sin_alpha*sin_alpha/(Kappa-sin_alpha*sin_alpha);
  
  return T*1000;
}

//
Double_t GetRecTByAlpha(Double_t Plab, Double_t alpha)
{
  TF1 *f1=new TF1("f1",GetRecTByAlpha_Imp,0,90,1);
  f1->SetParameter(0,Plab);
  return f1->Eval(alpha);
}

// T: in MeV
Double_t GetAlphaByRecT(Double_t Plab, Double_t T)
{
  Double_t alpha=-1;
  if(T>100){
    printf("The input value should be smaller than 1000 MeV\n");
  }
  else{
    TF1 *f1=new TF1("f1",GetRecTByAlpha_Imp,0,90,1);
    f1->SetParameter(0,Plab);
    alpha=f1->GetX(T);
  }
  return alpha;
}

void DrawAlphaVsRecT(Double_t Plab,Double_t min,Double_t max)
{
  TF1 *f1=new TF1("f1",GetRecTByAlpha_Imp,min,max,1);
  f1->SetParameter(0,Plab);
  f1->SetParNames("Beam Momentum (GeV)");
  
  f1->Draw();
}


// distance: cm
// T: MeV
// para[0]: Plab in GeV
// para[1]; Distance in cm
// return: mm
Double_t GetRecHitPositionByRecT_Imp(Double_t *T, Double_t *para)
{
  Double_t alpha=GetAlphaByRecT(para[0],T[0]);
  if(alpha>90 || alpha <0){
    printf("Not physical: please check the parameters\n");
    return 0;
  }
  else{
    return 10*Tan(alpha/180*Pi())*para[1];
  }
}

Double_t GetRecHitPositionByRecT(Double_t Plab, Double_t T, Double_t distance=100)
{
  TF1 *f1=new TF1("f1",GetRecHitPositionByRecT_Imp ,0,100,2);
  f1->SetParameter(0,Plab);
  f1->SetParameter(1,distance);
  return f1->Eval(T);
}

// Plab in GeV
// pos in mm
// distance in cm
Double_t GetRecTByRecHitPosition(Double_t Plab, Double_t pos, Double_t distance=100)
{
  TF1 *f1=new TF1("f1",GetRecHitPositionByRecT_Imp ,0,100,2);
  f1->SetParameter(0,Plab);
  f1->SetParameter(1,distance);
  return f1->GetX(pos);
}

//
Double_t GetThetaByAlpha_Imp(Double_t *alpha, Double_t *Plab)
{
  // Double_t T=GetRecTByAlpha(Plab,alpha[0])/1000;//in GeV
  Double_t T=GetRecTByAlpha_Imp(alpha,Plab)/1000;//in GeV

  Double_t px_abs=Sqrt(T*T+2*proton_mass*T)*Cos(alpha[0]/180*Pi());
  Double_t pz_abs=Plab[0] - Sqrt(T*T+2*proton_mass*T)*Sin(alpha[0]/180*Pi());

  Double_t tan_theta=px_abs/pz_abs;

  return ATan(tan_theta)/Pi()*180;
}

Double_t GetThetaByAlpha(Double_t Plab, Double_t alpha)
{
  TF1 *f=new TF1("f1",GetThetaByAlpha_Imp,0,90,1);
  f->SetParameter(0,Plab);
  return f->Eval(alpha);
}

Double_t GetAlphaByTheta(Double_t Plab, Double_t theta)
{
  Double_t alpha=-1;
  if(theta>=90){
    printf("The theta angle should be < 90 degree\n");
  }
  else {
    TF1 *f=new TF1("f1",GetThetaByAlpha_Imp,0,90,1);
    f->SetParameter(0,Plab);
    alpha=f->GetX(theta);
  }
  return alpha;
}

// Plab in GeV
// T in MeV
// distance in cm : where fwd detector located along z-axis
// return in cm
Double_t GetFwdHitPositionByRecT(Double_t Plab, Double_t T, Double_t distance=460)
{
  Double_t alpha=GetAlphaByRecT(Plab,T);
  Double_t theta=GetThetaByAlpha(Plab,alpha);
  return Tan(theta/180*Pi())*distance*10;
}

Double_t GetRecTByFwdHitPosition(Double_t Plab, Double_t pos, Double_t distance=460)
{
  Double_t theta=ATan(pos/distance)/Pi()*180;
  Double_t alpha=GetAlphaByTheta(Plab,theta);
  return GetRecTByAlpha(Plab, alpha);
}

// T in MeV
// para[0] : Plab in GeV
// para[1] : distance in cm
// para[2] : t0 electronics offset in ns
// return in ns
Double_t GetRecTofByRecT_Imp(Double_t *T, Double_t *para)
{
  Double_t alpha=GetAlphaByRecT(para[0],T[0]);
  Double_t s=para[1]/Cos(alpha/180*Pi());// in cm
  Double_t t=T[0]/1000;// in GeV
  // Double_t mom=Sqrt(t*t+2*proton_mass*t);
  // Double_t beta=get_beta(mom);
  Double_t gamma=(t+proton_mass)/proton_mass;
  Double_t beta=Sqrt((gamma*gamma-1)/gamma/gamma);
  // printf("beta=%f\n",beta);
  // printf("alpha=%f\n",alpha);
  // printf("s=%f\n",s);
  // printf("mom=%f\n",mom);

  return s/beta/30+para[2];
}

Double_t GetRecTofByRecT(Double_t Plab, Double_t T, Double_t distance=100)
{
  TF1 *f1=new TF1("f1",GetRecTofByRecT_Imp ,0,100,3);
  f1->SetParameter(0,Plab);
  f1->SetParameter(1,distance);
  f1->SetParameter(2,0);

  return f1->Eval(T);
  
}

void DrawRecTofVsRecT(Double_t Plab,Double_t xmin,Double_t xmax,Double_t distance=100)
{
  TF1 *f1=new TF1("f1",GetRecTofByRecT_Imp ,xmin,xmax,3);
  f1->SetParameter(0,Plab); f1->SetParNames("P_beam","RecDistance","T_offset");
  f1->SetParameter(1,distance);
  f1->SetParameter(2,0);

  f1->Draw();
}

// sensor: 1->Si#1, 2->Si#2, 3->Ge#1, 4->Ge#2
// strip:  1->48 for Si#1, 1->64 for Si#2, 1->32 for Ge#1, 1->32 for Ge#2
// unit: mm
// return center of the strip
// return the width of this strip in 'width'
Float_t GetPositionByStripID_Si1(Int_t strip, Float_t *width=nullptr)
{
  Float_t offset=26.4; // mm
  Float_t w, position;
  if(strip<17){
    w=2.4;
    if(strip<12){
      position = -(offset - 2.4*strip + w/2);
    }
    else{
      position = (strip-11)*w - w/2;
    }
  }
  else if(strip>16){
    w = 1.2;
    position = (strip-16)*w - w/2 + 16*2.4-offset;
  }
  if(width) *width=w;
  return position;
}

Float_t GetPositionByStripID_Si2(Int_t strip, Float_t *width=nullptr)
{
  Float_t offset=26.4; // mm
  Float_t w, position;
  if(width) *width=1.2;
  position = offset + 1.2*strip - 0.6;
  return position;
}

Float_t GetPositionByStripID_Ge1(Int_t strip, Float_t *width=nullptr)
{
  Float_t offset=92.4;// mm
  Float_t w, position;
  if(strip<10){
    w=1.2;
    position=offset+w*strip-w/2;
  }
  else if(strip>9 && strip<16){
    w=2.4;
    position=offset+1.2*9+(strip-9)*w-w/2;
  }
  else if(strip>15 && strip<28){
    w=3.6;
    position=offset+1.2*9+2.4*6+(strip-15)*w-w/2;
  }
  else{
    w=2.4;
    position=offset+1.2*9+2.4*6+3.6*12+(strip-27)*w-w/2;
  }
  //
  if(width) *width=w;
  return position;
}

Float_t GetPositionByStripID_Ge2(Int_t strip, Float_t *width=nullptr)
{
  Float_t offset=160.8;// mm
  Float_t w, position;
  if(strip<31){
    w=2.4;
    position=offset+strip*w-w/2;
  }
  else if(strip==31){
    w=3.6;
    position = offset+72+w/2;
  }
  else{
    w=4.8;
    position = offset+72+3.6+w/2;
  }
  //
  if(width) *width=w;
  return position;
}

Float_t GetPositionByStripID(Int_t sensor, Int_t strip, Float_t *width=nullptr, Float_t IP=0)
{
  Float_t position;
  switch (sensor) {
  case 1: {
    position = GetPositionByStripID_Si1(strip,width);
    break;
  }
  case 2: {
    position = GetPositionByStripID_Si2(strip,width);
    break;
  }
  case 3: {
    position = GetPositionByStripID_Ge1(strip,width);
    break;
  }
  case 4: {
    position = GetPositionByStripID_Ge2(strip,width);
    break;
  }
default:
    break;
  }
  return position+IP;
}
