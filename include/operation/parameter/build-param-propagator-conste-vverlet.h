
#ifndef _Build_Parameter_Propagator_ConstantE_VelocityVerlet_H_
#define _Build_Parameter_Propagator_ConstantE_VelocityVerlet_H_

#include "data/name/propagator-type.h"
#include "data/name/propagator-conste-vverlet.h"
#include "operation/parameter/build-param-propagator-base.h"
#include "operation/propagate/EV-move.h"

namespace std {

  template <template<typename,template<typename>class,typename> class IType,
            typename PmType, typename T, template<typename> class DBuffer,
            typename GeomType>
  void allocatePropagatorEVParameter(Vector<UniqueParameter>& P) {
    allocate(P,PropagatorEVNumberParameter);
    P[PropagatorMode].u=ConstantE_VelocityVerlet;
    typedef void (*MvFunc)(
        IType<T,DBuffer,GeomType>&,Vector<T>*,Vector<T>*,Vector<T>*,
        const Vector<T>*,const PmType&,Vector<UniqueParameter>&,
        Vector<UniqueParameter>*,const unsigned int&);
    P[StepMove].ptr=
      reinterpret_cast<void*>(
          static_cast<MvFunc>(EVMoveStep<IType,PmType,T,DBuffer,GeomType>));
  }

  template <typename T>
  void BuildParameterPropagatorEV(
      UniqueParameter* GP, Vector<UniqueParameter>* P, const unsigned int& nu) {
    typedef void (*BuildFunc)(UniqueParameter*,const UniqueParameter*);
    BuildParameterPropagatorBase<T>(GP);
    for(unsigned int i=0;i<nu;++i)
      reinterpret_cast<BuildFunc>(P[i][pBuild].ptr)(P[i].data,GP);
  }

  template <typename T>
  void BuildParameterPropagatorEV(
      Vector<UniqueParameter>& GP, Vector<Vector<UniqueParameter> >& P) {
    assert(GP.size>=PropagatorEVNumberParameter);
    BuildParameterPropagatorEV<T>(GP.data,P.data,P.size);
  }

}

#include "data/basic/property-list.h"

namespace std {

  template <typename T>
  void BuildParameterPropagatorEV(
      Vector<UniqueParameter>& GP, PropertyList<UniqueParameter>& P) {
    assert(GP.size>=PropagatorEVNumberParameter);
    BuildParameterPropagatorEV<T>(GP.data,P.structure,P.nunit);
  }

}

#endif

