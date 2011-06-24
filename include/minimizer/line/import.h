
#ifndef _Minimizer_Line_Import_H_
#define _Minimizer_Line_Import_H_

#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerName LNM,typename KT, template<typename> class VT,
            typename PT, typename T>
  void import(LineMinimizer<LNM,KT,VT,PT,T>& L,const void* FG,const void* Coor,
              const void* P, const void* umask) {
    Error("Operation Import for this Object Disabled!");
  }

}

#include "minimizer/line/tracking/import-specification.h"

#endif

