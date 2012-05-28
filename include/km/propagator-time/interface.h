
#ifndef _Propagator_Time_Interface_H_
#define _Propagator_Time_Interface_H_

#include "array/interface.h"
#include "unique/64bit/interface.h"
#include "propagator/name.h"

namespace mysimulator {

  template <typename T>
  class PropagatorTime {

    public:

      typedef PropagatorTime<T>   Type;
      template <typename T1> friend void Clear(PropagatorTime<T1>&);

      PropagatorTime() : _tag(UnknownPropagator), _param() {}
      ~PropagatorTime() { Clear(*this); }

      bool IsValid() const { return _param.IsValid(); }
      const PropagatorName Name() const { return _tag; }
      Unique64Bit& Parameter(unsigned int n) { return _param[n]; }
      const Unique64Bit& Parameter(unsigned int n) const { return _param[n]; }

      virtual void Allocate() = 0;
      virtual bool IsTProperty(unsigned int n) = 0;
      virtual bool IsUIntProperty(unsigned int n) = 0;
      virtual void Update(unsigned int) = 0;

    protected:

      PropagatorName  _tag;
      Array<Unique64Bit>  _param;

    private:

      PropagatorTime(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(PropagatorTime<T>& T) {
    Clear(T._param);
    T._tag=UnknownPropagator;
  }

}

#include "propagator-time/molecular-dynamics/interface.h"

namespace mysimulator {

  template <typename T>
  void Introduce(PropagatorTime<T>*& T,PropagatorName PN) {
    if(T!=NULL) { delete T; T=NULL; }
    switch(PN) {
      case MolecularDynamics:
        T=new PropagatorMDTime;
        break;
      default:
        fprintf(stderr,"Unknown Propagator Name!\n");
    }
    if(T!=NULL) T->Allocate();
  }

}

#endif

