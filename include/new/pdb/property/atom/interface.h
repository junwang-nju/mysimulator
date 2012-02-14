
#ifndef _PDB_Property_Atom_Interface_H_
#define _PDB_Property_Atom_Interface_H_

#include "object/interface.h"
#include "pdb/property/atom/position/interface.h"
#include "pdb/property/atom/name.h"
#include "pdb/property/residue/interface.h"
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
      char LocFlag;
      Array1D<char> altLocFlag;

      PDBAtom() : Residue(), AtomType(UnknownAtom), AtomID(0), BFactor(0),
                  Position(), altPosition(), LocFlag('\0'), altLocFlag() {}
      ~PDBAtom() { clearData(); }

      void clearData() {
        release(altPosition); release(Position);  AtomType=UnknownAtom;
        release(Residue); AtomID=0; BFactor=0; LocFlag='\0';
        release(altLocFlag);
      }
      bool isvalid() const {
        return IsValid(Residue)&&(AtomType!=UnknownAtom)&&
               IsValid(Position)&&IsValid(altPosition)&&(LocFlag!='\0')&&
               IsValid(altLocFlag);
      }

    private:

      PDBAtom(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(PDBAtom& A) { A.clearData(); }
  bool IsValid(const PDBAtom& A) { return A.isvalid(); }

}

#endif

