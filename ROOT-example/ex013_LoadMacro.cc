void ex013_LoadMacroA(){    // same result as ex02.cc, different method
  TGraph *g = new TGraph();
  g->SetPoint(0,1.,1.1);
  g->SetPoint(1,2.,1.9);
  g->SetPoint(2,3.,3.0);
  g->SetPoint(3,4.,3.9);
  g->SetMarkerStyle(20);

  TCanvas *c1 = new TCanvas("c1","c1");
  g->Draw("APL");
}

void ex013_LoadMacroB(double val){// different method part2. 3rd point is a valiable
  TGraph *g = new TGraph();
  g->SetPoint(0,1.,1.1);
  g->SetPoint(1,2.,1.9);
  g->SetPoint(2,3.,val);
  g->SetPoint(3,4.,3.9);
  g->SetMarkerStyle(20);

  TCanvas *c1 = new TCanvas("c1","c1");
  g->Draw("APL");
}

