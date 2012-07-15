
#ifndef _PDB_Residue_Interface_H_
#define _PDB_Residue_Interface_H_

#include "pdb-residue/name.h"
#include "pdb-atom/interface.h"
#include <cstdio>

namespace mysimulator {

  class PDBResidue {

    public:

      typedef PDBResidue    Type;
      friend void Clear(PDBResidue&);
      friend class PDBFile;

      PDBResidue() : _tag(UnknownResidue), _Atom(), _AtomName(), _ID(-1) {}
      ~PDBResidue() { Clear(*this); }

      bool IsValid() const {
        return (_tag!=UnknownResidue)&&_Atom.IsValid()&&_AtomName.IsValid()&&
               (_ID!=-1);
      }

      void Allocate(PDBResidueName RN, const unsigned int* key=NULL) {
        assert(RN!=UnknownResidue);
        Clear(*this);
        _tag=RN;
        _Atom.Allocate(NumberAtomNames);
        for(unsigned int i=0;i<NumberAtomNames;++i) _Atom[i]=NULL;
        if(DefaultKeyID[RN]==-1) fprintf(stderr,"Residue NOT Implemented!\n");
        else {
          unsigned int *mask=
            const_cast<unsigned int*>(ResidueKeyLibrary[DefaultKeyID[RN]]);
          bool isCover;
          isCover=true;
          if(key!=NULL)
            for(unsigned int i=0;i<NumberResidueKey;++i)
              if((key[i]|mask[i])^mask[i]) { isCover=false; break; }
          assert(isCover);
          if(key!=NULL) mask=const_cast<unsigned int*>(key);
          unsigned int sz=0;
          for(unsigned int i=0;i<NumberAtomNames;++i)
            if(mask[i/32]&(1<<(i%32))) {
              _Atom[i]=new PDBAtom;
              _Atom[i]->Allocate(static_cast<PDBAtomName>(i));
              ++sz;
            }
          _AtomName.Allocate(sz);
          sz=0;
          for(unsigned int i=0;i<NumberAtomNames;++i)
            if(mask[i/32]&(1<<(i%32))) {
              _AtomName[sz]=static_cast<PDBAtomName>(i);
              ++sz;
            }
        }
      }

      const PDBResidueName Name() const { return _tag; }
      PDBAtom& Atom(PDBAtomName i) {
        assert(_Atom.IsValid()&&_Atom[i]!=NULL); return *(_Atom[i]);
      }
      const PDBAtom& Atom(PDBAtomName i) const {
        assert(_Atom.IsValid()&&_Atom[i]!=NULL); return *(_Atom[i]);
      }
      const PDBAtomName AtomName(unsigned int i) const {
        assert(_AtomName.IsValid());  return _AtomName[i];
      }
      const unsigned int Index() const {
        assert(_ID>-1); return static_cast<unsigned int>(_ID);
      }

    protected:

      PDBResidueName      _tag;
      Array<PDBAtom*>     _Atom;
      Array<PDBAtomName>  _AtomName;
      int _ID;

      void ClearAtom() {
        if(_Atom.IsValid())
          for(unsigned int i=0;i<NumberAtomNames;++i)
            if(_Atom[i]!=NULL)  { delete _Atom[i]; _Atom[i]=NULL; }
      }

    private:

      PDBResidue(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBResidue& R) {
    R._tag=UnknownResidue;
    R.ClearAtom();
    Clear(R._Atom);
    Clear(R._AtomName);
    R._ID=-1;
  }

}

#endif

