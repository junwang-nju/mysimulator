
#ifndef _Propagator_Data_VelocityVerlet_Specification_H_
#define _Propagator_Data_VelocityVerlet_Specification_H_

#include "propagator/data/interface.h"
#include "propagator/data/common/interface.h"

namespace mysimulator {

  template <typename T>
  struct PropagatorData<VelocityVerlet,T> : public PropagatorDataCommon<T> {

    typedef PropagatorData<VelocityVerlet,T>  Type;
    typedef PropagatorDataCommon<T> ParentType;

    PropagatorData() : ParentType() {}
    PropagatorData(const Type&) { Error("Copier of PropagatorData Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for PropagatorData Disabled!");
      return *this;
    }
    ~PropagatorData() { clearData(); }

    void clearData() { release(*static_cast<ParentType*>(this)); }

  };

  template <typename T>
  bool IsValid(const PropagatorData<VelocityVerlet,T>& PD) {
    typedef PropagatorDataCommon<T>   Type;
    return IsValid(static_cast<const Type&>(PD));
  }

  template <typename T>
  void release(PropagatorData<VelocityVerlet,T>& PD) { PD.clearData(); }

}

#endif

