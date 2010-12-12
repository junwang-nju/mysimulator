
#ifndef _Propagator_H_
#define _Propagator_H_

#include "data/propagator/subsys-propagator.h"
#include "data/basic/property-list.h"

namespace std {

  template <typename T>
  struct Propagator : public Vector<UniqueParameter> {
    typedef Propagator<T> Type;
    typedef Vector<UniqueParameter>   ParentType;
    
    Vector<subsysPropagator<T> >  sysPg;
    PropertyList<T> X;
    PropertyList<T> V;
    PropertyList<T> G;
    PropertyList<T> Msk;

    Propagator() : ParentType(), sysPg(), X(), V(), G(), Msk() {}
    Propagator(const Type& P) { myError("Cannot create propagator"); }
    Type& operator=(const Type& P) {
      myError("Cannot copy propagator");
      return *this;
    }
    ~Propagator() { release(*this); }
  };

  template <typename T>
  void IsAvailable(const Propagator<T>& P) {
    bool fg=IsAvailable(static_cast<const Vector<UniqueParameter>&>(P))&&
            IsAvailable(P.sysPg)&&IsAvailable(P.X)&&IsAvailable(P.V)&&
            IsAvailable(P.G)&&IsAvailable(P.Msk);
    if(fg)
      for(unsigned int i=0;i<P.sysPg.size;++i)  fg=fg&&IsAvailable(P.sysPg[i]);
  }

  template <typename T>
  void release(Propagator<T>& P) {
    release(P.sysPg);
    releasr(P.X);
    releasr(P.V);
    releasr(P.G);
    releasr(P.Msk);
    release(static_cast<Vector<UniqueParameter>&>(P));
  }

  template <typename T>
  void copy(Propagator<T>& P, const Propagator<T>& cP) {
    assert(IsAvailable(P));
    assert(IsAvailable(cP));
    typedef Vector<UniqueParameter> VU;
    copy(static_cast<VU&>(P),static_cast<const VU&>(cP));
    copy(P.sysPg,cP.sysPg);
    copy(P.X,cP.X);
    copy(P.V,cP.V);
    copy(P.G,cP.G);
    copy(P.Msk,cP.Msk);
  }

  template <typename T>
  void refer(Propagator<T>& P, const Propagator<T>& rP) {
    assert(IsAvailable(rP));
    typedef Vector<UniqueParameter> VU;
    release(P);
    refer(P.sysPg,rP.sysPg);
    refer(P.X,rP.X);
    refer(P.V,rP.V);
    refer(P.G,rP.G);
    refer(P.Msk,rP.Msk);
    refer(static_cast<VU&>(P),static_cast<const VU&>(rP));
  }

}

#endif
