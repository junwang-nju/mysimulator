
#ifndef _PDB_Atom_Position_H_
#define _PDB_Atom_Position_H_

#include "array/interface.h"

namespace mysimulator {

  class __PDB_AtomPosition {

    public:

      typedef __PDB_AtomPosition  Type;

    private:

      Array<Float,ArrayKernelName::Direct3D>  _Pos;

    public:

      __PDB_AtomPosition() : _Pos() {}
      __PDB_AtomPosition(const Type& P) : _Pos(P._Pos) {}
      __PDB_AtomPosition(Type&& P) : __PDB_AtomPosition() { swap(P); }
      ~__PDB_AtomPosition() { reset(); }

      operator bool() const { return (bool)_Pos; }
      float& X() { assert((bool)_Pos); return _Pos[0]; }
      float& Y() { assert((bool)_Pos); return _Pos[1]; }
      float& Z() { assert((bool)_Pos); return _Pos[2]; }
      float X() const { assert((bool)_Pos); return _Pos[0]; }
      float Y() const { assert((bool)_Pos); return _Pos[1]; }
      float Z() const { assert((bool)_Pos); return _Pos[2]; }
      void reset() { _Pos.reset(); }

      Type& operator=(const Type& P) { _Pos=P._Pos; return *this; }
      template <typename T,ArrayKernelName K>
      Type& operator=(const Array<T,K>& A) { _Pos=A; return *this; }

      void allocate() { _Pos.allocate(); }
      void imprint(const Type&) { allocate(); }

      void swap(Type& P) { std::swap(_Pos,P._Pos); }

  };

  void __imprint(__PDB_AtomPosition& P, const __PDB_AtomPosition& IP) {
    P.imprint(IP);
  }

}

namespace std {

  void swap(mysimulator::__PDB_AtomPosition& P1,
            mysimulator::__PDB_AtomPosition& P2) { P1.swap(P2); }

}

#endif

