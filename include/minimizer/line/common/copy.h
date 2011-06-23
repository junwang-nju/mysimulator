
#ifndef _Minimizer_Line_Common_Copy_H_
#define _Minimizer_Line_Common_Copy_H_

#include "minimizer/line/common/interface.h"
#include "minimizer/base/copy.h"

namespace mysimulator {

  template <typename FT,template<typename> class VT,typename PT,typename T>
  void copy(LineMinimizerCommon<FT,VT,PT,T>& L,
            const LineMinimizerCommon<FT,VT,PT,T>& cL) {
    assert(IsValid(L)&&IsValid(cL));
    typedef MinimizerBase<FT,VT,PT,T>    Type;
    copy(static_cast<Type&>(L),static_cast<const Type&>(cL));
    copy(L.RunX,cL.RunX);
    copy(L.RunG,cL.RunG);
    copy(L.LineDirc,cL.LineDirc);
    copy(L.LineSearchCount,cL.LineSearchCount);
    copy(L.RunEnergy,cL.RunEnergy);
    copy(L.RunProject,cL.RunProject);
    copy(L.DecreaseFac,cL.DecreaseFac);
    copy(L.CurvatureFac,cL.CurvatureFac);
    copy(L.GradThreshold,cL.GradThreshold);
  }

}

#endif

