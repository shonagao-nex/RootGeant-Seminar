//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double p2E(double p, double M){
  return sqrt(p*p + M*M);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double E2p(double E, double M){
  return sqrt(E*E - M*M);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetQ2(double Ee, double Eep, double theta){
// Q2 = - q^{\mu} * q_{\mu}
  TVector3 v_pe;  v_pe.SetMagThetaPhi(E2p(Ee,Me),0,0);
  TVector3 v_pep; v_pep.SetMagThetaPhi(E2p(Eep,Me),theta,0);
  TLorentzVector lv_e(v_pe,Ee);
  TLorentzVector lv_ep(v_pep,Eep);
//  return 2.*Ee*Eep*(1.-cos(theta)); // URA
//  return 2.*(Ee*Eep - Me*Me - E2p(Ee,Me)*E2p(Eep,Me)*cos(theta)); // Exact
  return -(lv_e - lv_ep)*(lv_e - lv_ep);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetVPEnergy(double Ee, double Eep){
  return Ee - Eep;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetVPMomentum(double Ee, double Eep, double theta){
  return sqrt( GetQ2(Ee,Eep,theta) + GetVPEnergy(Ee,Eep)*GetVPEnergy(Ee,Eep) );
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetVPCosTheta(double Ee, double Eep, double theta){
  return (Ee - Eep*(1. - GetQ2(Ee,Eep,theta)/(2.*Ee*Eep))) / GetVPMomentum(Ee, Eep, theta);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetInvariantEnergy(double p1, double p2, double M1, double M2){
  TVector3 v_p1; v_p1.SetMagThetaPhi(p1,0,0);
  TVector3 v_p2; v_p2.SetMagThetaPhi(p2,PI,0);
  TLorentzVector lv_1(v_p1,p2E(p1,M1));
  TLorentzVector lv_2(v_p2,p2E(p2,M2));
  double E1 = p2E(p1,M1);
  double E2 = p2E(p2,M2);
//  return sqrt( E1*E1 - p1*p1 + E2*E2 - p2*p2 + 2.*E1*E2 );
  return sqrt((lv_1 + lv_2)*(lv_1 + lv_2));
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetVPInvariantEnergy(double Ee, double Eep, double Mt, double theta){
  TVector3 v_pt; v_pt.SetMagThetaPhi(0,0,0);
  TVector3 v_pb; v_pb.SetMagThetaPhi(GetVPMomentum(Ee,Eep,theta),PI,0);
  TLorentzVector lv_t(v_pt,Mt);
  TLorentzVector lv_b(v_pb,(Double_t)GetVPEnergy(Ee,Eep));
//  return sqrt( Mt*Mt - GetQ2(Ee,Eep,theta) + 2.*Mt*GetVPEnergy(Ee,Eep) );
  return sqrt((lv_t + lv_b)*(lv_t + lv_b));
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetVPEquivalentEnergy(double Ee, double Eep, double Mt, double theta){
//  double s = GetVPInvariantEnergy(Ee,Mt,Eep,theta);
//  return ( s*s - Mt*Mt ) / (2.*Mt);
  return GetVPEnergy(Ee,Eep) - GetQ2(Ee,Eep,theta)/(2.*Mt);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetEpsiron(double Ee, double Eep, double Mt, double theta){
  double val = 1. + 2.*GetVPMomentum(Ee, Eep, theta)*GetVPMomentum(Ee, Eep, theta)/GetQ2(Ee,Eep,theta)*tan(theta/2.)*tan(theta/2.);
  return 1. / val;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetVPFlux(double Ee, double Eep, double Mt, double theta){
  double k = GetVPEquivalentEnergy(Ee, Eep, Mt, theta);
  double Q2 = GetQ2(Ee, Eep, theta);
  double epsiron = GetEpsiron(Ee, Eep, Mt, theta);
  double val = 1./(2.*PI*PI)* alpha * Eep/Ee * k/Q2 / (1-epsiron);
  return val;
}

////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//double GetbetaCMMag(double p1, double p2, double M1, double M2, double theta1 = 0., double theta2 = PI){
//  TVector2 v_1; v_1.SetMagPhi(p1,theta1,0);
//  TVector2 v_2; v_2.SetMagPhi(p2,theta2,0);
//  TVector2 v_beta;
//  v_beta = (v_1 + v_2) * (1./(p2E(p1,M1) + p2E(p2,M2)));
//  return v_beta.Mag();
//}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetbetaCMTheta(double p1, double p2, double M1, double M2, double theta1 = 0., double theta2 = PI){
  TVector2 v_1; v_1.SetMagPhi(p1,theta1);
  TVector2 v_2; v_2.SetMagPhi(p2,theta2);
  TVector2 v_beta;
  v_beta = (v_1 + v_2) * (1./(p2E(p1,M1) + p2E(p2,M2)));
  return v_beta.Phi();
}
