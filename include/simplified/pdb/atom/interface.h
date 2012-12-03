
#ifndef _PDB_Atom_Interface_H_
#define _PDB_Atom_Interface_H_

#include "pdb/atom/name.h"
#include "pdb/atom-position/interface.h"

namespace mysimulator {

  class __PDB_Atom {

    public:

      typedef __PDB_Atom  Type;

    private:

      PDBAtomName _tag;
      __PDB_AtomPosition  _loc;
      double _bfac;

    public:

      __PDB_Atom() : _tag(PDBAtomName::Unknown), _loc(), _bfac(0.0) {}
      __PDB_Atom(const Type& A) : __PDB_Atom() { imprint(A); operator=(A); }
      __PDB_Atom(Type&& A) : __PDB_Atom() { swap(A); }
      ~__PDB_Atom() { reset(); }

      operator bool() const {
        return _tag!=PDBAtomName::Unknown && (bool)_loc;
      }
      PDBAtomName Name() const { return _tag; }
      double& X() { return _loc.X(); }
      double& Y() { return _loc.Y(); }
      double& Z() { return _loc.Z(); }
      double X() const { return _loc.X(); }
      double Y() const { return _loc.Y(); }
      double Z() const { return _loc.Z(); }
      double& BFactor() { return _bfac; }
      double BFactor() const { return _bfac; }
      void reset() {
        _tag=PDBAtomName::Unknown; _loc.reset(); _bfac=0.0;
      }

      Type& operator=(const Type& A) {
        _tag=A._tag;
        _loc=A._loc;
        _bfac=A._bfac;
        return *this;
      }

      void allocate(PDBAtomName AN) { reset(); _tag=AN; _loc.allocate(); }
      void imprint(const Type&) { allocate(); }

      void swap(__PDB_Atom& A) {
        std::swap(_tag,A._tag);
        std::swap(_loc,A._loc);
        std::swap(_bfac,A._bfac);
      }

  };

  void __imprint(__PDB_Atom& A, const __PDB_Atom& IA) { A.imprint(IA); }

}

namespace mysimulator {

  void swap(mysimulator::__PDB_Atom& A1, mysimulator::__PDB_Atom& A2) {
    A1.swap(A2);
  }

}

#endif

