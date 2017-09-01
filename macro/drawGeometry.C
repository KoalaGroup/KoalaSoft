void drawGeometry(const char* filename="geofile_full.root")
{
  TFile* file=new TFile(filename);
  TGeoManager* geoMan=(TGeoManager*)file->Get("FAIRGeom");
  TGeoVolume* top=geoMan->GetTopVolume();

  top->Draw("ogl");
  delete file;
}
