
#ifndef _Build_Parameter_Propagator_Berendsen_VelocityVerlet_H_
#define _Build_Parameter_Propagator_Berendsen_VelocityVerlet_H_

#include "data/name/propagator-type.h"
#include "data/name/propagator-berendsen-vverlet.h"
#include "operation/parameter/build-param-propagator-base.h"
#include "operation/propagate/BV-move.h"

namespace std {

  template <template<typename,template<typename>class,typename> class IType,
            typename IdType, typename T, template<typename> class DBuffer,
            typename GeomType>
  void allocatePropagatorBVParameter(Vector<UniqueParameter>& P) {
    allocate(P,PropagatorBVNumberParameter);
    P[PropagatorMode].u=Berendsen_VelocityVerlet;
    typedef void (*MvFunc)(
        IType<T,DBuffer,GeomType>&,Vector<T>*,Vector<T>*,Vector<T>*,
        const Vector<T>*,const IdType&,Vector<UniqueParameter>&,
        Vector<UniqueParameter>*,const unsigned int&);
    P[StepMove].ptr=
      reinterpret_cast<void*>(
          static_cast<MvFunc>(BVMoveStep<IType,IdType,T,DBuffer,GeomType>));
  }

  template <typename T>
  void BuildParameterPropagatorBV(
      UniqueParameter* GP, Vector<UniqueParameter>* P, const unsigned int& nu){
    typedef void (*BuildFunc)(UniqueParameter*,const UniqueParameter*);
    BuildParameterPropagatorBase<T>(GP);
    copy(GP[BV_TemperatureDOF],
         GP[BV_Temperature].value<T>()*GP[BV_DegreeFreedom].value<T>());
    copy(GP[BV_HalfDeltaTIvRelaxT],
         GP[DeltaTime].value<T>()/GP[BV_RelaxTime].value<T>());
    copy(GP[BV_IvHalfDeltaTIvRelaxTPlusOne],
         1./(GP[BV_HalfDeltaTIvRelaxT].value<T>()+1.));
    copy(GP[BV_TemperatureDOFIvDKineticEnergy],
         GP[BV_TemperatureDOF].value<T>()/GP[BV_DualKineticEnergy].value<T>());
    for(unsigned int i=0;i<nu;++i)
      reinterpret_cast<BuildFunc>(P[i][pBuild].ptr)(P[i].data,GP);
  }

  template <typename T>
  void BuildParameterPropagatorBV(
      Vector<UniqueParameter>& GP, Vector<Vector<UniqueParameter> >& P) {
    assert(GP.size>=PropagatorBVNumberParameter);
    BuildParameterPropagatorBV<T>(GP.data,P.data,P.size);
  }

}

#include "data/basic/property-list.h"

namespace std {

  template <typename T>
  void BuildParameterPropagatorBV(
      Vector<UniqueParameter>& GP, PropertyList<UniqueParameter>& P) {
    assert(GP.size>=PropagatorBVNumberParameter);
    BuildParameterPropagatorBV<T>(GP.data,P.structure,P.nunit);
  }

}

#endif

