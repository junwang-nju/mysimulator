
#ifndef _Propagator_Monomer_VelocityVerlet_ConstantE_Specification_H_
#define _Propagator_Monomer_VelocityVerlet_ConstantE_Specification_H_

#include "propagator/monomer/move-interface.h"
#include "propagator/monomer/move-ensemble-interface.h"

namespace mysimulator {

  template <typename T>
  struct MonomerPropagatorMoveEnsemble<VelocityVerlet,ConstantE,T>
      : public MonomerPropagatorMove<VelocityVerlet,T> {

    typedef MonomerPropagatorMoveEnsemble<VelocityVerlet,ConstantE,T> Type;
    typedef MonomerPropagatorMove<VelocityVerlet,T> ParentType;

    MonomerPropagatorMoveEnsemble() : ParentType() {}
    MonomerPropagatorMoveEnsemble(const Type&) {
      Error("Copier of MonomerPropagatorMoveEnsemble Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for MonomerPropagatorMoveEnsemble Disabled!");
      return *this;
    }
    ~MonomerPropagatorMoveEnsemble() { clearData(); }

    void clearData() { release(*static_cast<ParentType*>(this)); }

  };

  template <typename T>
  bool IsValid(
      const MonomerPropagatorMoveEnsemble<VelocityVerlet,ConstantE,T>& P) {
    typedef MonomerPropagatorMove<VelocityVerlet,T> Type;
    return IsValid(static_cast<Type&>(P));
  }

  template <typename T>
  void release(MonomerPropagatorMoveEnsemble<VelocityVerlet,ConstantE,T>& P) {
    P.clearData();
  }

}

#endif

