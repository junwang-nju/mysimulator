
#ifndef _Interaction_Angle_Base_H_
#define _Interaction_Angle_Base_H_

#include "ref-vector.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc_Angle_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy,
      void (*efunc)(const double, const double, const double,
                    const VectorBase<double>&, double&)) {
    double DSQ01,DSQ12,DSQ20;
    DEval.Evaluate(Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    DSQ01=DEval.DistanceSQ();
    DEval.Evaluate(Coor[Idx[1]],Coor[Idx[2]],Idx[1],Idx[2],Geo);
    DSQ12=DEval.DistanceSQ();
    DEval.Evaluate(Coor[Idx[2]],Coor[Idx[0]],Idx[2],Idx[0],Geo);
    DSQ20=DEval.DistanceSQ();
    double ee;
    efunc(DSQ01,DSQ12,DSQ20,Param,ee);
    Energy+=ee;
  }

}

#endif

