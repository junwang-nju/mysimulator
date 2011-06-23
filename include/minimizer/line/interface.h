
#ifndef _Minimizer_Line_Interface_H_
#define _Minimizer_Line_Interface_H_

#include "minimizer/line/name.h"
#include "io/error.h"

namespace mysimulator {

  template <LineMinimizerName LMName, typename IKernelType,
            template<typename> class SpaceVType,typename IParamType,typename T>
  struct LineMinimizer {

    typedef LineMinimizer<LMName,IKernelType,SpaceVType,IParamType,T>   Type;

    LineMinimizer() { Error("Not Available for this LineMinimizer Method!"); }
    LineMinimizer(const Type&) { Error("Copier of LineMinimizer Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for LineMinimizer Disabled!");
      return *this;
    }
    ~LineMinimizer() { clearData(); }

    void clearData() {}

    virtual int Go(const unsigned int) { return 0; }

  };

  template <LineMinimizerName LN,typename KT,template<typename> class VT,
            typename PT,typename T>
  bool IsValid(const LineMinimizer<LN,KT,VT,PT,T>& L) { return false; }

  template <LineMinimizerName LN,typename KT,template<typename> class VT,
            typename PT,typename T>
  void release(LineMinimizer<LN,KT,VT,PT,T>& L) { L.clearData(); }

}

#include "minimizer/line/tracking/specification.h"

#endif

