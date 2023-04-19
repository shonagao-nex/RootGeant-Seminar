//++++++++++++++++++++++++++++++++++++++++++++++
// simple drawing
void ex052a(){
  TFile *fp = new TFile("tree.root");
  TTree *tree = (TTree*)fp->Get("tree");
  tree->Draw("dval");
}

//++++++++++++++++++++++++++++++++++++++++++++++
// simple 2D drawing
void ex052b(){
  TFile *fp = new TFile("tree.root");
  TTree *tree = (TTree*)fp->Get("tree");
  tree->Draw("fval:dval","","colz");
}

//++++++++++++++++++++++++++++++++++++++++++++++
// 2D drawing (define nbin, min, max)
void ex052c(){
  TFile *fp = new TFile("tree.root");
  TTree *tree = (TTree*)fp->Get("tree");
  tree->Draw("fval:dval>>(200,-50,50,200,-50,50)","","colz");
}

//++++++++++++++++++++++++++++++++++++++++++++++
// draw several histograms
void ex052d(){
  TFile *fp = new TFile("tree.root");
  TTree *tree = (TTree*)fp->Get("tree");

  TCanvas *c1 = new TCanvas("c1","c1",1000,800);
  c1->Divide(2,2,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.07);
    tree->Draw("fval:dval>>h1(200,-50,50,200,-50,50)","","colz");
  c1->cd(2)->SetMargin(0.15,0.10,0.15,0.07);
    tree->Draw("fval:dval>>h2(50,-50,50,50,-50,50)","","lego2z");
  c1->cd(3)->SetMargin(0.15,0.10,0.15,0.07);
    tree->Draw("fval:dval>>h3(200,-50,50,200,-50,50)","","scat");
  c1->cd(4)->SetMargin(0.15,0.10,0.15,0.07);
    tree->Draw("fval:dval>>h4(200,-50,50,200,-50,50)","fval>-10","scat");
}

//++++++++++++++++++++++++++++++++++++++++++++++
// fill to histogram, and draw
void ex052e(){
  TChain *tree = new TChain("tree");
  tree->Add("tree.root");

  TH2D *h = new TH2D("h","h",200,-50,50,200,-50,50);
  SetTH2(h,"ex052e","tqval.dval1","tqval.dval2",0.);

  tree->Project("h","tqval.dval2:tqval.dval1","tqval.dval1>-20");

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.07);
  h->Draw("colz");
}


//++++++++++++++++++++++++++++++++++++++++++++++
typedef struct{
  double dval1, dval2;
  int ival1;
} TQ;
// for roop of GetEntries()
void ex052f(){
  TFile *fp = new TFile("tree.root");
  TTree *tree = (TTree*)fp->Get("tree");

  int ival;
  char cval[100];
  float fval;
  double dval;
  double darray[2];
  vector<double> *vdval = 0;
  TQ tqval;
 
  tree->SetBranchStatus("*",0);
  tree->SetBranchStatus("ival"  ,1);  tree->SetBranchAddress("ival"  ,  &ival    );
  tree->SetBranchStatus("cval"  ,1);  tree->SetBranchAddress("cval"  ,  &cval    );
  tree->SetBranchStatus("fval"  ,1);  tree->SetBranchAddress("fval"  ,  &fval    );
  tree->SetBranchStatus("dval"  ,1);  tree->SetBranchAddress("dval"  ,  &dval    );
  tree->SetBranchStatus("darray",1);  tree->SetBranchAddress("darray",  darray   );
  tree->SetBranchStatus("vdval" ,1);  tree->SetBranchAddress("vdval" ,  &vdval   );
  tree->SetBranchStatus("tqval" ,1);  tree->SetBranchAddress("tqval" ,  &tqval   );

  TH2D *h1 = new TH2D("h1","h1",20,0,20,30,0,30);
  TH2D *h2 = new TH2D("h2","h2",200,-50,50,200,-40,60);
  SetTH2(h1,"ex052 h1","vdval2","vdval6",0.);
  SetTH2(h2,"ex052 h2","tqval.dval1","tqval.dval2",0.);

  int ENum = tree->GetEntries();

  for(int n=0;n<ENum;n++){
    tree->GetEntry(n);
    h1->Fill(vdval->at(2), vdval->at(6));
    if( tqval.dval1 > -20 ){
      h2->Fill(tqval.dval1, tqval.dval2);
    }
  }

  TCanvas *c1 = new TCanvas("c1","c1",500,800);
  c1->Divide(1,2,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.10,0.15,0.07);
  h1->Draw("colz"); gPad->SetLogz();
  c1->cd(2)->SetMargin(0.15,0.10,0.15,0.07);
  h2->Draw("colz");
}

