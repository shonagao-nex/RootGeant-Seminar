void example(double mean = 10., double wid = 2.){  // Call example function
  double min_x = mean-wid*5;                       // Set minimum fit-range
  double max_x = mean+wid*5;                       // Set maximum fit-range

  TF1 *f = new TF1("f","gaus",min_x,max_x);        // Call TF1 (Fitting) class, name="f", PDF="gauss", min-range, max-range
  f->SetParameters(10,mean,wid);                   // Initialization of fitting parameters

  TH1D *h1 = new TH1D("h1","h1",100,min_x,max_x);  // Call TH1 (Histogram) class, name="f", title="f", 100bins, min-range, max-range

  for(int i=0;i<100000;i++){                       // Roop for event generation
    double val = gRandom->Gaus(mean,wid);          // Call random generation (Gaussian shape)
    h1->Fill(val);                                 // fill histogram
  }

  h1->Fit(f,"","",min_x,max_x);                    // Fit histogram by "f" fuction 

  TCanvas *c1 = new TCanvas("c1","c1",600,500);    // Call TCanvas class
  c1->cd(1);                                       // Change directory in c1
  h1->Draw();                                      // Draw h1 histogram
}

