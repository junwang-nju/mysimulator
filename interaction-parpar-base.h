
#ifndef _Interaction_ParticleParticle_Base_H_
#define _Interaction_ParticleParticle_Base_H_

#include "property-frame.h"
#include "param-list.h"
#include "distance-evaluation.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_Base(const VectorBase<Property*>& P,
                     const ParamList& PList,
                     DistEvalObj& DEval, const GeomType& Geo,
                     double& Energy,
                     const uint& iTag, 
                     void (*func)(const double&,
                                  const VectorBase<double>&,
                                  double&)) {
    static fixVector<uint,3>  prmKey;
    prmKey[0]=iTag;
    prmKey[1]=P[0]->Info[MonomerKindID];
    prmKey[2]=P[1]->Info[MonomerKindID];
    const varVector<double>* Parm=PList.get(prmKey);
    double DistSQ=DEval(*P[0],*P[1],Geo);
    double ee;
    func(DistSQ,*Parm,ee);
    Energy+=ee;
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_Base(VectorBase<Property*>& P,
                     const ParamList& PList,
                     DistEvalObj& DEval, const GeomType& Geo,
                     const uint& iTag, 
                     void (*func)(const double&,
                                  const VectorBase<double>&,
                                  double&)) {
    static fixVector<uint,3>  prmKey;
    prmKey[0]=iTag;
    prmKey[1]=P[0]->Info[MonomerKindID];
    prmKey[2]=P[1]->Info[MonomerKindID];
    const varVector<double>* Parm=PList.get(prmKey);
    double DistSQ=DEval(*P[0],*P[1],Geo,' ');
    double ef;
    func(DistSQ,*Parm,ef);
    P[0]->Gradient.shift(+ef,DEval.DisplaceVector());
    P[1]->Gradient.shift(-ef,DEval.DisplaceVector());
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_Base(VectorBase<Property*>& P,
                      const ParamList& PList,
                      DistEvalObj& DEval, const GeomType& Geo,
                      double& Energy,
                      const uint& iTag, 
                      void (*func)(const double&,
                                   const VectorBase<double>&,
                                   double&,double&)) {
    static fixVector<uint,3>  prmKey;
    prmKey[0]=iTag;
    prmKey[1]=P[0]->Info[MonomerKindID];
    prmKey[2]=P[1]->Info[MonomerKindID];
    const varVector<double>* Parm=PList.get(prmKey);
    double DistSQ=DEval(*P[0],*P[1],Geo,' ');
    double ee,ef;
    func(DistSQ,*Parm,ee,ef);
    Energy+=ee;
    P[0]->Gradient.shift(+ef,DEval.DisplaceVector());
    P[1]->Gradient.shift(-ef,DEval.DisplaceVector());
  }

}

#endif

