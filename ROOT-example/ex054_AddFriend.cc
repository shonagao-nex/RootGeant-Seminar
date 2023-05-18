void ex054(){
  TFile *ifp = new TFile("tree.root");
  TTree *tree = (TTree*)ifp->Get("tree");

  tree->AddFriend("tree2","tree2.root");

  TCanvas *c1 = new TCanvas("c1","c1",1000,800);
  c1->cd(1);
  tree->Draw("dval:tree2.newval");
}

