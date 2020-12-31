#ifndef ParamManager_h
#define ParamManager_h 1

#include "globals.hh"
#include <fstream>

#include "G4ThreeVector.hh"

class ParamManager
{
public:
  ParamManager(G4String runnum);
  ParamManager(G4String runnum, G4String infilename);

private:
  static ParamManager *thisPointer;

  bool ReadParam( void );

private:
  G4String ifname;
  G4String ofname;
  G4String runID;
  // Generate
  G4String bpar;
  G4int    btype;
  G4double bmom, bmomr;
  G4double bx, by, bz, bxr, byr, bzr;
  G4double bt, bp, btr, bpr;
  // Target
  double tthick;
  // Physics
  int decay;

public:
  static ParamManager *GetParam(){ return thisPointer; }

  G4String GetOutputFile()        { return ofname;  }
  G4String GetBeamParticle()      { return bpar;    }
  G4int    GetBeamType()          { return btype;   }
  G4double GetBeamMom()           { return bmom;    }
  G4double GetBeamMomRange()      { return bmomr;   }
  G4double GetBeamX()             { return bx;      }
  G4double GetBeamXRange()        { return bxr;     }
  G4double GetBeamY()             { return by;      }
  G4double GetBeamYRange()        { return byr;     }
  G4double GetBeamZ()             { return bz;      }
  G4double GetBeamZRange()        { return bzr;     }
  G4double GetBeamTheta()         { return bt;      }
  G4double GetBeamThetaRange()    { return btr;     }
  G4double GetBeamPhi()           { return bp;      }
  G4double GetBeamPhiRange()      { return bpr;     }

  G4double GetTargetThick()       { return tthick;  }

  G4int GetDecayFlag()            { return decay;   }

};

#endif
