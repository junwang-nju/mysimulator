
#ifndef _PDB_Residue_Interface_H_
#define _PDB_Residue_Interface_H_

#include "pdb/residue/name.h"
#include "pdb/atom/interface.h"

namespace mysimulator {

  struct PDBResidue {

    public:

      typedef PDBResidue    Type;

      Array1D<PDBAtom>  Atom;
      PDBResidueName    Name;
      int               ID;

      PDBResidue() : Atom(), Name(UnknownResidue), ID(-1) {}
      ~PDBResidue() { clearData(); }

      void clearData() { ID=-1; Name=UnknownResidue; release(Atom); }
      bool isvalid() const {
        return IsValid(Atom)&&(Name!=UnknownResidue)&&(ID!=-1);
      }

    private:

      PDBResidue(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(PDBResidue& R) { R.clearData(); }
  bool IsValid(const PDBResidue& R) { return R.isvalid(); }

}

#endif

