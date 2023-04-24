void ex063(){
  TH1D *h1 = new TH1D("h1","h1",100,0,1.);
  TH1D *h2 = new TH1D("h2","h2",100,0,1.);
  SetTH1(h1,"Generate","X","Counts");
  h1->SetMinimum(0);
  SetTH1(h2,"Rejection Sampling","X","Counts",1,3001,3);

  gRandom->SetSeed(0);
  for(int i=0;i<1E+5;i++){
    double x  = gRandom->Uniform(0.,1.);
    double yy = gRandom->Uniform(0.,1.);
    double y  = 1. - x;
    h1->Fill(x);
    if( yy < y ) h2->Fill(x);
  }

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd();
  h1->Draw();
  h2->Draw("same");
}
