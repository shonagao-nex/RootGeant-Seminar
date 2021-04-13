void example(){
  TH1D *h1 = new TH1D("h1","h1",100,0,1.);
  TH1D *h2 = new TH1D("h2","h2",100,0,1.);
  SetTH1(h1,"example5-3","X","Counts");
  h1->SetMinimum(0);
  SetTH1(h2,"example5-3","X","Counts",1,3001,3);

  gRandom->SetSeed(0);
  for(int i=0;i<1E+5;i++){
    double x  = gRandom->Uniform(0.,1.);
    double yy = gRandom->Uniform(0.,1.);
    double y  = 1. - x;
    h1->Fill(x);
    if( yy < y ) h2->Fill(x);                   // Fill random events with the rejection method
  }

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd();
  h1->Draw();
  h2->Draw("same");

}
