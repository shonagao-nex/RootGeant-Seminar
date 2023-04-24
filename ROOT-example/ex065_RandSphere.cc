//////////////////////////////////////////////////
void ex065a(){
  TH3D *h1 = new TH3D("h1","Sphere",100,-1,1,100,-1,1,100,-1,1);
  h1->GetXaxis()->SetTitle("X");
  h1->GetXaxis()->CenterTitle();
  h1->GetXaxis()->SetTitleSize(0.06);
  h1->GetXaxis()->SetTitleOffset(1.2);
  h1->GetXaxis()->SetNdivisions(505);
  h1->GetYaxis()->SetTitle("Y");
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetTitleSize(0.06);
  h1->GetYaxis()->SetTitleOffset(1.2);
  h1->GetYaxis()->SetNdivisions(505);
  h1->GetZaxis()->SetTitle("Z");
  h1->GetZaxis()->CenterTitle();
  h1->GetZaxis()->SetTitleSize(0.06);
  h1->GetZaxis()->SetTitleOffset(1.2);
  h1->GetZaxis()->SetNdivisions(505);

  gRandom->SetSeed(0);
  for(int i=0;i<1E+4;i++){
    double theta = gRandom->Uniform(0,PI);
    double phi   = gRandom->Uniform(0.,2*PI);
    double x = sin(theta) * cos(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(theta);
    h1->Fill(x,y,z);
  }

  TCanvas *c1 = new TCanvas("c1","c1",750,800);
  c1->cd();
  h1->Draw("scat");
}

//////////////////////////////////////////////////
void ex065b(){
  TH3D *h1 = new TH3D("h1","Sphere",100,-1,1,100,-1,1,100,-1,1);
  h1->GetXaxis()->SetTitle("X");
  h1->GetXaxis()->CenterTitle();
  h1->GetXaxis()->SetTitleSize(0.06);
  h1->GetXaxis()->SetTitleOffset(1.2);
  h1->GetXaxis()->SetNdivisions(505);
  h1->GetYaxis()->SetTitle("Y");
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetTitleSize(0.06);
  h1->GetYaxis()->SetTitleOffset(1.2);
  h1->GetYaxis()->SetNdivisions(505);
  h1->GetZaxis()->SetTitle("Z");
  h1->GetZaxis()->CenterTitle();
  h1->GetZaxis()->SetTitleSize(0.06);
  h1->GetZaxis()->SetTitleOffset(1.2);
  h1->GetZaxis()->SetNdivisions(505);

  gRandom->SetSeed(0);
  for(int i=0;i<1E+4;i++){
    double theta = acos( gRandom->Uniform(-1,1) );
    double phi   = gRandom->Uniform(0.,2*PI);
    double x = sin(theta) * cos(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(theta);
    h1->Fill(x,y,z);
  }

  TCanvas *c1 = new TCanvas("c1","c1",750,800);
  c1->cd();
  h1->Draw("scat");
}
