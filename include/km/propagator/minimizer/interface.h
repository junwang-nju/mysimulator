
#ifndef _Propagator_Minimizer_Interface_H_
#define _Propagator_Minimizer_Interface_H_

#include "propagator/minimizer-line/tracking/interface.h"

namespace mysimulator {

  template <typename T,typename GT,
            template<typename,typename> class LineMinimizerType=
                                              PropagatorTrackingLineMinimizer>
  class PropagatorMinimizer : public LineMinimizerType<T,GT> {

    public:

      typedef PropagatorMinimizer<T,GT,LineMinimizerType>   Type;
      typedef LineMinimizerType<T,GT>   ParentType;

      PropagatorMinimizer() : ParentType() {}
      ~PropagatorMinimizer() { Clear(*this); }

    private:

      PropagatorMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT,template<typename,typename>class LM>
  void Clear(PropagatorMinimizer<T,GT,LM>& M) {
    typedef typename PropagatorMinimizer<T,GT,LM>::ParentType PType;
    Clear(static_cast<PType&>(M));
  }

}

#endif

