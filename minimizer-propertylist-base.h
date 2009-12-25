
#ifndef _Minimizer_PropertyList_Base_H_
#define _Minimizer_PropertyList_Base_H_

#include "interaction-4listset.h"

namespace std {

  template <typename DistEvalObj, typename GeomType, uint bMode>
  class Parameter4MinimizerPropertyList {
    public:
      PropertyList<refVector,refVector,uint>                    Mask;
      PropertyList<refVector>                                   DMask;
      DistEvalObj                                               *pDEval;
      GeomType                                                  *pRunGeo;
      ParamList                                                 *pRunParam;
      refVector<InteractionList<DistEvalObj,GeomType,bMode> >   ILS;
  };

  template <template <typename> class ListType,
            typename DistEvalObj,typename GeomType, uint bMode>
  void E_MinPropertyList(
    const PropertyList<ListType>& Coordinate,
    const Parameter4MinimizerPropertyList<DistEvalObj,GeomType,bMode>& Prm,
    double& Energy){
    E_ListSet(Coordinate,Prm.ILS,*(Prm.pRunParam),*(Prm.pDEval),
              *(Prm.pRunGeo),Energy);
  }

  template <template <typename> class ListType,
            typename DistEvalObj,typename GeomType, uint bMode>
  void G_MinPropertyList(
    const PropertyList<ListType>& Coordinate,
    const Parameter4MinimizerPropertyList<DistEvalObj,GeomType,bMode>& Prm,
    PropertyList<ListType>& Gradient){
    G_ListSet(Coordinate,Prm.ILS,*(Prm.pRunParam),*(Prm.pDEval),
              *(Prm.pRunGeo),Gradient);
  }

  template <template <typename> class ListType,
            typename DistEvalObj,typename GeomType, uint bMode>
  void EG_MinPropertyList(
    const PropertyList<ListType>& Coordinate,
    const Parameter4MinimizerPropertyList<DistEvalObj,GeomType,bMode>& Prm,
    double& Energy,PropertyList<ListType>& Gradient){
    G_ListSet(Coordinate,Prm.ILS,*(Prm.pRunParam),*(Prm.pDEval),
              *(Prm.pRunGeo),Energy,Gradient);
  }

}

#endif

