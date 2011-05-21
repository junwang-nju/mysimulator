
#ifndef _Lattice_Enumerate_Square2D_Act_H_
#define _Lattice_Enumerate_Square2D_Act_H_

#include "lattice/motif-chain/allocate.h"
#include "list/allocate.h"
#include "list/fill.h"
#include "vector/shift.h"
#include "vector/copy.h"
#include "io/output/interface.h"
#include "vector/io.h"

namespace mysimulator {

  template <unsigned int L>
  void _init_Enum_Square2D(
      List<int>& Mesh, List<int>& Loc,LatticeMotifChain<SquareLattice,2,L>&C,
      Vector<unsigned int>& Len, Vector<unsigned short>& bHigh) {
    Vector<unsigned int> sz;

    allocate(sz,L+L-1);
    fill(sz,L+L-1);
    allocate(Mesh,sz);
    fill(Mesh,-1);

    allocate(sz,L);
    fill(sz,2U);
    allocate(Loc,sz);
    fill(Loc[0],static_cast<int>(L-1));
    Mesh[L-1][L-1]=0;

    allocate(C);

    allocate(Len,LatticeMotifChain<SquareLattice,2,L>::NumMotifs);
    fill(Len,LatticeLibrary<SquareLattice,2>::MaxBondOfMotif);
    Len[Len.size-1]=LatticeMotifChain<SquareLattice,2,L>::NumBondsLastMotif;

    allocate(bHigh,C.NumMotifs);
  }

  void _init_Enum_Square2D_1stbond(
      int& Bc, int& Bs, int& BsL, int& BsH, unsigned short& C0,
      unsigned short& Bh0, const unsigned int Len0) {
    Bs=0;
    BsL=Bs+1;
    BsH=BsL+Len0;
    Bc=-1;
    C0=0;
    Bh0=LatticeLibrary<SquareLattice,2>::shiftLoc[Len0-1][0];
  }

  bool _propagate_Enum_Square2D(
      const int B, const int Bs, const int BsL, const int BsH,
      const unsigned short CB, const unsigned int LenB,
      List<int>& Loc, const List<int>& Mesh) {
    bool oflag=false;
    Vector<int> rLoc(2),nLoc(2);
    copy(rLoc,Loc[Bs]);
    for(int i=BsL,n=0;i<BsH;++i,++n) {
      copy(nLoc,rLoc);
      shift(nLoc,
            LatticeLibrary<SquareLattice,2>::map[LenB-1][CB].coordinate[n]);
      if(Mesh[nLoc[0]][nLoc[1]]>=0) { oflag=true; break; }
      copy(Loc[i],nLoc);
    }
    return oflag;
  }

  template <unsigned int L>
  void _new_Enum_Square2D(
      int& B, int& Bc, int& Bs, int& BsL, int& BsH, const List<int>& Loc,
      List<int>& Mesh, LatticeMotifChain<SquareLattice,2,L>& C,
      const Vector<unsigned int>& Len, Vector<unsigned short>& bHigh) {
    for(int i=BsL;i<BsH;++i)  Mesh[Loc[i][0]][Loc[i][1]]=i;
    if((B-Bc==1)&&(C.motifValue[B]==0)) ++Bc;
    Bs+=Len[B];
    ++B;
    BsL=Bs+1;   BsH=BsL+Len[B];
    bHigh[B]=(B-Bc==1?LatticeLibrary<SquareLattice,2>::shiftLoc[Len[B]-1][1]:
                      LatticeLibrary<SquareLattice,2>::shiftLoc[Len[B]-1][2]);
    C.motifValue[B]=0;
  }

  template <unsigned int L>
  void _inc_Enum_Square2D(
      int& B, int& Bc, int& Bs, int& BsL, int& BsH, const List<int>& Loc,
      List<int>& Mesh, LatticeMotifChain<SquareLattice,2,L>& C,
      const Vector<unsigned int>& Len, const Vector<unsigned short>& bHigh) {
    ++C.motifValue[B];
    while(C.motifValue[B]>=bHigh[B]) {
      --B;
      if(B<0) break;
      BsH=BsL;
      Bs-=Len[B];
      BsL=Bs+1;
      if(B==Bc) --Bc;
      for(int i=BsL;i<BsH;++i)  Mesh[Loc[i][0]][Loc[i][1]]=-1;
      ++C.motifValue[B];
    }
  }

  template <unsigned int L>
  int enumerate(
      bool (*CheckFunc)(const LatticeMotifChain<SquareLattice,2,L>&,
                        const List<int>&,const List<int>&),
      OutputBase& os) {
    List<int> Mesh,Loc;
    LatticeMotifChain<SquareLattice,2,L>  C;
    Vector<unsigned int> Len;
    Vector<unsigned short> boundHigh;

    _init_Enum_Square2D<L>(Mesh,Loc,C,Len,boundHigh);

    unsigned int NC=0;

    int B,Bs,BsL,BsH,Bc;
    B=0;
    _init_Enum_Square2D_1stbond(Bc,Bs,BsL,BsH,C.motifValue[B],boundHigh[B],
                                Len[B]);

    bool oflag, bflag;
    do {
      oflag=_propagate_Enum_Square2D(B,Bs,BsL,BsH,C.motifValue[B],
                                     Len[B],Loc,Mesh);
      bflag=true;
      if(!oflag) {
        if(static_cast<unsigned int>(B+1)<
           LatticeMotifChain<SquareLattice,2,L>::NumMotifs) {
          _new_Enum_Square2D(B,Bc,Bs,BsL,BsH,Loc,Mesh,C,Len,boundHigh);
          bflag=false;
        } else {
          if(CheckFunc(C,Loc,Mesh)) {
            os<<C<<Endl;
            ++NC;
          }
        }
      }
      if(bflag)
        _inc_Enum_Square2D(B,Bc,Bs,BsL,BsH,Loc,Mesh,C,Len,boundHigh);
    } while(B>=0);

    return NC;
  }

}


#endif

