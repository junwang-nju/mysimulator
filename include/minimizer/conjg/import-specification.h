
#ifndef _Minimizer_ConjugateGradient_Import_Specification_H_
#define _Minimizer_ConjugateGradient_Import_Specification_H_

#include "minimizer/conjg/specification.h"

namespace mysimulator {

  template <LineMinimizerName LMN, typename KT, template<typename> class VT,
            typename PT, typename T>
  void import(Minimizer<ConjugateGradient,LMN,KT,VT,PT,T>& M, const void* FG,
              const void* Coor, const void* P, const void* umask) {
    typedef LineMinimizer<LMN,KT,VT,PT,T>    Type;
    import(static_cast<Type&>(M),FG,Coor,P,umask);
    if(Coor!=NULL) {
      const VT<T>* pCoor=static_cast<const VT<T>*>(Coor);
      assert(IsValid(pCoor));
      imprint(M.OldMinG,*pCoor);
    }
  }

}

#endif

