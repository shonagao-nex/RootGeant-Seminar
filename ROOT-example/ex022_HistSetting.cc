void ex022(double mean = 10., double wid = 2.){
  double min_x = mean-wid*5;
  double max_x = mean+wid*5;

  TF1 *f = new TF1("f","gaus",min_x,max_x);
  f->SetParameters(10,mean,wid);
  f->SetNpx(1000);                                  // Set Number of points (smoothness)
  f->SetLineColor(4);                               // Set Line Color (blue)
  f->SetLineStyle(7);                               // Set Line Style (dashed)

  TH1D *h1 = new TH1D("h1","Hist022",100,min_x,max_x);
  h1->SetTitle("Hist022");                          // Set main title
  h1->GetXaxis()->SetTitle("X (mm)");               // Set title of X-axis
  h1->GetXaxis()->CenterTitle();                    // Set X title position at the center
  h1->GetXaxis()->SetTitleSize(0.06);               // Set X title font size
  h1->GetXaxis()->SetTitleOffset(1.00);             // Set X title offset
  h1->GetYaxis()->SetTitle(Form("counts / %.1lf mm",(max_x-min_x)/100.));  // Set title of Y-axis
  h1->GetYaxis()->CenterTitle();                    // Set Y title position at the center
  h1->GetYaxis()->SetTitleSize(0.06);               // Set Y title font size
  h1->GetYaxis()->SetTitleOffset(1.30);             // Set Y title offset
  h1->SetFillStyle(3002);                           // Set Fill Style of histogram (Dots)
  h1->SetFillColor(3);                              // Set Fill color (light green)

  for(int i=0;i<100000;i++){
    double val = gRandom->Gaus(mean,wid);
    h1->Fill(val);
  }

  h1->Fit(f,"","",min_x,max_x);

  TLegend *leg = new TLegend(0.60,0.70,0.89,0.89,"","NDC");  // Set legend (x1, y1, x2, y2) NDC=relative position
  leg->SetFillColor(0);                                      // Fill color (none)
  leg->SetTextSize(0.05);                                    // Text size
  leg->SetTextFont(42);                                      // Text Font
  leg->SetNColumns(1);                                       // Number of columns
  leg->AddEntry(h1,"Histogram","pfl");                       // 1st entry
  leg->AddEntry(f ,"Fitting","pl");                          // 2nd entry

  TCanvas *c1 = new TCanvas("c1","c1",600,500);
  c1->Divide(1,1,1E-5,1E-5);                                 // Divide canvas and set x and margin
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.10);                 // Change 1st pad in a canvas, set margin of the pad
  h1->Draw();                                                // Draw histogram
  leg->Draw("same");                                         // Draw legend with "same" option
}

