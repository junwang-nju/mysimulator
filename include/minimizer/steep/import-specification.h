
#ifndef _Minimizer_SteepestDescent_Import_Specification_H_
#define _Minimizer_SteepestDescent_Import_Specification_H_

#include "minimizer/steep/specification.h"
#include "minimizer/line/import.h"

namespace mysimulator {

  template <LineMinimizerName LMN, typename KT, template<typename> class VT,
            typename PT, typename T>
  void import(Minimizer<SteepestDescent,LMN,KT,VT,PT,T>& M, const void* FG,
              const void* Coor, const void* P, const void* umask) {
    typedef LineMinimizer<LMN,KT,VT,PT,T>   Type;
    import(static_cast<Type&>(M),FG,Coor,P,umask);
  }

}

#endif

