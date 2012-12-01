
#ifndef _PDB_Model_Interface_H_
#define _PDB_Model_Interface_H_

#include "pdb/molecule/interface.h"

namespace mysimulator {

  class __PDB_Model : public Array<__PDB_Molecule> {

    public:

      typedef __PDB_Model                   Type;
      typedef Array<__PDB_Molecule>   ParentType;

    private:

      Array<char>   _AltTable;
      bool __is_same_table(const Type& M) {
        if(_AltTable.size()!=M._AltTable.size())  return false;
        for(unsigned int i=0;i<_AltTable.size();++i)
          if(_AltTable[i]!=M._AltTable[i])  return false;
        return true;
      }
      unsigned int _AltIndex(char c) const {
        unsigned int m=_AltTable.size()+1;
        if(c==' ')  m=0;
        else
          for(unsigned int i=0;i<_AltTable.size();++i)
            if(c==_AltTable[i]) { m=i; break; }
        if(m>_AltTable.size())  {
          fprintf(stderr,"Unknown Alternative Flag in Table!\n");
          m=0;
        }
        return m;
      }

    public:

      __PDB_Model() : ParentType(), _AltTable() {}
      __PDB_Model(const Type& M) : ParentType((ParentType const&)M),
                                   _AltTable(M._AltTable) {}
      __PDB_Model(Type&& M) : __PDB_Model() { swap(M); }
      ~__PDB_Model() { reset(); }

      operator bool() const {
        return ParentType::operator bool() && (bool)_AltTable;
      }
      __PDB_Residue& Residue(unsigned int im,unsigned int ir,char w=' ') {
        return ParentType::operator[](im).Residue(ir,_AltIndex(w));
      }
      __PDB_Residue const&
      Residue(unsigned int im,unsigned int ir,char w=' ') const {
        return ParentType::operator[](im).Residue(ir,_AltIndex(w));
      }
      unsigned int NumberMolecule() const { return ParentType::size(); }
      void reset() { ParentType::reset(); _AltTable.reset(); }

      Type& operator(const Type& M) {
        assert((bool)(*this));
        assert((bool)M);
        assert(ParentType::size()==M.size());
        assert(__is_same_table(M));
        ParentType::operator=((ParentType const&)M);
        return *this;
      }

      void allocate(unsigned int nMol) { reset(); ParentType::allocate(nMol); }


  };

}

#endif

