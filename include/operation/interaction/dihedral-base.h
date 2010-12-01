
#ifndef _Interaction_Dihedral_Base_H_
#define _Interaction_Dihedral_Base_H_

#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void EFuncDihedralBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec, void (*efunc)(const T&,const UniqueParameter*,T&)) {
    assert(B.Dimension()==3);
    unsigned int I=idx[0], J=idx[1], K=idx[2], L=idx[3];
    Distance(X[J],X[I],J,I,Geo,B);
    copy(tmvec[0],B.DisplaceVec);
    Distance(X[K],X[J],K,J,Geo,B);
    copy(tmvec[1],B.DisplaceVec);
    Distance(X[L],X[K],L,K,Geo,B);
    copy(tmvec[2],B.DisplaceVec);
    crossProd(tmvec[3],tmvec[0],tmvec[1]);
    crossProd(tmvec[4],tmvec[1],tmvec[2]);
    T nr1,nr2;
    nr1=norm(tmvec[3]);
    nr2=norm(tmvec[4]);
    assert(nr1>1e-8);
    assert(nr2>1e-8);
    scale(tmvec[3],1./nr1);
    scale(tmvec[4],1./nr2);
    T csDih=dot(tmvec[3],tmvec[4]);
    crossProd(tmvec[5],tmvec[3],tmvec[4]);
    T sgnDih=(dot(tmvec[1],tmvec[5])>0?1:-1);
    T dih=arccos(csDih)*sgnDih;
    T ee;
    efunc(dih,P,ee);
    Energy+=ee;
  }

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void GFuncDihedralBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec, void (*gfunc)(const T&,const UniqueParameter*,T&)) {
    assert(B.Dimension()==3);
    unsigned int I=idx[0], J=idx[1], K=idx[2], L=idx[3];
    T dsq01,dsq12,dsq23;
    dsq01=Distance(X[J],X[I],J,I,Geo,B);
    copy(tmvec[0],B.DisplaceVec);
    dsq12=Distance(X[K],X[J],K,J,Geo,B);
    copy(tmvec[1],B.DisplaceVec);
    dsq23=Distance(X[L],X[K],L,K,Geo,B);
    copy(tmvec[2],B.DisplaceVec);
    crossProd(tmvec[3],tmvec[0],tmvec[1]);
    crossProd(tmvec[4],tmvec[1],tmvec[2]);
    T nr1,nr2;
    nr1=norm(tmvec[3]);
    nr2=norm(tmvec[4]);
    assert(nr1>1e-8);
    assert(nr2>1e-8);
    scale(tmvec[3],1./nr1);
    scale(tmvec[4],1./nr2);
    T csDih=dot(tmvec[3],tmvec[4]);
    crossProd(tmvec[5],tmvec[3],tmvec[4]);
    T sgnDih=(dot(tmvec[1],tmvec[5])>0?1:-1);
    T dih=arccos(csDih)*sgnDih;
    T ef,ef0,ef1,ef2,ef3;
    gfunc(dih,P,ef);
    T ivdsq12=1./dsq12;
    T tma,tmb;
    T dotab=dot(tmvec[0],tmvec[1]), dotbc=dot(tmvec[1],tmvec[2]);
    tma=dotab*ivdsq12;
    tmb=dotbc*ivdsq12;
    ef0=-ef/sqroot(dsq01-dotab*tma);
    ef3=+ef/sqroot(dsq23-dotbc*tmb);
    ef1=tma*ef0;
    ef2=tmb*ef3;
    shift(Gradient[I],ef0,tmvec[3]);
    shift(Gradient[L],ef3,tmvec[4]);
    shift(Gradient[J],-ef0-ef1,tmvec[3]);
    shift(Gradient[J],+ef2,tmvec[4]);
    shift(Gradient[K],+ef1,tmvec[3]);
    shift(Gradient[K],-ef3-ef2,tmvec[4]);
  }

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void BFuncDihedralBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec, void (*bfunc)(const T&,const UniqueParameter*,T&,T&)) {
    assert(B.Dimension()==3);
    unsigned int I=idx[0], J=idx[1], K=idx[2], L=idx[3];
    T dsq01,dsq12,dsq23;
    dsq01=Distance(X[J],X[I],J,I,Geo,B);
    copy(tmvec[0],B.DisplaceVec);
    dsq12=Distance(X[K],X[J],K,J,Geo,B);
    copy(tmvec[1],B.DisplaceVec);
    dsq23=Distance(X[L],X[K],L,K,Geo,B);
    copy(tmvec[2],B.DisplaceVec);
    crossProd(tmvec[3],tmvec[0],tmvec[1]);
    crossProd(tmvec[4],tmvec[1],tmvec[2]);
    T nr1,nr2;
    nr1=norm(tmvec[3]);
    nr2=norm(tmvec[4]);
    assert(nr1>1e-8);
    assert(nr2>1e-8);
    scale(tmvec[3],1./nr1);
    scale(tmvec[4],1./nr2);
    T csDih=dot(tmvec[3],tmvec[4]);
    crossProd(tmvec[5],tmvec[3],tmvec[4]);
    T sgnDih=(dot(tmvec[1],tmvec[5])>0?1:-1);
    T dih=arccos(csDih)*sgnDih;
    T ee,ef,ef0,ef1,ef2,ef3;
    bfunc(dih,P,ee,ef);
    Energy+=ee;
    T ivdsq12=1./dsq12;
    T tma,tmb;
    T dotab=dot(tmvec[0],tmvec[1]), dotbc=dot(tmvec[1],tmvec[2]);
    tma=dotab*ivdsq12;
    tmb=dotbc*ivdsq12;
    ef0=-ef/sqroot(dsq01-dotab*tma);
    ef3=+ef/sqroot(dsq23-dotbc*tmb);
    ef1=tma*ef0;
    ef2=tmb*ef3;
    shift(Gradient[I],ef0,tmvec[3]);
    shift(Gradient[L],ef3,tmvec[4]);
    shift(Gradient[J],-ef0-ef1,tmvec[3]);
    shift(Gradient[J],+ef2,tmvec[4]);
    shift(Gradient[K],+ef1,tmvec[3]);
    shift(Gradient[K],-ef3-ef2,tmvec[4]);
  }

}

#endif
