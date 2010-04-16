
#ifndef _Interaction_Angle_Base_H_
#define _Interaction_Angle_Base_H_

#include "ref-vector.h"
#include "vector-op.h"
#include <cmath>

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc_Angle_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy,
      void (*efunc)(const double, const VectorBase<double>&, double&)) {
    double DSQ01,DSQ12,DSQ20;
    DEval.Evaluate(Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    DSQ01=DEval.DistanceSQ();
    DEval.Evaluate(Coor[Idx[1]],Coor[Idx[2]],Idx[1],Idx[2],Geo);
    DSQ12=DEval.DistanceSQ();
    DEval.Evaluate(Coor[Idx[2]],Coor[Idx[0]],Idx[2],Idx[0],Geo);
    DSQ20=DEval.DistanceSQ();
    double cosAngle=(DSQ01+DSQ12-DSQ20)/sqrt(DSQ01*DSQ12)*0.5;
    double ee;
    efunc(cosAngle,Param,ee);
    Energy+=ee;
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc_Angle_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >& tmVec,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      VectorBase<refVector<double> >& Grad,
      void (*gfunc)(const double, const VectorBase<double>&, double&)) {
    assert(tmVec.size()>=4);
    double DSQ01,DSQ12,DSQ20;
    DEval.Evaluate(Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    DSQ01=DEval.DistanceSQ();
    tmVec[0]=DEval.Displacement();
    DEval.Evaluate(Coor[Idx[2]],Coor[Idx[1]],Idx[2],Idx[1],Geo);
    DSQ12=DEval.DistanceSQ();
    tmVec[1]=DEval.Displacement();
    DEval.Evaluate(Coor[Idx[2]],Coor[Idx[0]],Idx[2],Idx[0],Geo);
    DSQ20=DEval.DistanceSQ();
    double cosAngle=(DSQ01+DSQ12-DSQ20)*0.5;
    tmVec[2]=tmVec[1];
    tmVec[2].shift(-cosAngle/DSQ01,tmVec[0]);
    tmVec[3]=tmVec[0];
    tmVec[3].shift(-cosAngle/DSQ12,tmVec[1]);
    double D01,D12;
    D01=sqrt(DSQ01);
    D12=sqrt(DSQ12);
    cosAngle/=D01*D12;
    double sinAngle,nr0,nr2;
    sinAngle=sqrt(1-cosAngle*cosAngle);
    nr0=D12*sinAngle;
    nr2=D01*sinAngle;
    if(nr0>1e-8)  tmVec[2].scale(1./nr0);
    else          tmVec[2]=0;
    if(nr2>1e-8)  tmVec[3].scale(1./nr2);
    else          tmVec[3]=0;
    double ef;
    gfunc(cosAngle,Param,ef);
    double ef0,ef2;
    ef0=ef/D01;
    ef2=ef/D12;
    Grad[Idx[0]].shift(+ef0,tmVec[2],DEval.Dimension());
    Grad[Idx[1]].shift(-ef0,tmVec[2],DEval.Dimension());
    Grad[Idx[2]].shift(+ef2,tmVec[3],DEval.Dimension());
    Grad[Idx[1]].shift(-ef2,tmVec[3],DEval.Dimension());
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc_Angle_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >& tmVec,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy, VectorBase<refVector<double> >& Grad,
      void (*bfunc)(const double,const VectorBase<double>&,double&,double&)) {
    assert(tmVec.size()>=4);
    double DSQ01,DSQ12,DSQ20;
    DEval.Evaluate(Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    DSQ01=DEval.DistanceSQ();
    tmVec[0]=DEval.Displacement();
    DEval.Evaluate(Coor[Idx[2]],Coor[Idx[1]],Idx[2],Idx[1],Geo);
    DSQ12=DEval.DistanceSQ();
    tmVec[1]=DEval.Displacement();
    DEval.Evaluate(Coor[Idx[2]],Coor[Idx[0]],Idx[2],Idx[0],Geo);
    DSQ20=DEval.DistanceSQ();
    double cosAngle=(DSQ01+DSQ12-DSQ20)*0.5;
    tmVec[2]=tmVec[1];
    tmVec[2].shift(-cosAngle/DSQ01,tmVec[0]);
    tmVec[3]=tmVec[0];
    tmVec[3].shift(-cosAngle/DSQ12,tmVec[1]);
    double D01,D12;
    D01=sqrt(DSQ01);
    D12=sqrt(DSQ12);
    cosAngle/=D01*D12;
    double sinAngle,nr0,nr2;
    sinAngle=sqrt(1-cosAngle*cosAngle);
    nr0=D12*sinAngle;
    nr2=D01*sinAngle;
    if(nr0>1e-8)  tmVec[2].scale(1./nr0);
    else          tmVec[2]=0;
    if(nr2>1e-8)  tmVec[3].scale(1./nr2);
    else          tmVec[3]=0;
    double ee,ef;
    bfunc(cosAngle,Param,ee,ef);
    double ef0,ef2;
    ef0=ef/D01;
    ef2=ef/D12;
    Energy+=ee;
    Grad[Idx[0]].shift(+ef0,tmVec[2],DEval.Dimension());
    Grad[Idx[1]].shift(-ef0,tmVec[2],DEval.Dimension());
    Grad[Idx[2]].shift(+ef2,tmVec[3],DEval.Dimension());
    Grad[Idx[1]].shift(-ef2,tmVec[3],DEval.Dimension());
  }

}

#endif

