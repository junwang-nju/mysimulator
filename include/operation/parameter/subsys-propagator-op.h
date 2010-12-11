
#ifndef _Subsystem_Propagator_Operation_H_
#define _Subsystem_Propagator_Operation_H_

#include "data/propagator/subsystem-propagator.h"
#include "data/name/subsys-propagator-type.h"
#include "data/name/monomer-propagator-type.h"

namespace std {

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
        myError("unknown subsystem propagator");
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
        myError("unknown subsystem propagator type");
    } else
      myError("unknown monomer type");
    return 0;
  }

  template <typename T>
  void allocate(subsysPropagator<T>& SP,
                const unsigned int& spgtype, const Vector<unsigned int>& mtype){
    release(SP);
    allocate(static_cast<Vector<UniqueParameter>&>(SP),
             subsysPropagatorParameterSize[spgtype]);
    assignBuild(SP,spgtype);
    allocate(SP.merPg,mtype.size);
    for(unsigned int i=0;i<mtype.size;++i)
      allocate(SP.merPg[i],composeMonomerPropagatorType(spgtype,mtype[i]));
  }

}

#endif
