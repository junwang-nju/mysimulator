
#ifndef _Interaction_for_List_H_
#define _Interaction_for_List_H_

#include "parameter-list.h"
#include "interaction-method.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP,
            typename RunDistEvalMethod, typename RunGeomType>
  void EFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterList<VecTypeP>& ParamCollection,
             RunDistEvalMethod& DEval, const RunGeomType& Geo,
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
            typename RunDistEvalMethod, typename RunGeomType>
  void GFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterList<VecTypeP>& ParamCollection,
             RunDistEvalMethod& DEval, const RunGeomType& Geo,
             VectorBase<refVector<double> >& GradientSeq) {
    unsigned int n=IdxLst.size();
    if(n==0)  return;
    unsigned int nmer=IdxLst[0].size();
    varVector<refVector<double> > rCoor(nmer), rGrad(nmer);
    varVector<unsigned int> prmKey(nmer+1);
    for(unsigned int i=0;i<n;++i) {
      assert(IdxLst[i].size()==nmer);
      prmKey[0]=IM.InteractionTag();
      for(unsigned int k=0,m;k<nmer;++k) {
        m=IdxLst[i][k];
        rCoor[k].refer(CoorSeq[m]);
        rGrad[k].refer(GradientSeq[m]);
        prmKey[k+1]=KindSeq[m];
      }
      IM.GFunc(rCoor,IdxLst[i],*ParamCollection.get(prmKey),DEval,Geo,rGrad);
    }
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP,
            typename RunDistEvalMethod, typename RunGeomType>
  void BFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterList<VecTypeP>& ParamCollection,
             RunDistEvalMethod& DEval, const RunGeomType& Geo,
             double& Energy, VectorBase<refVector<double> >& GradientSeq) {
    unsigned int n=IdxLst.size();
    if(n==0)  return;
    unsigned int nmer=IdxLst[0].size();
    varVector<refVector<double> > rCoor(nmer) ,rGrad(nmer);
    varVector<unsigned int> prmKey(nmer+1);
    for(unsigned int i=0;i<n;++i) {
      assert(IdxLst[i].size()==nmer);
      prmKey[0]=IM.InteractionTag();
      for(unsigned int k=0,m;k<nmer;++k) {
        m=IdxLst[i][k];
        rCoor[k].refer(CoorSeq[m]);
        rGrad[k].refer(GradientSeq[m]);
        prmKey[k+1]=KindSeq[m];
      }
      IM.BFunc(rCoor,IdxLst[i],*ParamCollection.get(prmKey),DEval,Geo,
               Energy,rGrad);
    }
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            typename RunDistEvalMethod, typename RunGeomType>
  void EFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             RunDistEvalMethod& DEval, const RunGeomType& Geo,
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
            typename RunDistEvalMethod, typename RunGeomType>
  void GFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             RunDistEvalMethod& DEval, const RunGeomType& Geo,
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
            typename RunDistEvalMethod, typename RunGeomType>
  void BFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             RunDistEvalMethod& DEval, const RunGeomType& Geo,
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
