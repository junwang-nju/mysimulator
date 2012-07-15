
#ifndef _PDB_Alternative_Residue_Interface_H_
#define _PDB_Alternative_Residue_Interface_H_

#include "pdb-residue/interface.h"

namespace mysimulator {

  class PDBAltResidue {

    public:

      typedef PDBAltResidue Type;
      friend void Clear(PDBAltResidue&);
      friend class PDBFile;

      PDBAltResidue() : _AResidue() {}
      ~PDBAltResidue() { Clear(*this); }

      bool IsValid() const { return _AResidue.IsValid(); }
      void Allocate(unsigned int n) { Clear(*this); _AResidue.Allocate(n); }

      PDBResidue& WorkResidue(unsigned int i) {
        if(i>=_AResidue.Size())
          fprintf(stderr,"NO this AltLoc! Using Default\n");
        const unsigned int m=(i>=_AResidue.Size()?0:i);
        return _AResidue[m];
      }
      const PDBResidue& WorkResidue(unsigned int i) const {
        if(i>=_AResidue.Size())
          fprintf(stderr,"NO this AltLoc! Using Default\n");
        const unsigned int m=(i>=_AResidue.Size()?0:i);
        return _AResidue[m];
      }

      const unsigned int NumberAltLoc() const { return _AResidue.Size(); }

    protected:

      Array<PDBResidue> _AResidue;

    private:

      PDBAltResidue(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBAltResidue& R) { Clear(R._AResidue); }

}

#endif

