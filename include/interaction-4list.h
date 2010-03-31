
#ifndef _Interaction_For_List_H_
#define _Interaction_For_List_H_

#include "interaction-method.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             double& Energy) {
    if(IdxLst.size()==0)    return;
    assert(IdxLst.size()==ParamLst.size());
    for(unsigned int i=0;i<IdxLst.size();++i)
      IM.EFunc(CoorSeq,IdxLst[i],ParamLst[i],DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             VectorBase<refVector<double> >& GradSeq) {
    if(IdxLst.size()==0)    return;
    assert(IdxLst.size()==ParamLst.size());
    for(unsigned int i=0;i<IdxLst.size();++i)
      IM.GFunc(CoorSeq,IdxLst[i],ParamLst[i],DEval,Geo,GradSeq);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             double& Energy, VectorBase<refVector<double> >& GradSeq) {
    if(IdxLst.size()==0)    return;
    assert(IdxLst.size()==ParamLst.size());
    for(unsigned int i=0;i<IdxLst.size();++i)
      IM.BFunc(CoorSeq,IdxLst[i],ParamLst[i],DEval,Geo,Energy,GradSeq);
  }

}

#endif

