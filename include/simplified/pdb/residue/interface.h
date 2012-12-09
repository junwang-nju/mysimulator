
#ifndef _PDB_Residue_Interface_H_
#define _PDB_Residue_Interface_H_

#include "pdb/residue/library.h"
#include "pdb/atom/interface.h"

namespace mysimulator {

  class __PDB_Residue {

    public:

      typedef __PDB_Residue   Type;

    private:

      PDBResidueName  _tag;
      Array<__PDB_Atom*>  _Atom;
      Array<PDBAtomName>  _AtomName;
      int _ID;

      void _allocate(const unsigned int _Key[ResidueKeySize]) {
        _Atom.allocate(NumberAtomName);
        _Atom=nullptr;
        unsigned int sz=0;
        for(unsigned int i=0;i<NumberAtomName;++i)
          if( _Key[i>>5] & (1<<(i&0x1F)) ) {
            _Atom[i]= new __PDB_Atom;
            _Atom[i]->allocate((PDBAtomName)i);
            ++sz;
          }
        _AtomName.allocate(sz);
        for(unsigned int i=0,n=0;i<NumberAtomName;++i)
          if( _Key[i>>5] & (1<<(i&0x1F)) )
            _AtomName[n++] = ((PDBAtomName)i);
      }

    public:

      __PDB_Residue() : _tag(PDBResidueName::Unknown),
                        _Atom(), _AtomName(), _ID(-1) {}
      __PDB_Residue(const Type& R) : __PDB_Residue() {
        imprint(R); operator=(R);
      }
      __PDB_Residue(Type&& R) : __PDB_Residue() { swap(R); }
      ~__PDB_Residue() { reset(); }

      operator bool() const {
        return _tag!=PDBResidueName::Unknown && (bool)_Atom &&
               (bool)_AtomName && (_ID>=0);
      }
      bool __is_same_residue(const Type& R) {
        if(_tag!=R._tag)  return false;
        if(_AtomName.size()!=R._AtomName.size())  return false;
        for(unsigned int i=0;i<_AtomName.size();++i)
          if(_AtomName[i]!=R._AtomName[i])  return false;
        return true;
      }
      PDBResidueName Name() const { return _tag; }
      __PDB_Atom& Atom(PDBAtomName AN) {
        assert((bool)_Atom);
        assert(_Atom[(unsigned int)AN]!=nullptr);
        return *(_Atom[(unsigned int)AN]);
      }
      __PDB_Atom const& Atom(PDBAtomName AN) const {
        assert((bool)_Atom);
        assert(_Atom[(unsigned int)AN]!=nullptr);
        return *(_Atom[(unsigned int)AN]);
      }
      PDBAtomName AtomName(unsigned int i) const {
        assert((bool)_AtomName);
        return _AtomName[i];
      }
      unsigned int Index() const { assert(_ID>-1); return _ID; }
      unsigned int NumberAtom() const { return _AtomName.size(); }
      void reset() {
        _ID=-1;
        _AtomName.reset();
        _Atom.reset();
        _tag=PDBResidueName::Unknown;
      }

      Type& operator=(const Type& R) {
        assert((bool)(*this));
        assert((bool)R);
        assert(__is_same_residue(R));
        for(unsigned int i=0,w;i<_AtomName.size();++i) {
          w=(unsigned int)(_AtomName[i]);
          *(_Atom[w])=*(R._Atom[w]);
        }
        return *this;
      }

      void allocate(const unsigned int Key[ResidueKeySize]) {
        int _rlid = __residue_library_id(Key);
        if(_rlid==-1) {
          fprintf(stderr,"Key for Unknown Residue!\n");
          return;
        }
        reset();
        _tag = ResidueLibrary[_rlid].Value;
        _allocate(Key);
      }
      void allocate(const PDBResidueName RN) {
        int _rlid = __residue_library_id(RN);
        if(_rlid==-1) {
          fprintf(stderr,"Key for Unknown Residue!\n");
          return;
        }
        reset();
        _tag = RN;
        _allocate(ResidueLibrary[_rlid].Key);
      }
      void imprint(const Type& R) {
        assert((bool)R);
        unsigned int Key[ResidueKeySize];
        for(unsigned int i=0;i<ResidueKeySize;++i)  Key[i]=0;
        for(unsigned int i=0;i<NumberAtomName;++i)
          if(_Atom[i]!=nullptr)   Key[i>>5] |= (1<<(i&0x1F));
        allocate(Key);
      }

      void SetIndex(int id) { _ID=id; }
      void swap(Type& R) {
        std::swap(_tag,R._tag);
        std::swap(_Atom,R._Atom);
        std::swap(_AtomName,R._AtomName);
        std::swap(_ID,R._ID);
      }

  };

}

namespace mysimulator {

  void swap(mysimulator::__PDB_Residue& R1, mysimulator::__PDB_Residue& R2) {
    R1.swap(R2);
  }

}

#endif

