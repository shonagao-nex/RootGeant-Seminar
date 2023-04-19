#include <iostream>
#include <string>
#include <stdio.h>
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"

void ex015(){
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
  g->Draw("APL");
}

