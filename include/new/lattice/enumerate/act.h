
#ifndef _Lattice_Enumerate_Act_H_
#define _Lattice_Enumerate_Act_H_

#include "lattice/library/interface.h"
#include "lattice/enumerate/method/interface.h"
#include "lattice/node/coordinate/plus.h"
#include "array/1d/refer.h"
#include "lattice/output/interface.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim, LatticeEnumMethodName LEN,
            LatticeOutputMethodName LON>
  unsigned long long
  enumerate(const unsigned int& L, LatticeEnumMethod<LSN,Dim,LEN>& Method,
            LatticeOutput<LSN,Dim,LON>& Out){
    assert(IsValid(Method));
    LatticeMesh<LSN,Dim> M;
    Array1D<typename LatticeNodeCoordinate<LSN,Dim>::Type> Pos;
    Array1D<typename LatticeLibrary<LSN,Dim>::NodeType*> parent,child;
    Array1D<unsigned int> DepthReq,PosOrigin;
    Array1D<int> Branch,State,oBranch;
    typename LatticeLibrary<LSN,Dim>::NodeType *now;
    unsigned int level;
    int state;

    allocate(M);
    M.nullify();
    allocate(Pos,L);
    allocate(parent,L);
    allocate(child,L);
    allocate(DepthReq,L);
    allocate(PosOrigin,L);
    for(unsigned int i=0,w=0,v=L-1,u=LatticeLibrary<LSN,Dim>::MaxDepth;i<L;++i){
      u=(u<v?u:v);
      DepthReq[i]=u;
      PosOrigin[i]=w;
      if(u==0) { u=LatticeLibrary<LSN,Dim>::MaxDepth; w=i; }
      --u;
      --v;
    }
    allocate(Branch,L);   fill(Branch,-1);
    refer(oBranch,Branch,1,L-1,1);
    allocate(State,L);

    Method.PreProcess(Branch,State,Pos,M,level,parent,child,now);

    unsigned long long int NC=0;
    while(true) {
      if(!M.occupied(Pos[level])) {
        if(level<L-1) {
          M.set_occupied(Pos[level]);
          ++level;
          parent[level]=now;
        } else {
          NC++;
          Out(oBranch,M,Pos);
        }
      }
      do {
        do {
          Branch[level]++;
          while(Branch[level]>=
                static_cast<int>(LatticeLibrary<LSN,Dim>::NumChildren)) {
            Branch[level]=-1;
            --level;
            if(level==0)  break;
            M.remove_occupied(Pos[level]);
            Branch[level]++;
          }
          if(level==0)  break;
          state=Method.NextState(Branch,State,Pos,level);
        } while(state<0);
        if(level==0)  break;
        now=child[level-1]+Branch[level];
      } while(now->Depth<static_cast<int>(DepthReq[level]));
      if(level==0)  break;
      State[level]=state;
      child[level]=(DepthReq[level]==0?Method.Lib().root->child:
                                       now->child);
      plus(Pos[level],Pos[PosOrigin[level]],now->Pos);
    }

    release(State);
    release(oBranch);
    release(Branch);
    release(PosOrigin);
    release(DepthReq);
    release(child);
    release(parent);
    release(Pos);
    release(M);

    return NC;
  }

}

#endif

