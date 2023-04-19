void ex027(){
  auto f =  new TF1("f",Pois,0.,20.,3);
  SetTF1(f,2,2,1);
  f->SetParameter(0,6.);
  f->SetParameter(1,1.);
  f->SetParameter(2,100.);

  auto h1 = new TH1D("h1","ex027",200,0.,20.);
  SetTH1(h1,"ex027","X","counts");
  h1->FillRandom("f",10000);

  h1->Fit(f,"","",0.,20.);

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->Divide(1,1);
  c1->cd(1);
  h1->Draw();
  f->Draw("same");
}
