
#ifndef _Propagator_Base_Allocate_H_
#define _Propagator_Base_Allocate_H_

#include "propagator/base/parameter/vverlet/update.h"
#include "list/allocate.h"
#include "vector/fill.h"

namespace mysimulator {

  template <typename T>
  void allocate(PropagatorBase<T>& P, const PropagatorMoveName& Mv,
                const Vector<PropagatorEnsembleName>& Es,
                const Vector<Vector<PropagatorMonomerName> >& Mn,
                const unsigned int nunit, const unsigned int dim) {
    release(P);
    P.MoveMode=Mv;
    switch(Mv) {
      case VelocityVerlet:
        allocate(P.Data,PropagatorBaseNumberParameterVelocityVerlet);
        P.Update=UpdatePropagatorBaseVelocityVerlet<T>;
        break;
      default:
        Error("Unknown Move Type!");
    }
    assert(Es.size==Mn.size);
    allocate(P.Sys,Es.size);
    for(unsigned int i=0;i<P.Sys.size;++i) allocate(P.Sys[i],Mv,Es[i],Mn[i]);
    Vector<unsigned int> sz;
    allocate(sz,nunit);
    fill(sz,dim);
    allocate(P.X,sz);
    allocate(P.V,sz);
    allocate(P.G,sz);
    allocate(P.Msk,sz);
    allocate(sz,Es.size);
    for(unsigned int i=0;i<Es.size;++i) sz[i]=Mn[i].size;
    allocate(P.ID,sz);
    release(sz);
  }

  template <typename T>
  void allocate(PropagatorBase<T>& P, const PropagatorMoveName& Mv,
                const Vector<PropagatorEnsembleName>& Es,
                const List<PropagatorMonomerName>& Mn,
                const unsigned int nunit, const unsigned int dim) {
    allocate(P,Mv,Es,Mn.infra,nunit,dim);
  }

  template <typename T>
  void imprint(PropagatorBase<T>& P, const PropagatorBase<T>& cP) {
    assert(IsValid(cP));
    release(P);
    P.MoveMode=cP.MoveMode;
    imprint(P.Data,cP.Data);
    imprint(P.Sys,cP.Sys);
    imprint(P.X,cP.X);
    imprint(P.V,cP.V);
    imprint(P.G,cP.G);
    imprint(P.Msk,cP.Msk);
    P.Update=cP.Update;
  }

}

#endif

