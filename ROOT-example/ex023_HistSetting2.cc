void ex023(double mean = 10., double wid = 2.){
  double min_x = mean-wid*5;
  double max_x = mean+wid*5;

  TF1 *f = new TF1("f","gaus",min_x,max_x);
  f->SetParameters(10,mean,wid);
  SetTF1(f,2,2,7);

  TH1D *h1 = new TH1D("h1","h1",100,min_x,max_x);   // Set titles with special function
  SetTH1(h1,"Histogram Setting Method 2","X (mm)",Form("counts / %.1lf mm",(max_x-min_x)/100.),1,3003,3);

  for(int i=0;i<100000;i++){
    double val = gRandom->Gaus(mean,wid);
    h1->Fill(val);
  }

  double par[3], epar;
  h1->Fit(f,"0Q","",min_x,max_x);
  f->GetParameters(&par[0]);                      // Get parameters of "f"
  epar = f->GetParError(2);                       // Get an error of 3rd parameter
  cout<<Form("Constant : %e",par[0])<<endl;       // Output results in a terminal
  cout<<Form("Mean     : %lf",par[1])<<endl;
  cout<<Form("Sigma    : %.3lf",par[2])<<endl;

  double max = h1->GetMaximum();
  TLatex *t = new TLatex(par[1]+1.,max*0.95,Form("#sigma = %.3lf #pm %.3lf mm",par[2],epar));  // Set Text
  t->SetTextSize(0.04);
  t->SetTextColor(2);
  t->SetTextFont(42);

  TCanvas *c1 = new TCanvas("c1","c1",1000,800);
  c1->Divide(1,1,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.10);
  h1->Draw();
  f->Draw("same");
  t->Draw();

//  Save Canvas
//  c1->Print("example023.png");     // Save c1 canvas to PNG file
//  c1->Print("example023.pdf");     // Save c1 canvas to PDF file
//  c1->Print("example023.ps");      // Save c1 canvas to ps file
//  c1->Print("example023.root");    // Save c1 canvas to root file
}

