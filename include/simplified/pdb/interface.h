
#ifndef _PDB_Inteface_H_
#define _PDB_Inteface_H_

#include "pdb/model/interface.h"
#include "array-2d/interface.h"
#include <cstring>

namespace mysimulator {

  class PDB : public Array<__PDB_Model> {

    public:

      typedef PDB                 Type;
      typedef __PDB_Model   ParentType;

    private:

      char _Code[5];
      Array2D<Int,ArrayKernelName::SSE> _SeqMap;

    public:

      PDB() : ParentType(), _Code("    "), _SeqMap() {}
      PDB(const Type& F) : ParentType((ParentType const&)F), _Code(F._Code),
                           _SeqMap(F._SeqMap) {}
      PDB(Type&& F) : PDB() { swap(F); }
      ~PDB() { reset(); }

      operator bool() const {
        return ParentType::operator bool() && strncmp(_Code,"    ",4)!=0 &&
               (bool)_SeqMap;
      }
      const char* Code() const { return _code; }
      unsigned int NumberModels() const { return ParentType::size(); }
      unsigned int NumberResidues() const { return _SeqMap.Data().size(); }
      __PDB_Residue& Residue(unsigned int nMod,unsigned int nMol,
                             unsigned int nRes,char alt) {
        assert((bool)(*this));
        return ParentType::operator[](nMod).Residue(nMol,nRes,alt);
      }
      __PDB_Residue const& Residue(unsigned int nMod,unsigned int nMol,
                                   unsigned int nRes,char alt) const {
        assert((bool)(*this));
        return ParentType::operator[](nMod).Residue(nMol,nRes,alt);
      }
      unsigned int SequentialIndex(unsigned int nMol,unsigned int nRes) const {
        return _SeqMap[nMol][nRes];
      }
      void reset() {
        ParentType::reset(); strncpy(_Code,"    ",5); _SeqMap.reset();
      }

      void BuildSeqMap() {
        assert(ParentType::operator bool());
        Array<UInt,ArrayKernelName::SSE> SZ;
        SZ.allocate(ParentType::operator[](0).NumberMolecule());
        for(unsigned int i=0;i<SZ.size();++i)
          SZ[i]=ParentType::operator[](0)[i].NumberResidues();
        _SeqMap.allocate(SZ);
        unsigned int S=Sum(SZ);
        for(unsigned int i=0;i<S;++i) _SeqMap.Data()[i]=i;
      }

  };

}

#endif

