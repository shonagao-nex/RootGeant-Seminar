#include "MaterialList.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

MaterialList *MaterialList::thisPointer=NULL;

MaterialList::MaterialList()
{
  G4NistManager *nist = G4NistManager::Instance();

  G4double a, iz, z, density;
  G4String name, symbol;
  G4int nel, nAtoms;
//  G4double fractionMass;

  // Nist Material //
  nist->FindOrBuildMaterial("G4_Galactic");
  nist->FindOrBuildMaterial("G4_AIR");
  nist->FindOrBuildMaterial("G4_Li");
  nist->FindOrBuildMaterial("G4_Be");
  nist->FindOrBuildMaterial("G4_B");
  nist->FindOrBuildMaterial("G4_C");
  nist->FindOrBuildMaterial("G4_Al");
  nist->FindOrBuildMaterial("G4_Ca");
  nist->FindOrBuildMaterial("G4_Fe");
  nist->FindOrBuildMaterial("G4_Pb");
  nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  nist->FindOrBuildMaterial("G4_lH2");

  Vacuum = G4Material::GetMaterial("G4_Galactic");
  Air    = G4Material::GetMaterial("G4_AIR");
  Li     = G4Material::GetMaterial("G4_Li");
  Be     = G4Material::GetMaterial("G4_Be");
  B      = G4Material::GetMaterial("G4_B");
  C      = G4Material::GetMaterial("G4_C");
  Al     = G4Material::GetMaterial("G4_Al");
  Ca     = G4Material::GetMaterial("G4_Ca");
  Fe     = G4Material::GetMaterial("G4_Fe");
  Pb     = G4Material::GetMaterial("G4_Pb");
  Scinti = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  LiqH   = G4Material::GetMaterial("G4_lH2");

  //=== Elements ===//
  name = "Hydrogen"; symbol = "H";
  a = 1.00794*CLHEP::gram/mole;
  elH = new G4Element( name, symbol, iz=1., a);

  name = "Carbon"; symbol = "C";
  a = 12.011*CLHEP::gram/mole;
  elC = new G4Element( name, symbol, iz=6., a);

  //=== Simple Materials ==//
  name = "Argon Gas";
  a = 39.948*g/mole;
  density = 0.001782*g/cm3;
  ArGas = new G4Material( name, z=18., a, density );

  name = "Nitrogen Gas";
  a = 28.01*g/mole;
  density = 1.251*mg/cm3;
  N2Gas = new G4Material( name, z=14., a, density );

  name = "Oxygen Gas";
  a = 32.00*g/mole;
  density = 1.429*mg/cm3;
  O2Gas = new G4Material( name, z=16., a, density );

  //=== Componds Materials ===//
  name = "MyLiqHydrogen";
  density = 1.0*g/cm3;
  MyLiqH = new G4Material( name, density, nel=1);
  MyLiqH->AddElement(elH, nAtoms=1);

  name = "Graphite";
  density = 1.8*g/cm3;
  Graphite = new G4Material( name, density, nel=1);
  Graphite->AddElement(elC, nAtoms=1);

//  name = "Scintillator";
//  density = 1.032*g/cm3;
//  Scinti = new G4Material( name, density, nel=2);
//  Scinti->AddElement(nist->FindOrBuildElement("G4_H"), nAtoms=8);
//  Scinti->AddElement(nist->FindOrBuildElement("G4_C"), nAtoms=8);
//
//  name = "Aerogel";
//  density = 0.06*g/cm3;
//  AC = new G4Material( name, density, nel=2);
//  AC->AddElement(nist->FindOrBuildElement("G4_Si"), nAtoms=1);
//  AC->AddElement(nist->FindOrBuildElement("G4_O"),  nAtoms=2);
//
//  name = "Pet";
//  density = 1.3*g/cm3;
//  Pet = new G4Material( name, density, nel=3);
//  Pet->AddElement(nist->FindOrBuildElement("G4_H"), nAtoms=8);
//  Pet->AddElement(nist->FindOrBuildElement("G4_C"), nAtoms=10);
//  Pet->AddElement(nist->FindOrBuildElement("G4_O"), nAtoms=4);
//
//  name = "Acrylic";
//  density = 1.19*g/cm3;
//  Acrylic = new G4Material( name, density, nel=3);
//  Acrylic->AddElement(nist->FindOrBuildElement("G4_H"), nAtoms=8);
//  Acrylic->AddElement(nist->FindOrBuildElement("G4_C"), nAtoms=5);
//  Acrylic->AddElement(nist->FindOrBuildElement("G4_O"), nAtoms=2);
//
//  name = "CarbonDioxide";
//  density = 1.977*g/cm3;
//  CO2 = new G4Material( name, density, nel=2);
//  CO2->AddElement(nist->FindOrBuildElement("G4_C"), nAtoms=1);
//  CO2->AddElement(nist->FindOrBuildElement("G4_O"), nAtoms=2);
//
//  name = "Isobutane";
//  density = 2.673*g/cm3;
//  C4H10 = new G4Material( name, density, nel=2);
//  C4H10->AddElement(nist->FindOrBuildElement("G4_C"), nAtoms=4);
//  C4H10->AddElement(nist->FindOrBuildElement("G4_H"), nAtoms=10);
//
//  name = "DCGas";
//  density = (0.84*39.948+0.09*1.977*22.3+0.07*2.673*22.3)/22.3*mg/cm3;
//  DCGas = new G4Material( name, density, nel=3);
//  fractionMass = 0.84*39.948/(0.84*39.948+0.09*1.977*22.3+0.07*2.673*22.3);
//  DCGas->AddMaterial(ArGas, fractionMass);
//  fractionMass = 0.09*1.977*22.3/(0.84*39.948+0.09*1.977*22.3+0.07*2.673*22.3);
//  DCGas->AddMaterial(CO2, fractionMass);
//  fractionMass = 0.07*2.673*22.3/(0.84*39.948+0.09*1.977*22.3+0.07*2.673*22.3);
//  DCGas->AddMaterial(C4H10, fractionMass);
//
//  name = "Heavy Metal";
//  density = 16.9*g/cm3;
//  Heavymet = new G4Material( name, density, nel=3 );
//  Heavymet->AddElement(nist->FindOrBuildElement("G4_W") , .9 );
//  Heavymet->AddElement(nist->FindOrBuildElement("G4_Ni"), .06 );
//  Heavymet->AddElement(nist->FindOrBuildElement("G4_Cu"), .04 );

}

// MaterialList::~MaterialList()
//{
//   delete Heavymet;
//   delete DCGas;
//   delete Vacuum;
//
//   delete BaSO4;
//   delete C4H10;
//   delete CO2;
//   delete CH2;
//   delete CH4;
//   delete C2H6;
//   delete Pet;
//   delete Acrylic;
//   delete AC;
//   delete Scinti;
//
//   delete ArGas;
//   delete N2Gas;
//   delete O2Gas;
//   delete SiO2;
//   delete Graphite;
//
//   delete elH;
//   delete elC;
//   delete elN;
//   delete elO;
//   delete elSi;
//   delete elAr;
//   delete elNi;
//   delete elCu;
//   delete elW;
//   delete elAu;
//   delete elS;
//   delete elBa;
//}

