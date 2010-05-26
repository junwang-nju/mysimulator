
#ifndef _Interaction_Expanded_Core_Pairwise_Base_H_
#define _Interaction_Expanded_Core_Pairwise_Base_H_

#include "ref-vector.h"
#include "parameter-name-expanded-core-common.h"
#include <cmath>

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc_ExpandedCore_Pairwise_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy,
      void (*efunc)(const double,const VectorBase<double>&,double&)) {
    DEval.Evaluate(Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    double cDistSQ=DEval.DistanceSQ();
    double cDist=sqrt(cDistSQ);
    double Dist=cDist-Param[ExpandCoreCommon_CoreRadius];
    assert(Dist>=0);
    double DistSQ=Dist*Dist;
    static refVector<double> rParam;
    rParam.refer(Param,1,Param.size()-1);
    efunc(DistSQ,rParam,ee);
    Energy+=ee;
  }

}

#endif

