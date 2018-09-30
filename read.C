void read()
{
  auto file = new TFile("opentutorials_example.root");
  auto tree = (TTree *) file -> Get("data");

  auto cvs = new TCanvas("cvs","",550,500);
  auto hist = new TH1D("h1",";z (mm);Energy deposit (MeV)",100,0,40);
  tree -> Draw("z>>h1(50,0,50)","edep/50.","hist");
}
