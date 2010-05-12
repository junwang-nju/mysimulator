
#ifndef _Minimizer_Function_For_PropertyList_H_
#define _Minimizer_Function_For_PropertyList_H_

#include "minimizer-flat-parameter-4propertylist.h"
#include "minimizer-hierarchy-parameter-4propertylist.h"
#include "interaction-4listset.h"
#include "property-list.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecType>
  void EFunc_4PropertyList(
      const PropertyList<double,VecType>& CoorSeq, double& Energy,
      MinimizerFlatParameter4PropertyList<DistEvalMethod,GeomType>& MParam) {
    EFunc(CoorSeq.Structure(),MParam.IMethodLst,MParam.IdxLst.Structure(),
          MParam.ParamLst,MParam.DEval,MParam.Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecType>
  void GFunc_4PropertyList(
      const PropertyList<double,VecType>& CoorSeq,
      PropertyList<double,VecType>& GradSeq,
      MinimizerFlatParameter4PropertyList<DistEvalMethod,GeomType>& MParam) {
    GFunc(CoorSeq.Structure(),MParam.IMethodLst,MParam.IdxLst.Structure(),
          MParam.ParamLst,MParam.DEval,MParam.Geo,GradSeq.Structure());
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecType>
  void BFunc_4PropertyList(
      const PropertyList<double,VecType>& CoorSeq,
      double& Energy, PropertyList<double,VecType>& GradSeq,
      MinimizerFlatParameter4PropertyList<DistEvalMethod,GeomType>& MParam) {
    BFunc(CoorSeq.Structure(),MParam.IMethodLst,MParam.IdxLst.Structure(),
          MParam.ParamLst,MParam.DEval,MParam.Geo,Energy,GradSeq.Structure());
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecType>
  void EFunc_4PropertyList(
      const PropertyList<double,VecType>& CoorSeq, double& Energy,
      MinimizerHierarchyParameter4PropertyList<DistEvalMethod,GeomType>&
        MParam) {
    EFunc(CoorSeq.Structure(),MParam.IMethodLst,MParam.IdxLst.Structure(),
          MParam.ParamLst.Structure(),MParam.DEval,MParam.Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecType>
  void GFunc_4PropertyList(
      const PropertyList<double,VecType>& CoorSeq,
      PropertyList<double,VecType>& GradSeq,
      MinimizerHierarchyParameter4PropertyList<DistEvalMethod,GeomType>&
        MParam) {
    GFunc(CoorSeq.Structure(),MParam.IMethodLst,MParam.IdxLst.Structure(),
          MParam.ParamLst.Structure(),MParam.DEval,MParam.Geo,
          GradSeq.Structure());
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecType>
  void BFunc_4PropertyList(
      const PropertyList<double,VecType>& CoorSeq,
      double& Energy, PropertyList<double,VecType>& GradSeq,
      MinimizerHierarchyParameter4PropertyList<DistEvalMethod,GeomType>&
        MParam) {
    BFunc(CoorSeq.Structure(),MParam.IMethodLst,MParam.IdxLst.Structure(),
          MParam.ParamLst.Structure(),MParam.DEval,MParam.Geo,Energy,
          GradSeq.Structure());
  }

}

#endif

