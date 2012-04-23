
#ifndef _System_Evaluate_Regular_H_
#define _System_Evaluate_Regular_H_

#include "system/interaction/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT,template<typename> class CT2>
  void _Evaluate(const CT<T>&,SystemInteraction<T,IDT,PT,GT,BT,CT2>&) {
    fprintf(stderr,"Regular Eval Not Available!\n");
  }

}

#include "system/evaluate/energy.h"

#define _EVAL_E(RCT) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT,\
            template<typename> class CT> \
  void _Evaluate(const CT<T>& C,SystemInteraction<T,IDT,PT,GT,BT,RCT>& SI) { \
    _EvalEnergy(C,SI); \
  }

namespace mysimulator {

  _EVAL_E(SystemContentWithE)
  _EVAL_E(SystemContentWithEV)

}

#undef _EVAL_E

#include "system/evaluate/gradient.h"

#define _EVAL_G(RCT) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT,\
            template<typename> class CT> \
  void _Evaluate(const CT<T>& C,SystemInteraction<T,IDT,PT,GT,BT,RCT>& SI) { \
    _EvalGradient(C,SI); \
  }

namespace mysimulator {

  _EVAL_G(SystemContentWithG)
  _EVAL_G(SystemContentWithGV)

}

#undef _EVAL_G

#include "system/evaluate/both.h"

#define _EVAL_EG(RCT) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT,\
            template<typename> class CT> \
  void _Evaluate(const CT<T>& C,SystemInteraction<T,IDT,PT,GT,BT,RCT>& SI) { \
    _EvalBoth(C,SI); \
  }

namespace mysimulator {

  _EVAL_EG(SystemContentWithEG)
  _EVAL_EG(SystemContentWithEGV)

}

#undef _EVAL_EG

#include "system/content/data/nullify.h"
#include "system/content/data/append.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT,template<typename> class CT2>
  void Evaluate(CT<T>& C,Array1D<SystemInteraction<T,IDT,PT,GT,BT,CT2> >& SI) {
    assert(C.IsValid()&&SI.IsValid());
    for(unsigned int i=0;i<SI.Size();++i) _Evaluate(C,SI[i]);
    Nullify(C.EGData);
    for(unsigned int i=0;i<SI.Size();++i) Append(C.EGData,SI[i].EGData);
  }

}

#endif

