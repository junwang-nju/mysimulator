
#ifndef _PDB_Property_Atom_Position_Copy_H_
#define _PDB_Property_Atom_Position_Copy_H_

#include "pdb/property/atom/position/interface.h"

namespace mysimulator {

  void copy(PDBAtomPosition& P, const PDBAtomPosition& cP) {
    P.X=cP.X;
    P.Y=cP.Y;
    P.Z=cP.Z;
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void _copy(PDBAtomPosition& P, const Array1DContent<T>& A) {
    assert(A.size>=3);
    P.X=A[0];
    P.Y=A[1];
    P.Z=A[2];
  }

  template <typename T>
  void _copy(Array1D<T>& A, const PDBAtomPosition& P) {
    assert(A.size>=3);
    A[0]=P.X;
    A[1]=P.Y;
    A[2]=P.Z;
  }

  void copy(PDBAtomPosition& P, const Array1D<double>& A) { _copy(P,A); }
  void copy(PDBAtomPosition& P, const Array1D<float>& A) { _copy(P,A); }
  void copy(Array1D<double>& A, const PDBAtomPosition& P) { _copy(A,P); }
  void copy(Array1D<float>& A, const PDBAtomPosition& P) { _copy(A,P); }

}

#endif

