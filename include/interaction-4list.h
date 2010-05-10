
#ifndef _Interaction_for_List_H_
#define _Interaction_for_List_H_

#include "interaction-method.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFunc(const Vector<double>* Coor, const Vector<unsigned int>* IdxLst,
             const Vector<UniqueParameter>* PrmLst, const unsigned int nLst,
             InteractionMethod<DistEvalMethod,GeomType>& IM,
             DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    for(unsigned int i=0;i<nLst;++i)
      IM.EFunc(Coor,IdxLst[i](),PrmLst[i](),IdxLst[i].size,
               IM.tmpvec->structure,IM.tmpvec->size,DEval,Geo,Energy);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFunc(const Vector<double>* Coor, const Vector<unsigned int>* IdxLst,
             const Vector<UniqueParameter>* PrmLst, const unsigned int nLst,
             InteractionMethod<DistEvalMethod,GeomType>& IM,
             DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* G) {
    for(unsigned int i=0;i<nLst;++i)
      IM.GFunc(Coor,IdxLst[i](),PrmLst[i](),IdxLst[i].size,
               IM.tmpvec->structure,IM.tmpvec->size,DEval,Geo,G);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFunc(const Vector<double>* Coor, const Vector<unsigned int>* IdxLst,
             const Vector<UniqueParameter>* PrmLst, const unsigned int nLst,
             InteractionMethod<DistEvalMethod,GeomType>& IM,
             DistEvalMethod& DEval, const GeomType& Geo,
             double& Energy, Vector<double>* G) {
    for(unsigned int i=0;i<nLst;++i)
      IM.BFunc(Coor,IdxLst[i](),PrmLst[i](),IdxLst[i].size,
               IM.tmpvec->structure,IM.tmpvec->size,DEval,Geo,Energy,G);
  }

}

#endif

