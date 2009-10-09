
#ifndef _Propagator_Particle_ConstE_vverlet_H_
#define _Propagator_Particle_ConstE_vverlet_H_

#include "property.h"
#include "param-list.h"
#include "id-list-set.h"
#include "interaction-4listset.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void Particle_ConstE_VelVerlet(
      Property& nowProp,
      varVector<Property>& PropSet,
      const ParamList& PList,
      IDListSet<DistEvalObj,GeomType>& IDLS,
      const varVector<varVector<double> >& mvParm,
      DistEvalObj& DEval, const GeomType& Geo) {
    nowProp.Coordinate.shift(mvParm[0][0],nowProp.Velocity);
    nowProp.Velocity.shift(mvParm[1][0],nowProp.Gradient);
    G_ListSet(PropSet,PList,IDLS,mvParm,DEval,Geo);
  }

}

#endif

