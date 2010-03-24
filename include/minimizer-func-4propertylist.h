
#ifndef _Minimizer_Function_For_PropertyList_H_
#define _Minimizer_Function_For_PropertyList_H_

#include "minimizer-parameter-4propertylist.h"
#include "interaction-4listset.h"
#include "property-list.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecType>
  void EFunc_4PropertyList(
      const PropertyList<double,VecType>& CoorSeq, double& Energy,
      MinimizerParameter4PropertyList<DistEvalMethod,GeomType>& MParam) {
    EFunc(MParam.CoorLst,MParam.IMethodLst,MParam.IdxLst,MParam.ParamLst,
          MParam.DEval,MParam.Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecType>
  void GFunc_4PropertyList(
      const PropertyList<double,VecType>& CoorSeq,
      PropertyList<double,VecType>& GradSeq,
      MinimizerParameter4PropertyList<DistEvalMethod,GeomType>& MParam) {
    GFunc(MParam.CoorLst,MParam.IMethodLst,MParam.IdxLst,MParam.ParamLst,
          MParam.DEval,MParam.Geo,MParam.GradLst);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecType>
  void BFunc_4PropertyList(
      const PropertyList<double,VecType>& CoorSeq,
      double& Energy, PropertyList<double,VecType>& GradSeq,
      MinimizerParameter4PropertyList<DistEvalMethod,GeomType>& MParam) {
    BFunc(MParam.CoorLst,MParam.IMethodLst,MParam.IdxLst,MParam.ParamLst,
          MParam.DEval,MParam.Geo,Energy,MParam.GradLst);
  }

}

#endif

