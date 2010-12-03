
#ifndef _Build_Parameter_Propagator_ConstantE_VelocityVerlet_H_
#define _Build_Parameter_Propagator_ConstantE_VelocityVerlet_H_

#include "data/basic/vector.h"
#include "data/basic/unique-parameter.h"
#include "data/name/parameter-propagator-type.h"
#include "operation/parameter/build-param-propagator-base.h"

namespace std {

  void allocatePropagatorEVParameter(Vector<UniqueParameter>& P) {
    allocate(P,PropagatorEVNumberParameter);
    P[PropagatorMode].u=ConstantE_VelocityVerlet;
  }

  template <typename T>
  void BuildParameterPropagatorEV(
      UniqueParameter* GP, Vector<UniqueParameter>* P, const unsigned int nu) {
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

