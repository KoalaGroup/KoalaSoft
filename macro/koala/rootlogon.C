{
  // Setup a new TStyle
  TStyle* koaStyle = new TStyle("koaStyle", "Koala Analysis Style");
  koaStyle->SetPalette(kRainBow); // set a better color palette

  // 1. Statistics box
  koaStyle->SetOptStat(0); // not statistics box
  // koaStyle->SetOptStat("euo"); // only print basic information in statistics box: entries, underflow, overflow

  // koaStyle->SetOptTitle(0); // no title printed

  // Legend
  koaStyle->SetLegendBorderSize(0); // no legend border
  // koaStyle->SetLegendFillColor(0); // no fill color
  // koaStyle->SetLegendFont(42);
  // koaStyle->SetLegendTextSize(0.);

  // Canvas
  koaStyle->SetCanvasBorderMode(0); // no canvas border

  // Frame
  koaStyle->SetFrameBorderMode(0); // no frame border, default: 1

  // Paper size
  koaStyle->SetPaperSize();

  /////////////////////////
  // set current style
  gROOT->SetStyle("koaStyle");

  // Setup include path
  TString configm(gSystem->Getenv("VMCWORKDIR"));

  // for interpreter macro loading, the two methods have same effect
  // gInterpreter->AddIncludePath("./utility");
  gROOT->ProcessLine(Form(".include %s/macro/koala/utility", configm.Data()));

  // for ACLiC include path
  gSystem->AddIncludePath(Form(".include %s/macro/koala/utility", configm.Data()));
}
