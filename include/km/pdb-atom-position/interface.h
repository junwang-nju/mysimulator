
#ifndef _PDB_Atom_Position_Interface_H_
#define _PDB_Atom_Position_Interface_H_

#include "array/data/interface.h"

namespace mysimulator {

  class PDBAtomPosition {

    public:

      typedef PDBAtomPosition Type;
      friend void Clear(PDBAtomPosition&);

      PDBAtomPosition() : _X(0), _Y(0), _Z(0) {}
      ~PDBAtomPosition() { Clear(*this); }

      bool IsValid() const { return true; }
      void Copy(PDBAtomPosition& P) { _X=P._X; _Y=P._Y; _Z=P._Z; }
      template <typename T>
      void Copy(ArrayData<T>& A) {
        typedef typename IsFloatPoint<T>::Type  FloatPointCheck;
        assert(A.IsValid()); _X=A[0]; _Y=A[1]; _Z=A[2];
      }

      double& X() { return _X; }
      double& Y() { return _Y; }
      double& Z() { return _Z; }
      const double& X() const { return _X; }
      const double& Y() const { return _Y; }
      const double& Z() const { return _Z; }

      void Allocate() { Clear(*this); }

    protected:

      double _X,_Y,_Z;

    private:

      PDBAtomPosition(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBAtomPosition& P) { P._X=P._Y=P._Z=0.; }
  void _Copy(PDBAtomPosition& P,const PDBAtomPosition& BP) { P.Copy(BP); }
  template <typename T>
  void _Copy(PDBAtomPosition& P,const ArrayData<T>& A) { P.Copy(A); }

}

#endif

