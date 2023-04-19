#include <iostream>
#include <string>
#include <stdio.h>
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TApplication.h"

int main(int argc, char** argv) {

  TApplication *theApp = new TApplication("App", &argc, argv);

  TGraph *g = new TGraph();
  g->SetPoint(0,1.,1.1);
  g->SetPoint(1,2.,1.9);
  g->SetPoint(2,3.,3.0);
  g->SetPoint(3,4.,3.9);
  g->SetMarkerStyle(20);
  g->SetTitle("Y v.s X");
  g->GetXaxis()->SetTitle("X (mm)");
  g->GetYaxis()->SetTitle("Y (mm)");

  TCanvas *c1 = new TCanvas("c1","c1");
  c1->Divide(1,1);
  c1->cd(1);
  g->Draw("APL");

  theApp->Run();
  return 0;
}

