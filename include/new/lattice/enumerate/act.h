
#ifndef _Lattice_Enumerate_Act_H_
#define _Lattice_Enumerate_Act_H_

#include "lattice/library/interface.h"
#include "lattice/enumerate/method/name.h"
#include "lattice/node/coordinate/plus.h"
#include "lattice/node/coordinate/io.h"

namespace mysimulator {

  //template <LatticeShapeName LSN, unsigned int Dim,
  //          LatticeEnumMethodName LEMN>
  //void enumerate(const unsigned int& L,
  //               LatticeEnumMethod<LSN,Dim,LatticeEnumMethodName>& Method,
  //               LatticeOutput<LSN,Dim>& os) {
  template <LatticeShapeName LSN, unsigned int Dim>
  void enumerate(const unsigned int& L) {
    if(!IsValid(LatticeLibrary<LSN,Dim>::root)) LatticeLibrary<LSN,Dim>::load();
    LatticeMesh<LSN,Dim> M;
    Array1D<typename LatticeNodeCoordinate<LSN,Dim>::Type> Pos;
    Array1D<typename LatticeLibrary<LSN,Dim>::NodeType*> parent,child;
    Array1D<unsigned int> DepthReq,PosOrigin;
    Array1D<int> Branch;
    typename LatticeLibrary<LSN,Dim>::NodeType *now;
    unsigned int level;

    M.nullify();
    allocate(Pos,L);
    allocate(parent,L);
    allocate(child,L);
    allocate(DepthReq,L);
    allocate(PosOrigin,L);
    for(unsigned int i=0,w=0,v=L-1,u=LatticeLibrary<LSN,Dim>::MaxDepth;i<L;++i) {
      u=(u<v?u:v);
      DepthReq[i]=u;
      PosOrigin[i]=w;
      if(u==0) { u=LatticeLibrary<LSN,Dim>::MaxDepth; w=i; }
      --u;
      --v;
    }
    allocate(Branch,1,L-1);   fill(Branch,-1);

    level=0;
    now=LatticeLibrary<LSN,Dim>::root;
    Pos[level].nullify();
    parent[level]=now->parent;
    child[level]=now->child;

    unsigned long long int NC=0,ND=0;
    while(true) {
      if(!M.occupied(Pos[level])) {
        if(level<L-1) {
          M.set_occupied(Pos[level]);
          ++level;
          parent[level]=now;
          //now=child[level-1];
        } else {
          NC++;
        }
      }
      do {
        Branch[level]++;
        while(Branch[level]>=static_cast<int>(LatticeLibrary<LSN,Dim>::NumChildren)) {
          Branch[level]=-1;
          //now=parent[level];
          --level;
          if(level==0)  break;
          M.remove_occupied(Pos[level]);
          Branch[level]++;
        }
        if(level==0)  break;
        now=child[level-1]+Branch[level];
        if(now->Depth==-1) ND++;
      } while(now->Depth<static_cast<int>(DepthReq[level]));
      if(level==0)  break;
      child[level]=(DepthReq[level]==0?LatticeLibrary<LSN,Dim>::root->child:now->child);
      plus(Pos[level],Pos[PosOrigin[level]],now->Pos);
    }

    release(Branch);
    release(PosOrigin);
    release(DepthReq);
    release(child);
    release(parent);
    release(Pos);

    COut<<NC<<Endl;
    COut<<ND<<Endl;
  }

}

#endif

