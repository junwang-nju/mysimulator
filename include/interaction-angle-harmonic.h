
#ifndef _Interaction_Angle_Harmonic_H_
#define _Interaction_Angle_Harmonic_H_

#include "interaction-angle-base.h"
#include "functional-angle-harmonic.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc_Angle_Harmonic(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >&,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy) {
    EFunc_Angle_Base(Coor,Idx,Param,DEval,Geo,Energy,FuncAngHarmonic);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc_Angle_Harmonic(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >& tmVec,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      VectorBase<refVector<double> >& Grad) {
    GFunc_Angle_Base(Coor,Idx,Param,tmVec,DEval,Geo,Grad,DiffAngHarmonic);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc_Angle_Harmonic(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >& tmVec,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy, VectorBase<refVector<double> >& Grad) {
    BFunc_Angle_Base(Coor,Idx,Param,tmVec,DEval,Geo,
                     Energy,Grad,BothAngHarmonic);
  }

}

#endif
