void ex053(){
  TFile *ifp = new TFile("tree.root");
  TTree *tree = (TTree*)ifp->Get("tree");

  int ival;
  tree->SetBranchStatus("ival"  ,1);  tree->SetBranchAddress("ival"  ,  &ival    );


  TFile *ofp = new TFile("clone.root","recreate");
  ofp->cd();
  TTree *newtree = new TTree();
  newtree = tree->CloneTree(0);

  int ENum = tree->GetEntries();

  for(int n=0;n<ENum;n++){
    tree->GetEntry(n);
    if( ival < 10 ){
      newtree->Fill();
    }
  }

  newtree->AutoSave();
  ofp->Write();
  ofp->Close();
  ifp->Close();
}

