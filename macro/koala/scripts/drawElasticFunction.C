void drawElasticFunction(Double_t mom, Double_t distance)
{
  KoaElasticCalculator func(mom, distance);
  TF1* f = new TF1("fElastic", func, 0, 300, 2);
  f->SetParameter(0, mom);
  f->SetParameter(1, distance);

  f->Draw();
}
