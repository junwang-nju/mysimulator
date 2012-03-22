
#ifndef _Interaction_Func_Allocate_H_
#define _Interaction_Func_Allocate_H_

#include "interaction/func/interface.h"

#include "interaction/func/impl/pairwise/harmonic/func-dsq.h"
#include "interaction/func/impl/pairwise/lj612/func-dsq.h"
#include "interaction/func/impl/pairwise/lj612cut/func-dsq.h"
#include "interaction/func/impl/pairwise/lj1012/func-dsq.h"
#include "interaction/func/impl/pairwise/lj1012cut/func-dsq.h"
#include "interaction/func/impl/pairwise/core12/func-dsq.h"
#include "interaction/func/impl/pairwise/corelj612/func-dsq.h"
#include "interaction/func/impl/pairwise/coulomb/func-dsq.h"
#include "interaction/func/impl/pairwise/dist-coulomb/func-dsq.h"
#include "interaction/func/impl/angle/harmonic/func-cs.h"
#include "interaction/func/impl/dihedral/periodic/func-dh.h"

#include "interaction/func/impl/pairwise/harmonic/diff-dsq.h"
#include "interaction/func/impl/pairwise/lj612/diff-dsq.h"
#include "interaction/func/impl/pairwise/lj612cut/diff-dsq.h"
#include "interaction/func/impl/pairwise/lj1012/diff-dsq.h"
#include "interaction/func/impl/pairwise/lj1012cut/diff-dsq.h"
#include "interaction/func/impl/pairwise/core12/diff-dsq.h"
#include "interaction/func/impl/pairwise/corelj612/diff-dsq.h"
#include "interaction/func/impl/pairwise/coulomb/diff-dsq.h"
#include "interaction/func/impl/pairwise/dist-coulomb/diff-dsq.h"
#include "interaction/func/impl/angle/harmonic/diff-cs.h"
#include "interaction/func/impl/dihedral/periodic/diff-dh.h"

#include "interaction/func/impl/pairwise/harmonic/both-dsq.h"
#include "interaction/func/impl/pairwise/lj612/both-dsq.h"
#include "interaction/func/impl/pairwise/lj612cut/both-dsq.h"
#include "interaction/func/impl/pairwise/lj1012/both-dsq.h"
#include "interaction/func/impl/pairwise/lj1012cut/both-dsq.h"
#include "interaction/func/impl/pairwise/core12/both-dsq.h"
#include "interaction/func/impl/pairwise/corelj612/both-dsq.h"
#include "interaction/func/impl/pairwise/coulomb/both-dsq.h"
#include "interaction/func/impl/pairwise/dist-coulomb/both-dsq.h"
#include "interaction/func/impl/angle/harmonic/both-cs.h"
#include "interaction/func/impl/dihedral/periodic/both-dh.h"

#include "interaction/func/method/pairwise/energy.h"
#include "interaction/func/method/angle/energy.h"
#include "interaction/func/method/dihedral/energy.h"

#include "interaction/func/method/pairwise/gradient.h"
#include "interaction/func/method/angle/gradient.h"
#include "interaction/func/method/dihedral/gradient.h"

#include "interaction/func/method/pairwise/both.h"
#include "interaction/func/method/angle/both.h"
#include "interaction/func/method/dihedral/both.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void allocate(InteractionFunc<GeomType,T>& F,
                const InteractionFuncName& itag, const unsigned int& dim) {
    release(F);
    F.tag=itag;
    switch(itag) {
      case Harmonic:
        F.EFunc=FuncHarmonicDistSQ<T>;
        F.GFunc=DiffHarmonicDistSQ<T>;
        F.BFunc=BothHarmonicDistSQ<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case LJ612:
        F.EFunc=FuncLJ612DistSQ<T>;
        F.GFunc=DiffLJ612DistSQ<T>;
        F.BFunc=BothLJ612DistSQ<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case LJ612Cut:
        F.EFunc=FuncLJ612CutDistSQ<T>;
        F.GFunc=DiffLJ612CutDistSQ<T>;
        F.BFunc=BothLJ612CutDistSQ<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case LJ1012:
        F.EFunc=FuncLJ1012DistSQ<T>;
        F.GFunc=DiffLJ1012DistSQ<T>;
        F.BFunc=BothLJ1012DistSQ<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case LJ1012Cut:
        F.EFunc=FuncLJ1012CutDistSQ<T>;
        F.GFunc=DiffLJ1012CutDistSQ<T>;
        F.BFunc=BothLJ1012CutDistSQ<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case Core12:
        F.EFunc=FuncCore12DistSQ<T>;
        F.GFunc=DiffCore12DistSQ<T>;
        F.BFunc=BothCore12DistSQ<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case CoreLJ612:
        F.EFunc=FuncCoreLJ612DistSQ<T>;
        F.GFunc=DiffCoreLJ612DistSQ<T>;
        F.BFunc=BothCoreLJ612DistSQ<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case Coulomb:
        F.EFunc=FuncCoulombDistSQ<T>;
        F.GFunc=DiffCoulombDistSQ<T>;
        F.BFunc=BothCoulombDistSQ<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case distCoulomb:
        F.EFunc=FuncDistCoulombDistSQ<T>;
        F.GFunc=DiffDistCoulombDistSQ<T>;
        F.BFunc=BothDistCoulombDistSQ<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case AngleHarmonic:
        F.EFunc=FuncAngleHarmonicCosine<T>;
        F.GFunc=DiffAngleHarmonicCosine<T>;
        F.BFunc=BothAngleHarmonicCosine<T>;
        F.EMethod=EFuncMethodAngle<GeomType,T>;
        F.GMethod=GFuncMethodAngle<GeomType,T>;
        F.BMethod=BFuncMethodAngle<GeomType,T>;
        allocate(F.tmvec,4U,dim);
        break;
      case DihedralPeriodic:
        F.EFunc=FuncDihedralPeriodicDih<T>;
        F.GFunc=DiffDihedralPeriodicDih<T>;
        F.BFunc=BothDihedralPeriodicDih<T>;
        F.EMethod=EFuncMethodDihedral<GeomType,T>;
        F.GMethod=GFuncMethodDihedral<GeomType,T>;
        F.BMethod=BFuncMethodDihedral<GeomType,T>;
        allocate(F.tmvec,6U,dim);
        break;
      default:
        Error("Unknown Interaction Function Name!");
    }
  }

  template <typename GeomType, typename T>
  void imprint(InteractionFunc<GeomType,T>& F,
               const InteractionFunc<GeomType,T>& cF) { allocate(F,cF.tag); }

}

#endif

