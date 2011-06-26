
#ifndef _Minimizer_Import_H_
#define _Minimizer_Import_H_

#include "minimizer/interface.h"

namespace mysimulator {

  template <MinimizerName MN, LineMinimizerName LMN, typename KT,
            template<typename> class VT, typename PT, typename T>
  void import(Minimizer<MN,LMN,KT,VT,PT,T>& M, const void* FG,
              const void* Coor, const void* P, const void* umask) {
    Error("Operation Import for this Object Disabled!");
  }

}

#include "minimizer/steep/import-specification.h"
#include "minimizer/conjg/import-specification.h"
#include "minimizer/lbfgs/import-specification.h"

#endif
