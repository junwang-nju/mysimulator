
#ifndef _Minimizer_LBFGS_Import_Specification_H_
#define _Minimizer_LBFGS_Import_Specification_H_

#include "minimizer/lbfgs/specification.h"

namespace mysimulator {

  template <LineMinimizerName LMN,typename KT,template<typename> class VT,
            typename PT,typename T>
  void import(Minimizer<LBFGS,LMN,KT,VT,PT,T>& M, const void* FG,
              const void* Coor, const void* P, const void* umask) {
    typedef LineMinimizer<LMN,KT,VT,PT,T> Type;
    import(static_cast<Type&>(M),FG,Coor,P,umask);
    if(Coor!=NULL) {
      const VT<T>* pCoor=static_cast<const VT<T>*>(Coor);
      assert(IsValid(pCoor));
      if(M.MaxCorrelation==0)   M.SetMaxCorrelation();
      allocate(M.dX,M.MaxCorrelation);
      allocate(M.dG,M.MaxCorrelation);
      for(unsigned int i=0;i<M.MaxCorrelation;++i) {
        imprint(M.dX[i],*pCoor);
        imprint(M.dG[i],*pCoor);
      }
      allocate(M.alpha,M.MaxCorrelation);
      allocate(M.rho,M.MaxCorrelation);
      imprint(M.lastX,*pCoor);
      imprint(M.lastG,*pCoor);
    }
  }

}

#endif

