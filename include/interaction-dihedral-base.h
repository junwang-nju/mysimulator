
#ifndef _Interaction_Dihedral_Base_H_
#define _Interaction_Dihedral_Base_H_

#include "ref-vector.h"
#include "vector-op.h"
#include <cmath>

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc_Dihedral_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >& tmVec,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy,
      void (*efunc)(const double, const VectorBase<double>&, double&)) {
    assert(DEval.Displacement().size()==3);
    assert(tmVec.size()>=6);
    DEval.Evaluate(Coor[Idx[1]],Coor[Idx[0]],Idx[1],Idx[0],Geo);
    tmVec[0]=DEval.Displacement();
    DEval.Evaluate(Coor[Idx[2]],Coor[Idx[1]],Idx[2],Idx[1],Geo);
    tmVec[1]=DEval.Displacement();
    DEval.Evaluate(Coor[Idx[3]],Coor[Idx[2]],Idx[3],Idx[2],Geo);
    tmVec[2]=DEval.Displacement();
    crossProd(tmVec[0],tmVec[1],tmVec[3]);
    crossProd(tmVec[1],tmVec[2],tmVec[4]);
    double nr1,nr2;
    nr1=norm(tmVec[3]);
    nr2=norm(tmVec[4]);
    assert(nr1>1e-8);
    assert(nr2>1e-8);
    tmVec[3].scale(1./nr1);
    tmVec[4].scale(1./nr2);
    double cosDihedral=dot(tmVec[3],tmVec[4]);
    crossProd(tmVec[3],tmVec[4],tmVec[5]);
    double SgnSinDihedral=dot(tmVec[1],tmVec[5]);
    double dihedral=acos(cosDihedral)*(SgnSinDihedral>0?1:-1);
    double ee;
    efunc(dihedral,Param,ee);
    Energy+=ee;
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc_Dihedral_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >& tmVec,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      VectorBase<refVector<double> >& Grad,
      void (*gfunc)(const double, const double, const double, const double,
                    const Vector<refVector<double> >&,
                    const VectorBase<double>&,
                    double&, double&, double&, double&)) {
    assert(DEval.Displacement().size()==3);
    assert(tmVec.size()>=6);
    double DSQ01,DSQ12,DSQ23;
    DEval.Evaluate(Coor[Idx[1]],Coor[Idx[0]],Idx[1],Idx[0],Geo);
    DSQ01=DEval.DistanceSQ();
    tmVec[0]=DEval.Displacement();
    DEval.Evaluate(Coor[Idx[2]],Coor[Idx[1]],Idx[2],Idx[1],Geo);
    DSQ12=DEval.DistanceSQ();
    tmVec[1]=DEval.Displacement();
    DEval.Evaluate(Coor[Idx[3]],Coor[Idx[2]],Idx[3],Idx[2],Geo);
    DSQ23=DEval.DistanceSQ();
    tmVec[2]=DEval.Displacement();
    crossProd(tmVec[0],tmVec[1],tmVec[3]);
    crossProd(tmVec[1],tmVec[2],tmVec[4]);
    double nr1,nr2;
    nr1=norm(tmVec[3]);
    nr2=norm(tmVec[4]);
    assert(nr1>1e-8);
    assert(nr2>1e-8);
    tmVec[3].scale(1./nr1);
    tmVec[4].scale(1./nr2);
    double cosDihedral=dot(tmVec[3],tmVec[4]);
    crossProd(tmVec[3],tmVec[4],tmVec[5]);
    double SgnSinDihedral=dot(tmVec[1],tmVec[5]);
    double dihedral=acos(cosDihedral)*(SgnSinDihedral>0?1:-1);
    double ef0,ef1,ef2,ef3;
    gfunc(dihedral,DSQ01,DSQ12,DSQ23,tmVec,Param,ef0,ef1,ef2,ef3);
    Grad[Idx[0]].shift(ef0,tmVec[3]);
    Grad[Idx[3]].shift(ef3,tmVec[4]);
    Grad[Idx[1]].shift(-ef0-ef1,tmVec[3]);
    Grad[Idx[1]].shift(ef2,tmVec[4]);
    Grad[Idx[2]].shift(ef1,tmVec[3]);
    Grad[Idx[2]].shift(-ef3-ef2,tmVec[4]);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc_Dihedral_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >& tmVec,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy, VectorBase<refVector<double> >& Grad,
      void (*bfunc)(const double, const double, const double, const double,
                    const VectorBase<refVector<double> >&,
                    const VectorBase<double>&,
                    double&, double&, double&, double&, double&)) {
    assert(DEval.Displacement().size()==3);
    assert(tmVec.size()>=6);
    double DSQ01,DSQ12,DSQ23;
    DEval.Evaluate(Coor[Idx[1]],Coor[Idx[0]],Idx[1],Idx[0],Geo);
    DSQ01=DEval.DistanceSQ();
    tmVec[0]=DEval.Displacement();
    DEval.Evaluate(Coor[Idx[2]],Coor[Idx[1]],Idx[2],Idx[1],Geo);
    DSQ12=DEval.DistanceSQ();
    tmVec[1]=DEval.Displacement();
    DEval.Evaluate(Coor[Idx[3]],Coor[Idx[2]],Idx[3],Idx[2],Geo);
    DSQ23=DEval.DistanceSQ();
    tmVec[2]=DEval.Displacement();
    crossProd(tmVec[0],tmVec[1],tmVec[3]);
    crossProd(tmVec[1],tmVec[2],tmVec[4]);
    double nr1,nr2;
    nr1=norm(tmVec[3]);
    nr2=norm(tmVec[4]);
    assert(nr1>1e-8);
    assert(nr2>1e-8);
    tmVec[3].scale(1./nr1);
    tmVec[4].scale(1./nr2);
    double cosDihedral=dot(tmVec[3],tmVec[4]);
    crossProd(tmVec[3],tmVec[4],tmVec[5]);
    double SgnSinDihedral=dot(tmVec[1],tmVec[5]);
    double dihedral=acos(cosDihedral)*(SgnSinDihedral>0?1:-1);
    double ee, ef0,ef1,ef2,ef3;
    bfunc(dihedral,DSQ01,DSQ12,DSQ23,tmVec,Param,ee,ef0,ef1,ef2,ef3);
    Grad[Idx[0]].shift(ef0,tmVec[3]);
    Grad[Idx[3]].shift(ef3,tmVec[4]);
    Grad[Idx[1]].shift(-ef0-ef1,tmVec[3]);
    Grad[Idx[1]].shift(ef2,tmVec[4]);
    Grad[Idx[2]].shift(ef1,tmVec[3]);
    Grad[Idx[2]].shift(-ef3-ef2,tmVec[4]);
  }

}

#endif

