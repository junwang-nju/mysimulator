
#ifndef _LBFGS_Minimizer_Buffer_Operation_H_
#define _LBFGS_Minimizer_Buffer_Operation_H_

#include "data/minimizer/lbfgs-minimizer-buffer.h"

namespace std {

  template <typename IType, template <typename> class SpType,
            typename PmType, typename T,
            template<typename,template<typename>class,
                     typename,typename> class LMin,
            unsigned int MCorr>
  void initMinimizerLocation(
      LBFGSMinimizerBuffer<IType,SpType,PmType,T,LMin,MCorr>& B,
      const SpType<T>& Coor, PmType& Pmx) {
    typedef LMin<IType,SpType,PmType,T> LMType;
    initMinimizerLocation(static_cast<LMType&>(B),Coor,Pmx);
    imprint(B.Dirc,Coor);
    for(unsigned int i=0;i<MCorr;++i) {
      imprint(B.dX[i],Coor);
      imprint(B.dG[i],Coor);
    }
    imprint(B.lastX,Coor);
    imprint(B.lastG,Coor);
  }

}

#endif

