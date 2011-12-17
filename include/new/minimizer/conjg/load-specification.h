
#ifndef _Minimizer_Conjg_Load_Specification_H_
#define _Minimizer_Conjg_Load_Specification_H_

#include "minimizer/conjg/specification.h"
#include "minimizer/line/load.h"

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void _create_minimizer(
      Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,VT,SCT,LCM>& M) {
    imprint(M.OldMinG,M.MemSys().Content().X);
    if(M.MaxBeta<RelativeDelta<T>())  M.SetMaxBeta();
  }

}

#define _Load_Min \
  assert(IsValid(S)); \
  typedef \
  typename Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,VT,SCT,LCM>::ParentType \
  Type;\
  load(static_cast<Type&>(M),S);\
  _create_minimizer(M);

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,VT,SCT,LCM>& M,
            System<T,IDT,PT,GT,VT,SCT>& S) { _Load_Min }

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,VT,SCT,LCM>& M,
            Object<System<T,IDT,PT,GT,VT,SCT> >& S) { _Load_Min }

}

#undef _Load_Min

#endif

