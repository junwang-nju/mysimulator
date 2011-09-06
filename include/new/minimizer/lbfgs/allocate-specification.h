
#ifndef _Minimizer_LBFGS_Allocate_Specification_H_
#define _Minimizer_LBFGS_Allocate_Specification_H_

#include "minimizer/interface.h"
#include "minimizer/line/allocate.h"

namespace mysimulator {

  template <LineMinimizerName LMN,typename T,typename FT,typename IDT,
            typename PT,typename GT,template <typename> class ST>
  void allocate(Minimizer<LBFGS,LMN,T,FT,IDT,PT,GT,ST>& M,
                const System<T,FT,IDT,PT,GT,ST>& S) {
    typedef
      typename Minimizer<LBFGS,LMN,T,FT,IDT,PT,GT,ST>::ParentType
      Type;
    allocate(static_cast<Type&>(M),S);
    if(M.MaxCorrelation==0)   M.SetMaxCorrelation();
    allocate(M.dX,M.MaxCorrelation);
    allocate(M.dG,M.MaxCorrelation);
    for(unsigned int i=0;i<M.MaxCorrelation;++i) {
      imprint(M.dX[i],M.Sys().X);
      imprint(M.dG[i],M.Sys().X);
    }
    allocate(M.alpha,M.MaxCorrelation);
    allocate(M.rho,M.MaxCorrelation);
    imprint(M.lastX,M.Sys().X);
    imprint(M.lastG,M.Sys().X);
  }

}

#endif

