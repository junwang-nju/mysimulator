
#ifndef _PDB_Inteface_H_
#define _PDB_Inteface_H_

#include "pdb/model/interface.h"
#include "array-2d/interface.h"
#include <cstring>

namespace mysimulator {

  class PDB : public Array<__PDB_Model> {

    public:

      typedef PDB                       Type;
      typedef Array<__PDB_Model>  ParentType;

    private:

      char _Code[5];
      Array2D<Int,ArrayKernelName::SSE> _SeqMap;

    public:

      PDB() : ParentType(), _SeqMap() {
        strncpy(_Code,"    ",4); _Code[5]='\0';
      }
      PDB(const Type& F) : ParentType((ParentType const&)F),
                           _SeqMap(F._SeqMap) { strncpy(_Code,F._Code,4); }
      PDB(Type&& F) : PDB() { swap(F); }
      ~PDB() { reset(); }

      operator bool() const {
        return ParentType::operator bool() && strncmp(_Code,"    ",4)!=0 &&
               (bool)_SeqMap;
      }
      const char* Code() const { return _Code; }
      unsigned int NumberModel() const { return ParentType::size(); }
      unsigned int NumberResidue() const { return _SeqMap.Data().size(); }
      __PDB_Residue& Residue(unsigned int nMod,unsigned int nMol,
                             unsigned int nRes,char alt=' ') {
        assert((bool)(*this));
        return ParentType::operator[](nMod).Residue(nMol,nRes,alt);
      }
      __PDB_Residue const& Residue(unsigned int nMod,unsigned int nMol,
                                   unsigned int nRes,char alt=' ') const {
        assert((bool)(*this));
        return ParentType::operator[](nMod).Residue(nMol,nRes,alt);
      }
      unsigned int SequentialIndex(unsigned int nMol,unsigned int nRes) const {
        return _SeqMap[nMol][nRes];
      }
      void reset() {
        ParentType::reset(); strncpy(_Code,"    ",5); _SeqMap.reset();
      }

      Type& operator=(const Type&) = delete;

      void SetCode(const char* code) {
        for(unsigned int i=0;i<4;++i) _Code[i]=code[i];
        _Code[4]='\0';
      }
      void BuildSeqMap() {
        assert(ParentType::operator bool());
        Array<UInt,ArrayKernelName::SSE> SZ;
        SZ.allocate(ParentType::operator[](0).NumberMolecule());
        for(unsigned int i=0;i<SZ.size();++i)
          SZ[i]=ParentType::operator[](0)[i].NumberResidue();
        _SeqMap.allocate(SZ);
        unsigned int S=Sum(SZ);
        for(unsigned int i=0;i<S;++i) _SeqMap.Data()[i]=i;
      }

      void swap(Type& O) {
        ParentType::swap((ParentType&)O);
        std::swap(_Code,O._Code);
        std::swap(_SeqMap,O._SeqMap);
      }

  };

}

namespace std {

  void swap(mysimulator::PDB& A, mysimulator::PDB& B) { A.swap(B); }

}

#endif

