//////////////////////////////////////////
void ex064a(){
  TH1D *h1 = new TH1D("h1","h1",200,0,10);
  SetTH1(h1,"Pois","X","counts");

  gRandom->SetSeed(0);
  double p = 2.;
  for(int i=0;i<1E+6;i++){
    double x = gRandom->Uniform(0,10);
    double y = gRandom->Uniform(0,0.3);
    double fx = TMath::Exp(-p) * pow(p,x) / TMath::Gamma(x+1);
    if( y < fx ){ h1->Fill(x); }
  }

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd(1);
  h1->Draw();
}

//////////////////////////////////////////
void ex064b(){
  TH1D *h1 = new TH1D("h1","h1",200,0,10);
  SetTH1(h1,"Pois","X","counts");

  gRandom->SetSeed(0);
  for(int i=0;i<1E+6;i++){
    double x = gRandom->Uniform(0,10);
    double y = gRandom->Uniform(0,0.3);
    double fx = TMath::Poisson(x,2.);
    if( y < fx ){ h1->Fill(x); }
  }

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd(1);
  h1->Draw();
}

//////////////////////////////////////////
void ex064c(){
  TH1D *h1 = new TH1D("h1","h1",200,0,10);
  SetTH1(h1,"Pois","X","counts");

  TF1 *f = new TF1("f","TMath::Poisson(x,2.)",0,10);

  gRandom->SetSeed(0);
  h1->FillRandom("f",1E+6);

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd(1);
  h1->Draw();
}

//////////////////////////////////////////
void ex064d(){
  TH1D *h1 = new TH1D("h1","h1",200,0,10);
  SetTH1(h1,"Pois","X","counts");

  TF1 *f = new TF1("f","TMath::Poisson(x,2.)",0,10);

  gRandom->SetSeed(0);
  for(int i=0;i<1E+6;i++){
    double val = f->GetRandom();
    h1->Fill(val);
  }

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd(1);
  h1->Draw();
}

