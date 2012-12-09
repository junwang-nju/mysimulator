
#ifndef _PDB_Molecule_Interface_H_
#define _PDB_Molecule_Interface_H_

#include "pdb/residue-with-alt/interface.h"

namespace mysimulator {

  class __PDB_Molecule : public Array<__PDB_Residue_wAlt> {

    public:

      typedef __PDB_Molecule                    Type;
      typedef Array<__PDB_Residue_wAlt>   ParentType;

    private:

      int _tag;

    public:

      __PDB_Molecule() : ParentType(), _tag(-1) {}
      __PDB_Molecule(const Type& M)
        : ParentType((ParentType const&)M), _tag(M._tag) {}
      __PDB_Molecule(Type&& M) : __PDB_Molecule() { swap(M); }
      ~__PDB_Molecule() { reset(); }

      operator bool() const { return ParentType::operator bool() && _tag>-1; }
      unsigned int Tag() const { assert(_tag>-1); return _tag; }
      unsigned int NumberResidue() const { return ParentType::size(); }
      __PDB_Residue& Residue(unsigned int i,unsigned int alt=0) {
        return ParentType::operator[](i)[alt];
      }
      __PDB_Residue const& Residue(unsigned int i,unsigned int alt=0) const {
        return ParentType::operator[](i)[alt];
      }
      void reset() { ParentType::reset(); _tag=-1; }

      Type& operator=(const Type& M) {
        assert((bool)(*this));
        assert((bool)M);
        assert(ParentType::size()==M.size());
        ParentType::operator=((ParentType const&)M);
        return *this;
      }

      void allocate(unsigned int nRes) { reset(); ParentType::allocate(nRes); }
      void imprint_structure(const Type& M) {
        assert((bool)M); 
        allocate(M.size());
      }
      void imprint(const Type&) {
        fprintf(stderr,"Cannot be imprinted Due to residue reason!\n");
      }

      void SetTag(unsigned int it) { _tag=it; }
      void swap(Type& M) {
        ParentType::swap((ParentType&)M);
        std::swap(_tag,M._tag);
      }
  };

}

namespace std {

  void swap(mysimulator::__PDB_Molecule& M1,mysimulator::__PDB_Molecule& M2) {
    M1.swap(M2);
  }

}

#endif

