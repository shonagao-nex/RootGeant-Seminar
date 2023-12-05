#include "MagField.hh"
#include "ParamManager.hh"
#include "G4FieldManager.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

#include "stdlib.h"
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

MagField::MagField()
{
//  cleanmap();

  paramMan = ParamManager::GetParam();
  G4String ifname = paramMan->GetFieldMapFile();
  std::cout<<"map file name = "<<ifname<<std::endl;

  G4double bx, by, bz;

  std::ifstream ifp;
  ifp.open(ifname);
  if(!ifp){
    std::cout<<"no file "<<ifname<<std::endl;
  }
  else{
    ifp >> Nx >> Ny >> Nz >> X0 >> Y0 >> Z0 >> dX >> dY >> dZ; 
//    G4cout<<"macnetic field value readout"<<G4endl;
//    std::cout <<Nx<<" "<<Ny<<" "<<Nz<<" "<<X0<<" "<<Y0<<" "<<Z0<<" "<<dX<<" "<<dY<<" "<<dZ<<std::endl<<std::endl;
    
    B.resize(Nx);
    for(int ix=0;ix<Nx;ix++){
      B[ix].resize(Ny);
      for(int iy=0;iy<Ny;iy++){ B[ix][iy].resize(Nz); }
    }
    
    int readid = 0;
    while(!ifp.eof()){
      ifp >> x >> y >> z >> bx >> by >> bz;
      int ix = int((x-X0+0.5*dX)/dX);
      int iy = int((y-Y0+0.5*dY)/dY);
      int iz = int((z-Z0+0.5*dZ)/dZ);
//      std::cout <<"while  "<<ix<<" "<<iy<<" "<<iz<<" "<<x<<" "<<y<<" "<<z<<" "<<bx<<" "<<by<<" "<<bz<<std::endl;
      B[ix][iy][iz].x = bx;
      B[ix][iy][iz].y = by;
      B[ix][iy][iz].z = bz;
      if(readid%3000==0) std::cout<<".."<<std::flush;
      readid++;
    }  // while ifp>>aaa
    std::cout<<std::endl;
  
  }  // else

  sleep(1);

}

MagField::~MagField()
{
  cleanmap();
}

void MagField::GetFieldValue(const double Point[3], double *Bfield)const
{

  //Point[3]
  Bfield[0] = 0;
  Bfield[1] = 0;
  Bfield[2] = 0;
  int Xflag = 1;
  int Yflag = 1;
  int Zflag = 1;

  double scale = paramMan->GetFieldScale();
  
  G4ThreeVector pos(Point[0],Point[1],Point[2]);

  //xt,yt,zt coordinate should be same with magnetic field map coordinate (global)
  double xt = pos.x() / cm;
  double yt = pos.y() / cm;
  double zt = pos.z() / cm;
  
  //G4cout<<xt<<" "<<yt<<" "<<zt<<" "<<X0<<" "<<Y0<<" "<<Z0<<" "<<dX<<" "<<dY<<" "<<dZ<<G4endl;

  if( yt<0 ){
    yt    *= -1;
    Xflag *= -1;
    Zflag *= -1;
  }
  
  int ix1, iy1, iz1, ix2, iy2, iz2;
//  ix1 = int((xt-X0+0.5*dX)/dX-1);
//  iy1 = int((yt-Y0+0.5*dY)/dY-1);
//  iz1 = int((zt-Z0+0.5*dZ)/dZ-1);
  ix1 = int( floor( (xt-X0)/dX ) );
  iy1 = int( floor( (yt-Y0)/dY ) );
  iz1 = int( floor( (zt-Z0)/dZ ) );
  //  G4cout<<ix1<<" "<<iy1<<" "<<iz1<<G4endl;

  double wx1, wy1, wz1, wx2, wy2, wz2;

  if(ix1>=0 && iy1>=0 && iz1>=0 && ix1<Nx-1 && iy1<Ny-1 && iz1<Nz-1){
    ix2 = ix1 + 1;  wx1 = (X0+dX*ix2-xt)/dX;  wx2 = 1. - wx1;
    iy2 = iy1 + 1;  wy1 = (Y0+dY*iy2-yt)/dY;  wy2 = 1. - wy1;
    iz2 = iz1 + 1;  wz1 = (Z0+dZ*iz2-zt)/dZ;  wz2 = 1. - wz1;
    double bx1=wx1*wy1*B[ix1][iy1][iz1].x+wx1*wy2*B[ix1][iy2][iz1].x
      +wx2*wy1*B[ix2][iy1][iz1].x+wx2*wy2*B[ix2][iy2][iz1].x;
    double bx2=wx1*wy1*B[ix1][iy1][iz2].x+wx1*wy2*B[ix1][iy2][iz2].x
      +wx2*wy1*B[ix2][iy1][iz2].x+wx2*wy2*B[ix2][iy2][iz2].x;
    double bx=wz1*bx1+wz2*bx2;
    double by1=wx1*wy1*B[ix1][iy1][iz1].y+wx1*wy2*B[ix1][iy2][iz1].y
      +wx2*wy1*B[ix2][iy1][iz1].y+wx2*wy2*B[ix2][iy2][iz1].y;
    double by2=wx1*wy1*B[ix1][iy1][iz2].y+wx1*wy2*B[ix1][iy2][iz2].y
      +wx2*wy1*B[ix2][iy1][iz2].y+wx2*wy2*B[ix2][iy2][iz2].y;
    double by=wz1*by1+wz2*by2;
    double bz1=wx1*wy1*B[ix1][iy1][iz1].z+wx1*wy2*B[ix1][iy2][iz1].z
      +wx2*wy1*B[ix2][iy1][iz1].z+wx2*wy2*B[ix2][iy2][iz1].z;
    double bz2=wx1*wy1*B[ix1][iy1][iz2].z+wx1*wy2*B[ix1][iy2][iz2].z
      +wx2*wy1*B[ix2][iy1][iz2].z+wx2*wy2*B[ix2][iy2][iz2].z;
    double bz=wz1*bz1+wz2*bz2;

    Bfield[0] = Xflag*bx*scale * gauss;//
    Bfield[1] = Yflag*by*scale * gauss;
    Bfield[2] = Zflag*bz*scale * gauss;
      
//    G4cout <<"Magnetic: "<<ix1<<" "<<iy1<<" "<<iz1<<" "<<Point[0]<<" "<<Point[1]<<" "<<Point[2]<<" "<<Bfield[0]<<" "<<Bfield[1]<<" "<<Bfield[2]<<G4endl;
  }
//  else{
//    G4cout <<"None: "<<ix1<<" "<<iy1<<" "<<iz1<<" "<<Point[0]<<" "<<Point[1]<<" "<<Point[2]<<" "<<Bfield[0]<<" "<<Bfield[1]<<" "<<Bfield[2]<<G4endl;
//  }
//  G4cout <<ix1<<" "<<iy1<<" "<<iz1<<" "<<" "<<Bfield[0]<<" "<<Bfield[1]<<" "<<Bfield[2]<<G4endl;
//  G4cout <<"Magnetic: "<<ix1<<" "<<iy1<<" "<<iz1<<" "<<xt<<" "<<yt<<" "<<zt<<" "<<Bfield[0]<<" "<<Bfield[1]<<" "<<Bfield[2]<<G4endl;

}

void MagField::cleanmap()
{
  for( int ix=0; ix<Nx; ++ix ){
    for( int iy=0; iy<Ny; ++iy ){
      B[ix][iy].clear();
    }
    B[ix].clear();
  }
  B.clear();
}

