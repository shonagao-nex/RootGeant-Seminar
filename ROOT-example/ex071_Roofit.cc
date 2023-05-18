using namespace RooFit;
void ex071(){
//// Making Dummy Data
  TFile *ofp = new TFile("roofit.root","recreate");
  TTree *otree = new TTree("tree","tree");
  double VAL;
  TF1 *f1 = new TF1("f1","pol1",0,20);
  f1->SetParameters(0,1.0);

  otree->Branch("val"   , &VAL   , "val/D"       );

  for(int i=0;i<100;i++){
    VAL = gRandom->Landau(8.,0.2) + gRandom->Gaus(0,0.1);
    if( VAL < 20. ){ otree->Fill(); }
  }
  for(int i=0;i<300;i++){
    VAL = f1->GetRandom();
    otree->Fill();
  }
  otree->Write();
  ofp->Close();

//// Reading Dummy Data
  TFile *ifp = new TFile("roofit.root");
  TTree *tree = (TTree*)ifp->Get("tree");

//// Set Data, Range
  RooRealVar val("val","val",0.,20.);
  val.setRange("FULL"  ,0.,20.);
  val.setRange("BG1"  ,0.,2.);
  val.setRange("BG2"  ,18.,20.);
  RooDataSet data("data","data",tree,val);

//// Define Gaussian Function
  RooRealVar  gaus_mean ("gaus_mean" ,"gaus_mean" , 0.0 , -1.0,  1.0);
  RooRealVar  gaus_width("gaus_width","gaus_width", 0.20,  0.0,  1.0);
  RooGaussian  gaus("gaus","gaus",val,gaus_mean,gaus_width);
  gaus_mean.setConstant(kTRUE);  // mean parameter should be fixed

//// Define Landau Function
  RooRealVar  landau_mean ("landau_mean" ,"landau_mean",  8.,  6., 10.);
  RooRealVar  landau_width("landau_width","landau_width",0.2, 0.0, 1.0);
  RooGenericPdf land("land","land","TMath::Landau(val,landau_mean,landau_width)",RooArgSet(val,landau_mean,landau_width));

//// convolution
  RooFFTConvPdf landaugaus("landaugaus","landaugaus",val,land,gaus);
  RooRealVar  slope("slope","slope",1.,0.,100.);
  RooPolynomial bg("bg","bg",val,RooArgList(slope),1);
  bg.fitTo(data,Save(kFALSE),Range("BG1,BG2"),PrintLevel(-1),SplitRange(kTRUE));
//// Add pdf [c1*bg + (1-c1)*landaugaus]
  RooRealVar ratio("ratio","ratio",0.5, 0, 1.0);
  RooAddPdf total("total","total",RooArgList(bg,landaugaus),ratio);

  RooFitResult *result  = total.fitTo(data,Save(kTRUE),Hesse(kTRUE),Minos(RooArgSet(landau_mean,landau_width,gaus_width)),Range("FULL"),PrintLevel(-1));

  RooPlot *frame = val.frame();
  data.plotOn(frame,Binning(100),XErrorSize(0),DataError(RooAbsData::Poisson),MarkerSize(1));
  total.plotOn(frame,Name("total"),Precision(1e-6),LineWidth(1),LineColor(kBlue));
  total.plotOn(frame,Components(landaugaus),LineStyle(kDashed),Precision(1e-6),LineWidth(1));
  total.plotOn(frame,Components(bg),LineStyle(kDotted),Precision(1e-6),LineWidth(1));
  RooArgSet *param = total.getParameters(val);

//// NLL distribution 
  RooNLLVar nll("nll","nll",total,data);
  int bin_NLL1 = 100; // Binning for 1D histograms
  double MPV  = fabs(landau_mean.getValV());
  double WIDTH  = fabs(landau_width.getValV());

  TH1D *h_mland = (TH1D*)nll.createHistogram("h_mland",landau_mean,Binning(100,MPV*0.99,MPV*1.01),Scaling(kFALSE));
  SetTH1(h_mland,"Neg Log Likelihood Dist (Landau MPV)","Landau MPV","Log Likelihood",4,0,0);
  h_mland->SetLineWidth(3);
  h_mland->SetStats(kFALSE);

  RooPlot *frame_wland = landau_width.frame(Bins(100),Range(WIDTH*0.7, WIDTH*1.3),Scaling(kFALSE));
  nll.plotOn(frame_wland,ShiftToZero());

  TH2D *h_wland_mland = (TH2D*)nll.createHistogram("h_wland_mland",landau_mean,Binning(100,MPV*0.99,MPV*1.01),YVar(landau_width,Binning(100,WIDTH*0.7,WIDTH*1.3)),Scaling(kFALSE));
  SetTH2(h_wland_mland,"Neg Log Likelihood Dist","Landau MPV","Landau Width",h_wland_mland->GetMinimum());
  h_wland_mland->SetStats(kFALSE);

  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
  c1->Divide(2,2);
  c1->cd(1);
    frame->Draw();
  c1->cd(2);
    h_mland->Draw("LF2");
  c1->cd(3);
    frame_wland->Draw();
  c1->cd(4);
    h_wland_mland->Draw("colz");

} 

