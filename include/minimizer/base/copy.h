
#ifndef _Minimizer_Base_Copy_H_
#define _Minimizer_Base_Copy_H_

#include "minimizer/base/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename KT, template<typename> class VT,  typename PT, typename T>
  void copy(MinimizerBase<KTe,VT,PT,T>& M,const MinimizerBase<KT,VT,PT,T>& cM){
    copy(M.MinFunc,cM.MinFunc);
    copy(M.MinX,cM.MinX);
    copy(M.MinG,cM.MinG);
    copy(M.MinP,cM.MinP);
    copy(M.MinMask,cM.MinMask);
    copy(M.MinUMask,cM.MinUMask);
    copy(M.MinEnergy,cM.MinEnergy);
    copy(M.MinProject,cM.MinProject);
    copy(M.MinMove,cM.MinMove);
    copy(M.GCalcCount,cM.GCalcCount);
    copy(M.SearchScale,cM.SearchScale);
    copy(M.DOF,cM.DOF);
  }

}

#endif

