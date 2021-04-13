// Other method. compile macro with g++ compiler. Fast! I prefer.
#include <iostream>
#include <string>
#include <stdio.h>

#include "TApplication.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TGaxis.h"
#include "TRandom.h"

int main(int argc, char** argv) {

  TApplication *theApp = new TApplication("App", &argc, argv);

  double mean = 10.;
  double wid  = 2.;

  double min_x = mean-wid*5;
  double max_x = mean+wid*5;

  TF1 *f = new TF1("f","gaus",0.,20.);
  f->SetParameters(10,mean,wid);
  f->SetNpx(1000);
  f->SetLineColor(4);
  f->SetLineStyle(7);

  TH1D *h1 = new TH1D("h1","h1",100,min_x,max_x);
  h1->SetTitle("Example2  h1");
  h1->GetXaxis()->SetTitle("X (mm)");
  h1->GetXaxis()->CenterTitle();
  h1->GetXaxis()->SetTitleSize(0.05);
  h1->GetXaxis()->SetTitleOffset(1.00);
  h1->GetYaxis()->SetTitle(Form("counts / %.1lf mm",(max_x-min_x)/100.));
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetYaxis()->SetTitleOffset(1.20);
  h1->SetFillStyle(3002);
  h1->SetFillColor(3);
  h1->SetStats(kFALSE);

  for(int i=0;i<1E+7;i++){
    double val = gRandom->Gaus(mean,wid);
    h1->Fill(val);
  }

  double par[3], epar;
  h1->Fit(f,"0Q","",min_x,max_x);
  f->GetParameters(&par[0]);
  epar = f->GetParError(2);
  std::cout<<Form("Constant : %e",par[0])<<std::endl;
  std::cout<<Form("Mean     : %lf",par[1])<<std::endl;
  std::cout<<Form("Sigma    : %.3lf",par[2])<<std::endl;

  double max = h1->GetMaximum();
  TLatex *t = new TLatex(par[1]+1.,max*0.95,Form("#sigma = %.3lf #pm %.3lf mm",par[2],epar));
  t->SetTextSize(0.04);
  t->SetTextColor(2);
  t->SetTextFont(42);

  TCanvas *c1 = new TCanvas("c1","c1",600,500);
  c1->Divide(1,1,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.10);
  h1->Draw();
  f->Draw("same");
  t->Draw();

  theApp->Run();
  return 0;
}

