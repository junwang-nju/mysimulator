
#ifndef _PDB_Model_Interface_H_
#define _PDB_Model_Interface_H_

#include "pdb-molecule/interface.h"

namespace mysimulator {

  class PDBModel {

    public:

      typedef PDBModel    Type;
      friend void Clear(PDBModel&);
      friend class PDBFile;

      PDBModel() : _Molecule() {}
      ~PDBModel() { Clear(*this); }

      bool IsValid() const { return _Molecule.IsValid(); }

      void Allocate(unsigned int n) { Clear(*this); _Molecule.Allocate(n); }

      PDBMolecule& Molecule(unsigned int i) {
        assert(_Molecule.IsValid());
        return _Molecule[i];
      }
      const PDBMolecule& Molecule(unsigned int i) const {
        assert(_Molecule.IsValid());
        return _Molecule[i];
      }

      PDBResidue& Residue(unsigned int i,unsigned int k,char w=' ') {
        return _Molecule[i].Residue(k,_Index(w));
      }
      const PDBResidue& Residue(unsigned int i,unsigned int k,char w=' ') const{
        return _Molecule[i].Residue(k,_Index(w));
      }

    protected:

      Array<PDBMolecule>  _Molecule;
      Array<char> _AFlag;

      unsigned int _Index(char c) const {
        unsigned int m=_AFlag.Size()+1;
        if(c==' ') m=0;
        else {
          for(unsigned int i=0;i<_AFlag.Size();++i)
            if(c==_AFlag[i]) { m=i; break; }
        }
        if(m>_AFlag.Size()) { fprintf(stderr,"Unknown Alt Flag!\n"); m=0; }
        return m;
      }

    private:

      PDBModel(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBModel& M) { Clear(M._Molecule); }

}

#endif

