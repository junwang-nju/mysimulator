
#ifndef _Build_Parameter_Propagator_Langevin_VelocityVerlet_H_
#define _Build_Parameter_Propagator_Langevin_VelocityVerlet_H_

#include "data/name/propagator-type.h"
#include "data/name/propagator-langevin-vverlet.h"
#include "operation/parameter/build-param-propagator-base.h"
#include "operation/propagate/LV-move.h"

namespace std {

  template <template<typename,template<typename>class,typename> class IType,
            typename IdType, typename T, template<typename> class DBuffer,
            typename GeomType>
  void allocatePropagatorLVParameter(Vector<UniqueParameter>& P) {
    allocate(P,PropagatorLVNumberParameter);
    P[PropagatorMode].u=Langevin_VelocityVerlet;
    typedef void (*MvFunc)(
        IType<T,DBuffer,GeomType>&,Vector<T>*,Vector<T>*,Vector<T>*,
        const Vector<T>*,const IdType&,Vector<UniqueParameter>&,
        Vector<UniqueParameter>*,const unsigned int&);
    P[StepMove].ptr=
      reinterpret_cast<void*>(
          static_cast<MvFunc>(LVMoveStep<IType,IdType,T,DBuffer,GeomType>));
  }

  template <typename T>
  void BuildParameterPropagatorLV(
      UniqueParameter* GP, Vector<UniqueParameter>* P, const unsigned int& nu) {
    typedef void (*BuildFunc)(UniqueParameter*,const UniqueParameter*);
    BuildParameterPropagatorBase<T>(GP);
    copy(GP[LV_TemperatureDeltaT],
         GP[LV_Temperature].value<T>()*GP[DeltaTime].value<T>());
    for(unsigned int i=0;i<nu;++i)
      reinterpret_cast<BuildFunc>(P[i][pBuild].ptr)(P[i].data,GP);
  }

  template <typename T>
  void BuildParameterPropagatorLV(
      Vector<UniqueParameter>& GP, Vector<Vector<UniqueParameter> >& P) {
    assert(GP.size>=PropagatorLVNumberParameter);
    BuildParameterPropagatorLV<T>(GP.data,P.data,P.size);
  }

}

#include "data/basic/property-list.h"

namespace std{

  template <typename T>
  void BuildParameterPropagatorLV(
      Vector<UniqueParameter>& GP, PropertyList<UniqueParameter>& P) {
    assert(GP.size>=PropagatorLVNumberParameter);
    BuildParameterPropagatorLV<T>(GP.data,P.structure,P.nunit);
  }

}

#endif

