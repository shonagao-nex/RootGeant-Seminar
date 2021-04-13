void example(){
  TFile *fp = new TFile("example4-1.root","recreate");  // Create a ROOT file
  TTree *tree = new TTree("tree","tree");               // Make tree
  int evID;                                             // Define valiables
  double val1, val2;
  double val3[2];

  tree->Branch("evID"  , &evID  , "evID/I"   );         // Register branches in tree (evID, int type)
  tree->Branch("val1"  , &val1  , "val1/D"   );         // (val1, double type)
  tree->Branch("val2"  , &val2  , "val2/D"   );
  tree->Branch("val3"  ,  val3  , "val3[2]/D");         // (val3, double array)

  for(int i=0;i<10000;i++){
    evID = i;
    val1 = gRandom->Gaus(10,2);
    val2 = val1 * 2. + gRandom->Gaus(0,2.);
    val3[0] = val1;
    val3[1] = val2;
    tree->Fill();                                       // Fill tree
  }
  tree->Write();                                        // Write tree
  fp->Close();                                          // Close rootfile
}

