
#ifndef _Interaction_Dihedral_Base_H_
#define _Interaction_Dihedral_Base_H_

#include "vector.h"
#include "unique-parameter.h"
#include <cmath>

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncDihedralBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, Vector<double>* tmvec,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy,
      void (*efunc)(const double,const UniqueParameter*,double&)) {
    assert(DEval.size==3);
    // tmvec must have more than 6 vectors
    Evaluate(DEval,Coor[Idx[1]],Coor[Idx[0]],Idx[1],Idx[0],Geo);
    assign(tmvec[0],DEval.displacementvec);
    Evaluate(DEval,Coor[Idx[2]],Coor[Idx[1]],Idx[2],Idx[1],Geo);
    assign(tmvec[1],DEval.displacementvec);
    Evaluate(DEval,Coor[Idx[3]],Coor[Idx[2]],Idx[3],Idx[2],Geo);
    assign(tmvec[2],DEval.displacementvec);
    crossProd(tmvec[0],tmvec[1],tmvec[3]);
    crossProd(tmvec[1],tmvec[2],tmvec[4]);
    double nr1, nr2;
    nr1=norm(tmvec[3]);
    nr2=norm(tmvec[4]);
    assert(nr1>1e-8);
    assert(nr2>1e-8);
    scale(tmvec[3],1./nr1);
    scale(tmvec[4],1./nr2);
    double cosDihedral=dot(tmvec[3],tmvec[4]);
    crossProd(tmvec[3],tmvec[4],tmvec[5]);
    double sgnDihedral=dot(tmvec[0],tmvec[5]);
    double dihedral=acos(cosDihedral)*(sgnDihedral>0?1:-1);
    double ee;
    efunc(dihedral,Prm,ee);
    Energy+=ee;
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncDihedralBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, Vector<double>* tmvec,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient,
      void (*gfunc)(const double,const UniqueParameter*,double&)) {
    assert(DEval.size==3);
    // tmvec must have more than 6 vectors
    double dsq01,dsq12,dsq23;
    Evaluate(DEval,Coor[Idx[1]],Coor[Idx[0]],Idx[1],Idx[0],Geo);
    dsq01=DEval();
    assign(tmvec[0],DEval.displacementvec);
    Evaluate(DEval,Coor[Idx[2]],Coor[Idx[1]],Idx[2],Idx[1],Geo);
    dsq12=DEval();
    assign(tmvec[1],DEval.displacementvec);
    Evaluate(DEval,Coor[Idx[3]],Coor[Idx[2]],Idx[3],Idx[2],Geo);
    dsq23=DEval();
    assign(tmvec[2],DEval.displacementvec);
    crossProd(tmvec[0],tmvec[1],tmvec[3]);
    crossProd(tmvec[1],tmvec[2],tmvec[4]);
    double nr1, nr2;
    nr1=norm(tmvec[3]);
    nr2=norm(tmvec[4]);
    assert(nr1>1e-8);
    assert(nr2>1e-8);
    scale(tmvec[3],1./nr1);
    scale(tmvec[4],1./nr2);
    double cosDihedral=dot(tmvec[3],tmvec[4]);
    crossProd(tmvec[3],tmvec[4],tmvec[5]);
    double sgnDihedral=dot(tmvec[0],tmvec[5]);
    double dihedral=acos(cosDihedral)*(sgnDihedral>0?1:-1);
    double ef;
    gfunc(dihedral,Prm,ef);
    double ef0,ef1,ef2,ef3;
    double ivdsq12=1./dsq12,tmda,tmdb;
    double dotab=dot(tmvec[0],tmvec[1]),dotbc=dot(tmvec[1],tmvec[2]);
    tmda=dotab*ivdsq12;
    tmdb=dotbc*ivdsq12;
    ef0=-ef/sqrt(dsq01-dotab*tmda);
    ef3=+ef/sqrt(dsq23-dotbc*tmdb);
    ef1=tmda*ef0;
    ef2=tmdb*ef3;
    shift(Gradient[Idx[0]],ef0,tmvec[3]);
    shift(Gradient[Idx[3]],ef3,tmvec[4]);
    shift(Gradient[Idx[1]],-ef0-ef1,tmvec[3]);
    shift(Gradient[Idx[1]],ef2,tmvec[4]);
    shift(Gradient[Idx[2]],ef1,tmvec[3]);
    shift(Gradient[Idx[2]],-ef3-ef2,tmvec[4]);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncDihedralBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, Vector<double>* tmvec,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient,
      void (*bfunc)(const double,const UniqueParameter*,double&,double&)) {
    assert(DEval.size==3);
    // tmvec must have more than 6 vectors
    double dsq01,dsq12,dsq23;
    Evaluate(DEval,Coor[Idx[1]],Coor[Idx[0]],Idx[1],Idx[0],Geo);
    dsq01=DEval();
    assign(tmvec[0],DEval.displacementvec);
    Evaluate(DEval,Coor[Idx[2]],Coor[Idx[1]],Idx[2],Idx[1],Geo);
    dsq12=DEval();
    assign(tmvec[1],DEval.displacementvec);
    Evaluate(DEval,Coor[Idx[3]],Coor[Idx[2]],Idx[3],Idx[2],Geo);
    dsq23=DEval();
    assign(tmvec[2],DEval.displacementvec);
    crossProd(tmvec[0],tmvec[1],tmvec[3]);
    crossProd(tmvec[1],tmvec[2],tmvec[4]);
    double nr1, nr2;
    nr1=norm(tmvec[3]);
    nr2=norm(tmvec[4]);
    assert(nr1>1e-8);
    assert(nr2>1e-8);
    scale(tmvec[3],1./nr1);
    scale(tmvec[4],1./nr2);
    double cosDihedral=dot(tmvec[3],tmvec[4]);
    crossProd(tmvec[3],tmvec[4],tmvec[5]);
    double sgnDihedral=dot(tmvec[0],tmvec[5]);
    double dihedral=acos(cosDihedral)*(sgnDihedral>0?1:-1);
    double ee,ef;
    bfunc(dihedral,Prm,ee,ef);
    Energy+=ee;
    double ef0,ef1,ef2,ef3;
    double ivdsq12=1./dsq12,tmda,tmdb;
    double dotab=dot(tmvec[0],tmvec[1]),dotbc=dot(tmvec[1],tmvec[2]);
    tmda=dotab*ivdsq12;
    tmdb=dotbc*ivdsq12;
    ef0=-ef/sqrt(dsq01-dotab*tmda);
    ef3=+ef/sqrt(dsq23-dotbc*tmdb);
    ef1=tmda*ef0;
    ef2=tmdb*ef3;
    shift(Gradient[Idx[0]],ef0,tmvec[3]);
    shift(Gradient[Idx[3]],ef3,tmvec[4]);
    shift(Gradient[Idx[1]],-ef0-ef1,tmvec[3]);
    shift(Gradient[Idx[1]],ef2,tmvec[4]);
    shift(Gradient[Idx[2]],ef1,tmvec[3]);
    shift(Gradient[Idx[2]],-ef3-ef2,tmvec[4]);
  }

}

#endif
