
#ifndef _Interaction_Angle_Base_H_
#define _Interaction_Angle_Base_H_

#include "vector.h"
#include "unique-parameter.h"
#include <cmath>

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncAngleBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy,
      void (*efunc)(const double,const UniqueParameter*,double&)) {
    double dsq01,dsq12,dsq20;
    Evaluate(DEval,Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    dsq01=DEval();
    Evaluate(DEval,Coor[Idx[1]],Coor[Idx[2]],Idx[1],Idx[2],Geo);
    dsq12=DEval();
    Evaluate(DEval,Coor[Idx[2]],Coor[Idx[0]],Idx[2],Idx[0],Geo);
    dsq20=DEval();
    double cosAngle=(dsq01+dsq12-dsq20)/sqrt(dsq01*dsq12)*0.5;
    double ee;
    efunc(cosAngle,Prm,ee);
    Energy+=ee;
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncAngleBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm,
      Vector<double>* tmvec,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient,
      void (*gfunc)(const double,const UniqueParameter*,double&)) {
    // tmvec must have more than 4 vectors
    double dsq01,dsq12,dsq20;
    Evaluate(DEval,Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    dsq01=DEval();
    assign(tmvec[0],DEval.displacementvec);
    Evaluate(DEval,Coor[Idx[2]],Coor[Idx[1]],Idx[2],Idx[1],Geo);
    dsq12=DEval();
    assign(tmvec[1],DEval.displacementvec);
    Evaluate(DEval,Coor[Idx[2]],Coor[Idx[0]],Idx[2],Idx[0],Geo);
    dsq20=DEval();
    double cosAngle=(dsq01+dsq12-dsq20)*0.5;
    assign(tmvec[2],tmvec[1]);
    shift(tmvec[2],-cosAngle/dsq01,tmvec[0]);
    assign(tmvec[3],tmvec[0]);
    shift(tmvec[3],-cosAngle/dsq12,tmvec[1]);
    double d01,d12;
    d01=sqrt(dsq01);
    d12=sqrt(dsq12);
    cosAngle/=d01*d12;
    double sinAngle,nr0,nr2;
    sinAngle=sqrt(1.-cosAngle*cosAngle);
    nr0=d12*sinAngle;
    nr2=d01*sinAngle;
    scale(tmvec[2],(nr0>1e-8?1./nr0:0.));
    scale(tmvec[3],(nr2>1e-8?1./nr2:0.));
    double ef;
    gfunc(cosAngle,Prm,ef);
    double ef0,ef2;
    ef0=-ef/d01;
    ef2=-ef/d12;
    shift(Gradient[Idx[0]],+ef0,tmvec[2]);
    shift(Gradient[Idx[1]],-ef0,tmvec[2]);
    shift(Gradient[Idx[2]],+ef2,tmvec[3]);
    shift(Gradient[Idx[1]],-ef2,tmvec[3]);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncAngleBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm,
      Vector<double>* tmvec,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient,
      void (*bfunc)(const double,const UniqueParameter*,double&,double&)) {
    // tmvec must have more than 4 vectors
    double dsq01,dsq12,dsq20;
    Evaluate(DEval,Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    dsq01=DEval();
    assign(tmvec[0],DEval.displacementvec);
    Evaluate(DEval,Coor[Idx[2]],Coor[Idx[1]],Idx[2],Idx[1],Geo);
    dsq12=DEval();
    assign(tmvec[1],DEval.displacementvec);
    Evaluate(DEval,Coor[Idx[2]],Coor[Idx[0]],Idx[2],Idx[0],Geo);
    dsq20=DEval();
    double cosAngle=(dsq01+dsq12-dsq20)*0.5;
    assign(tmvec[2],tmvec[1]);
    shift(tmvec[2],-cosAngle/dsq01,tmvec[0]);
    assign(tmvec[3],tmvec[0]);
    shift(tmvec[3],-cosAngle/dsq12,tmvec[1]);
    double d01,d12;
    d01=sqrt(dsq01);
    d12=sqrt(dsq12);
    cosAngle/=d01*d12;
    double sinAngle,nr0,nr2;
    sinAngle=sqrt(1.-cosAngle*cosAngle);
    nr0=d12*sinAngle;
    nr2=d01*sinAngle;
    scale(tmvec[2],(nr0>1e-8?1./nr0:0.));
    scale(tmvec[3],(nr2>1e-8?1./nr2:0.));
    double ee,ef;
    bfunc(cosAngle,Prm,ee,ef);
    Energy+=ee;
    double ef0,ef2;
    ef0=-ef/d01;
    ef2=-ef/d12;
    shift(Gradient[Idx[0]],+ef0,tmvec[2]);
    shift(Gradient[Idx[1]],-ef0,tmvec[2]);
    shift(Gradient[Idx[2]],+ef2,tmvec[3]);
    shift(Gradient[Idx[1]],-ef2,tmvec[3]);
  }

}

#endif

