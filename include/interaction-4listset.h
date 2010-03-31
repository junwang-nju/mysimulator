
#ifndef _Interaction_for_List_Set_H_
#define _Interaction_for_List_Set_H_

#include "interaction-4list.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc(const VectorBase<refVector<double> >& CoorSeq,
             const VectorBase<InteractionMethod<DistEvalMethod,GeomType> >& IM,
             const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
             const VectorBase<refVector<refVector<double> > >& ParamLst,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             double& Energy) {
    assert(IM.size()==IdxLst.size());
    assert(IM.size()==ParamLst.size());
    for(unsigned int i=0;i<IM.size();++i)
      EFunc(CoorSeq,IM[i],IdxLst[i],ParamLst[i],DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc(const VectorBase<refVector<double> >& CoorSeq,
             const VectorBase<InteractionMethod<DistEvalMethod,GeomType> >& IM,
             const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
             const VectorBase<refVector<refVector<double> > >& ParamLst,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             VectorBase<refVector<double> >& GradSeq) {
    assert(IM.size()==IdxLst.size());
    assert(IM.size()==ParamLst.size());
    for(unsigned int i=0;i<IM.size();++i)
      GFunc(CoorSeq,IM[i],IdxLst[i],ParamLst[i],DEval,Geo,GradSeq);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc(const VectorBase<refVector<double> >& CoorSeq,
             const VectorBase<InteractionMethod<DistEvalMethod,GeomType> >& IM,
             const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
             const VectorBase<refVector<refVector<double> > >& ParamLst,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             double& Energy, VectorBase<refVector<double> >& GradSeq) {
    assert(IM.size()==IdxLst.size());
    assert(IM.size()==ParamLst.size());
    for(unsigned int i=0;i<IM.size();++i)
      BFunc(CoorSeq,IM[i],IdxLst[i],ParamLst[i],DEval,Geo,Energy,GradSeq);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc(const VectorBase<refVector<double> >& CoorSeq,
             const VectorBase<InteractionMethod<DistEvalMethod,GeomType> >& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             double& Energy) {
    assert(IM.size()==IdxLst.size());
    assert(IM.size()==ParamLst.size());
    for(unsigned int i=0;i<IM.size();++i)
      IM[i].EFunc(CoorSeq,IdxLst[i],ParamLst[i],DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc(const VectorBase<refVector<double> >& CoorSeq,
             const VectorBase<InteractionMethod<DistEvalMethod,GeomType> >& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             VectorBase<refVector<double> >& GradSeq) {
    assert(IM.size()==IdxLst.size());
    assert(IM.size()==ParamLst.size());
    for(unsigned int i=0;i<IM.size();++i)
      IM[i].GFunc(CoorSeq,IdxLst[i],ParamLst[i],DEval,Geo,GradSeq);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc(const VectorBase<refVector<double> >& CoorSeq,
             const VectorBase<InteractionMethod<DistEvalMethod,GeomType> >& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             double& Energy, VectorBase<refVector<double> >& GradSeq) {
    assert(IM.size()==IdxLst.size());
    assert(IM.size()==ParamLst.size());
    for(unsigned int i=0;i<IM.size();++i)
      IM[i].BFunc(CoorSeq,IdxLst[i],ParamLst[i],DEval,Geo,Energy,GradSeq);
  }

}

#endif

