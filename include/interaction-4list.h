
#ifndef _Interaction_for_List_H_
#define _Interaction_for_List_H_

#include "parameter-list-base.h"
#include "interaction-method.h"
#include "var-vector.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFuncBase(const VectorBase<refVector<double> >& CoorSeq,
                 const InteractionMethod<DistEvalMethod,GeomType>& IM,
                 const VectorBase<refVector<unsigned int> >& IdxLst,
                 const VectorBase<unsigned int>& KindSeq,
                 const ParameterListBase<VecTypeP>& ParamCollection,
                 DistEvalMethod<VecTypeD>& DEval,const GeomType<VecTypeG>& Geo,
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
            template <typename> class VecTypeP>
  void EFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<varVector>& DEval, const GeomType<varVector>& Geo,
             double& Energy) {
    EFuncBase<DistEvalMethod,GeomType,varVector,varVector>(
        CoorSeq,IM,IdxLst,KindSeq,ParamCollection,DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP>
  void EFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<varVector>& DEval, const GeomType<refVector>& Geo,
             double& Energy) {
    EFuncBase<DistEvalMethod,GeomType,varVector,refVector>(
        CoorSeq,IM,IdxLst,KindSeq,ParamCollection,DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP>
  void EFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<refVector>& DEval, const GeomType<varVector>& Geo,
             double& Energy) {
    EFuncBase<DistEvalMethod,GeomType,refVector,varVector>(
        CoorSeq,IM,IdxLst,KindSeq,ParamCollection,DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP>
  void EFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<refVector>& DEval, const GeomType<refVector>& Geo,
             double& Energy) {
    EFuncBase<DistEvalMethod,GeomType,refVector,refVector>(
        CoorSeq,IM,IdxLst,KindSeq,ParamCollection,DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFuncBase(const VectorBase<refVector<double> >& CoorSeq,
                 const InteractionMethod<DistEvalMethod,GeomType>& IM,
                 const VectorBase<refVector<unsigned int> >& IdxLst,
                 const VectorBase<unsigned int>& KindSeq,
                 const ParameterListBase<VecTypeP>& ParamCollection,
                 DistEvalMethod<VecTypeD>& DEval,const GeomType<VecTypeG>& Geo,
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
            template <typename> class VecTypeP>
  void GFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<varVector>& DEval, const GeomType<varVector>& Geo,
             VectorBase<refVector<double> >& Gradient) {
    GFuncBase<DistEvalMethod,GeomType,varVector,varVector>(
        CoorSeq,IM,IdxLst,KindSeq,ParamCollection,DEval,Geo,Gradient);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP>
  void GFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<varVector>& DEval, const GeomType<refVector>& Geo,
             VectorBase<refVector<double> >& Gradient) {
    GFuncBase<DistEvalMethod,GeomType,varVector,refVector>(
        CoorSeq,IM,IdxLst,KindSeq,ParamCollection,DEval,Geo,Gradient);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP>
  void GFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<refVector>& DEval, const GeomType<varVector>& Geo,
             VectorBase<refVector<double> >& Gradient) {
    GFuncBase<DistEvalMethod,GeomType,refVector,varVector>(
        CoorSeq,IM,IdxLst,KindSeq,ParamCollection,DEval,Geo,Gradient);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP>
  void GFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<refVector>& DEval, const GeomType<refVector>& Geo,
             VectorBase<refVector<double> >& Gradient) {
    GFuncBase<DistEvalMethod,GeomType,refVector,refVector>(
        CoorSeq,IM,IdxLst,KindSeq,ParamCollection,DEval,Geo,Gradient);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFuncBase(const VectorBase<refVector<double> >& CoorSeq,
                 const InteractionMethod<DistEvalMethod,GeomType>& IM,
                 const VectorBase<refVector<unsigned int> >& IdxLst,
                 const VectorBase<unsigned int>& KindSeq,
                 const ParameterListBase<VecTypeP>& ParamCollection,
                 DistEvalMethod<VecTypeD>& DEval,const GeomType<VecTypeG>& Geo,
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
            template <typename> class VecTypeP>
  void BFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<varVector>& DEval, const GeomType<varVector>& Geo,
             double& Energy, VectorBase<refVector<double> >& Gradient) {
    BFuncBase<DistEvalMethod,GeomType,varVector,varVector>(
        CoorSeq,IM,IdxLst,KindSeq,ParamCollection,DEval,Geo,Energy,Gradient);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP>
  void BFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<varVector>& DEval, const GeomType<refVector>& Geo,
             double& Energy, VectorBase<refVector<double> >& Gradient) {
    BFuncBase<DistEvalMethod,GeomType,varVector,refVector>(
        CoorSeq,IM,IdxLst,KindSeq,ParamCollection,DEval,Geo,Energy,Gradient);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP>
  void BFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<refVector>& DEval, const GeomType<varVector>& Geo,
             double& Energy, VectorBase<refVector<double> >& Gradient) {
    BFuncBase<DistEvalMethod,GeomType,refVector,varVector>(
        CoorSeq,IM,IdxLst,KindSeq,ParamCollection,DEval,Geo,Energy,Gradient);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeP>
  void BFunc(const VectorBase<refVector<double> >& CoorSeq,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<unsigned int>& KindSeq,
             const ParameterListBase<VecTypeP>& ParamCollection,
             DistEvalMethod<refVector>& DEval, const GeomType<refVector>& Geo,
             double& Energy, VectorBase<refVector<double> >& Gradient) {
    BFuncBase<DistEvalMethod,GeomType,refVector,refVector>(
        CoorSeq,IM,IdxLst,KindSeq,ParamCollection,DEval,Geo,Energy,Gradient);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFuncBase(const VectorBase<refVector<refVector<double> > >& CoorLst,
                 const InteractionMethod<DistEvalMethod,GeomType>& IM,
                 const VectorBase<refVector<unsigned int> >& IdxLst,
                 const VectorBase<refVector<double> >& ParamLst,
                 DistEvalMethod<VecTypeD>& DEval,const GeomType<VecTypeG>& Geo,
                 double& Energy) {
    unsigned int n=CoorLst.size();
    assert(n==IdxLst.size());
    assert(n==ParamLst.size());
    if(n==0)  return;
    for(unsigned int i=0;i<n;++i)
      IM.EFunc(CoorLst[i],IdxLst[i],ParamLst[i],DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void EFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<varVector>& DEval, const GeomType<varVector>& Geo,
             double& Energy) {
    EFuncBase<DistEvalMethod,GeomType,varVector,varVector>(
        CoorLst,IM,IdxLst,ParamLst,DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void EFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<varVector>& DEval, const GeomType<refVector>& Geo,
             double& Energy) {
    EFuncBase<DistEvalMethod,GeomType,varVector,refVector>(
        CoorLst,IM,IdxLst,ParamLst,DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void EFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<refVector>& DEval, const GeomType<varVector>& Geo,
             double& Energy) {
    EFuncBase<DistEvalMethod,GeomType,refVector,varVector>(
        CoorLst,IM,IdxLst,ParamLst,DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void EFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<refVector>& DEval, const GeomType<refVector>& Geo,
             double& Energy) {
    EFuncBase<DistEvalMethod,GeomType,refVector,refVector>(
        CoorLst,IM,IdxLst,ParamLst,DEval,Geo,Energy);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFuncBase(const VectorBase<refVector<refVector<double> > >& CoorLst,
                 const InteractionMethod<DistEvalMethod,GeomType>& IM,
                 const VectorBase<refVector<unsigned int> >& IdxLst,
                 const VectorBase<refVector<double> >& ParamLst,
                 DistEvalMethod<VecTypeD>& DEval,const GeomType<VecTypeG>& Geo,
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
            template <template <typename> class> class GeomType>
  void GFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<varVector>& DEval,const GeomType<varVector>& Geo,
             VectorBase<refVector<refVector<double> > >& GradientLst) {
    GFuncBase<DistEvalMethod,GeomType,varVector,varVector>(
        CoorLst,IM,IdxLst,ParamLst,DEval,Geo,GradientLst);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void GFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<varVector>& DEval,const GeomType<refVector>& Geo,
             VectorBase<refVector<refVector<double> > >& GradientLst) {
    GFuncBase<DistEvalMethod,GeomType,varVector,refVector>(
        CoorLst,IM,IdxLst,ParamLst,DEval,Geo,GradientLst);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void GFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<refVector>& DEval,const GeomType<varVector>& Geo,
             VectorBase<refVector<refVector<double> > >& GradientLst) {
    GFuncBase<DistEvalMethod,GeomType,refVector,varVector>(
        CoorLst,IM,IdxLst,ParamLst,DEval,Geo,GradientLst);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void GFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<refVector>& DEval,const GeomType<refVector>& Geo,
             VectorBase<refVector<refVector<double> > >& GradientLst) {
    GFuncBase<DistEvalMethod,GeomType,refVector,refVector>(
        CoorLst,IM,IdxLst,ParamLst,DEval,Geo,GradientLst);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFuncBase(const VectorBase<refVector<refVector<double> > >& CoorLst,
                 const InteractionMethod<DistEvalMethod,GeomType>& IM,
                 const VectorBase<refVector<unsigned int> >& IdxLst,
                 const VectorBase<refVector<double> >& ParamLst,
                 DistEvalMethod<VecTypeD>& DEval,const GeomType<VecTypeG>& Geo,
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

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void BFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<varVector>& DEval, const GeomType<varVector>& Geo,
             double& Energy,
             VectorBase<refVector<refVector<double> > >& GradientLst) {
    BFuncBase<DistEvalMethod,GeomType,varVector,varVector>(
        CoorLst,IM,IdxLst,ParamLst,DEval,Geo,Energy,GradientLst);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void BFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<varVector>& DEval, const GeomType<refVector>& Geo,
             double& Energy,
             VectorBase<refVector<refVector<double> > >& GradientLst) {
    BFuncBase<DistEvalMethod,GeomType,varVector,refVector>(
        CoorLst,IM,IdxLst,ParamLst,DEval,Geo,Energy,GradientLst);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void BFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<refVector>& DEval, const GeomType<varVector>& Geo,
             double& Energy,
             VectorBase<refVector<refVector<double> > >& GradientLst) {
    BFuncBase<DistEvalMethod,GeomType,refVector,varVector>(
        CoorLst,IM,IdxLst,ParamLst,DEval,Geo,Energy,GradientLst);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void BFunc(const VectorBase<refVector<refVector<double> > >& CoorLst,
             const InteractionMethod<DistEvalMethod,GeomType>& IM,
             const VectorBase<refVector<unsigned int> >& IdxLst,
             const VectorBase<refVector<double> >& ParamLst,
             DistEvalMethod<refVector>& DEval, const GeomType<refVector>& Geo,
             double& Energy,
             VectorBase<refVector<refVector<double> > >& GradientLst) {
    BFuncBase<DistEvalMethod,GeomType,refVector,refVector>(
        CoorLst,IM,IdxLst,ParamLst,DEval,Geo,Energy,GradientLst);
  }

}

#endif
