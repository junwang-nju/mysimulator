
#ifndef _Interaction_for_List_Set_H_
#define _Interaction_for_List_Set_H_

#include "interaction-4list.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFunc(const Vector<double>* Coor,
             const Vector<Vector<unsigned int> >* IdxSet,
             const Vector<Vector<UniqueParameter> >* PrmSet,
             InteractionMethod<DistEvalMethod,GeomType>* imSet,
             const unsigned int nSet,
             DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    for(unsigned int i=0;i<nSet;++i)
      EFunc(Coor,IdxSet[i](),PrmSet[i](),IdxSet[i].size,imSet[i],DEval,Geo,
            Energy);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFunc(const Vector<double>* Coor,
             const Vector<Vector<unsigned int> >* IdxSet,
             const Vector<Vector<UniqueParameter> >* PrmSet,
             InteractionMethod<DistEvalMethod,GeomType>* imSet,
             const unsigned int nSet,
             DistEvalMethod& DEval, const GeomType& Geo,
             Vector<double>* Gradient) {
    for(unsigned int i=0;i<nSet;++i)
      GFunc(Coor,IdxSet[i](),PrmSet[i](),IdxSet[i].size,imSet[i],DEval,Geo,
            Gradient);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFunc(const Vector<double>* Coor,
             const Vector<Vector<unsigned int> >* IdxSet,
             const Vector<Vector<UniqueParameter> >* PrmSet,
             InteractionMethod<DistEvalMethod,GeomType>* imSet,
             const unsigned int nSet,
             DistEvalMethod& DEval, const GeomType& Geo,
             double& Energy, Vector<double>* Gradient) {
    for(unsigned int i=0;i<nSet;++i)
      BFunc(Coor,IdxSet[i](),PrmSet[i](),IdxSet[i].size,imSet[i],DEval,Geo,
            Energy,Gradient);
  }

  template <typename DistEvalMethod, typename GeomType>
  void EFunc(const Vector<double>* Coor, const Vector<unsigned int>* IdxSet,
             const Vector<UniqueParameter>* PrmSet,
             InteractionMethod<DistEvalMethod,GeomType>* imSet,
             const unsigned int nSet,
             DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    for(unsigned int i=0;i<nSet;++i)
      EFunc(Coor,IdxSet+i,PrmSet+i,1,imSet[i],DEval,Geo,Energy);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFunc(const Vector<double>* Coor, const Vector<unsigned int>* IdxSet,
             const Vector<UniqueParameter>* PrmSet,
             InteractionMethod<DistEvalMethod,GeomType>* imSet,
             const unsigned int nSet,
             DistEvalMethod& DEval, const GeomType& Geo,
             Vector<double>* Gradient) {
    for(unsigned int i=0;i<nSet;++i)
      GFunc(Coor,IdxSet+i,PrmSet+i,1,imSet[i],DEval,Geo,Gradient);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFunc(const Vector<double>* Coor, const Vector<unsigned int>* IdxSet,
             const Vector<UniqueParameter>* PrmSet,
             InteractionMethod<DistEvalMethod,GeomType>* imSet,
             const unsigned int nSet,
             DistEvalMethod& DEval, const GeomType& Geo,
             double& Energy, Vector<double>* Gradient) {
    for(unsigned int i=0;i<nSet;++i)
      BFunc(Coor,IdxSet+i,PrmSet+i,1,imSet[i],DEval,Geo,Energy,Gradient);
  }

}

#endif

