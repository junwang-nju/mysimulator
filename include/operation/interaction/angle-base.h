
#ifndef _Interaction_Angle_Base_H_
#define _Interaction_Angle_Base_H_

#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T,template <typename> class DistBuffer, typename GeomType>
  void EFuncAngleBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      void (*efunc)(const T&,const UniqueParameter*,T&)) {
    unsigned int I=idx[0], J=idx[1], K=idx[2];
    T dsq01, dsq12, dsq20;
    dsq01=Distance(X[I],X[J],I,J,Geo,B);
    dsq12=Distance(X[J],X[K],J,K,Geo,B);
    dsq20=Distance(X[K],X[I],K,I,Geo,B);
    T cosAngle=(dsq01+dsq12-dsq20)/sqroot(dsq01*dsq12)*0.5;
    T ee;
    efunc(cosAngle,P,ee);
    Energy+=ee;
  }

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void GFuncAngleBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec,
      void (*gfunc)(const T&,const UniqueParameter*,T&)) {
    unsigned int I=idx[0], J=idx[1], K=idx[2];
    T dsq01, dsq12, dsq20;
    dsq01=Distance(X[I],X[J],I,J,Geo,B);
    copy(tmvec[0],B.DisplaceVec);
    dsq12=Distance(X[J],X[K],J,K,Geo,B);
    copy(tmvec[1],B.DisplaceVec);
    dsq20=Distance(X[K],X[I],K,I,Geo,B);
    T cosAngle=(dsq01+dsq12-dsq20)*0.5;
    copy(tmvec[2],tmvec[1]);
    shift(tmvec[2],-cosAngle/dsq01,tmvec[0]);
    copy(tmvec[3],tmvec[0]);
    shift(tmvec[3],-cosAngle/dsq12,tmvec[1]);
    T d01,d12;
    d01=sqroot(dsq01);
    d12=sqroot(dsq12);
    cosAngle/=d01*d12;
    T sinAngle,nr0,nr2;
    sinAngle=sqroot(1.-cosAngle*cosAngle);
    nr0=d12*sinAngle;
    nr2=d01*sinAngle;
    assert(nr0>1e-8);
    assert(nr2>1e-8);
    scale(tmvec[2],1./nr0);
    scale(tmvec[3],1./nr2);
    T ef;
    gfunc(cosAngle,P,ef);
    T ef0,ef2;
    ef0=-ef/d01;
    ef2=-ef/d12;
    shift(Gradient[I],+ef0,tmvec[2]);
    shift(Gradient[J],-ef0,tmvec[2]);
    shift(Gradient[K],+ef2,tmvec[3]);
    shift(Gradient[J],-ef2,tmvec[3]);
  }

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void BFuncAngleBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec,
      void (*bfunc)(const T&,const UniqueParameter*,T&,T&)) {
    unsigned int I=idx[0], J=idx[1], K=idx[2];
    T dsq01, dsq12, dsq20;
    dsq01=Distance(X[I],X[J],I,J,Geo,B);
    copy(tmvec[0],B.DisplaceVec);
    dsq12=Distance(X[J],X[K],J,K,Geo,B);
    copy(tmvec[1],B.DisplaceVec);
    dsq20=Distance(X[K],X[I],K,I,Geo,B);
    T cosAngle=(dsq01+dsq12-dsq20)*0.5;
    copy(tmvec[2],tmvec[1]);
    shift(tmvec[2],-cosAngle/dsq01,tmvec[0]);
    copy(tmvec[3],tmvec[0]);
    shift(tmvec[3],-cosAngle/dsq12,tmvec[1]);
    T d01,d12;
    d01=sqroot(dsq01);
    d12=sqroot(dsq12);
    cosAngle/=d01*d12;
    T sinAngle,nr0,nr2;
    sinAngle=sqroot(1.-cosAngle*cosAngle);
    nr0=d12*sinAngle;
    nr2=d01*sinAngle;
    assert(nr0>1e-8);
    assert(nr2>1e-8);
    scale(tmvec[2],1./nr0);
    scale(tmvec[3],1./nr2);
    T ee,ef;
    bfunc(cosAngle,P,ee,ef);
    Energy+=ee;
    T ef0,ef2;
    ef0=-ef/d01;
    ef2=-ef/d12;
    shift(Gradient[I],+ef0,tmvec[2]);
    shift(Gradient[J],-ef0,tmvec[2]);
    shift(Gradient[K],+ef2,tmvec[3]);
    shift(Gradient[J],-ef2,tmvec[3]);
  }

}

#endif
