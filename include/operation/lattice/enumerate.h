
#ifndef _Lattice_Enumerate_H_
#define _Lattice_Enumerate_H_

#include "operation/lattice/chain-op.h"

namespace std {

  template <unsigned int LatType, unsigned int LatDim, typename OType>
  int enumerate(const unsigned int N, OType& OObj) {
    myError("The enumeration for this lattice is not available");
    return 0;
  }

  void enumerateSquare2D_Init(
      PropertyList<int>& Mesh, PropertyList<int>& R, 
      LatticeChain<SquareLattice,2>& LC, Vector<unsigned short int>& BoundHigh,
      Vector<unsigned int>& Len, Vector<PropertyList<unsigned int> >& Motif,
      const unsigned int N) {
    const BondLib<SquareLattice,2>& rBL=RunBondLibrary<SquareLattice,2>();
    Vector<unsigned int> sz;
    allocate(LC,N);
    allocate(sz,N+N-1);
    copy(sz,N+N-1);
    allocate(Mesh,sz);
    copy(Mesh,-1);
    allocate(sz,N);
    copy(sz,2);
    allocate(R,sz);
    R[0][0]=R[0][1]=N-1;
    Mesh[N-1][N-1]=0;
    allocate(BoundHigh,LC.size);
    allocate(Len,LC.size);
    copy(Len,rBL.MaxBonds);
    Len[Len.size-1]=rBL.ResidualBonds();
    allocate(Motif,LC.size);
    for(unsigned int i=0;i<LC.size;++i) refer(Motif[i],rBL.mapper[Len[i]-1]);
  }

  bool enumerateSquare2D_Propagate(
      const unsigned int B, const unsigned int BS, const unsigned int BSL,
      const unsigned int BSH, const unsigned int LCB, const unsigned int LenB,
      PropertyList<int>& R, const PropertyList<int>& Mesh) {
    const BondLib<SquareLattice,2>& rBL=RunBondLibrary<SquareLattice,2>();
    int* tmR=rBL.xmapper[LenB-1][LCB].data;
    bool oflag=false;
    int X=R[BS][0],Y=R[BS][1],Xn,Yn;
    for(unsigned int i=BSL,n=0;i<BSH;++i) {
      Xn=X+tmR[n++];
      Yn=Y+tmR[n++];
      R[i][0]=Xn;
      R[i][1]=Yn;
      if(Mesh[Xn][Yn]>=0) { oflag=true; break; }
    }
    return oflag;
  }

  template <typename OutputType>
  int enumerateSquare2D(const unsigned int N, OutputType& OB) {
    const BondLib<SquareLattice,2>& rBL=RunBondLibrary<SquareLattice,2>();
    PropertyList<int> Mesh,R;
    LatticeChain<SquareLattice,2> LC;
    Vector<unsigned int> Len;
    Vector<PropertyList<unsigned int> > Motif;
    Vector<unsigned short int> BoundHigh;
    int* tmR;

    enumerateSquare2D_Init(Mesh,R,LC,BoundHigh,Len,Motif,N);

    int B,BS,BSL,BSH,BC,Z=0;
    bool oflag;
    B=0;
    BS=0;
    BSL=BS+1;
    BSH=BSL+Len[B];
    BC=-1;
    BoundHigh[B]=rBL.mshift[Len[B]-1][0];
    LC[0]=0;
    do {
      oflag=enumerateSquare2D_Propagate(B,BS,BSL,BSH,LC[B],Len[B],R,Mesh);
      if(!oflag) {
        if(B<static_cast<int>(LC.size-1)) {
          for(unsigned int i=BSL;i<BSH;++i) Mesh[R[i][0]][R[i][1]]=i;
          if((B-BC==1)&&(LC[B]==0)) ++BC;
          BS+=Len[B]; ++B;
          BoundHigh[B]=(B-BC==1?rBL.mshift[Len[B]-1][1]:
                                rBL.mshift[Len[B]-1][2]);
          LC[B]=0;
        } else {
          WriteSequence(LC,OB,Z);
          ++Z;
        }
      } ///
      if((!oflag)&&(B<static_cast<int>(LC.size-1))) {
        if((B-BC==1)&&(LC[B]==BoundLow[B])) BC++;
        B++;
        BoundLow[B]=rBL.MotifShift(ID[B]);
        BoundHigh[B]=(B-BC==1?rBL.ConfShift(ID[B])[HeadWithZeroOne2D]:
                              rBL.ConfShift(ID[B])[AllConfigures2D]);
        LC[B]=BoundLow[B];
      } else {
        if(!oflag)
          for(unsigned int i=1+BS[B];i<1+BS[B+1];++i)
            Mesh[R[i][0]][R[i][1]]=-1;
        LC[B]++;
        while(LC[B]>=BoundHigh[B]) {
          B--;
          if(B<0) break;
          if(B==BC) BC--;
          for(unsigned int i=1+BS[B];i<1+BS[B+1];++i)
            Mesh[R[i][0]][R[i][1]]=-1;
          LC[B]++;
        }
      }
    } while(B>=0);
    return Z;
  }

  template <typename OutputType>
  int enumerateSquare2DPart(const unsigned int N,
                            const PropertyList<unsigned int>& FixedBonds,
                            OutputType& OB) {
    const BondLib<SquareLattice,2>& rBL=RunBondLibrary<SquareLattice,2>();
    PropertyList<int> Mesh,R;
    LatticeChain<SquareLattice,2> LC;
    Vector<unsigned int> ID,BS;
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
    allocate(BS,LC.size+1);
    copy(BS,rBL.BondNumber());
    BS[BS.size-1]=LC.FinalByte();
    BS[0]=0;
    for(unsigned int i=1;i<BS.size;++i) BS[i]+=BS[i-1];
    copy(ID,0);
    ID[ID.size-1]=rBL.BondNumber()-LC.FinalByte();

    static const unsigned int
      MapSize=rBL.ConfShift(rBL.BondNumber()-1)[AllConfigures2D];
    PropertyList<bool> flag;
    allocate(sz,LC.size);
    copy(sz,MapSize);
    allocate(flag,sz);
    copy(flag,true);
    for(unsigned int i=0,n,m,l;i<FixedBonds.nunit;++i) {
      m=FixedBonds[i][0]/rBL.BondNumber();
      n=ID[m];
      l=FixedBonds[i][0]%rBL.BondNumber();
      for(unsigned int k=0;k<MapSize;++k) {
        if(!flag[m][k])   continue;
        if((k<rBL.MotifShift(ID[m]))||
           (k>=rBL.ConfShift(ID[m])[AllConfigures2D]))
          flag[m][k]=false;
        else if(rBL.Bond(k)[l]!=FixedBonds[i][1])  flag[m][k]=false;
      }
    }

    int B,BC,X,Y,Xn,Yn,Z=0;
    bool oflag;
    B=0;
    BC=-1;
    BoundLow[B]=rBL.MotifShift(ID[B]);
    BoundHigh[B]=rBL.ConfShift(ID[B])[HeadWithZero2D];
    LC[0]=BoundLow[0];
    do {
      if(!flag[B][LC[B]]) oflag=true;
      else {
        tmR=rBL.Site(LC[B]).data;
        oflag=false;
        X=R[BS[B]][0];
        Y=R[BS[B]][1];
        for(unsigned int i=1+BS[B],n=0;i<1+BS[B+1];++i) {
          Xn=X+tmR[n++];
          Yn=Y+tmR[n++];
          R[i][0]=Xn;
          R[i][1]=Yn;
          if(Mesh[Xn][Yn]>=0) { oflag=true; break; }
        }
        if(!oflag) {
          for(unsigned int i=1+BS[B];i<1+BS[B+1];++i)
            Mesh[R[i][0]][R[i][1]]=i;
          if(B==static_cast<int>(LC.size-1)) {
            WriteSequence(LC,OB,Z);
            ++Z;
          }
        }
      }
      if((!oflag)&&(B<static_cast<int>(LC.size-1))) {
        if((B-BC==1)&&(LC[B]==BoundLow[B])) BC++;
        B++;
        BoundLow[B]=rBL.MotifShift(ID[B]);
        BoundHigh[B]=(B-BC==1?rBL.ConfShift(ID[B])[HeadWithZeroOne2D]:
                              rBL.ConfShift(ID[B])[AllConfigures2D]);
        LC[B]=BoundLow[B];
      } else {
        if(!oflag)
          for(unsigned int i=1+BS[B];i<1+BS[B+1];++i)
            Mesh[R[i][0]][R[i][1]]=-1;
        LC[B]++;
        while(LC[B]>=BoundHigh[B]) {
          B--;
          if(B<0) break;
          if(B==BC) BC--;
          for(unsigned int i=1+BS[B];i<1+BS[B+1];++i)
            Mesh[R[i][0]][R[i][1]]=-1;
          LC[B]++;
        }
      }
    } while(B>=0);
    return Z;
  }

}

#endif

