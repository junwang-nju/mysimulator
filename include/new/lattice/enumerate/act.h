
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
    LatticeMesh<LSN,Dim> M;
    M.nullify();
    typename LatticeNodeCoordinate<LSN,Dim>::Type *Pos;
    Pos=new typename LatticeNodeCoordinate<LSN,Dim>::Type[L];
    for(unsigned int i=0;i<L;++i) Pos[i].nullify();
    unsigned int level;
    Array1D<int> Branch,LevRq,PosOrigin;
    allocate(Branch,1U,L-1);
    fill(Branch,-1);
    allocate(LevRq,L);
    int u=LatticeLibrary<LSN,Dim>::MaxDepth,v;
    for(unsigned int i=0;i<L;++i) {
      LevRq[i]=u;
      u--;
      if(u==0) u=LatticeLibrary<LSN,Dim>::MaxDepth;
    }
    allocate(PosOrigin,L);
    u=0; v=0;
    for(unsigned int i=0;i<L;++i) {
      PosOrigin[i]=v;
      if(u==(int)(LatticeLibrary<LSN,Dim>::MaxDepth))  { v+=u; u=0; }
      u++;
    }

    typename LatticeLibrary<LSN,Dim>::NodeType *now;
    level=0;
    now=LatticeLibrary<LSN,Dim>::root;
    Pos[0].nullify();
    while(true) {
      COut<<Branch<<Endl;
      COut<<level<<Endl;
      COut<<Pos[level]<<Endl;
      COut<<"######  "<<M.occupied(Pos[level])<<Endl;
      if(!M.occupied(Pos[level])) {
        if(level<L-1) {
          M.set_occupied(Pos[level]);
          level++;
          if((level>0)&&(level%LatticeLibrary<LSN,Dim>::MaxDepth==0))
            now=LatticeLibrary<LSN,Dim>::root->child;
          else now=now->child;
          COut<<"*******  "<<LevRq[level]<<"\t"<<now->Depth<<Endl;
          if(((int)(L-1-level)>now->Depth)&&(now->Depth<LevRq[level])) {
            level--;
            now=now->parent;
            COut<<"+++++++++++"<<Endl;
          }
        } else {
          COut<<"=======A======"<<Endl;
        }
        COut<<"-----------1-----------"<<Endl;
      }
      Branch[level]++;
      COut<<Branch<<Endl;
      while(true) {
        COut<<level<<"\t"<<Branch[level]<<Endl;
        if(Branch[level]>=static_cast<int>(LatticeLibrary<LSN,Dim>::NumChildren)) {
          Branch[level]=-1;
          level--;
          now=now->parent;
          if(level==0) break;
          M.remove_occupied(Pos[level]);
          Branch[level]++;
        } else if(now->parent->child[Branch[level]].Depth==-1) {
          Branch[level]++;
        } else break;
      }
      COut<<"--------------2----------------"<<Endl;
      now=now->parent->child+Branch[level];
      COut<<PosOrigin[level]<<Endl;
      plus(Pos[level],Pos[PosOrigin[level]],now->Pos);
      COut<<Branch<<Endl;
      COut<<"--------------3----------------"<<Endl;
    }
    release(Branch);
    delete_array(Pos);
  }

}

#endif

