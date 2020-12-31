#include "ParamManager.hh"

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

ParamManager *ParamManager::thisPointer=0;

ParamManager::ParamManager(G4String runnum, G4String infilename)
{
  runID = runnum;
  ifname = infilename;
  ReadParam();

  thisPointer = this;
}

bool ParamManager::ReadParam()
{
  G4cout << "Input Parameter file : " << ifname << G4endl;
  FILE *ifp = fopen(ifname, "r" );
  if(!ifp){
    std::cout<<"no input file!!!"<<std::endl;
    exit(-1);
  }

  char aaa[200];
  char bbb[200];

  // initialize
  ofname = "output.root";

  // fill param
  while( fgets( aaa, 250, ifp ) ){
    if( aaa[0] == '#' ) continue;

    else if( sscanf( aaa, "OutputFile: %s", bbb )==1 ){
      G4String tmp = bbb;
      ofname = "root/" + tmp + runID + ".root";
    }
    else if( sscanf( aaa, "BeamPar: %s"        , bbb ) ==1 ){
      bpar = bbb;
    }
    else if( sscanf( aaa, "BeamType: %d"       , &btype )==1 ){
    }
    else if( sscanf( aaa, "BeamMom: %lf %lf"   , &bmom, &bmomr ) ==1 ){
    }
    else if( sscanf( aaa, "BeamX: %lf %lf"     , &bx, &bxr )==1 ){
    }
    else if( sscanf( aaa, "BeamY: %lf %lf"     , &by, &byr )==1 ){
    }
    else if( sscanf( aaa, "BeamZ: %lf %lf"     , &bz, &bzr )==1 ){
    }
    else if( sscanf( aaa, "BeamTheta: %lf %lf" , &bt, &btr )==1 ){
    }
    else if( sscanf( aaa, "BeamPhi: %lf %lf"   , &bp, &bpr )==1 ){
    }
    else if( sscanf( aaa, "TargetThick: %lf"   , &tthick )==1 ){
    }
    else if( sscanf( aaa, "Decay: %d"          , &decay )==1 ){
    }

  }

  return true;
}
