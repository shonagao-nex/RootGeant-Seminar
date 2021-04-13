void example(){
  TH1D *h = new TH1D("h","h",100,-1.5,1.5);
  SetTH1(h,"example5-1","X","Counts");

  gRandom->SetSeed(0);                            // Initialization of random seed
  for(int i=0;i<100;i++){
    double x = gRandom->Uniform(-1.,1.);          // Uniform generation from -1 to +1
    cout<<"i,x : "<<i<<"  "<<x<<endl;
    h->Fill(x);
  }

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd();
  h->Draw();

}
