
#ifndef _System_Evaluate_Energy_H_
#define _System_Evaluate_Energy_H_

#include "system/interaction/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT1,template<typename> CT2>
  void _EvalEnergy(CT1<T>&,SystemInteraction<T,IDT,PT,GT,BT,CT2>&) {
    fprintf(stderr,"Energy Eval Not Available!\n");
  }

}

#include "system/content/data/nullify.h"
#include "system/content/with-e/interface.h"
#include "system/content/with-ev/interface.h"
#include "system/content/with-eg/interface.h"
#include "system/content/with-egv/interface.h"

#ifndef _EVAL
#define _EVAL(RCT) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT, \
            template<typename> class CT> \
  void _EvalEnergy(CT<T>& C,SystemInteraction<T,IDT,PT,GT,BT,RCT>& SI) { \
    assert(C.IsValid()&&SI.IsValid()); \
    NullifyEnergy(SI.EGData); \
    SI.CalcE(C.X,SI.EGData.Energy[0]); \
  }
#else
#error "Duplicate Definition for Macro _EVAL"
#endif

namespace mysimulator {

  _EVAL(SystemContentWithE)
  _EVAL(SystemContentWithEV)
  _EVAL(SystemContentWithEG)
  _EVAL(SystemContentWithEGV)

}

#ifdef _EVAL
#undef _EVAL
#endif

namespace mysimulator {
}

#endif

