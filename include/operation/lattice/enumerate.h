
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
    Len[Len.size-1]=LC.ResidualBonds();
    allocate(Motif,LC.size);
    for(unsigned int i=0;i<LC.size;++i) refer(Motif[i],rBL.mapper[Len[i]-1]);
  }

  void enumerateSquare2D_InitFirstBond(
      int& BC, int& BS, int& BSL, int& BSH, unsigned short int& LC0,
      unsigned short int& BH0, const unsigned int Len0) {
    const BondLib<SquareLattice,2>& rBL=RunBondLibrary<SquareLattice,2>();
    BS=0;
    BSL=BS+1;
    BSH=BSL+Len0;
    BC=-1;
    BH0=rBL.mshift[Len0-1][0];
    LC0=0;
  }

  bool enumerateSquare2D_Propagate(
      const int B, const int BS, const int BSL, const int BSH,
      const unsigned short int LCB, const unsigned int LenB,
      PropertyList<int>& R, const PropertyList<int>& Mesh) {
    const BondLib<SquareLattice,2>& rBL=RunBondLibrary<SquareLattice,2>();
    int* tmR=rBL.xmapper[LenB-1][LCB].data;
    bool oflag=false;
    int X=R[BS][0],Y=R[BS][1],Xn,Yn;
    for(int i=BSL,n=0;i<BSH;++i) {
      Xn=X+tmR[n++];
      Yn=Y+tmR[n++];
      if(Mesh[Xn][Yn]>=0) { oflag=true; break; }
      R[i][0]=Xn;
      R[i][1]=Yn;
    }
    return oflag;
  }

  void enumerateSquare2D_NewBond(
      int& B, int& BC, int& BS, int& BSL, int& BSH, const PropertyList<int>& R,
      PropertyList<int>& Mesh, LatticeChain<SquareLattice,2>& LC,
      const Vector<unsigned int>& Len, Vector<unsigned short int>& BoundHigh) {
    const BondLib<SquareLattice,2>& rBL=RunBondLibrary<SquareLattice,2>();
    for(int i=BSL;i<BSH;++i) Mesh[R[i][0]][R[i][1]]=i;
    if((B-BC==1)&&(LC[B]==0)) ++BC;
    BS+=Len[B]; ++B;
    BSL=BS+1;   BSH=BSL+Len[B];
    BoundHigh[B]=(B-BC==1?rBL.mshift[Len[B]-1][1]:rBL.mshift[Len[B]-1][2]);
    LC[B]=0;
  }

  void enumerateSquare2D_IncBond(
      int& B, int& BC, int& BS, int& BSL, int& BSH, const PropertyList<int>& R,
      PropertyList<int>& Mesh, LatticeChain<SquareLattice,2>& LC,
      const Vector<unsigned int>& Len,
      const Vector<unsigned short int>& BoundHigh) {
    ++LC[B];
    while(LC[B]>=BoundHigh[B]) {
      --B;
      if(B<0)   break;
      BSH=BSL;
      BS-=Len[B];
      BSL=BS+1;
      if(B==BC)   --BC;
      for(int i=BSL;i<BSH;++i) Mesh[R[i][0]][R[i][1]]=-1;
      ++LC[B];
    }
  }

  template <typename OutputType>
  int enumerateSquare2D(const unsigned int N, OutputType& OB) {
    PropertyList<int> Mesh,R;
    LatticeChain<SquareLattice,2> LC;
    Vector<unsigned int> Len;
    Vector<PropertyList<unsigned int> > Motif;
    Vector<unsigned short int> BoundHigh;

    enumerateSquare2D_Init(Mesh,R,LC,BoundHigh,Len,Motif,N);

    int B,BS,BSL,BSH,BC,Z=0;
    bool oflag,bflag;
    B=0;
    enumerateSquare2D_InitFirstBond(BC,BS,BSL,BSH,LC[B],BoundHigh[B],Len[B]);
    do {
      oflag=enumerateSquare2D_Propagate(B,BS,BSL,BSH,LC[B],Len[B],R,Mesh);
      bflag=true;
      if(!oflag) {
        if(B<static_cast<int>(LC.size-1)) {
          enumerateSquare2D_NewBond(B,BC,BS,BSL,BSH,R,Mesh,LC,Len,BoundHigh);
          bflag=false;
        } else {
          WriteSequence(LC,OB,Z);
          ++Z;
        }
      }
      if(bflag)
        enumerateSquare2D_IncBond(B,BC,BS,BSL,BSH,R,Mesh,LC,Len,BoundHigh);
    } while(B>=0);
    return Z;
  }

  void enumerateSquare2D_FixBondFlagInit(
      PropertyList<bool>& flag, const Vector<unsigned int>& Len,
      const PropertyList<unsigned int>& FixedBonds) {
    const BondLib<SquareLattice,2>& rBL=RunBondLibrary<SquareLattice,2>();
    Vector<unsigned int> sz;
    allocate(sz,Len.size);
    for(unsigned int i=0;i<Len.size;++i)  sz[i]=rBL.mapper[Len[i]-1].nunit;
    allocate(flag,sz);
    copy(flag,true);
    for(unsigned int i=0,m,n,l;i<FixedBonds.nunit;++i) {
      m=FixedBonds[i][0]/rBL.MaxBonds;
      n=FixedBonds[i][0]%rBL.MaxBonds;
      l=Len[m]-1;
      for(unsigned int k=0;k<rBL.mapper[l].nunit;++k) {
        if(!flag[m][k])   continue;
        else if(rBL.mapper[l][k][n]!=FixedBonds[i][1])  flag[m][k]=false;
      }
    }
  }

  template <typename OutputType>
  int enumerateSquare2DFixBond(
      const unsigned int N, const PropertyList<unsigned int>& FixedBonds,
      OutputType& OB) {
    PropertyList<int> Mesh,R;
    LatticeChain<SquareLattice,2> LC;
    Vector<unsigned int> Len;
    Vector<PropertyList<unsigned int> > Motif;
    Vector<unsigned short int> BoundHigh;

    enumerateSquare2D_Init(Mesh,R,LC,BoundHigh,Len,Motif,N);

    PropertyList<bool> flag;
    enumerateSquare2D_FixBondFlagInit(flag,Len,FixedBonds);

    int B,BS,BSL,BSH,BC,Z=0;
    bool oflag,bflag;
    B=0;
    enumerateSquare2D_InitFirstBond(BC,BS,BSL,BSH,LC[B],BoundHigh[B],Len[B]);
    do {
      oflag=
        (!flag[B][LC[B]])||
        enumerateSquare2D_Propagate(B,BS,BSL,BSH,LC[B],Len[B],R,Mesh);
      bflag=true;
      if(!oflag) {
        if(B<static_cast<int>(LC.size-1)) {
          enumerateSquare2D_NewBond(B,BC,BS,BSL,BSH,R,Mesh,LC,Len,BoundHigh);
          bflag=false;
        } else {
          WriteSequence(LC,OB,Z);
          ++Z;
        }
      }
      if(bflag)
        enumerateSquare2D_IncBond(B,BC,BS,BSL,BSH,R,Mesh,LC,Len,BoundHigh);
    } while(B>=0);
    return Z;
  }

  void enumerateSquare2D_FixedNodeIDInit(
      Vector<unsigned int>& NID, PropertyList<int>& rFixedNodes,
      const Vector<unsigned int>& Len, const PropertyList<int>& FixedNodes,
      const Vector<int>& R0) {
    allocate(NID,Len.size+1);
    copy(NID,FixedNodes.nunit);
    NID[0]=0;
    int n,m;
    n=0;
    m=Len[n];
    NID[n+1]=NID[n];
    for(unsigned int i=0;i<FixedNodes.nunit;++i) {
      if(FixedNodes[i][0]<m) ++NID[n+1];
      else {
        do {
          ++n;
          m+=Len[n];
          NID[n+1]=NID[n];
        } while(FixedNodes[i][0]>=m);
        ++NID[n+1];
      }
    }
    imprint(rFixedNodes,FixedNodes);
    copy(rFixedNodes,FixedNodes);
    for(unsigned int i=0;i<rFixedNodes.nunit;++i) {
      rFixedNodes[i][1]+=R0[0];
      rFixedNodes[i][2]+=R0[1];
    }
  }

  bool enumerateSquare2D_CheckNodes(
      const unsigned int NIDL, const unsigned int NIDH,
      const PropertyList<int>& FixedNodes, const PropertyList<int>& R) {
    bool flag=false;
    for(unsigned int i=NIDL,n;i<NIDH;++i) {
      n=FixedNodes[i][0];
      if((R[n][0]!=FixedNodes[i][1])||(R[n][1]!=FixedNodes[i][2])) {
        flag=true;
        break;
      }
    }
    return flag;
  }

  template <typename OutputType>
  int enumerateSquare2DFixedNode(
      const unsigned int N, const PropertyList<int>& FixedNodes,
      OutputType& OB) {
    PropertyList<int> Mesh,R;
    LatticeChain<SquareLattice,2> LC;
    Vector<unsigned int> Len;
    Vector<PropertyList<unsigned int> > Motif;
    Vector<unsigned short int> BoundHigh;

    enumerateSquare2D_Init(Mesh,R,LC,BoundHigh,Len,Motif,N);

    Vector<unsigned int> NID;
    PropertyList<int> rFixedNodes;
    enumerateSquare2D_FixedNodeIDInit(NID,rFixedNodes,Len,FixedNodes,R[0]);

    int B,BS,BSL,BSH,BC,Z=0;
    bool oflag,bflag;
    B=0;
    enumerateSquare2D_InitFirstBond(BC,BS,BSL,BSH,LC[B],BoundHigh[B],Len[B]);
    do {
      oflag=enumerateSquare2D_Propagate(B,BS,BSL,BSH,LC[B],Len[B],R,Mesh);
      oflag=oflag||enumerateSquare2D_CheckNodes(NID[B],NID[B+1],rFixedNodes,R);
      bflag=true;
      if(!oflag) {
        if(B<static_cast<int>(LC.size-1)) {
          enumerateSquare2D_NewBond(B,BC,BS,BSL,BSH,R,Mesh,LC,Len,BoundHigh);
          bflag=false;
        } else {
          WriteSequence(LC,OB,Z);
          ++Z;
        }
      }
      if(bflag)
        enumerateSquare2D_IncBond(B,BC,BS,BSL,BSH,R,Mesh,LC,Len,BoundHigh);
    } while(B>=0);
    return Z;
  }

}

#endif

