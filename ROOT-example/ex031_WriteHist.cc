void ex031(){
  TFile *ofp = new TFile("hist.root","RECREATE");

  TH1D *h1 = new TH1D("h1","title",100,-10,10);
  SetTH1(h1,"ex031 h1","x","y");

  ofp->mkdir("aaa");
  ofp->cd("aaa");
  TH1D *h2 = new TH1D("h2","title",100,-5,15);
  SetTH1(h2,"ex031 h2","x","y");

  gDirectory->cd("/");
  gDirectory->mkdir("bbb");
  gDirectory->cd("bbb");
  TH1D *h3 = new TH1D("h3","title",100,-5,15);
  SetTH1(h3,"ex031 h3","x","y");

  h1->FillRandom("gaus",10000);
  h2->FillRandom("landau",10000);
  h3->FillRandom("gaus",1000);

  ofp->Write();
  ofp->Close();
}
