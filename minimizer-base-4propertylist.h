
#ifndef _Minimizer_Base_For_PropertyList_H_
#define _Minimizer_Base_For_PropertyList_H_

#include "interaction-4listset.h"

namespace std {

  template <typename DistEvalObj, typename GeomType, uint bMode>
  class MinimizerParameter4PropertyList {
    public:
      PropertyList<refVector,refVector,uint,refVector>          Mask;
      PropertyList<refVector,refVector,double,refVector>        DMask;
      DistEvalObj                                               *pDEval;
      GeomType                                                  *pRunGeo;
      ParamList                                                 *pRunParam;
      refVector<InteractionList<DistEvalObj,GeomType,bMode> >   ILS;
      void Update() { pDEval->Update(); }
  };

  template <template <typename> class ListType,
            typename DistEvalObj,typename GeomType, uint bMode>
  void E_MinPropertyList(
    const PropertyList<ListType>& Coordinate,
    MinimizerParameter4PropertyList<DistEvalObj,GeomType,bMode>& Prm,
    double& Energy){
    E_ListSet(Coordinate,Prm.ILS,*(Prm.pRunParam),*(Prm.pDEval),
              *(Prm.pRunGeo),Energy);
  }

  template <template <typename> class ListType,
            typename DistEvalObj,typename GeomType, uint bMode>
  void G_MinPropertyList(
    const PropertyList<ListType>& Coordinate,
    MinimizerParameter4PropertyList<DistEvalObj,GeomType,bMode>& Prm,
    PropertyList<ListType>& Gradient){
    G_ListSet(Coordinate,Prm.ILS,*(Prm.pRunParam),*(Prm.pDEval),
              *(Prm.pRunGeo),Gradient);
  }

  template <template <typename> class ListType,
            typename DistEvalObj,typename GeomType, uint bMode>
  void EG_MinPropertyList(
    const PropertyList<ListType>& Coordinate,
    MinimizerParameter4PropertyList<DistEvalObj,GeomType,bMode>& Prm,
    double& Energy,PropertyList<ListType>& Gradient){
    EG_ListSet(Coordinate,Prm.ILS,*(Prm.pRunParam),*(Prm.pDEval),
               *(Prm.pRunGeo),Energy,Gradient);
  }

}

#endif

