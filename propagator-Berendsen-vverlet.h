
#ifndef _Propagator_Berendsen_VelVerlet_H_
#define _Propagator_Berendsen_VelVerlet_H_

#include "propagator-particle-Berendsen-vverlet.h"
#include "interaction-4listset.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void SetAs_BerendsenVelVerlet(
      const varVector<Property>& PropSet,
      varVector<MonomerPropagatorFormat<DistEvalObj,GeomType> >& MvSet) {
    uint n=PropSet.size(), mType;
    MvSet.allocate(n);
    for(uint i=0;i<n;++i) {
      mType=PropSet[i].MonomerType;
      if(mType==Particle)
        SetAs_ParticleBerendsenVelVerlet(MvSet[i]);
      else if(mType>NumberTypes) myError("Unknown monomer type!");
    }
  }

  template <typename DistEvalObj, typename GeomType>
  void Propagate_BerendsenVelVerlet(
      varVector<Property>& PropSet, const ParamList& PList,
      varVector<IDList<DistEvalObj,GeomType> >& IDLS,
      varVector<MonomerPropagatorFormat<DistEvalObj,GeomType> >& mv,
      DistEvalObj& DEval, const GeomType& Geo) {
    uint n=PropSet.size();
    for(uint i=0;i<n;++i) mv[i].mvfunc[BeforeG_4PBV](
        PropSet[i],mv[i].PropagatorParam);
    DEval.Update();
    for(uint i=0;i<n;++i) PropSet[i].Gradient=0.;
    G_ListSet(PropSet,PList,IDLS,DEval,Geo);
    for(uint i=0;i<n;++i) mv[i].mvfunc[AfterG_4PBV](
        PropSet[i],mv[i].PropagatorParam);
    double fac;
    fac=0;
    for(uint i=0;i<n;++i)
      fac+=normSQ(PropSet[i].Velocity)*PropSet[i].Mass[0];
    for(uint i=0;i<n;++i) mv[i].setfunc[SetScaleFac_4PBV](
        mv[i].PropagatorParam,&fac,1);
    for(uint i=0;i<n;++i) mv[i].mvfunc[PostProcess_4PBV](
        PropSet[i],mv[i].PropagatorParam);
  }

}

#endif
