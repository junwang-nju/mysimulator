
#ifndef _PDB_Property_Atom_Interface_H_
#define _PDB_Property_Atom_Interface_H_

#include "object/interface.h"
#include "pdb/property/atom/position/interface.h"
#include "pdb/property/atom/name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  struct PDBResidue;

  struct PDBAtom {

    public:

      typedef PDBAtom   Type;

      Object<PDBResidue> Residue;
      PDBAtomName AtomType;
      unsigned int AtomID;
      double BFactor;
      PDBAtomPosition Position;
      Array1D<PDBAtomPosition>  altPosition;

      PDBAtom() : Residue(), AtomType(UnknownAtom), AtomID(0), BFactor(0),
                  Position(), altPosition() {}
      ~PDBAtom() { clearData(); }

      void clearData() {
        release(altPosition); release(Position);  AtomType=UnknownAtom;
        release(Residue); AtomID=0; BFactor=0;
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

