void ex081(){
  double mom  = 300.;  // MeV/c
  double mass = Mp;
  double T = p2E(mom,mass) - mass;
  double layer_thickness = 1.; // mm
  double step = 0.1;  // mm

  vector<double> edep, x;
  double thick_int = 0;
  while(1){
    double thick = layer_thickness;  // mm
    double edep_layer = 0;
    thick_int += thick;
    while(1){
      mom = E2p(T + mass,mass);
      double dedx_step = 0.1*GetdEdx_Scinti(mom,mass) * step;
      thick = thick - step;
      if( thick < 1E-8 ){ break; }
      else if( dedx_step > T ){ T = 0.; edep_layer += T; break; }
      else{ edep_layer += dedx_step; T -= dedx_step; }
    }
    if( T >= 1E-8 ){ edep.push_back(edep_layer); x.push_back(thick_int); }
    else{ break; }
  }

  TGraph *g = new TGraph((int)edep.size(),&x[0],&edep[0]);
  SetGr(g,"Edep v.s Scinti-Depth","Depth (mm)","Edep (MeV)");
  g->SetMinimum(0.);

  TCanvas *c1 = new TCanvas("c1","c1",1000,800);
  c1->Divide(1,1);
  c1->cd();
  g->Draw("APL");

}
