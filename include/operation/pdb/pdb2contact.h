
#ifndef _PDB_to_Contact_H_
#define _PDB_to_Contact_H_

#include "data/pdb/pdb-info.h"
#include "data/pdb/contact-calc-mode.h"
#include "data/basic/string-buffer-input.h"
#include "data/basic/string-buffer-output.h"

namespace std {

  template <unsigned int ModeFlag>
  void PdbInfo2ContactMap(const PDBInfo& I, ContactMap& CM,
                          const ContactCalcMode<ModeFlag>& Mode) {
    Error("This Mode is not ecognized!");
  }

  void PdbInfo2ContactMap(const PDBInfo& I, ContactMap& CM,
                          const ContactCalcMode<UsingHeavyAtoms>& Mode) {
    if(!IsAvailable(IsHeavyAtom)) InitHeavyAtomProperty();
    Vector<double> tmV(3);
    unsigned int nc=0;
    char *buffer;
    buffer=new char[8192000];
    StringOutput SO(buffer,8192000);
    StringInput SI(buffer,8192000);
    for(unsigned int i=0;i<I.UnitName.size;++i)
    for(unsigned int j=i+1;j<I.UnitName.size;++j) {
      if(get(I.UnitBond,i,j)!=NULL) continue;
      for(unsigned int k=0;k<I.UnitAtomID[i].size;++k)
      for(unsigned int l=0;l<I.UnitAtomID[j].size;++l) {
        if(I.UnitAtomID[i][k]<0)  continue;
        if(I.UnitAtomID[j][l]<0)  continue;
        if(!IsHeavyAtom[I.UnitName[i]][I.AtomName[I.UnitAtomID[i][k]]])
          continue;
        if(!IsHeavyAtom[I.UnitName[j]][I.AtomName[I.UnitAtomID[j][l]]])
          continue;
        copy(tmV,I.Coordinate[Mode.ModelID()][I.UnitAtomID[i][k]]);
        shift(tmV,-1.,I.Coordinate[Mode.ModelID()][I.UnitAtomID[j][l]]);
        if(norm(tmV)<Mode.CutoffDistance()) {
          ++nc;
          SO<<i<<" "<<j<<" ";
          k=I.UnitAtomID[i].size;
          l=I.UnitAtomID[j].size;
        }
      }
    }
    allocate(CM,nc);
    for(unsigned int i=0,k,l;i<nc;++i) {
      SI>>k>>l;
      Set(CM,i,k,l);
    }
    CM.update();
    delete[] buffer;
  }

}

#endif

