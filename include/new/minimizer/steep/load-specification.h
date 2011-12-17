
#ifndef _Minimizer_Steep_Load_Specification_H_
#define _Minimizer_Steep_Load_Specification_H_

#include "minimizer/steep/specification.h"
#include "minimizer/line/load.h"

#define _Load_Min \
  assert(IsValid(S));\
  typedef \
  typename Minimizer<SteepestDescent,LMN,T,IDT,PT,GT,VT,SCT,LCM>::ParentType \
  Type;\
  load(static_cast<Type&>(M),S);

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(Minimizer<SteepestDescent,LMN,T,IDT,PT,GT,VT,SCT,LCM>& M,
            System<T,IDT,PT,GT,VT,SCT>& S) { _Load_Min }

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(Minimizer<SteepestDescent,LMN,T,IDT,PT,GT,VT,SCT,LCM>& M,
            Object<System<T,IDT,PT,GT,VT,SCT> >& S) { _Load_Min }

}

#undef _Load_Min

#endif

