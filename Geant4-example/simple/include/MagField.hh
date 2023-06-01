#ifndef MagField_h
#define MagField_h 1

#include "G4MagneticField.hh"
#include "ParamManager.hh"

#include <string>
#include <vector>

class MagField: public G4MagneticField
{
  public :
  MagField();
  ~MagField();

  virtual void GetFieldValue (const double Point[3], double *Bfield) const;

  private :
  struct cont {
    float x, y, z;
  };
  typedef std::vector < std::vector < std::vector < cont > > > contB;
  contB B;

  double x, y, z;
  double X0, Y0, Z0;
  double dX, dY, dZ;
  int Nx, Ny, Nz;

  ParamManager *paramMan;

  void cleanmap();
};
#endif



