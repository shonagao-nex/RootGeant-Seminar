#ifndef MaterialList_h
#define MaterialList_h 1

#include "G4Element.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"

class MaterialList
{
public:
  MaterialList();
  ~MaterialList();

// G4NistMaterial
  G4Material *Vacuum;
  G4Material *Air;
  G4Material *Li;
  G4Material *Be;
  G4Material *B;
  G4Material *C;
  G4Material *Al;
  G4Material *Ca;
  G4Material *Fe;
  G4Material *Pb;
  G4Material *Scinti;
  G4Material *LiqH;

  G4Element *elH;
  G4Element *elC;

  G4Material *HeGas;
  G4Material *ArGas;
  G4Material *N2Gas;
  G4Material *O2Gas;

//  G4Material *Scinti;
  G4Material *MyLiqH;
  G4Material *Graphite;

private:
//  MaterialList();
  MaterialList( const MaterialList & );
  MaterialList & operator = ( const MaterialList & );

  static MaterialList *thisPointer;

public:
  static MaterialList *GetInstance(){
    if( thisPointer==NULL ) thisPointer = new MaterialList();
    return thisPointer;
  }
};

#endif

