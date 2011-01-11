
#ifndef _Lattice_Enumerate_H_
#define _Lattice_Enumerate_H_

#include "operation/lattice/chain-op.h"

namespace std {

  template <unsigned int LT, unsigned int LD>
  void enumerate(const unsigned int N, ostream& os) {
    myError("This Lattice Cannot be enumerated");
  }

  template <>
  void enumerate<SquareLattice,2>(const unsigned int N, ostream& os) {
    const BondLib<SquareLattice,2>& rBL=RunBondLibrary<SquareLattice,2>();
    PropertyList<int> Mesh,R;
    LatticeChain<SquareLattice,2> LC;
    Vector<unsigned int> ID,BN,BS;
    Vector<unsigned char> BoundLow,BoundHigh;
    Vector<unsigned int> sz;
    int* tmR;

    allocate(sz,N+N-1);
    copy(sz,N+N-1);
    allocate(Mesh,sz);
    copy(Mesh,-1);

    allocate(LC,N);

    allocate(sz,N);
    copy(sz,2);
    allocate(R,sz);
    R[0][0]=N-1;
    R[0][1]=N-1;
    Mesh[R[0][0]][R[0][1]]=0;

    allocate(BoundLow,LC.size);
    allocate(BoundHigh,LC.size);
    allocate(ID,LC.size);
    allocate(BN,LC.size);
    allocate(BS,LC.size);
    copy(BN,rBL.BondNumber());
    BN[BN.size-1]=LC.FinalByte();
    copy(ID,0);
    ID[ID.size-1]=rBL.BondNumber()-LC.FinalByte();
    BS[0]=0;
    for(unsigned int i=1;i<BS.size;++i) BS[i]=BS[i-1]+BN[i-1];

    int B,BC;
    bool oflag;
    B=0;
    BC=-1;
    BoundLow[B]=rBL.MotifShift(ID[B]);
    BoundHigh[B]=rBL.ConfShift(ID[B])[HeadWithZero2D];
    LC[0]=BoundLow[0];
    do {
      tmR=const_cast<int*>(GetBondDirection(LC,BS[B]));
      oflag=false;
      for(unsigned int i=1+BS[B],n=0;i<1+BS[B]+BN[B];++i) {
        R[i][0]=R[BS[B]][0]+tmR[n++];
        R[i][1]=R[BS[B]][1]+tmR[n++];
        if(Mesh[R[i][0]][R[i][1]]>=0) { oflag=true; break; }
      }
      if(!oflag) {
        for(unsigned int i=1+BS[B];i<1+BS[B]+BN[B];++i)
          Mesh[R[i][0]][R[i][1]]=i;
        if(B==static_cast<int>(LC.size-1))  os<<LC;
      }
      if((!oflag)&&(B<static_cast<int>(LC.size-1))) {
        if((B-BC==1)&&(LC[B]==BoundLow[B])) BC++;
        B++;
        BoundLow[B]=rBL.MotifShift(ID[B]);
        BoundHigh[B]=(B-BC==1?rBL.ConfShift(ID[B])[HeadWithZeroOne2D]:
                              rBL.ConfShift(ID[B])[AllConfigures2D]);
        LC[B]=BoundLow[B];
      } else {
        for(unsigned int i=1+BS[B];i<1+BS[B]+BN[B];++i)
          Mesh[R[i][0]][R[i][1]]=-1;
        LC[B]++;
        while(LC[B]>=BoundHigh[B]) {
          B--;
          if(B<0) break;
          if(B==BC) BC--;
          for(unsigned int i=1+BS[B];i<1+BS[B]+BN[B];++i)
            Mesh[R[i][0]][R[i][1]]=-1;
          LC[B]++;
        }
      }
    } while(B>=0);
  }

}

#endif

