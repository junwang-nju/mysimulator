
#ifndef _Interaction_Pairwise_Base_H_
#define _Interaction_Pairwise_Base_H_

#include "ref-vector.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc_Pairwise_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy,
      void (*efunc)(const double, const VectorBase<double>&, double&)) {
    DEval.Evaluate(Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    double DistSQ=DEval.DistanceSQ();
    double ee;
    efunc(DistSQ,Param,ee);
    Energy+=ee;
  } 

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc_Pairwise_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      VectorBase<refVector<double> >& Gradient,
      void (*gfunc)(const double, const VectorBase<double>&, double&)) {
    DEval.Evaluate(Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    double DistSQ=DEval.DistanceSQ();
    double ef;
    gfunc(DistSQ,Param,ef);
    Gradient[Idx[0]].shift(+ef,DEval.Displacement(),DEval.Dimension());
    Gradient[Idx[1]].shift(-ef,DEval.Displacement(),DEval.Dimension());
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc_Pairwise_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy, VectorBase<refVector<double> >& Gradient,
      void (*bfunc)(const double,const VectorBase<double>&,double&,double&)) {
    DEval.Evaluate(Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    double DistSQ=DEval.DistanceSQ();
    double ee,ef;
    bfunc(DistSQ,Param,ee,ef);
    Energy+=ee;
    Gradient[Idx[0]].shift(+ef,DEval.Displacement(),DEval.Dimension());
    Gradient[Idx[1]].shift(-ef,DEval.Displacement(),DEval.Dimension());
  }

}

#endif

