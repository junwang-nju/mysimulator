
#ifndef _Lattice_Enumerate_Square2D_Act_H_
#define _Lattice_Enumerate_Square2D_Act_H_

#include "lattice/enumerate/square-2d/check/interface.h"
#include "lattice/enumerate/square-2d/run-data/allocate.h"
#include "vector/copy.h"
#include "vector/shift.h"

namespace mysimulator {

  template <unsigned int L>
  bool _Propagate_LatticeEnumSquare2D(LatticeEnumSquare2DRunData<L>& Data) {
    bool oflag=false;
    Vector<int> nLoc(2);
    const unsigned int l=Data.Len[Data.B]-1;
    const unsigned int u=Data.C.motifValue[Data.B];
    for(int i=Data.BsL,n=0;i<Data.BsH;++i,++n) {
      copy(nLoc,Data.Loc[Data.Bs]);
      shift(nLoc,LatticeLibrary<SquareLattice,2>::map[l][u].coordinate[n]);
      if(Data.Mesh[nLoc[0]][nLoc[1]]>=0)  { oflag=true; break; }
      copy(Data.Loc[i],nLoc);
    }
    return oflag;
  }

  template <unsigned int L>
  void _NewBond_LatticeEnumSquare2D(LatticeEnumSquare2DRunData<L>& Data) {
    for(int i=Data.BsL;i<Data.BsH;++i)
      Data.Mesh[Data.Loc[i][0]][Data.Loc[i][1]]=i;
    if((Data.B-Data.Bc==1)&&(Data.C.motifValue[Data.B]==0)) ++Data.Bc;
    Data.Bs+=Data.Len[Data.B];
    ++Data.B;
    Data.BsL=Data.Bs+1;
    Data.BsH=Data.BsL+Data.Len[Data.B];
    const unsigned int l=Data.Len[Data.B]-1;
    Data.bHigh[Data.B]=
      (Data.B-Data.Bc==1?LatticeLibrary<SquareLattice,2>::shiftLoc[l][1]:
                         LatticeLibrary<SquareLattice,2>::shiftLoc[l][2]);
    Data.C.motifValue[Data.B]=0;
  }

  template <unsigned int L>
  void _IncBond_LatticeEnumSquare2D(LatticeEnumSquare2DRunData<L>& Data) {
    ++Data.C.motifValue[Data.B];
    while(Data.C.motifValue[Data.B]>=Data.bHigh[Data.B]) {
      --Data.B;
      if(Data.B<0)  break;
      Data.BsH=Data.BsL;
      Data.Bs-=Data.Len[Data.B];
      Data.BsL=Data.Bs+1;
      if(Data.B==Data.Bc) --Data.Bc;
      for(int i=Data.BsL;i<Data.BsH;++i)
        Data.Mesh[Data.Loc[i][0]][Data.Loc[i][1]]=-1;
      ++Data.C.motifValue[Data.B];
    }
  }
  
  template <unsigned int L, LatticeEnumSquare2DCheckMethodName Method>
  unsigned long long enumerate(const LatticeEnumSquare2DCheck<Method>& Check,
                               OutputBase& os) {
    unsigned long long NC=0;
    bool oflag, bflag;
    LatticeEnumSquare2DRunData<L> Data;
    allocate(Data);
    do {
      oflag=_Propagate_LatticeEnumSquare2D(Data);
      oflag=oflag||(!Check.Act(Data));
      bflag=true;
      if(!oflag) {
        if(Data.B+1U<LatticeMotifChain<SquareLattice,2,L>::NumMotifs) {
          _NewBond_LatticeEnumSquare2D(Data);
          bflag=false;
        } else {
          os<<Data.C<<Endl;
          ++NC;
        }
      }
      if(bflag)
        _IncBond_LatticeEnumSquare2D(Data);
    } while(Data.B>=0);
    release(Data);
    return NC;
  }

}

#endif

