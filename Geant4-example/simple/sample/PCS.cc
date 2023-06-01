#include "PCS.hh"
#include "PCSFieldMan.hh"

#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4DisplacedSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "HKSParamMan.hh"
#include <cmath>
#include <TMath.h>
#include <TString.h>

//For GDML
#include "G4GDMLParser.hh"
#include "G03ColorReader.hh"

/////////////////////////////////////////////////////
PCS::PCS( const G4String &name,
                  const G4ThreeVector &gPos,
                  const G4RotationMatrix *rotMtx,
                  const std::string deffilename)
  : BeamLineElement( name, gPos, rotMtx ), solidField(0), fMan(deffilename)
/////////////////////////////////////////////////////
{
  fMan.Initialize();
  HKSParamMan *paramMan = HKSParamMan::GetParamMan();
  Scale = paramMan->GetPCSScaleFactor();
  Scale = 1.;

  fReadFile = "./param/SM1.gdml";
  fReader = new G03ColorReader;
  fParser = new G4GDMLParser(fReader);
  
}

/////////////////////
PCS::~PCS()
/////////////////////
{
  delete fReader;
  delete fParser;
}

////////////////////////////////////////////////
bool PCS::ExistMagneticField( void ) const
////////////////////////////////////////////////
{
  return true;
}

///////////////////////////////////////////////////////////
bool PCS::IsInside( const G4ThreeVector &gPos ) const
///////////////////////////////////////////////////////////
{
  G4ThreeVector lPos = GetLocalPosition(gPos);    
    
  if( lPos.x() >= -50.*cm && lPos.x() <= 50.*cm &&
      lPos.y() >= -20.*cm && lPos.y() <= 20.*cm &&
      lPos.z() >= -50.*cm && lPos.z() <= 110.*cm ){
      return true;
    } else { return false; }
}

////////////////////////////////////////////////////
G4ThreeVector PCS::GetMagneticField( const G4ThreeVector &gPos ) const
////////////////////////////////////////////////////
{
  if( IsInside(gPos) ){
    G4ThreeVector lPos = GetLocalPosition( gPos );
    return GetGlobalDirection( Field(lPos) );
  } else { return G4ThreeVector(); }
}

////////////////////////////////////////////////////////////////
G4ThreeVector PCS::Field( const G4ThreeVector &pos) const
////////////////////////////////////////////////////////////////
{ 
  double X[3];
  double Bfield[3];
  int Xflag = 1;
  int Yflag = 1;
  int Zflag = 1;
  X[0] = pos.x() / cm;
  X[1] = pos.y() / cm;
  X[2] = pos.z() / cm;

  if( fMan.GetFieldValue(X, Bfield) ){
    Bfield[0] *= Xflag*Scale;
    Bfield[1] *= Yflag*Scale;
    Bfield[2] *= Zflag*Scale;
  }
  else{
    Bfield[0] = Bfield[1] = Bfield[2] = 0;
  }

  G4ThreeVector B( Bfield[0]*gauss, Bfield[1]*gauss, Bfield[2]*gauss ); 

  return B;
}

////////////////////////////////////////////////////////////////
G4VPhysicalVolume *PCS::Place( G4VPhysicalVolume *pMother )
////////////////////////////////////////////////////////////////
{
  const int PCSNo = 1;
  G4cout << G4endl << "**** PCS::GDMLPlace()..... ****" << G4endl;

// Read GDML file
  fParser->Read(fReadFile, false);

  G4VPhysicalVolume *PCSPV = fParser->GetWorldVolume();
  G4String fPCSName = PCSPV->GetName();
  G4LogicalVolume *PCSLV = PCSPV->GetLogicalVolume();
  G4int daughters = PCSLV->GetNoDaughters();

  G4cout << fReadFile << G4endl;
  G4cout << "Numer of daughters: " << daughters << G4endl;

// Devide assemble to each part
  G4VPhysicalVolume *daughter[PCSNo];
  G4LogicalVolume *LV_tmp[PCSNo];
  G4VSolid *solidDaughter[PCSNo];
  for( G4int i = 0; i < daughters; i++ ){
    daughter[i] = PCSLV->GetDaughter(i);
    LV_tmp[i] = daughter[i]->GetLogicalVolume();
    solidDaughter[i] = daughter[i]->GetLogicalVolume()->GetSolid();
  }

// Translate eack part and generate assembly
  G4ThreeVector posRef_[PCSNo];
  G4DisplacedSolid *postsolidDaughter[PCSNo];
  for( G4int i = 0; i < daughters; i++ ){
    posRef_[i] = daughter[i]->GetTranslation();
    postsolidDaughter[i] = new G4DisplacedSolid(Form("postsolidDaughter[%d]",i), solidDaughter[i],0,posRef_[i]);
  }

// Define logical volumes
  G4LogicalVolume *daughterLV[PCSNo];
  for( G4int i = 0; i < daughters; i++ ){
    daughterLV[i] = new G4LogicalVolume(postsolidDaughter[i], mYoke_, Form("postsolidDaughter[%d]", i));
    daughterLV[i]->SetMaterial(mYoke_);
  }

  ///////////////////////////////////////////////
  // Define physical volumes
  ///////////////////////////////////////////////
  G4VPhysicalVolume *PCSMag;
  G4VPhysicalVolume *daughterPV[PCSNo];
  daughterPV[0] = 0;
  for( G4int i = 0; i < daughters; i++ ){
    if( i == 0 ){
      PCSMag = new G4PVPlacement(&rotMtx_, gPos_, elemName_, daughterLV[0], pMother, false, 0);
    } else {
      daughterPV[i] = new G4PVPlacement(&rotMtx_, gPos_, elemName_, daughterLV[i], pMother, false, 0);
    }
  }

// Visualisation
  G4Colour colour(1., 0., 0.);
  G4VisAttributes *VisAtt = new G4VisAttributes(true, colour);

  for( G4int i = 0; i < daughters; i++ ){
    daughterLV[i]->SetVisAttributes(VisAtt);
  }

  return PCSMag;
}

//////////////////////////////////////////////////////
void PCS::SetUserLimits( G4UserLimits *limitYoke, G4UserLimits *limitGap )
//////////////////////////////////////////////////////
{
  if( yokeLog_ ) yokeLog_-> SetUserLimits(limitYoke);
  if( gapLog_ && limitGap )
    gapLog_-> SetUserLimits(limitGap);
}
