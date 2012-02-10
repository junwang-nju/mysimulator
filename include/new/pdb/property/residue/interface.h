
#ifndef _PDB_Property_Residue_Interface_H_
#define _PDB_Property_Residue_Interface_H_

#include "pdb/property/residue/name.h"
#include "pdb/property/atom/interface.h"

namespace mysimulator {

  struct PDBResidue {

    public:

      typedef PDBResidue  Type;

      PDBResidueName ResidueType;
      unsigned int ResidueID;
      Array1D<PDBAtom>  Atoms;

      PDBResidue() : ResidueType(UnknownResidue), ResidueID(0), Atoms() {}
      ~PDBResidue() { clearData(); }

      void clearData() {
        release(Atoms); ResidueType=UnknownResidue; ResidueID=0;
      }
      bool isvalid() const { return IsValid(Atoms); }

    private:

      PDBResidue(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(PDBResidue& R) { R.clearData(); }
  bool IsValid(const PDBResidue& R) { return R.isvalid(); }

}

#endif

