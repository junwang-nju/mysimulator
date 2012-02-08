
#ifndef _PDB_Property_Atom_Interface_H_
#define _PDB_Property_Atom_Interface_H_

#include "object/interface.h"
#include "pdb/property/atom/position/interface.h"

namespace mysimulator {

  struct PDBAtom {

    public:

      typedef PDBAtom   Type;

      Object<PDBResidue> Residue;
      PDBAtomName AtomType;
      PDBAtomPosition Position;
      Array1D<PDBAtomPosition>  altPosition;

      PDBAtom() : Residue(), AtomType(UnknownAtom), Position(),
                  altPosition() {}
      ~PDBAtom() { clearData(); }

      void clearData() {
        release(altPosition); release(Position);  AtomType=UnknownAtom;
        release(Residue);
      }
      bool isvalid() const {
        return IsValid(Residue)&&(AtomType!=UnknownAtom)&&
               IsValid(Position)&&IsValid(altPosition);
      }

    private:

      PDBAtom(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(PDBAtom& A) { A.clearData(); }
  bool IsValid(const PDBAtom& A) { return A.isvalid(); }

}

#endif

