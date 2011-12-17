
#ifndef _Minimizer_LBFGS_Load_Specification_H_
#define _Minimizer_LBFGS_Load_Specification_H_

#include "minimizer/lbfgs/specification.h"
#include "minimizer/line/load.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(Minimizer<LBFGS,LMN,T,IDT,PT,GT,VT,SCT,LCM>& M,
            System<T,IDT,PT,GT,VT,SCT>& S) {
    typedef
    typename Minimizer<LBFGS,LMN,T,IDT,PT,GT,VT,SCT,LCM>::ParentType
    Type;
    load(static_cast<Type&>(M),S);
    if(M.MaxCorrelations==0)  M.SetMaxCorrelations();
    allocate(M.dX,M.MaxCorrelations);
    allocate(M.dG,M.MaxCorrelations);
    for(unsigned int i=0;i<M.MaxCorrelations;++i) {
      imprint(M.dX[i],M.MemSys().Content().X);
      imprint(M.dG[i],M.MemSys().Content().X);
    }
    allocate(M.alpha,M.MaxCorrelations);
    allocate(M.rho,M.MaxCorrelations);
    imprint(M.lastX,M.MemSys().Content().X);
    imprint(M.lastG,M.MemSys().Content().X);
  }

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(Minimizer<LBFGS,LMN,T,IDT,PT,GT,VT,SCT,LCM>& M,
            Object<System<T,IDT,PT,GT,VT,SCT> >& S) {
    load(M.S());
  }

}

#endif

