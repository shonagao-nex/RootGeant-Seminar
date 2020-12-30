//++++++++++++++++++++++++++++++++++++++++++++++
// simple drawing
void example1(){
  TFile *fp = new TFile("example4-1.root");
  TTree *tree = (TTree*)fp->Get("tree");
  tree->Draw("val1");
}

//++++++++++++++++++++++++++++++++++++++++++++++
// simple 2D drawing
void example2(){
  TFile *fp = new TFile("example4-1.root");
  TTree *tree = (TTree*)fp->Get("tree");
  tree->Draw("val1:val2","","colz");
}

//++++++++++++++++++++++++++++++++++++++++++++++
// 2D drawing (define nbin, min, max)
void example3(){
  TFile *fp = new TFile("example4-1.root");
  TTree *tree = (TTree*)fp->Get("tree");
  tree->Draw("val1:val2>>(200,0,40,200,0,20)","","colz");
}

//++++++++++++++++++++++++++++++++++++++++++++++
// draw several histograms
void example4(){
  TFile *fp = new TFile("example4-1.root");
  TTree *tree = (TTree*)fp->Get("tree");

  TCanvas *c1 = new TCanvas("c1","c1",1000,800);
  c1->Divide(2,2,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.07);
  tree->Draw("val1:val2>>h1(200,0,40,200,0,20)","","colz");
  c1->cd(2)->SetMargin(0.15,0.10,0.15,0.07);
  tree->Draw("val1:val2>>h2(50,0,40,50,0,20)","","lego2z");
  c1->cd(3)->SetMargin(0.15,0.10,0.15,0.07);
  tree->Draw("val2>>h3(200,0,40)","","");
  c1->cd(4)->SetMargin(0.15,0.10,0.15,0.07);
  tree->Draw("val3[0]:evID>>h4(200,0,10000,200,0,20)","evID<8000","scat");
}

//++++++++++++++++++++++++++++++++++++++++++++++
// fill to histogram, and draw
void example5(){
  TChain *tree = new TChain("tree");
  tree->Add("example4-1.root");

  TH2D *h = new TH2D("h","h",200,0,40,200,0,20);
  SetTH2(h,"example5","val2","val1",0.);

  tree->Project("h","val1:val2","");

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.07);
  h->Draw("colz");
}

//++++++++++++++++++++++++++++++++++++++++++++++
// for roop of GetEntries()
void example6(){
  TFile *fp = new TFile("example4-1.root");
  TTree *tree = (TTree*)fp->Get("tree");

  int evID;
  double val1, val2, val3[2];

  tree->SetBranchAddress("evID",&evID);
  tree->SetBranchAddress("val1",&val1);
  tree->SetBranchAddress("val2",&val2);
  tree->SetBranchAddress("val3", val3);

  TH2D *h1 = new TH2D("h1","h1",200,0,40,200,0,20);
  TH2D *h2 = new TH2D("h2","h2",200,0,40,200,0,20);
  SetTH2(h1,"example6 h1","val2","val1",0.);
  SetTH2(h2,"example6 h2","val2","val1",0.);

  int ENum = tree->GetEntries();

  for(int n=0;n<ENum;n++){
    tree->GetEntry(n);
    h1->Fill(val2,val1);
    if(evID<2000){
      h2->Fill(val2,val1);
    }
  }

  TCanvas *c1 = new TCanvas("c1","c1",1000,500);
  c1->Divide(2,1,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.07);
  h1->Draw("colz");
  c1->cd(2)->SetMargin(0.15,0.10,0.15,0.07);
  h2->Draw("colz");
}



