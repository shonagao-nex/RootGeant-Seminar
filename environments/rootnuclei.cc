//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool Ex_table(unsigned int Z, unsigned int A, unsigned int L = 0, double &Ex, int &bound, double &eEx){
  Ex = eEx = 0.;
  bound = -1; // -1:unbound, 0:shord lives(<1e-9sec), 1:bound, 2:stable
  int N = (A - Z);
  if(N<0){ Ex = 0.; std::cout<<"negative neutron number"<<std::endl; return false; }
  unsigned long ID = L*1e6 + A*1e3 + Z;
//  std::cout<<"Z = "<<Z<<",  A = "<<A<<",  L = "<<L<<",  ID = "<<ID<<std::endl;

  switch(ID){
// Nuclear Mass Excess from G.Audi NPA729 (2003) 337, bound from JAEA chart 2010 wwwndc.jaea.go.jp/CN10/
    case   2001:  Ex = 13135.7216;  eEx = 0.0003;  bound =  2;  break; // H2

    case   3001:  Ex = 14949.8060;  eEx = 0.0023;  bound =  1;  break; // H3
    case   3002:  Ex = 14931.2148;  eEx = 0.0024;  bound =  2;  break; // He3
    case   3003:  Ex = 28670.    ;  eEx = 2000. ;  bound = -1;  break; // Li3

    case   4001:  Ex = 25900     ;  eEx = 100    ; bound = -1;  break; // H4
    case   4002:  Ex = 2424.91565;  eEx = 0.00006; bound =  2;  break; // He4
    case   4003:  Ex = 25320     ;  eEx = 210    ; bound = -1;  break; // Li4

    case   5001:  Ex = 32890     ;  eEx = 100    ; bound = -1;  break; // H5
    case   5002:  Ex = 11390     ;  eEx = 50     ; bound = -1;  break; // He5
    case   5003:  Ex = 11680     ;  eEx = 50     ; bound = -1;  break; // Li5
    case   5004:  Ex = 38000     ;  eEx = 4000   ; bound = -1;  break; // Be5

    case   6001:  Ex = 41860     ;  eEx = 260    ;  bound = -1;  break; // H6
    case   6002:  Ex = 17595.1   ;  eEx = 0.8    ;  bound =  1;  break; // He6
    case   6003:  Ex = 14086.793 ;  eEx = 0.015  ;  bound =  2;  break; // Li6
    case   6004:  Ex = 18375     ;  eEx = 5      ;  bound = -1;  break; // Be6
    case   6005:  Ex = 43600     ;  eEx = 700    ;  bound = -1;  break; // B6

    case   7001:  Ex = 49140     ;  eEx = 1010   ;  bound = -1;  break; // H7
    case   7002:  Ex = 26101     ;  eEx = 17     ;  bound = -1;  break; // He7
    case   7003:  Ex = 14908.14  ;  eEx = 0.08   ;  bound =  2;  break; // Li7
    case   7004:  Ex = 15770.03  ;  eEx = 0.11   ;  bound =  1;  break; // Be7
    case   7005:  Ex = 27870     ;  eEx = 70     ;  bound = -1;  break; // B7

    case   8002:  Ex = 31598     ;  eEx = 7      ;  bound =  1;  break; // He8
    case   8003:  Ex = 20946.84  ;  eEx = 0.09   ;  bound =  1;  break; // Li8
    case   8004:  Ex = 4941.67   ;  eEx = 0.04   ;  bound =  0;  break; // Be8
    case   8005:  Ex = 22921.5   ;  eEx = 1.0    ;  bound =  1;  break; // B8
    case   8006:  Ex = 35094     ;  eEx = 23     ;  bound = -1;  break; // C8
    
    case   9002:  Ex = 40939     ;  eEx = 29     ;  bound = -1;  break; // He9
    case   9003:  Ex = 24954.3   ;  eEx = 1.9    ;  bound =  1;  break; // Li9
    case   9004:  Ex = 11347.6   ;  eEx = 0.4    ;  bound =  2;  break; // Be9
    case   9005:  Ex = 12415.7   ;  eEx = 1.0    ;  bound =  0;  break; // B9
    case   9006:  Ex = 28910.5   ;  eEx = 2.1    ;  bound =  1;  break; // C9

    case  10002:  Ex = 48810     ;  eEx = 70     ;  bound = -1;  break; // He10
    case  10003:  Ex = 33051     ;  eEx = 15     ;  bound = -1;  break; // Li10
    case  10004:  Ex = 12606.7   ;  eEx = 0.4    ;  bound =  1;  break; // Be10
    case  10005:  Ex = 12050.7   ;  eEx = 0.4    ;  bound =  2;  break; // B10
    case  10006:  Ex = 15698.7   ;  eEx = 0.4    ;  bound =  1;  break; // C10
    case  10007:  Ex = 38800     ;  eEx = 400    ;  bound = -1;  break; // N10

    case  11003:  Ex = 40797     ;  eEx = 19     ;  bound =  1;  break; // Li11
    case  11004:  Ex = 20174     ;  eEx = 6      ;  bound =  1;  break; // Be11
    case  11005:  Ex = 8667.9    ;  eEx = 0.4    ;  bound =  2;  break; // B11
    case  11006:  Ex = 10650.3   ;  eEx = 1.0    ;  bound =  1;  break; // C11
    case  11007:  Ex = 24300     ;  eEx = 50     ;  bound = -1;  break; // N11

    case  12003:  Ex = 50100     ;  eEx = 1000   ;  bound = -1;  break; // Li12
    case  12004:  Ex = 25077     ;  eEx = 15     ;  bound =  1;  break; // Be12
    case  12005:  Ex = 13368.9   ;  eEx = 1.4    ;  bound =  1;  break; // B12
    case  12006:  Ex = 0         ;  eEx = 0      ;  bound =  2;  break; // C12
    case  12007:  Ex = 17338.1   ;  eEx = 1      ;  bound =  1;  break; // N12
    case  12008:  Ex = 32048     ;  eEx = 18     ;  bound = -1;  break; // O12

    case  13004:  Ex = 33250     ;  eEx = 70     ;  bound = -1;  break; // Be13
    case  13005:  Ex = 16562.2   ;  eEx = 1.1    ;  bound =  1;  break; // B13
    case  13006:  Ex = 3125.0113 ;  eEx = 0.0009 ;  bound =  2;  break; // C13
    case  13007:  Ex = 5345.48   ;  eEx = 0.27   ;  bound =  1;  break; // N13
    case  13008:  Ex = 23112     ;  eEx = 10     ;  bound =  1;  break; // O13

    case  14004:  Ex = 39950     ;  eEx = 130    ;  bound =  1;  break; // Be14
    case  14005:  Ex = 23664     ;  eEx = 21     ;  bound =  1;  break; // B14
    case  14006:  Ex = 3019.893  ;  eEx = 0.004  ;  bound =  1;  break; // C14
    case  14007:  Ex = 2863.4170 ;  eEx = 0.0006 ;  bound =  2;  break; // N14
    case  14008:  Ex = 8007.36   ;  eEx = 0.11   ;  bound =  1;  break; // O14
    case  14009:  Ex = 32660     ;  eEx = 400    ;  bound = -1;  break; // F14

    case  15004:  Ex = 49800     ;  eEx = 500    ;  bound = -1;  break; // Be15
    case  15005:  Ex = 28972     ;  eEx = 22     ;  bound =  1;  break; // B15
    case  15006:  Ex = 9873.1    ;  eEx = 0.8    ;  bound =  1;  break; // C15
    case  15007:  Ex = 101.4380  ;  eEx = 0.0007 ;  bound =  2;  break; // N15
    case  15008:  Ex = 2855.6    ;  eEx = 0.5    ;  bound =  1;  break; // O15
    case  15009:  Ex = 16780     ;  eEx = 130    ;  bound =  1;  break; // F15

    case  16004:  Ex = 57680     ;  eEx = 500    ;  bound = -1;  break; // Be16
    case  16005:  Ex = 37080     ;  eEx = 60     ;  bound = -1;  break; // B16
    case  16006:  Ex = 13694     ;  eEx = 4      ;  bound =  1;  break; // C16
    case  16007:  Ex = 5683.7    ;  eEx = 2.6    ;  bound =  1;  break; // N16
    case  16008:  Ex =-4737.00141;  eEx = 0.00016;  bound =  2;  break; // O16
    case  16009:  Ex = 10680     ;  eEx = 8      ;  bound =  0;  break; // F16
    case  16010:  Ex = 23996     ;  eEx = 20     ;  bound = -1;  break; // Ne16

    case 181073:  Ex =-48441.6   ;  eEx = 1.8    ;  bound =  2;  break; // Ta181

// Lambda hypernuclei (MeV) from NPA754 (2005) 3c, PRL108 (2012) 042501, PRL110 (2013) 012502, PRL103 (2009) 202501
    case  1003001:  Ex =  0.13;  eEx = 0.05;  bound = 0;  break; // H3L

    case  1004001:  Ex =  2.04;  eEx = 0.04;  bound = 0;  break; // H4L
    case  1004002:  Ex =  2.39;  eEx = 0.03;  bound = 0;  break; // He4L

    case  1005002:  Ex =  3.12;  eEx = 0.02;  bound = 0;  break; // He5L

    case  1006001:  Ex =  4.0 ;  eEx = 1.1 ;  bound = 0;  break; // H6L
    case  1006002:  Ex =  4.18;  eEx = 0.10;  bound = 0;  break; // He6L

    case  1007002:  Ex =  5.68;  eEx = 0.25;  bound = 0;  break; // He7L
    case  1007003:  Ex =  5.58;  eEx = 0.03;  bound = 0;  break; // Li7L
    case  1007004:  Ex =  5.16;  eEx = 0.08;  bound = 0;  break; // Be7L

    case  1008002:  Ex =  7.16;  eEx = 0.70;  bound = 0;  break; // He8L
    case  1008003:  Ex =  6.80;  eEx = 0.03;  bound = 0;  break; // Li8L
    case  1008004:  Ex =  6.84;  eEx = 0.05;  bound = 0;  break; // Be8L

    case  1009003:  Ex =  8.50;  eEx = 0.12;  bound = 0;  break; // Li9L
    case  1009004:  Ex =  6.71;  eEx = 0.04;  bound = 0;  break; // Be9L
    case  1009005:  Ex =  8.29;  eEx = 0.18;  bound = 0;  break; // B9L

    case  1010004:  Ex =  9.11;  eEx = 0.22;  bound = 0;  break; // Be10L
    case  1010005:  Ex =  8.89;  eEx = 0.12;  bound = 0;  break; // B10L

    case  1011005:  Ex = 10.24;  eEx = 0.05;  bound = 0;  break; // B11L

    case  1012005:  Ex = 11.37;  eEx = 0.06;  bound = 0;  break; // B12L
    case  1012006:  Ex = 10.76;  eEx = 0.19;  bound = 0;  break; // C12L

    case  1013006:  Ex = 11.69;  eEx = 0.12;  bound = 0;  break; // C13L

    case  1014006:  Ex = 12.17;  eEx = 0.33;  bound = 0;  break; // C14L

    case  1015007:  Ex = 13.59;  eEx = 0.15;  bound = 0;  break; // N15L

    case  1016007:  Ex = 13.76;  eEx = 0.16;  bound = 0;  break; // N16L
    case  1016008:  Ex = 12.4 ;  eEx = 0.4 ;  bound = 0;  break; // O16L

    default:    Ex = eEx = 0.; bound = false; std::cout<<"NOT registered nucleon "<<ID<<std::endl; break;
  }
  if(L==0){ Ex  /= 1000.; eEx /= 1000.; } // keV -> MeV
  return true;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetEx(unsigned int Z, unsigned int A, unsigned int L = 0){
  double Ex = 0, eEx = 0;  int bound = -1;
  Ex_table(Z,A,L,Ex,bound,eEx);
  return Ex;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetExError(unsigned int Z, unsigned int A, unsigned int L = 0){
  double Ex = 0, eEx = 0;  int bound = -1;
  Ex_table(Z,A,L,Ex,bound,eEx);
  return eEx;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int GetBound(unsigned int Z, unsigned int A, unsigned int L = 0){
  double Ex = 0, eEx = 0;  int bound = -1;
  Ex_table(Z,A,L,Ex,bound,eEx);
  return bound;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetNuclMass(unsigned int Z, unsigned int A){
  double Mass = A*Mu + GetEx(Z,A) - Z*Me + (14.4381*pow(Z,2.39) + 1.55468*1e-6*pow(Z,5.35)) * 1e-6;   
  if(Z==1 && A==1) Mass = Mp;
  if(Z==0 && A==1) Mass = Mn;
  return Mass;
} 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetHyperMass(unsigned int Z, unsigned int A, unsigned int L = 1){
  double Core_Mass = GetNuclMass(Z,A-1);
  double Mass = Core_Mass + ML - GetEx(Z,A,L);
  return Mass;
} 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetDecaypiQVal(unsigned int Z, unsigned int A, unsigned int L = 1){
  double D_Mass = GetNuclMass(Z+1,A); 
  double H_Mass = GetHyperMass(Z,A,L);
  return H_Mass - D_Mass - Mpi;
} 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double GetDecaypiMom(unsigned int Z, unsigned int A, unsigned int L = 1){
  double D_Mass = GetNuclMass(Z+1,A);
  double H_Mass = GetHyperMass(Z,A,L);
  return sqrt(pow(H_Mass,4) + pow(D_Mass,4) + pow(Mpi,4) - 2.*H_Mass*H_Mass*D_Mass*D_Mass - 2.*Mpi*Mpi*H_Mass*H_Mass - 2.*D_Mass*D_Mass*Mpi*Mpi) / 2. / H_Mass;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void GetDecaypiMomList(){
  cout<<"Parents                 Core                 Bound  Daughter              Bound  Momentum"<<endl;
  cout<<"(-1:unbound,0:shortlives,1:bound,2:stable)"<<endl;
  char *Nucl[] = {"H","He","Li","Be","B","C","N","O","F","Ne","Na","Mg"};
  int Z, A;
  A = 3; Z = 1;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 4; Z = 1;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 4; Z = 2;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 5; Z = 2;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 6; Z = 1;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 6; Z = 2;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 7; Z = 2;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 7; Z = 3;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 7; Z = 4;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 8; Z = 2;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 8; Z = 3;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 8; Z = 4;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 9; Z = 3;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 9; Z = 4;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A = 9; Z = 5;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A =10; Z = 4;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A =10; Z = 5;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A =11; Z = 5;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A =12; Z = 5;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A =12; Z = 6;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A =13; Z = 6;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A =14; Z = 6;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A =15; Z = 7;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A =16; Z = 7;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
  A =16; Z = 8;
  cout<<Form("%2s%2dL(%8.2lf+-%.2lf) : %2s%2d(%9.3lf+-%.3lf)  %+d  %2s%2d(%9.3lf+-%.3lf)  %+d    %6.2lf"
       ,Nucl[Z-1],A  ,GetHyperMass(Z,A,1),GetExError(Z,A,1)
       ,Nucl[Z-1],A-1,GetNuclMass(Z,A-1) ,GetExError(Z,A-1),GetBound(Z,A-1)
       ,Nucl[Z]  ,A  ,GetNuclMass(Z+1,A) ,GetExError(Z+1,A),GetBound(Z+1,A),GetDecaypiMom(Z,A,1))<<endl;
}


