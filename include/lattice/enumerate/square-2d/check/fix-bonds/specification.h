
#ifndef _Lattice_Enumerate_Square2D_Check_FixBonds_Specification_H_
#define _Lattice_Enumerate_Square2D_Check_FixBonds_Specification_H_

#include "lattice/enumerate/square-2d/check/interface.h"
#include "vector/copy.h"
#include "list/allocate.h"
#include "list/fill.h"

namespace mysimulator {

  template <>
  struct LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodFixBonds> {

    typedef LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodFixBonds>
            Type;

    List<bool> flag;
    List<unsigned int> fixedBond;

    LatticeEnumSquare2DCheck() : flag(), fixedBond() {}
    LatticeEnumSquare2DCheck(const Type&) {
      Error("Copier of LatticeEnumSquare2DCheck Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for LatticeEnumSquare2DCheck Disabled!");
      return *this;
    }
    ~LatticeEnumSquare2DCheck() { clearData(); }

    void clearData() { release(flag); release(fixedBond); }
    template <unsigned int L>
    void update() {
      const unsigned int u=LatticeLibrary<SquareLattice,2>::MaxBondOfMotif;
      Vector<unsigned int> len(LatticeMotifChain<SquareLattice,2,L>::NumMotifs);
      fill(len,u);
      len[len.size-1]=LatticeMotifChain<SquareLattice,2,L>::NumBondsLastMotif;
      Vector<unsigned int> sz(len.size);
      for(unsigned int i=0;i<sz.size;++i)
        sz[i]=LatticeLibrary<SquareLattice,2>::map[len[i]-1].size;
      allocate(flag,sz);
      fill(flag,true);
      for(unsigned int i=0,m,n,l,p;i<fixedBond.ListSize();++i) {
        m=fixedBond[i][0]/u;
        n=fixedBond[i][0]%u;
        l=len[m]-1;
        p=fixedBond[i][1];
        for(unsigned int k=0;k<sz[m];++k) {
          if(!flag[m][k]) continue;
          else if(LatticeLibrary<SquareLattice,2>::map[l][k].bond[n]!=p)
            flag[m][k]=false;
        }
      }
    }

    template <unsigned int L>
    bool Act(LatticeEnumSquare2DRunData<L>& D) const {
      return flag[D.B][D.C.motifValue[D.B]];
    }

  };

  bool IsValid(
      const LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodFixBonds>&
            C) { return IsValid(C.flag)&& IsValid(C.fixedBond); }

}

#endif

