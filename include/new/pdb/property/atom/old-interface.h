
#ifndef _PDB_Property_Atom_Interface_H_
#define _PDB_Property_Atom_Interface_H_

#include "array/1d/interface.h"
#include "pdb/property/atom/name.h"
#include "pdb/property/residue/name.h"

namespace mysimulator {

  struct PDBAtom {

    public:

      typedef PDBAtom   Type;

      Array1D<Array1D<double> > Positions;
      Array1D<double> BFactors;
      Array1D<PDBAtomName> AtomTypes;
      Array1D<PDBResidueName> ResidueTypes;
      Array1D<unsigned int> ResidueID;
      Array1D<char> ChainID;

      PDBAtom() : Positions(), BFactors(), AtomTypes(), ResidueTypes(),
                  ResidueID(), ChainID() {}
      ~PDBAtom() { clearData(); }

      void clearData() {
        release(ChainID); release(ResidueID); release(ResidueType);
        release(AtomTypes); release(BFactors);  release(Positions);
      }
      bool isvalid() {
        return IsValid(Positions)&&IsValid(BFactors)&&IsValid(AtomTypes)&&
               IsValid(ResidueType)&&IsValid(ResidueID)&&IsValid(Positions);
      }

    private:

      PDBAtom(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(PDBAtom& A) { A.clearData(); }
  bool IsValid(const PDBAtom& A) const { return A.isvalid(); }

}

#endif

