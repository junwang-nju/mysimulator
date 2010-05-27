
#ifndef _Interaction_Centroid_Base_H_
#define _Interaction_Centroid_Base_H_

#include "unique-parameter.h"
#include "system-op.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncCentroidBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const unsigned int nIdx, const UniqueParameter* Prm,
      Vector<double>* tmvec, DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy,
      void (*efunc)(const double,const UniqueParameter*,double&)) {
    MassCenter(Coor,Idx+Idx[nIdx-2],Idx[nIdx-1],tmvec[0]);
    MassCenter(Coor,Idx+Idx[nIdx-4],Idx[nIdx-3],tmvec[1]);
    DistanceDisplacementFunc(tmvec[0],tmvec[1],DEval.displacementvec,DEval(),
                             Geo);
    double dsq=DEval();
    double ee;
    efunc(dsq,Prm,ee);
    Energy+=ee;
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncCentroidBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const unsigned int nIdx, const UniqueParameter* Prm,
      Vector<double>* tmvec, DistEvalMethod& DEval, const GeomType& Geo,
      Vector<double>* Gradient,
      void (*gfunc)(const double,const UniqueParameter*,double&)) {
    MassCenter(Coor,Idx+Idx[nIdx-2],Idx[nIdx-1],tmvec[0]);
    MassCenter(Coor,Idx+Idx[nIdx-4],Idx[nIdx-3],tmvec[1]);
    DistanceDisplacementFunc(tmvec[0],tmvec[1],DEval.displacementvec,DEval(),
                             Geo);
    double dsq=DEval();
    double ef,ef0,ef1;
    gfunc(dsq,Prm,ef);
    ef0=ef/Idx[nIdx-1];
    ef1=ef/Idx[nIdx-3];
    for(unsigned int i=0,n=Idx[nIdx-2];i<Idx[nIdx-1];++i,++n)
      shift(Gradient[Idx[n]],ef0,DEval.displacementvec);
    for(unsigned int i=0,n=Idx[nIdx-4];i<Idx[nIdx-3];++i,++n)
      shift(Gradient[Idx[n]],-ef1,DEval.displacementvec);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncCentroidBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const unsigned int nIdx, const UniqueParameter* Prm,
      Vector<double>* tmvec, DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient,
      void (*bfunc)(const double,const UniqueParameter*,double&,double&)) {
    MassCenter(Coor,Idx+Idx[nIdx-2],Idx[nIdx-1],tmvec[0]);
    MassCenter(Coor,Idx+Idx[nIdx-4],Idx[nIdx-3],tmvec[1]);
    DistanceDisplacementFunc(tmvec[0],tmvec[1],DEval.displacementvec,DEval(),
                             Geo);
    double dsq=DEval();
    double ee,ef,ef0,ef1;
    bfunc(dsq,Prm,ee,ef);
    Energy+=ee;
    ef0=ef/Idx[nIdx-1];
    ef1=ef/Idx[nIdx-3];
    for(unsigned int i=0,n=Idx[nIdx-2];i<Idx[nIdx-1];++i,++n)
      shift(Gradient[Idx[n]],ef0,DEval.displacementvec);
    for(unsigned int i=0,n=Idx[nIdx-4];i<Idx[nIdx-3];++i,++n)
      shift(Gradient[Idx[n]],-ef1,DEval.displacementvec);
  }

}

#endif

