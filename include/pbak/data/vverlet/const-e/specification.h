
#ifndef _Propagator_Data_VelocityVerlet_ConstantE_Specification_H_
#define _Propagator_Data_VelocityVerlet_ConstantE_Specification_H_

#include "propagator/data/interface.h"
#include "propagator/data/move-interface.h"

namespace mysimulator {

  template <typename T>
  struct PropagatorData<VelocityVerlet,ConstantE,T>
      : public PropagatorDataMove<VelocityVerlet,T> {

      typedef PropagatorData<VelocityVerlet,ConstantE,T>    Type;
      typedef PropagatorDataMove<VelocityVerlet,T>    ParentType;

      PropagatorData() : ParentType() {}
      PropagatorData(const Type&) {
        Error("Copier of PropagatorData Disabled!");
      }
      Type& operator=(const Type&) {
        Error("Operator= for PropagatorData Disabled!");
        return *this;
      }
      ~PropagatorData() { clearData(); }

      void clearData() { release(*static_cast<ParentType*>(this)); }

  };

  template <typename T>
  bool IsValid(const PropagatorData<VelocityVerlet,ConstantE,T>& PD) {
    typedef PropagatorDataMove<VelocityVerlet,T>  Type;
    return IsValid(static_cast<const Type&>(PD));
  }

  template <typename T>
  void release(PropagatorData<VelocityVerlet,ConstantE,T>& PD) {
    PD.clearData();
  }

}

#endif

