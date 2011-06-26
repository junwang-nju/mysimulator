
#ifndef _Propagator_Monomer_VelocityVerlet_Specification_H_
#define _Propagator_Monomer_VelocityVerlet_Specification_H_

#include "propagator/monomer/move-interface.h"
#include "propagator/move-name.h"
#include "propagator/monomer/common/interface.h"

namespace mysimulator {

  template <typename T>
  struct MonomerPropagatorMove<VelocityVerlet,T>
      : public MonomerPropagatorCommon<T> {

    typedef MonomerPropagatorMove<VelocityVerlet,T>   Type;
    typedef MonomerPropagatorCommon<T>  ParentType;

    MonomerPropagatorMove() : ParentType() {}
    MonomerPropagatorMove(const Type&) {
      Error("Copier of MonomerPropagatorMove Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= of MonomerPropagatorMove Disabled!");
      return *this;
    }
    ~MonomerPropagatorMove() { clearData(); }

    void clearData() { release(static_cast<ParentType*>(this)); }

  };

  template <typename T>
  bool IsValid(const MonomerPropagatorMove<VelocityVerlet,T>& P) {
    typedef MonomerPropagatorCommon<T>  Type;
    return IsValid(static_cast<Type&>(P));
  }

  template <typename T>
  void release(MonomerPropagatorMove<VelocityVerlet,T>& P) { P.clearData(); }

}

#endif

