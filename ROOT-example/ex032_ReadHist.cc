void ex032(){
  TFile *ifp = new TFile("hist.root");
  
  TH1D *h01 = (TH1D*)ifp->Get("h1");
  gDirectory->cd("aaa");
  TH1D *h02 = (TH1D*)gROOT->FindObject("h2");
  gDirectory->cd("../bbb");
  TH1D *h03 = (TH1D*)gROOT->FindObject("h3");

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->Divide(2,2);
  c1->cd(1);
   h01->Draw();
  c1->cd(2);
   h02->Draw();
  c1->cd(3);
   h03->Draw();
}
