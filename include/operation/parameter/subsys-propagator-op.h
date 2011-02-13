
#ifndef _Subsystem_Propagator_Operation_H_
#define _Subsystem_Propagator_Operation_H_

#include "data/propagator/subsys-propagator.h"
#include "data/name/subsys-propagator-type.h"
#include "operation/propagate/subsys-move.h"
#include "operation/parameter/build-param-subsys-propagator.h"
#include "operation/parameter/monomer-propagator-op.h"

namespace std {

  template <typename T>
  void assignMoveMode(subsysPropagator<T>& SP,const unsigned int& spgtype) {
    switch(spgtype) {
      case ConstantE_VelocityVerlet:
      case Berendsen_VelocityVerlet:
      case Langevin_VelocityVerlet:
        SP[SubsysMoveMode].u=VelocityVerlet;
        break;
      default:
        Error("unknown subsystem propagator type");
    }
  }

  template <typename T>
  void assignEnsembleMode(subsysPropagator<T>& SP,const unsigned int& spgtype){
    switch(spgtype) {
      case ConstantE_VelocityVerlet:
        SP[SubsysEnsembleMode].u=ConstantE;
        break;
      case Berendsen_VelocityVerlet:
        SP[SubsysEnsembleMode].u=Berendsen;
        break;
      case Langevin_VelocityVerlet:
        SP[SubsysEnsembleMode].u=Langevin;
        break;
      default:
        Error("unknown subsystem propagator type");
    }
  }

  template <typename T>
  void assignBuild(subsysPropagator<T>& SP, const unsigned int& spgtype) {
    typedef void(*BuildFunc)(subsysPropagator<T>&);
    switch(spgtype) {
      case ConstantE_VelocityVerlet:
        SP[subsysPgBuild].ptr=
          reinterpret_cast<void*>(
              static_cast<BuildFunc>(BuildParameterSubsysPropagatorEV));
        break;
      case Berendsen_VelocityVerlet:
        SP[subsysPgBuild].ptr=
          reinterpret_cast<void*>(
              static_cast<BuildFunc>(BuildParameterSubsysPropagatorBV));
        break;
      case Langevin_VelocityVerlet:
        SP[subsysPgBuild].ptr=
          reinterpret_cast<void*>(
              static_cast<BuildFunc>(BuildParameterSubsysPropagatorLV));
        break;
      default:
        Error("unknown subsystem propagator type");
    }
  }

  template <typename T>
  void assignMove(subsysPropagator<T>& SP, const unsigned int& spgtype) {
    typedef void (*MoveFunc)(subsysPropagator<T>&);
    switch(spgtype) {
      case ConstantE_VelocityVerlet:
        SP[VVerletMove_BeforeG].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(EVMove_BeforeG));
        SP[VVerletMove_AfterG].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(EVMove_AfterG));
        break;
      case Berendsen_VelocityVerlet:
        SP[VVerletMove_BeforeG].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(BVMove_BeforeG));
        SP[VVerletMove_AfterG].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(BVMove_AfterG));
        break;
      case Langevin_VelocityVerlet:
        SP[VVerletMove_BeforeG].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(LVMove_BeforeG));
        SP[VVerletMove_AfterG].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(LVMove_AfterG));
        break;
      default:
        Error("unknown subsystem propagator type");
    }
  }

  unsigned int composeMonomerPropagatorType(const unsigned int& spgtype,
                                            const unsigned int& mertype) {
    if(mertype==ParticleType) {
      if(spgtype==ConstantE_VelocityVerlet)
        return ParticleConstEVVerlet;
      else if(spgtype==Berendsen_VelocityVerlet)
        return ParticleBerendsenVVerlet;
      else if(spgtype==Langevin_VelocityVerlet)
        return ParticleLangevinVVerlet;
      else
        Error("unknown subsystem propagator type");
    } else
      Error("unknown monomer type");
    return 0;
  }

  template <typename T>
  void allocate(subsysPropagator<T>& SP,
                const unsigned int& spgtype, const Vector<unsigned int>& mtype){
    release(SP);
    allocate(static_cast<Vector<UniqueParameter>&>(SP),
             subsysPropagatorParameterSize[spgtype]);
    assignMoveMode(SP,spgtype);
    assignEnsembleMode(SP,spgtype);
    assignBuild(SP,spgtype);
    assignMove(SP,spgtype);
    allocate(SP.merPg,mtype.size);
    for(unsigned int i=0;i<mtype.size;++i)
      allocate(SP.merPg[i],composeMonomerPropagatorType(spgtype,mtype[i]));
  }

}

#endif
