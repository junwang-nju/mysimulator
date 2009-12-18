
#ifndef _Interaction_ParticleParticle_Base_H_
#define _Interaction_ParticleParticle_Base_H_

#include "property-list.h"
#include "param-list.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_Base(const VectorBase<Property<refVector>*>& P,
                     const VectorBase<uint>& Idx,const VectorBase<uint>& KIdx,
                     const ParamList& PList,
                     DistEvalObj& DEval,const GeomType& Geo,
                     double& Energy, const uint& iTag, 
                     void (*func)(const double&,
                                  const VectorBase<double>&,
                                  double&)) {
    static fixVector<uint,3>  prmKey;
    prmKey[0]=iTag;
    prmKey[1]=KIdx[0];
    prmKey[2]=KIdx[1];
    const varVector<double>* Parm=PList.get(prmKey);
    double DistSQ=DEval(*P[0],*P[1],Idx[0],Idx[1],Geo);
    double ee;
    func(DistSQ,*Parm,ee);
    Energy+=ee;
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_Base(const VectorBase<Property<refVector>*>& P,
                     const VectorBase<uint>& Idx,const VectorBase<uint>& KIdx,
                     const ParamList& PList,
                     DistEvalObj& DEval, const GeomType& Geo,
                     VectorBase<Property<refVector>*>& G,
                     const uint& iTag,
                     void (*func)(const double&,
                                  const VectorBase<double>&,
                                  double&)) {
    static fixVector<uint,3>  prmKey;
    prmKey[0]=iTag;
    prmKey[1]=KIdx[0];
    prmKey[2]=KIdx[1];
    const varVector<double>* Parm=PList.get(prmKey);
    double DistSQ=DEval(*P[0],*P[1],Idx[0],Idx[1],Geo,' ');
    double ef;
    func(DistSQ,*Parm,ef);
    G[0]->shift(+ef,DEval.DisplaceVector());
    G[1]->shift(-ef,DEval.DisplaceVector());
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_Base(const VectorBase<Property<refVector>*>& P,
                      const VectorBase<uint>& Idx,const VectorBase<uint>& KIdx,
                      const ParamList& PList,
                      DistEvalObj& DEval, const GeomType& Geo,
                      double& Energy,
                      VectorBase<Property<refVector>*>& G,
                      const uint& iTag, 
                      void (*func)(const double&,
                                   const VectorBase<double>&,
                                   double&,double&)) {
    static fixVector<uint,3>  prmKey;
    prmKey[0]=iTag;
    prmKey[1]=KIdx[0];
    prmKey[2]=KIdx[1];
    const varVector<double>* Parm=PList.get(prmKey);
    double DistSQ=DEval(*P[0],*P[1],Idx[0],Idx[1],Geo,' ');
    double ee,ef;
    func(DistSQ,*Parm,ee,ef);
    Energy+=ee;
    G[0]->shift(+ef,DEval.DisplaceVector());
    G[1]->shift(-ef,DEval.DisplaceVector());
  }

}

#endif

