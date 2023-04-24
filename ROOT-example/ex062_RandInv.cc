void ex062(){
  TH1D *h = new TH1D("h","h",100,0.,10);
  SetTH1(h,"ex062","X","Counts");

  gRandom->SetSeed(0);
  for(int i=0;i<1E+5;i++){
    double x = -log(1. - gRandom->Uniform(0.,1.));
    h->Fill(x);
  }

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd();
  gPad->SetLogy();
  h->Draw();
}
