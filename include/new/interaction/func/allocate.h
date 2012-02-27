
#ifndef _Interaction_Func_Allocate_H_
#define _Interaction_Func_Allocate_H_

#include "interaction/func/interface.h"

#include "interaction/func/impl/pairwise/harmonic/func.h"
#include "interaction/func/impl/pairwise/lj612/func.h"
#include "interaction/func/impl/pairwise/lj612cut/func.h"
#include "interaction/func/impl/pairwise/lj1012/func.h"
#include "interaction/func/impl/pairwise/lj1012cut/func.h"
#include "interaction/func/impl/pairwise/core12/func.h"
#include "interaction/func/impl/pairwise/corelj612/func.h"
#include "interaction/func/impl/pairwise/coulomb/func.h"
#include "interaction/func/impl/pairwise/dist-coulomb/func.h"
#include "interaction/func/impl/angle/harmonic/func.h"

#include "interaction/func/impl/pairwise/harmonic/diff.h"
#include "interaction/func/impl/pairwise/lj612/diff.h"
#include "interaction/func/impl/pairwise/lj612cut/diff.h"
#include "interaction/func/impl/pairwise/lj1012/diff.h"
#include "interaction/func/impl/pairwise/lj1012cut/diff.h"
#include "interaction/func/impl/pairwise/core12/diff.h"
#include "interaction/func/impl/pairwise/corelj612/diff.h"
#include "interaction/func/impl/pairwise/coulomb/diff.h"
#include "interaction/func/impl/pairwise/dist-coulomb/diff.h"
#include "interaction/func/impl/angle/harmonic/diff.h"

#include "interaction/func/impl/pairwise/harmonic/both.h"
#include "interaction/func/impl/pairwise/lj612/both.h"
#include "interaction/func/impl/pairwise/lj612cut/both.h"
#include "interaction/func/impl/pairwise/lj1012/both.h"
#include "interaction/func/impl/pairwise/lj1012cut/both.h"
#include "interaction/func/impl/pairwise/core12/both.h"
#include "interaction/func/impl/pairwise/corelj612/both.h"
#include "interaction/func/impl/pairwise/coulomb/both.h"
#include "interaction/func/impl/pairwise/dist-coulomb/both.h"
#include "interaction/func/impl/angle/harmonic/both.h"

#include "interaction/func/method/pairwise/energy.h"
#include "interaction/func/method/angle/energy.h"

#include "interaction/func/method/pairwise/gradient.h"
#include "interaction/func/method/angle/gradient.h"

#include "interaction/func/method/pairwise/both.h"
#include "interaction/func/method/angle/both.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void allocate(InteractionFunc<GeomType,T>& F,
                const InteractionFuncName& itag, const unsigned int& dim) {
    release(F);
    F.tag=itag;
    switch(itag) {
      case Harmonic:
        F.EFunc=FuncHarmonic<T>;
        F.GFunc=DiffHarmonic<T>;
        F.BFunc=BothHarmonic<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case LJ612:
        F.EFunc=FuncLJ612<T>;
        F.GFunc=DiffLJ612<T>;
        F.BFunc=BothLJ612<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case LJ612Cut:
        F.EFunc=FuncLJ612Cut<T>;
        F.GFunc=DiffLJ612Cut<T>;
        F.BFunc=BothLJ612Cut<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case LJ1012:
        F.EFunc=FuncLJ1012<T>;
        F.GFunc=DiffLJ1012<T>;
        F.BFunc=BothLJ1012<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case LJ1012Cut:
        F.EFunc=FuncLJ1012Cut<T>;
        F.GFunc=DiffLJ1012Cut<T>;
        F.BFunc=BothLJ1012Cut<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case Core12:
        F.EFunc=FuncCore12<T>;
        F.GFunc=DiffCore12<T>;
        F.BFunc=BothCore12<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case CoreLJ612:
        F.EFunc=FuncCoreLJ612<T>;
        F.GFunc=DiffCoreLJ612<T>;
        F.BFunc=BothCoreLJ612<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case Coulomb:
        F.EFunc=FuncCoulomb<T>;
        F.GFunc=DiffCoulomb<T>;
        F.BFunc=BothCoulomb<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case distCoulomb:
        F.EFunc=FuncDistCoulomb<T>;
        F.GFunc=DiffDistCoulomb<T>;
        F.BFunc=BothDistCoulomb<T>;
        F.EMethod=EFuncMethodPairwise<GeomType,T>;
        F.GMethod=GFuncMethodPairwise<GeomType,T>;
        F.BMethod=BFuncMethodPairwise<GeomType,T>;
        allocate(F.tmvec,1U,dim);
        break;
      case AngleHarmonic:
        F.EFunc=FuncAngleHarmonic<T>;
        F.GFunc=DiffAngleHarmonic<T>;
        F.BFunc=BothAngleHarmonic<T>;
        F.EMethod=EFuncMethodAngle<GeomType,T>;
        F.GMethod=GFuncMethodAngle<GeomType,T>;
        F.BMethod=BFuncMethodAngle<GeomType,T>;
        allocate(F.tmvec,4U,dim);
      default:
        Error("Unknown Interaction Function Name!");
    }
  }

  template <typename GeomType, typename T>
  void imprint(InteractionFunc<GeomType,T>& F,
               const InteractionFunc<GeomType,T>& cF) { allocate(F,cF.tag); }

}

#endif

