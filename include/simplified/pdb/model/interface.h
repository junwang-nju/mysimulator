
#ifndef _PDB_Model_Interface_H_
#define _PDB_Model_Interface_H_

#include "pdb/molecule/interface.h"

namespace mysimulator {

  class _AltInfoTable : public Array<Char> {

    public:

      typedef _AltInfoTable         Type;
      typedef Array<Char>     ParentType;

      _AltInfoTable() : ParentType() {}
      _AltInfoTable(const Type& TB) : ParentType((ParentType const&)TB) {}
      _AltInfoTable(Type&& TB) : ParentType((ParentType&&)TB) {}
      ~_AltInfoTable() { ParentType::reset(); }

      Type& operator=(const Type& TB) {
        ParentType::operator=((ParentType const&)TB); return *this;
      }

      unsigned int operator()(char c) const {
        unsigned int m=ParentType::size()+1;
        if(c==' ')  m=0;
        else
          for(unsigned int i=0;i<ParentType::size();++i)
            if(c==ParentType::operator[](i)) { m=i; break; }
        if(m>ParentType::size()) {
          fprintf(stderr,"Unknown Alternative Flag in Table!\n");
          m=0;
        }
        return m;
      }

  };

  class __PDB_Model : public Array<__PDB_Molecule> {

    public:

      typedef __PDB_Model                   Type;
      typedef Array<__PDB_Molecule>   ParentType;

    private:

      _AltInfoTable _Table;

    public:

      __PDB_Model() : ParentType(), _Table() {}
      __PDB_Model(const Type& M) : ParentType((ParentType const&)M),
                                   _Table(M._Table) {}
      __PDB_Model(Type&& M) : __PDB_Model() { swap(M); }
      ~__PDB_Model() { reset(); }

      operator bool() const {
        return ParentType::operator bool() && (bool)_Table;
      }
      __PDB_Residue& Residue(unsigned int im,unsigned int ir,char w=' ') {
        return ParentType::operator[](im).Residue(ir,_Table(w));
      }
      __PDB_Residue const&
      Residue(unsigned int im,unsigned int ir,char w=' ') const {
        return ParentType::operator[](im).Residue(ir,_Table(w));
      }
      unsigned int NumberMolecule() const { return ParentType::size(); }
      _AltInfoTable& AlternativeInfoTable() { return _Table; }
      _AltInfoTable const& AlternativeInfoTable() const { return _Table; }
      void reset() { ParentType::reset(); _Table.reset(); }

      Type& operator=(const Type& M) {
        assert((bool)(*this));
        assert((bool)M);
        assert(ParentType::size()==M.size());
        ParentType::operator=((ParentType const&)M);
        return *this;
      }

      void allocate(unsigned int nMol) { reset(); ParentType::allocate(nMol); }

      void swap(Type& M) {
        ParentType::swap((ParentType&)M);
        std::swap(_Table,M._Table);
      }

  };

}

namespace std {

  void swap(mysimulator::__PDB_Model& A,mysimulator::__PDB_Model& B) { A.swap(B); }

}

#endif

