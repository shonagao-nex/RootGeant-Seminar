void ex017(){
  time_t start, end;
  start = time(NULL);
  time(&start);

  TF1 *f = new TF1("f","gaus",0.,20.);
  f->SetParameters(10,10.,2.);
  f->SetNpx(1000);
  f->SetLineColor(4);
  f->SetLineStyle(7);

  TH1D *h1 = new TH1D("h1","h1",100,0.,20.);
  h1->SetTitle("Example2  h1");
  h1->GetXaxis()->SetTitle("X (mm)");
  h1->GetXaxis()->CenterTitle();
  h1->GetXaxis()->SetTitleSize(0.05);
  h1->GetXaxis()->SetTitleOffset(1.00);
  h1->GetYaxis()->SetTitle("counts");
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetYaxis()->SetTitleOffset(1.20);
  h1->SetFillStyle(3002);
  h1->SetFillColor(3);
  h1->SetStats(kFALSE);

  int ENum = 5E+8;
  for(int i=0;i<ENum;i++){
    double val = gRandom->Gaus(10.,2.);
    h1->Fill(val);

    if(i%10000000==0){
      end = time(NULL);
      time(&end);
      cout<<Form("\r%d / %d    %.0lf sec",i,ENum,(double)difftime(end,start))<<flush;
    }
  }
  cout<<endl;

  double par[3], epar;
  h1->Fit(f,"0Q","",0.,20.);
  f->GetParameters(&par[0]);
  epar = f->GetParError(2);
  cout<<Form("Constant : %e",par[0])<<endl;
  cout<<Form("Mean     : %lf",par[1])<<endl;
  cout<<Form("Sigma    : %.3lf",par[2])<<endl;

  double max = h1->GetMaximum();
  TLatex *t = new TLatex(par[1]+1.,max*0.95,Form("#sigma = %.3lf #pm %.3lf mm",par[2],epar));
  t->SetTextSize(0.04);
  t->SetTextColor(2);
  t->SetTextFont(42);

}

