
#ifndef _Interaction_for_List_H_
#define _Interaction_for_List_H_

#include "property-list.h"
#include "interaction-list.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_List(const VectorBase<refVector<double> >& Coordinate,
              InteractionList<DistEvalObj,GeomType,LooseDataBinding>& IL,
              const ParamList& PList, DistEvalObj& DEval, const GeomType& Geo,
              double& Energy){
    uint nl=IL.List.size();
    for(uint i=0;i<nl;++i) {
      IL.BuildCoordinateBinding(Coordinate,i);
      IL.efunc(IL.Coordinate,IL.List[i],IL.KindIdx[i],PList,DEval,Geo,Energy);
    }
  }

  template <typename DistEvalObj, typename GeomType>
  void E_List(const VectorBase<refVector<double> >& Coordinate,
              InteractionList<DistEvalObj,GeomType,TightDataBinding>& IL,
              const ParamList& PList, DistEvalObj& DEval, const GeomType& Geo,
              double& Energy){
    uint nl=IL.List.size();
    for(uint i=0;i<nl;++i)
      IL.efunc(IL.Coordinate[i],IL.List[i],IL.KindIdx[i],PList,DEval,Geo,
               Energy);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_List(const VectorBase<refVector<double> >& Coordinate,
              InteractionList<DistEvalObj,GeomType,LooseDataBinding>& IL,
              const ParamList& PList,DistEvalObj& DEval,const GeomType& Geo,
              VectorBase<refVector<double> >& Gradient) {
    uint nl=IL.List.size();
    for(uint i=0;i<nl;++i) {
      IL.BuildCoordinateBinding(Coordinate,i);
      IL.BuildGradientBinding(Gradient,i);
      IL.gfunc(IL.Coordinate,IL.List[i],IL.KindIdx[i],PList,DEval,Geo,
               IL.Gradient);
    }
  }

  template <typename DistEvalObj, typename GeomType>
  void G_List(const VectorBase<refVector<double> >& Coordinate,
              InteractionList<DistEvalObj,GeomType,TightDataBinding>& IL,
              const ParamList& PList,DistEvalObj& DEval,const GeomType& Geo,
              VectorBase<refVector<double> >& Gradient) {
    uint nl=IL.List.size();
    for(uint i=0;i<nl;++i)
      IL.gfunc(IL.Coordinate[i],IL.List[i],IL.KindIdx[i],
               PList,DEval,Geo,IL.Gradient[i]);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_List(const VectorBase<refVector<double> >& Coordinate,
               InteractionList<DistEvalObj,GeomType,LooseDataBinding>& IL,
               const ParamList& PList,DistEvalObj& DEval,const GeomType& Geo,
               double& Energy,
               VectorBase<refVector<double> >& Gradient) {
    uint nl=IL.List.size();
    for(uint i=0;i<nl;++i) {
      IL.BuildCoordinateBinding(Coordinate,i);
      IL.BuildGradientBinding(Gradient,i);
      IL.bfunc(IL.Coordinate,IL.List[i],IL.KindIdx[i],PList,DEval,Geo,
               Energy,IL.Gradient);
    }
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_List(const VectorBase<refVector<double> >& Coordinate,
               InteractionList<DistEvalObj,GeomType,TightDataBinding>& IL,
               const ParamList& PList,DistEvalObj& DEval,const GeomType& Geo,
               double& Energy,
               VectorBase<refVector<double> >& Gradient) {
    uint nl=IL.List.size();
    for(uint i=0;i<nl;++i)
      IL.bfunc(IL.Coordinate[i],IL.List[i],IL.KindIdx[i],
               PList,DEval,Geo,Energy,IL.Gradient[i]);
  }

}

#endif

