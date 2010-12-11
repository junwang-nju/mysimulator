
#ifndef _SubSystem_Propagator_H_
#define _SubSystem_Propagator_H_

#include "data/propagator/monomer-propagator.h"

namespace std {

  template <typename T>
  struct subsysPropagator : public Vector<UniqueParameter> {
    typedef subsysPropagator<T> Type;
    typedef Vector<UniqueParameter> ParentType;
    
    Vector<monomerPropagator<T> >   merPg;

    subsysPropagator() : ParentType(), merPg() {}
    subsysPropagator(const Type& SP) {
      myError("Cannot create subsystem propagator");
    }
    Type& operator=(const Type& SP) {
      myError("Cannot copy subsystem propagator");
      return *this;
    }
    ~subsysPropagator() { release(*this); }
  };

  template <typename T>
  bool IsAvailable(const subsysPropagator<T>& P) {
    bool fg=IsAvailable(static_cast<const Vector<UniqueParameter>&>(P))&&
            IsAvailable(P.merPg);
    if(fg)
      for(unsigned int i=0;i<P.merPg.size;++i)  fg=fg&&IsAvailable(P.merPg[i]);
    return fg; 
  }

  template <typename T>
  void release(const subsysPropagator<T>& SP) {
    release(SP.merPg);
    release(static_cast<Vector<UniqueParameter>&>(SP));
  }

  template <typename T>
  void copy(subsysPropagator<T>& P, const subsysPropagator<T>& cP) {
    assert(IsAvailable(P));
    assert(IsAvailable(cP));
    assert(P.merPg.size==cP.merPg.size);
    typedef Vector<UniqueParameter>   VU;
    copy(static_cast<VU&>(P),static_cast<const VU&>(cP));
    for(unsigned int i=0;i<P.merPg.size;++i) copy(P.merPg[i],cP.merPg[i]);
  }

  template <typename T>
  void refer(subsysPropagator<T>& P, const subsysPropagator<T>& rP) {
    assert(IsAvailable(rP));
    typedef Vector<UniqueParameter> VU;
    release(P);
    refer(P.merPg,rP.merPg);
    refer(static_cast<VU&>(P),static_cast<const VU&>(rP));
  }

}

#endif
