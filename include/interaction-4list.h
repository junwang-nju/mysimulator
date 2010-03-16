
#ifndef _Interaction_for_List_H_
#define _Interaction_for_List_H_

#include "property-list-base.h"
#include "parameter-list-base.h"
#include "interaction-method.h"
#include "var-vector.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             double& Energy) {
    unsigned int n=IdxLst.size();
    if(n==0)  return;
    unsigned int nmer=IdxLst[0].size();
    varVector<refVector<double> > rCoor(nmer);
    varVector<unsigned int> prmKey(nmer+1);
    for(unsigned int i=0;i<n;++i) {
      assert(IdxLst[i].size()==nmer);
      prmKey[0]=IM.InteractionTag();
      for(unsigned int k=0,m;k<nmer;++k) {
        m=IdxLst[i][k];
        rCoor[k].refer(CoorSeq[m]);
        prmKey[k+1]=KindSeq[m];
      }
      IM.EFunc(rCoor,IdxLst[i],*ParamCollection.get(prmKey),DEval,Geo,Energy);
    }
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             VectorBase<refVector<double> >& Gradient) {
    unsigned int n=IdxLst.size();
    if(n==0)  return;
    unsigned int nmer=IdxLst[0].size();
    varVector<refVector<double> > rCoor(nmer);
    varVector<unsigned int> prmKey(nmer+1);
    for(unsigned int i=0;i<n;++i) {
      assert(IdxLst[i].size()==nmer);
      prmKey[0]=IM.InteractionTag();
      for(unsigned int k=0,m;k<nmer;++k) {
        m=IdxLst[i][k];
        rCoor[k].refer(CoorSeq[m]);
        prmKey[k+1]=KindSeq[m];
      }
      IM.GFunc(rCoor,IdxLst[i],*ParamCollection.get(prmKey),DEval,Geo,
               Gradient);
    }
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             double& Energy, VectorBase<refVector<double> >& Gradient) {
    unsigned int n=IdxLst.size();
    if(n==0)  return;
    unsigned int nmer=IdxLst[0].size();
    varVector<refVector<double> > rCoor(nmer);
    varVector<unsigned int> prmKey(nmer+1);
    for(unsigned int i=0;i<n;++i) {
      assert(IdxLst[i].size()==nmer);
      prmKey[0]=IM.InteractionTag();
      for(unsigned int k=0,m;k<nmer;++k) {
        m=IdxLst[i][k];
        rCoor[k].refer(CoorSeq[m]);
        prmKey[k+1]=KindSeq[m];
      }
      IM.BFunc(rCoor,IdxLst[i],*ParamCollection.get(prmKey),DEval,Geo,
               Energy,Gradient);
    }
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             double& Energy) {
    unsigned int n=CoorLst.size();
    assert(n==IdxLst.size());
    assert(n==ParamLst.size());
    if(n==0)  return;
    for(unsigned int i=0;i<n;++i)
      IM.EFunc(CoorLst[i],IdxLst[i],ParamLst[i],DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             VectorBase<refVector<refVector<double> > >& GradientLst) {
    unsigned int n=CoorLst.size();
    assert(n==IdxLst.size());
    assert(n==ParamLst.size());
    assert(n==GradientLst.size());
    if(n==0)  return;
    for(unsigned int i=0;i<n;++i)
      IM.GFunc(CoorLst[i],IdxLst[i],ParamLst[i],DEval,Geo,GradientLst[i]);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
             double& Energy,
             VectorBase<refVector<refVector<double> > >& GradientLst) {
    unsigned int n=CoorLst.size();
    assert(n==IdxLst.size());
    assert(n==ParamLst.size());
    assert(n==GradientLst.size());
    if(n==0)  return;
    for(unsigned int i=0;i<n;++i)
      IM.BFunc(CoorLst[i],IdxLst[i],ParamLst[i],DEval,Geo,
               Energy,GradientLst[i]);
  }

}

#endif