//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double p2E(double p, double M){
  return sqrt(p*p + M*M);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double E2p(double E, double M){
  return sqrt(E*E - M*M);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetQ2(double Ee, double Eep, double theta){  // Q2 (MeV^2)
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
double GetVPInvariantEnergy(double Ee, double Mt, double Eep, double theta){
  TVector3 v_pt; v_pt.SetMagThetaPhi(0,0,0);
  TVector3 v_pb; v_pb.SetMagThetaPhi(GetVPMomentum(Ee,Eep,theta),PI,0);
  TLorentzVector lv_t(v_pt,Mt);
  TLorentzVector lv_b(v_pb,(Double_t)GetVPEnergy(Ee,Eep));
//  return sqrt( Mt*Mt - GetQ2(Ee,Eep,theta) + 2.*Mt*GetVPEnergy(Ee,Eep) );
  return sqrt((lv_t + lv_b)*(lv_t + lv_b));
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetVPEquivalentEnergy(double Ee, double Mt, double Eep, double theta){
  double s = GetVPInvariantEnergy(Ee,Mt,Eep,theta);
  return ( s*s - Mt*Mt ) / (2.*Mt);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//double GetbetaCMMag(double p1, double p2, double M1, double M2, double theta1 = 0., double theta2 = PI){
//  TVector2 v_1; v_1.SetMagPhi(p1,theta1);
//  TVector2 v_2; v_2.SetMagPhi(p2,theta2);
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


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetVPFlux(double E, double Ep, double theta){
  double p = sqrt(E*E - Me*Me); // momentum of incident electron
  double pp = sqrt(Ep*Ep - Me*Me); // momentum of scattered electron
//  double Q2 = 2.*(E*Ep - Me*Me - fabs(p)*fabs(pp)*cos(theta)); // Q2 (mass square of vertual photon)
  double Q2 = GetQ2(E, Ep, theta); // Q2 (mass square of vertual photon)
  double k_gamma = (E-Ep) - Q2/(2*Mp); // photon equivalent energy
  double q_2 = Q2 + (E-Ep)*(E-Ep); // momentum square of vertual photon
  double epsiron = (2.*p*p*pp*pp*sin(theta)*sin(theta)) / (Q2*q_2 + 2.*p*p*pp*pp*sin(theta)*sin(theta));
  double Gamma = (alpha/(2.*PI*PI*Q2)) * (Ep/E) * (k_gamma/(1-epsiron)); // vertual photon flux
            //  cout<<p<<"  "<<pp<<"  "<<Q2<<"  "<<k_gamma<<"  "<<q_2<<endl;

  return Gamma;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetVPEpsiron(double E, double Ep, double theta){
  double p = sqrt(E*E - Me*Me); // momentum of incident electron
  double pp = sqrt(Ep*Ep - Me*Me); // momentum of scattered electron
//  double Q2 = 2.*(E*Ep - Me*Me - fabs(p)*fabs(pp)*cos(theta)); // Q2 (mass square of vertual photon)
  double Q2 = GetQ2(E, Ep, theta); // Q2 (mass square of vertual photon)
  double k_gamma = (E-Ep) - Q2/(2.*Mp); // photon equivalent energy
  double q_2 = Q2 + (E-Ep)*(E-Ep); // momentum square of vertual photon
//  double epsiron = (2*p*p*pp*pp*sin(theta)*sin(theta)) / (Q2*q_2 + 2*p*p*pp*pp*sin(theta)*sin(theta));
  double epsiron = (Q2+2.*q_2*tan(theta/2.)*tan(theta/2.)) / Q2;

  return 1./epsiron;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetVPEpsironL(double E, double Ep, double Mt, double theta){
  double Q2    = GetQ2(E, Ep, theta);
  double omega = E - Ep;
  double epsiron  = GetVPEpsiron(E, Ep, theta);
  TVector3 v_pt; v_pt.SetMagThetaPhi(0,0,0);
  TVector3 v_pb; v_pb.SetMagThetaPhi(GetVPMomentum(E,Ep,theta),PI,0);
  TLorentzVector lv_t(v_pt,Mt);
  TLorentzVector lv_b(v_pb,(Double_t)GetVPEnergy(E,Ep));
  double Einv = 1. / (Mt + GetVPEnergy(E,Ep) );
  TVector3 v_beta; v_beta = (v_pt + v_pb); v_beta *= Einv;
  lv_b.Boost(-v_beta);
  double omega_cm = lv_b.E();

//  double epsironL = epsiron * Q2 / omega_cm /omega_cm;
  double epsironL = epsiron * Q2 / omega /omega;

  return epsironL;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetVPTheta(double E, double Ep, double theta){
  double Q2    = GetQ2(E, Ep, theta);
  double omega = E - Ep;
  double vptheta = acos((E-Ep*(1.-Q2/2./E/Ep))/sqrt(omega*omega+Q2));

  return vptheta;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetCherenkov(double n, double p, double m = Me){
  double N = 0;
  double beta = p / sqrt( p*p + m*m );
  double dlambda = 1E-9;
  for(int i=0;i<200;i++){
    double lambda = (350. + i) * 1E-9;
    double dN = 2.*PI*alpha/lambda/lambda*(1 - 1/beta/beta/n/n);
    N += dN * dlambda;
  }
  return N/100.;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void test(double E, double Ep, double M, double theta){
  cout<<"Q2 = "<<GetQ2(E,Ep,theta)/1E+6<<endl;
  cout<<"Gamma = "<<GetVPFlux(E,Ep,theta)<<endl;
  cout<<"eT = "<<GetVPEpsiron(E,Ep,theta)<<endl;
  cout<<"eL = "<<GetVPEpsironL(E,Ep,M,theta)<<endl;
  cout<<"theta = "<<GetVPTheta(E,Ep,theta) * rad_to_deg<<endl;
}



