
#ifndef _PDB_Atom_Position_Copy_H_
#define _PDB_Atom_Position_Copy_H_

#include "pdb/atom/position/interface.h"

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
    assert(IsValid(A));
    P.X=A[0];
    P.Y=A[1];
    P.Z=A[2];
  }

  template <typename T>
  void _copy(Array1DContent<T>& A, const PDBAtomPosition& cP) {
    assert(IsValid(A));
    A[0]=cP.X;
    A[1]=cP.Y;
    A[2]=cP.Z;
  }

}

#if defined(_COPYTO) or defined(_COPYFROM)
#error _COPY not UN-defined, ERROR may occur.
#endif
#define _COPYTO(type) \
  void copy(PDBAtomPosition& P, const Array1DContent<type>& A) { _copy(P,A); }
#define _COPYFROM(type) \
  void copy(Array1DContent<type>& A, const PDBAtomPosition& cP) { _copy(A,cP); }

namespace mysimulator {

  _COPYTO(double)
  _COPYTO(float)
  _COPYFROM(double)
  _COPYFROM(float)

}

#undef _COPYFROM
#undef _COPYTO

#endif

