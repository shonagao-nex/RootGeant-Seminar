///////////////////////////////////////////////
void ex041a(){
  double x[5] = {1, 2, 3, 4, 5};
  double y[5] = {1, 4, 9,16,25};
  TGraph *g = new TGraph(5, x, y);
  g->SetMarkerSize(1.0);
  g->SetMarkerStyle(20);
  g->SetLineWidth(2);
  g->SetLineColor(1);
  g->SetLineStyle(7);
  g->GetXaxis()->SetTitle("X");
  g->GetYaxis()->SetTitle("Y");
  g->SetTitle("Graph");

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd(1);
  g->Draw("APL");
}

///////////////////////////////////////////////
void ex041b(){
  vector<double> x, y;
  for(int i=0;i<5;i++){
    x.push_back(i);
    y.push_back(i*i);
  }
  TGraph *g = new TGraph(x.size(), &x[0], &y[0]);
  SetGr(g,"Graph","X","Y",1,2,7,1,20,1.);

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd(1);
  g->Draw("APC");
}

///////////////////////////////////////////////
void ex041c(){
  double x[5]  = {1, 2, 3, 4, 5};
  double y[5]  = {1, 4, 9,16,25};
  TGraph *g = new TGraph(5, x, y);
  SetGr(g,"","","",1,2,7,1,20,1.);

  TH2D *h2 = new TH2D("h2","h2",1000,0,6,1000,0,30);
  SetTH2(h2,"Graph","X","Y",0.0);
  h2->SetStats(kFALSE);

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd(1);
  h2->Draw();
  g->Draw("samePL");
}

///////////////////////////////////////////////
void ex041d(){
  double x[5]  = {1, 2, 3, 4, 5};
  double y[5]  = {1, 4, 9,16,25};
  double ey[5] = {1, 2, 3, 4, 5};
  TGraphErrors *g = new TGraphErrors(5, x, y, 0, ey);
  SetGr(g,"Graph","X","Y",1,2,1,1,21,1.);

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd(1);
  g->Draw("AP");
}

///////////////////////////////////////////////
void ex041e(){
  double x[5]   = {1, 2, 3, 4, 5};
  double y[5]   = {1, 4, 9,16,25};
  double eyl[5] = {1, 2, 3, 4, 5};
  double eyh[5] = {2, 4, 6, 8,10};
  auto *g = new TGraphAsymmErrors(5, x, y, 0, 0, eyl, eyh);
  SetGr(g,"Graph","X","Y",1,2,1,1,22,2.);

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd(1);
  g->Draw("AP");
}

///////////////////////////////////////////////
void ex041f(){
  TGraph *g = new TGraph("data.txt","%lg %lg",",");
  SetGr(g,"Graph","X","Y",1,2,1,1,24,2.);

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd(1);
  g->Draw("APL");
}




