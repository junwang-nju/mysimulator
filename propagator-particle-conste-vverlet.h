
#ifndef _Propagator_Particle_ConstE_vverlet_H_
#define _Propagator_Particle_ConstE_vverlet_H_

#include "property.h"
#include "param-list.h"
#include "id-list-set.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void Particle_ConstE_VelVerlet(
      Property& nowProp,
      varVector<Property>& PropSet,
      const ParamList& PList,
      IDListSet<DistEvalObj,GeomType>& IDLS,
      const varVector<varVector<double> >& mvParm,
      DistEvalObj& DEval, const GeomType& Geo) {
    nowProp.Coordinate.shift(mvParm[1][0],nowProp.Velocity);
  }

}

#endif

