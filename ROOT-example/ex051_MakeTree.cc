typedef struct{
  double dval1, dval2;
  int ival1;
} TQ;

void ex051(){
  TFile *ofp = new TFile("tree.root","recreate");
  TTree *tree = new TTree("tree","tree");
  int ival;
  char cval[100];
  float fval;
  double dval;
  double darray[2];
  vector<double> vdval;
  TQ tqval;
  
  tree->Branch("ival"  , &ival  , "ival/I"      );
  tree->Branch("cval"  , &cval  , "cval/C"      );
  tree->Branch("fval"  , &fval  , "fval/F"      );
  tree->Branch("dval"  , &dval  , "dval/D"      );
  tree->Branch("darray",  darray, "darray[2]/D" );
  tree->Branch("vdval" , &vdval                 );
  tree->Branch("tqval" , &tqval , "dval1/D:dval2:ival1/I" );

  string sval[4] = {"Nameko", "Eringi", "Kare", "Masaru"};

  for(int i=0;i<100000;i++){
    ival = (int)gRandom->Gaus(10.,2.);
    strcpy(cval, sval[gRandom->Integer(4)].c_str());
    fval = (float)gRandom->Gaus(0.,10.);
    dval = gRandom->Gaus(0.,10.);
    darray[0] = gRandom->Gaus(0.,1.);
    darray[1] = gRandom->Gaus(0.,10.);
    for(int j=0;j<10;j++){
      vdval.push_back( gRandom->Poisson(j+1) );
    }
    tqval.dval1 = gRandom->Gaus(0.,10.);
    tqval.dval2 = 10. + gRandom->Gaus(tqval.dval1,4);
    tqval.ival1 = gRandom->Poisson(4);
    tree->Fill();

    vdval.clear();
  }

  tree->Write();
  ofp->Close();
}

