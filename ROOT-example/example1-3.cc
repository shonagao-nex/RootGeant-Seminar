void setgraph(TGraph *g, double val){
  g->SetPoint(0,1.,1.1);
  g->SetPoint(1,2.,1.9);
  g->SetPoint(2,3.,val);
  g->SetPoint(3,4.,3.9);
}

void example(double val){
  TGraph *g = new TGraph();
  setgraph(g,val);
  g->SetMarkerStyle(20);

  TCanvas *c1 = new TCanvas("c1","c1");
  g->Draw("APL");
}
