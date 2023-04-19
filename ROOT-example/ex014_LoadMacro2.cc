void setgraph(TGraph *g, double val){     // Set Graph point function
  g->SetPoint(0,1.,1.1);
  g->SetPoint(1,2.,1.9);
  g->SetPoint(2,3.,val);
  g->SetPoint(3,4.,3.9);
}

void ex014(double val){                 // Definition of example function
  TGraph *g = new TGraph();
  setgraph(g,val);                        // Call setgraph function
  g->SetMarkerStyle(20);

  TCanvas *c1 = new TCanvas("c1","c1");
  g->Draw("APL");
}
