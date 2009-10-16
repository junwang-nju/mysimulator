
#ifndef _Propagator_ConstE_VelVerlet_H_
#define _Propagator_ConstE_VelVerlet_H_

#include "propagator-particle-conste-vverlet.h"
#include "interaction-4listset.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void SetAs_VelVerlet(
      const varVector<Property>& PropSet,
      varVector<MonomerPropagatorFormat<DistEvalObj,GeomType> >& MvSet) {
    uint n=PropSet.size(),mType;
    MvSet.allocate(n);
    for(uint i=0;i<n;++i) {
      mType=PropSet[i].MonomerType;
      if(mType==Particle)
        SetAs_ParticleConstEVelVerlet(MvSet[i]);
      else if(mType>NumberTypes) myError("Unknown monomer type!");
    }
  }

  template <typename DistEvalObj, typename GeomType>
  void Propagate_ConstEVelVerlet(
      varVector<Property>& PropSet, const ParamList& PList,
      varVector<IDList<DistEvalObj,GeomType> >& IDLS,
      varVector<MonomerPropagatorFormat<DistEvalObj,GeomType> >& mv,
      DistEvalObj& DEval, const GeomType& Geo) {
    uint n=PropSet.size();
    for(uint i=0;i<n;++i) mv[i].mvfunc[0](PropSet[i],mv[i].PropagatorParam);
    DEval.Update();
    for(uint i=0;i<n;++i) PropSet[i].Gradient=0.;
    G_ListSet(PropSet,PList,IDLS,DEval,Geo);
    for(uint i=0;i<n;++i) mv[i].mvfunc[1](PropSet[i],mv[i].PropagatorParam);
  }

}

#endif
