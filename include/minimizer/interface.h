
#ifndef _Minimizer_Interface_H_
#define _Minimizer_Interface_H_

#include "minimizer/name.h"
#include "minimizer/line/name.h"
#include "io/error.h"

namespace mysimulator {

  template <MinimizerName MinName, LineMinimizerName LMinName,
            typename IKernelType, template<typename> class SpaceVType,
            typename IParamType, typename T>
  struct Minimizer {

    typedef Minimizer<MinName,LMinName,IKernelType,SpaceVType,IParamType,T>
            Type;

    Minimizer() { Error("Not Valid for this Minimizer Method"); }
    Minimizer(const Type&) { Error("Copier of Minimizer Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for Minimizer Disabled!");
      return *this;
    }
    ~Minimizer() { clearData(); }

    void clearData() {}

    virtual int Go(const unsigned int) { return 0; }

  };

  template <MinimizerName MN, LineMinimizerName LMN, typename KT,
            template<typename> class VT, typename PT, typename T>
  bool IsValid(const Minimizer<MN,LMN,KT,VT,PT,T>&) { return false; }

  template <MinimizerName MN, LineMinimizerName LMN, typename KT,
            template<typename> class VT, typename PT, typename T>
  void release(Minimizer<MN,LMN,KT,VT,PT,T>& M) { M.clearData(); }

}

#include "minimizer/steep/specification.h"
#include "minimizer/conjg/specification.h"
#include "minimizer/lbfgs/specification.h"

#endif

