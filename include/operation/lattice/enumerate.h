
#ifndef _Lattice_Enumerate_H_
#define _Lattice_Enumerate_H_

#include "operation/lattice/chain-op.h"

namespace std {

  template <unsigned int LT, unsigned int LD>
  void enumerate(const unsigned int N, istream& is) {
    myError("This Lattice Cannot be enumerated");
  }

  template <>
  void enumerate<SquareLattice,2>(const unsigned int N, istream& is) {
    PropertyList<int> Mesh;
    Vector<unsigned int> sz(N+N-1);
    copy(sz,N+N-1);
    allocate(Mesh,sz);
    copy(Mesh,-1);
    LatticeChain<SquareLattice,2> LC;
    allocate(LC,N-1);
    PropertyList<int> R;
    allocate(sz,N);
    copy(sz,2);
    allocate(R,sz);
    R[0][0]=N-1;
    R[0][1]=N-1;
    Mesh[R[0][0]][R[0][1]]=0;
    Vector<unsigned char> BoundLow,BoundHigh;
    allocate(BoundLow,N-1);
    allocate(BoundHigh,N-1);
    int J=(N-1)%RunBondLibrary<SquareLattice,2>::BondNumber();
    Vector<unsigned int> ID;
    allocate(ID,LC.size);
    copy(ID,0);
    if(J!=0)  ID[ID.size-1]=RunBondLibrary<SquareLattice,2>::BondNumber()-J;
    int B=0,BC;
    for(unsigned int i=0;i<LC.size-1;++i) {
      BoundLow[i]=0;
      BoundHigh[i]=confShift[0][HeadWithZero2D];
      LC[i]=BoundLow[i];
    }
    BoundLow[LC.size-1]=MotifShift(ID[LC.size-1]);
    BoundHigh[LC.size-1]=MotifShift(ID[LC.size-1])+
                         confShift[ID[LC.size-1]][HeadWithZeroOne2D];
    do {
    } while(B>0);
  }

}

#endif

