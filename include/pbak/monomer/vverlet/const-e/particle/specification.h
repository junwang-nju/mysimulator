
#ifndef _Propagator_Monomer_VelocityVerlet_ConstantE_Particle_Specification_H_
#define _Propagator_Monomer_VelocityVerlet_ConstantE_Particle_Specification_H_

#include "propagator/monomer/interface.h"
#include "propagator/monomer/move-ensemble-interface.h"
#include "propagator/data/interface.h"

namespace mysimulator {

  template <typename T>
  struct MonomerPropagator<ParticleType,VelocityVerlet,ConstantE,T>
      : public MonomerPropagatorMoveEnsemble<VelocityVerlet,ConstantE,T> {

    typedef MonomerPropagator<ParticleType,VelocityVerlet,ConstantE,T>  Type;
    typedef MonomerPropagatorMoveEnsemble<VelocityVerlet,ConstantE,T>
            ParentType;

    T HalfTimeStepIvM;

    MonomerPropagator() : ParentType(), HalfTimeStepIvM(0) {}
    MonomerPropagator(const Type&) {
      Error("Copier of MonomerPropagator Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for MonomerPropagator Disabled!");
      return *this;
    }
    ~MonomerPropagator() { clearData(); }

    void clearData() {
      HalfTimeStepIvM=0;
      release(*static_cast<ParentType*>(this));
    }

    void BeforeG(const PropagatorData<VelocityVerlet,ConstantE,T>& GP) {
      shift(this->VVector,-HalfTimeStepIvM,this->GVector);
      shift(this->XVector,GP.TimeStep,this->VVector);
    }
    void AfterG(const PropagatorData<VelocityVerlet,ConstantE,T>& GP) {
      shift(this->VVector,-HalfTimeStepIvM,this->GVector);
    }

  };

  template <typename T>
  bool IsValid(const
      MonomerPropagator<ParticleType,VelocityVerlet,ConstantE,T>& P) {
    typedef MonomerPropagatorMoveEnsemble<VelocityVerlet,ConstantE,T> Type;
    return IsValid(static_cast<Type&>(P));
  }

  template <typename T>
  void release(MonomerPropagator<ParticleType,VelocityVerlet,ConstantE,T>& P) {
    P.clearData();
  }

}

#endif

