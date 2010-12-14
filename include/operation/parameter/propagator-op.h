
#ifndef _Propagator_Operation_H_
#define _Propagator_Operation_H_

#include "data/propagator/propagator.h"
#include "operation/parameter/subsys-propagator-op.h"
#include "operation/propagate/vverlet-move.h"

namespace std {

  template <typename ParameterType,
            template <typename,template<typename>class,typename> class IType,
            template <typename> class DBuffer, typename GeomType, typename T>
  void assignMove(Propagator<T>& P, const unsigned int& pgtype) {
    typedef void (*MoveFunc)(Propagator<T>&,IType<T,DBuffer,GeomType>&,
                             const ParameterType&);
    switch(pgtype) {
      case VelocityVerlet:
        P[PgStep].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(VVerletStep));
        break;
      default:
        myError("unknown propagator type");
    }
  }

  unsigned int composeSubsysPropagatorType(const unsigned int& pgtype,
                                           const unsigned int& ensembletype) {
    if(pgtype==VelocityVerlet) {
      if(ensembletype==ConstantE)       return ConstantE_VelocityVerlet;
      else if(ensembletype==Berendsen)  return Berendsen_VelocityVerlet;
      else if(ensembletype==Langevin)   return Langevin_VelocityVerlet;
      else myError("unknown ensemble type");
    } else myError("unknown propagator type");
    return 0;
  }

  template <typename ParameterType,
            template <typename,template<typename>class,typename> class IType,
            template <typename> class DBuffer, typename GeomType, typename T>
  void allocate(Propagator<T>& P, const unsigned int& pgtype,
                const Vector<unsigned int>& ensembletype,
                const Vector<Vector<unsigned int> >& mertype) {
    assert(ensembletype.size==mertype.size);
    allocate(static_cast<Vector<UniqueParameter>&>(P),
             PropagatorParameterSize[pgtype]);
    assignMove<ParameterType,IType,DBuffer,GeomType,T>(P,pgtype);
    copy(P[MoveMode],pgtype);
    allocate(P.sysPg,ensembletype.size);
    for(unsigned int i=0;i<ensembletype.size;++i)
      allocate(P.sysPg[i],composeSubsysPropagatorType(pgtype,ensembletype[i]),
                          mertype[i]);
  }

}

#endif

