
#ifndef _PDB_Atom_Position_InputOutput_H_
#define _PDB_Atom_Position_InputOutput_H_

#include "pdb/atom/position/interface.h"
#include "io/output/base/interface.h"

namespace mysimulator {

  OutputBase& operator<<(OutputBase& OS, const PDBAtomPosition& P) {
    assert(IsValid(OS)&&IsValid(P));
    OS<<P.X<<"\t"<<P.Y<<"\t"<<P.Z;
    return OS;
  }

}

#endif

