
#ifndef _Minimizer_Function_for_PropertyList_H_
#define _Minimizer_Function_for_PropertyList_H_

#include "interaction-4listset.h"
#include "property-list.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType,
            template <typename,typename> class ParameterType>
  void EFunc4PropertyList(const PropertyList<double>& Coor, double& Energy,
                          ParameterType<DistEvalMethod,GeomType>& Prm) {
    EFunc(Coor.structure,Prm.IdxLst.structure,Prm.parameterface(),
          Prm.IMLst(),Prm.nlst,Prm.DEval,Prm.Geo,Energy);
  }

  template <typename DistEvalMethod, typename GeomType,
            template <typename,typename> class ParameterType>
  void GFunc4PropertyList(const PropertyList<double>& Coor,
                          PropertyList<double>& Grad,
                          ParameterType<DistEvalMethod,GeomType>& Prm) {
    GFunc(Coor.structure,Prm.IdxLst.structure,Prm.parameterface(),
          Prm.IMLst(),Prm.nlst,Prm.DEval,Prm.Geo,Grad.structure);
  }

  template <typename DistEvalMethod, typename GeomType,
            template <typename,typename> class ParameterType>
  void BFunc4PropertyList(const PropertyList<double>& Coor, double& Energy,
                          PropertyList<double>& Grad,
                          ParameterType<DistEvalMethod,GeomType>& Prm) {
    BFunc(Coor.structure,Prm.IdxLst.structure,Prm.parameterface(),
          Prm.IMLst(),Prm.nlst,Prm.DEval,Prm.Geo,Energy,Grad.structure);
  }

}

#endif

