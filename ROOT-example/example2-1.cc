void example(double mean = 10., double wid = 2.){
  double min_x = mean-wid*5;
  double max_x = mean+wid*5;

  TF1 *f = new TF1("f","gaus",min_x,max_x);
  f->SetParameters(10,mean,wid);

  TH1D *h1 = new TH1D("h1","h1",100,min_x,max_x);

  for(int i=0;i<100000;i++){
    double val = gRandom->Gaus(mean,wid);
    h1->Fill(val);
  }

  h1->Fit(f,"","",min_x,max_x);

  TCanvas *c1 = new TCanvas("c1","c1",600,500);
  c1->cd(1);
  h1->Draw();
}

