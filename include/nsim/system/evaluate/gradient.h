
#ifndef _System_Evaluate_Gradient_H_
#define _System_Evaluate_Gradient_H_

#include "system/interaction/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT, template<typename> class CT2>
  void _EvalGradient(const CT<T>&,SystemInteraction<T,IDT,PT,GT,BT,CT2>&) {
    fprintf(stderr,"Gradient Eval Not Available!\n");
  }

}

#include "system/content/data/nullify.h"
#include "system/content/with-g/interface.h"
#include "system/content/with-gv/interface.h"
#include "system/content/with-eg/interface.h"
#include "system/content/with-egv/interface.h"

#ifndef _EVAL
#define _EVAL(RCT) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT,\
            template<typename> class CT> \
  void _EvalGradient(const CT<T>& C,SystemInteraction<T,IDT,PT,GT,BT,RCT>& SI){\
    assert(C.IsValid()&&SI.IsValid()); \
    NullifyGradient(SI.EGData); \
    SI.Calc(C.X,SI.EGData.Gradient); \
  }
#else
#error "Duplicate Definition for Macro _EVAL"
#endif

namespace mysimulator {

  _EVAL(SystemContentWithG)
  _EVAL(SystemContentWithGV)
  _EVAL(SystemContentWithEG)
  _EVAL(SystemContentWithEGV)

}

#ifdef _EVAL
#undef _EVAL
#endif

#include "system/content/data/append.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT,template<typename> class CT2>
  void EvaluateGradient(CT<T>& C,
                        Array1D<SystemInteraction<T,IDT,PT,GT,BT,CT2> >& SI) {
    assert(C.IsValid()&&SI.IsValid());
    for(unsigned int i=0;i<SI.Size();++i) _EvalGradient(C,SI[i]);
    NullifyGradient(C.EGData);
    for(unsigned int i=0;i<SI.Size();++i) AppendGradient(C.EGData,SI[i].EGData);
  }
}

#endif

