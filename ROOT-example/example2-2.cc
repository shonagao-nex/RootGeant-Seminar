void example(double mean = 10., double wid = 2.){
  double min_x = mean-wid*5;
  double max_x = mean+wid*5;

  TF1 *f = new TF1("f","gaus",min_x,max_x);
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
  h1->GetYaxis()->SetTitleOffset(1.30);
  h1->SetFillStyle(3002);
  h1->SetFillColor(3);

  for(int i=0;i<100000;i++){
    double val = gRandom->Gaus(mean,wid);
    h1->Fill(val);
  }

  h1->Fit(f,"","",min_x,max_x);

  TLegend *leg = new TLegend(0.60,0.70,0.89,0.89,"","NDC");
  leg->SetFillColor(0);
  leg->SetTextSize(0.05);
  leg->SetNColumns(1);
  leg->AddEntry(h1,"Histogram","pfl");
  leg->AddEntry(f ,"Fitting","pl");

  TCanvas *c1 = new TCanvas("c1","c1",600,500);
  c1->Divide(1,1,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.10);
  h1->Draw();
  leg->Draw("same");
}

