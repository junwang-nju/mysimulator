
#ifndef _Interaction_Centroid_Base_H_
#define _Interaction_Centroid_Base_H_

#include "unique-parameter.h"
#include "vector.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncCentroidBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const unsigned int nIdx, const UniqueParameter* Prm,
      Vector<double>& tmvec, DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy,
      void (*efunc)(const double,const UniqueParameter*,double&)) {
    assign(tmvec,0.);
    for(unsigned int i=1;i<nIdx;++i)  shift(tmvec,dOne,Coor[Idx[i]]);
    scale(tmvec,1./(nIdx-1.));
    DistanceDisplacementFunc(tmvec,Coor[Idx[0]],DEval.displacementvec,DEval(),
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
      Vector<double>& tmvec, DistEvalMethod& DEval, const GeomType& Geo,
      Vector<double>* Gradient,
      void (*gfunc)(const double,const UniqueParameter*,double&)) {
    assign(tmvec,0.);
    for(unsigned int i=1;i<nIdx;++i)  shift(tmvec,dOne,Coor[Idx[i]]);
    double sfac;
    sfac=1./(nIdx-1.);
    scale(tmvec,sfac);
    DistanceDisplacementFunc(tmvec,Coor[Idx[0]],DEval.displacementvec,DEval(),
                             Geo);
    double dsq=DEval();
    double ef;
    gfunc(dsq,Prm,ef);
    shift(Gradient[Idx[0]],-ef,DEval.displacementvec);
    ef*=sfac;
    for(unsigned int i=1;i<nIdx;++i)
      shift(Gradient[Idx[i]],+ef,DEval.displacementvec);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncCentroidBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const unsigned int nIdx, const UniqueParameter* Prm,
      Vector<double>& tmvec, DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient,
      void (*bfunc)(const double,const UniqueParameter*,double&,double&)) {
    assign(tmvec,0.);
    for(unsigned int i=1;i<nIdx;++i)  shift(tmvec,dOne,Coor[Idx[i]]);
    double sfac;
    sfac=1./(nIdx-1.);
    scale(tmvec,sfac);
    DistanceDisplacementFunc(tmvec,Coor[Idx[0]],DEval.displacementvec,DEval(),
                             Geo);
    double dsq=DEval();
    double ee,ef;
    bfunc(dsq,Prm,ee,ef);
    Energy+=ee;
    shift(Gradient[Idx[0]],-ef,DEval.displacementvec);
    ef*=sfac;
    for(unsigned int i=1;i<nIdx;++i)
      shift(Gradient[Idx[i]],+ef,DEval.displacementvec);
  }

}

#endif

