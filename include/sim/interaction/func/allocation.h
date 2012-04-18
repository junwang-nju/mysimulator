
#ifndef _Interaction_Func_Allocate_H_
#define _Interaction_Func_Allocate_H_

#include "interaction/func/interface.h"

#include "interaction/func/impl/pairwise/func.h"
#include "interaction/func/impl/angle/func.h"

#include "interaction/func/impl/pairwise/diff.h"
#include "interaction/func/impl/angle/diff.h"

#include "interaction/func/impl/pairwise/both.h"
#include "interaction/func/impl/angle/both.h"

#include "interaction/func/method/pairwise/energy.h"
#include "interaction/func/method/angle/energy.h"

#include "interaction/func/method/pairwise/gradient.h"
#include "interaction/func/method/angle/gradient.h"

#include "interaction/func/method/pairwise/both.h"
#include "interaction/func/method/angle/both.h"

#include <cstdio>
#include <cstdlib>

namespace mysimulator {

  template <typename GeomType,typename T>
  void allocate(InteractionFunc<GeomType,T>& F,
                const InteractionFuncName& itag) {
    release(F);
    F.tag=itag;
    switch(itag) {
      case Harmonic:
        F.EFunc=FuncHarmonic<T>;
        F.GFunc=DiffHarmonic<T>;
        F.BFunc=BothHarmonic<T>;
        F.EMethod=EMethodPairwise<GeomType,T>;
        F.GMethod=GMethodPairwise<GeomType,T>;
        F.BMethod=BMethodPairwise<GeomType,T>;
        break;
      case LJ612:
        F.EFunc=FuncLJ612<T>;
        F.GFunc=DiffLJ612<T>;
        F.BFunc=BothLJ612<T>;
        F.EMethod=EMethodPairwise<GeomType,T>;
        F.GMethod=GMethodPairwise<GeomType,T>;
        F.BMethod=BMethodPairwise<GeomType,T>;
        break;
      case LJ612Cut:
        F.EFunc=FuncLJ612Cut<T>;
        F.GFunc=DiffLJ612Cut<T>;
        F.BFunc=BothLJ612Cut<T>;
        F.EMethod=EMethodPairwise<GeomType,T>;
        F.GMethod=GMethodPairwise<GeomType,T>;
        F.BMethod=BMethodPairwise<GeomType,T>;
        break;
      case LJ1012:
        F.EFunc=FuncLJ1012<T>;
        F.GFunc=DiffLJ1012<T>;
        F.BFunc=BothLJ1012<T>;
        F.EMethod=EMethodPairwise<GeomType,T>;
        F.GMethod=GMethodPairwise<GeomType,T>;
        F.BMethod=BMethodPairwise<GeomType,T>;
        break;
      case LJ1012Cut:
        F.EFunc=FuncLJ1012Cut<T>;
        F.GFunc=DiffLJ1012Cut<T>;
        F.BFunc=BothLJ1012Cut<T>;
        F.EMethod=EMethodPairwise<GeomType,T>;
        F.GMethod=GMethodPairwise<GeomType,T>;
        F.BMethod=BMethodPairwise<GeomType,T>;
        break;
      case Core12:
        F.EFunc=FuncCore12<T>;
        F.GFunc=DiffCore12<T>;
        F.BFunc=BothCore12<T>;
        F.EMethod=EMethodPairwise<GeomType,T>;
        F.GMethod=GMethodPairwise<GeomType,T>;
        F.BMethod=BMethodPairwise<GeomType,T>;
        break;
      case CoreLJ612:
        F.EFunc=FuncCoreLJ612<T>;
        F.GFunc=DiffCoreLJ612<T>;
        F.BFunc=BothCoreLJ612<T>;
        F.EMethod=EMethodPairwise<GeomType,T>;
        F.GMethod=GMethodPairwise<GeomType,T>;
        F.BMethod=BMethodPairwise<GeomType,T>;
        break;
      case Coulomb:
        F.EFunc=FuncCoulomb<T>;
        F.GFunc=DiffCoulomb<T>;
        F.BFunc=BothCoulomb<T>;
        F.EMethod=EMethodPairwise<GeomType,T>;
        F.GMethod=GMethodPairwise<GeomType,T>;
        F.BMethod=BMethodPairwise<GeomType,T>;
        break;
      case DistCoulomb:
        F.EFunc=FuncDistCoulomb<T>;
        F.GFunc=DiffDistCoulomb<T>;
        F.BFunc=BothDistCoulomb<T>;
        F.EMethod=EMethodPairwise<GeomType,T>;
        F.GMethod=GMethodPairwise<GeomType,T>;
        F.BMethod=BMethodPairwise<GeomType,T>;
        break;
      case AngleHarmonic:
        F.EFunc=FuncAngleHarmonic<T>;
        F.GFunc=DiffAngleHarmonic<T>;
        F.BFunc=BothAngleHarmonic<T>;
        F.EMethod=EMethodAngle<GeomType,T>;
        F.GMethod=GMethodAngle<GeomType,T>;
        F.BMethod=BMethodAngle<GeomType,T>;
        break;
      default:
        fprintf(stderr,"Unknown Interaction Func Name!\n");
    }
  }

}

#endif

