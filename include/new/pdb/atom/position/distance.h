
#ifndef _PDB_Atom_Position_Distance_H_
#define _PDB_Atom_Position_Distance_H_

#include "pdb/atom/position/interface.h"

namespace mysimulator {

  double DistanceSQ(const PDBAtomPosition& P1, const PDBAtomPosition& P2) {
    double X,Y,Z;
    X=P1.X-P2.X;
    Y=P1.Y-P2.Y;
    Z=P1.Z-P2.Z;
    return X*X+Y*Y+Z*Z;
  }

}

#include "intrinsic-type/square-root.h"

namespace mysimulator {

  double Distance(const PDBAtomPosition& P1, const PDBAtomPosition& P2) {
    return sqroot(DistanceSQ(P1,P2));
  }

}

#endif

