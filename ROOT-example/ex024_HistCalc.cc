void ex024(){
  TH1D *h[6];
  int color[6] = {2,3,0,0,0,0};
  string title[6] = {"Hist1", "Hist2", "Hist1 + Hist2", 
     "Hist3 = Hist1 / 10", "Hist1 x Hist2", "Hist1 / (Hist3 x 5)"};
  for(int i=0;i<6;i++){
    h[i] = new TH1D(Form("h%d",i+1),Form("h%d",i+1),100,-10.,10.);
    SetTH1(h[i],Form("%s",title[i].data()),"X","Counts",1,3003,color[i]);
  }

  for(int i=0;i<10000;i++){
    double val = gRandom->Gaus(0.,3.);
    h[0]->Fill(val);
  }
  for(int i=0;i<5000;i++){
    double val = gRandom->Gaus(0.,1.);
    h[1]->Fill(val);
  }

  h[2]->Add(h[0]);
  h[2]->Add(h[1]);
  h[3] = (TH1D*)h[0]->Clone("h4");
  h[3]->SetTitle(Form("%s",title[3].c_str()));
  h[3]->Scale(1./10.);
  h[4]->Multiply(h[0],h[1],1.,1.);
  h[5]->Divide(h[0],h[3],1.,5.);

  TCanvas *c1 = new TCanvas("c1","c1",1400,800);
  c1->Divide(3,2,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.10);
    h[0]->Draw();
  c1->cd(2)->SetMargin(0.15,0.10,0.15,0.10);
    h[1]->Draw();
  c1->cd(3)->SetMargin(0.15,0.10,0.15,0.10);
    h[2]->Draw("E");
    h[0]->Draw("same");
    h[1]->Draw("same");
  c1->cd(4)->SetMargin(0.15,0.10,0.15,0.10);
    h[3]->Draw("HIST");
  c1->cd(5)->SetMargin(0.15,0.10,0.15,0.10);
    h[4]->Draw("");
  c1->cd(6)->SetMargin(0.15,0.10,0.15,0.10);
    h[5]->Draw("");
}

