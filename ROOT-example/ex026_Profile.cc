/////////////////////////////////////////////////////////////
void ex026a(){
  TH2D *h2 = new TH2D("h2","title",100,0.,10.,100,-10.,10.);
  SetTH2(h2,"ex026"  ,"X","Y",0.0);

  TProfile *pr = new TProfile("pr","Profile",200,0.,10,-10.,10.);
  pr->SetLineWidth(4);

  for(int i=0;i<4000;i++){
    double xval = gRandom->Landau(4., 1.5);
    double yval = 5. / sqrt(xval + 1.) + gRandom->Gaus(0., 1.);
    h2->Fill(xval, yval);
    pr->Fill(xval, yval);
  }

  TF1 *f1 = new TF1("f1","[0]/sqrt(x+[1])",0.,10.);
  SetTF1(f1,2,2);
  pr->Fit(f1,"0","",0.,10.);
  double par[2], epar[2];
  f1->GetParameters(&par[0]);
  epar[0] = f1->GetParError(0);
  epar[1] = f1->GetParError(1);

  TCanvas *c1 = new TCanvas("c1","c1",1000,800);
  c1->Divide(1,1,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.10);
  h2->Draw("colz");
  pr->Draw("same");
  f1->Draw("same");
  TLatex text;
  text.DrawLatex(1.,-4.0,"par[0] / sqrt(x + par[1])");
  text.DrawLatex(1.,-5.5,Form("par[0] = %.3lf #pm %.3lf",par[0],epar[0]));
  text.DrawLatex(1.,-7.0,Form("par[1] = %.3lf #pm %.3lf",par[1],epar[1]));
}

/////////////////////////////////////////////////////////////
void ex026b(){
  gErrorIgnoreLevel = kWarning;
  TH2D *h2 = new TH2D("h2","title",100,0.,10.,100,-10.,10.);
  SetTH2(h2,"ex026"  ,"X","Y",0.0);

  for(int i=0;i<4000;i++){
    double xval = gRandom->Landau(4., 1.5);
    double yval = 5. / sqrt(xval + 1.) + gRandom->Gaus(0., 1.);
    h2->Fill(xval, yval);
  }

  TF1 *f1 = new TF1("f1","gaus",-10.,10.);
  h2->FitSlicesY(f1,1, 100, 0, "QNRG2");
  TH1D *h1 = (TH1D*)gROOT->FindObject("h2_1");
  h1->SetLineWidth(3);

  TF1 *f2 = new TF1("f2","[0]/sqrt(x+[1])",0.,10.);
  SetTF1(f2,2,2);
  h1->Fit(f2,"0","",0.,10.);
  double par[2], epar[2];
  f2->GetParameters(&par[0]);
  epar[0] = f2->GetParError(0);
  epar[1] = f2->GetParError(1);

  TCanvas *c1 = new TCanvas("c1","c1",1000,800);
  c1->Divide(1,1,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.10);
  h2->Draw("colz");
  h1->Draw("same");
  f2->Draw("same");
  TLatex text;
  text.DrawLatex(1.,-4.0,"par[0] / sqrt(x + par[1])");
  text.DrawLatex(1.,-5.5,Form("par[0] = %.3lf #pm %.3lf",par[0],epar[0]));
  text.DrawLatex(1.,-7.0,Form("par[1] = %.3lf #pm %.3lf",par[1],epar[1]));
}

