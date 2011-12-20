
#ifndef _System_Evaluate_Regular_H_
#define _System_Evaluate_Regular_H_

#include "system/interaction/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT1,
            template<typename,template<typename>class> class SCT2>
  void _Evaluate(SCT1<T,VT>&, SysInteraction<T,IDT,PT,GT,VT,SCT2>&) {
    Error("No Energy and Gradient Calculation are available for this System!");
  }

}

#include "system/evaluate/energy.h"

#define _EvalEOnly(SCType) \
  template <typename T,typename IDT,typename PT,typename GT,\
            template<typename> class VT,\
            template<typename,template<typename>class> class SCT>\
  void _Evaluate(SCT<T,VT>& SC,SysInteraction<T,IDT,PT,GT,VT,SCType>& SI) {\
    _EvaluateEnergy(SC,SI);\
  }

namespace mysimulator {

  _EvalEOnly(SysContentWithE)
  _EvalEOnly(SysContentWithEV)

}

#undef _EvalEOnly

#include "system/evaluate/gradient.h"

#define _EvalGOnly(SCType) \
  template <typename T,typename IDT,typename PT,typename GT,\
            template<typename> class VT,\
            template<typename,template<typename>class> class SCT>\
  void _Evaluate(SCT<T,VT>& SC,SysInteraction<T,IDT,PT,GT,VT,SCType>& SI) {\
    _EvaluateGradient(SC,SI);\
  }

namespace mysimulator {

  _EvalGOnly(SysContentWithG)
  _EvalGOnly(SysContentWithGV)

}

#undef _EvalGOnly

#include "system/evaluate/both.h"

#define _EvalEG(SCType) \
  template <typename T,typename IDT,typename PT,typename GT,\
            template<typename> class VT,\
            template<typename,template<typename>class> class SCT>\
  void _Evaluate(SCT<T,VT>& SC,SysInteraction<T,IDT,PT,GT,VT,SCType>& SI) {\
    _EvaluateBoth(SC,SI);\
  }

namespace mysimulator {

  _EvalEG(SysContentWithEG)
  _EvalEG(SysContentWithEGV)

}

#undef EvalEG

#include "system/content/data/nullify.h"
#include "system/content/data/accumulate.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT1,
            template<typename,template<typename>class> class SCT2>
  void GenericEvaluate(
      SCT1<T,VT>& SC,
      Array1DContent<SysInteraction<T,IDT,PT,GT,VT,SCT2> >& SI) {
    assert(IsValid(SC)&&IsValid(SI));
    for(unsigned int i=0;i<SI.size;++i) _Evaluate(SC,SI[i]);
    nullify(SC.EGData);
    for(unsigned int i=0;i<SI.size;++i)
      accumulate(SC.EGData,SI[i].EGData());
  }

}

#endif

