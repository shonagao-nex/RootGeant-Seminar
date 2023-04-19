void ex025(){
  TH2D *h21 = new TH2D("h21","title",20,-10.,10.,50,0.,20.);
  TH2D *h22, *h23;

  for(int i=0;i<100000;i++){
    double xval = gRandom->Uniform(-9., 9.);
    double yval = gRandom->Landau(4., 1.);
    h21->Fill(xval, yval);
  }

  h22 = (TH2D*)h21->Clone("h22");
  h23 = (TH2D*)h21->Clone("h23");

  SetTH2(h21,"scat option"  ,"X","Y",0.0);
  h21->SetMarkerStyle(1);
  SetTH2(h22,"colz option"  ,"X","Y",0.8);
  SetTH2(h23,"surf1z option","X","Y",0.8);

  TCanvas *c1 = new TCanvas("c1","c1",1000,800);
  c1->Divide(2,2,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.10);
   h21->Draw("scat");
  c1->cd(2)->SetMargin(0.15,0.10,0.15,0.10);
   h22->Draw("colz");
  c1->cd(3)->SetMargin(0.15,0.10,0.15,0.10);
   h23->Draw("lego2z");
   gPad->SetLogz();
   gPad->SetTheta(30.); gPad->SetPhi(120.);
  c1->cd(4)->SetMargin(0.15,0.10,0.15,0.10);
   h21->ProjectionY()->Draw("");
   h21->ProjectionY()->SetTitle("Y Projection");
}

