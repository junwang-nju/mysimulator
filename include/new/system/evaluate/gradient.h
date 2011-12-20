
#ifndef _System_Evaluate_Gradient_H_
#define _System_Evaluate_Gradient_H_

#include "system/interaction/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT1,
            template<typename,template<typename>class> class SCT2>
  void _EvaluateGradient(SCT1<T,VT>&, SysInteraction<T,IDT,PT,GT,VT,SCT2>&) {
    Error("No Gradient Calculation are available for this System!");
  }

}

#define _EvalGradient(ISCT) \
  template <typename T,typename IDT,typename PT,typename GT,\
            template<typename> class VT,\
            template<typename,template<typename>class> class SCT>\
  void _EvaluateGradient(SCT<T,VT>& S,SysInteraction<T,IDT,PT,GT,VT,ISCT>& SI){\
    assert(IsValid(S)&&IsValid(SI));\
    nullifyGradient(SI.EGData());\
    Calc(SI.Func(),S.X(),SI.ID(),SI.Param(),SI.Geom(),SI.EGData().Gradient());\
  }

#include "interaction/calc.h"
#include "system/content/with-g/interface.h"
#include "system/content/with-gv/interface.h"
#include "system/content/with-eg/interface.h"
#include "system/content/with-egv/interface.h"
#include "system/content/data/nullify.h"

namespace mysimulator {

  _EvalGradient(SysContentWithG)
  _EvalGradient(SysContentWithGV)
  _EvalGradient(SysContentWithEG)
  _EvalGradient(SysContentWithEGV)

}

#undef _EvalGradient

#include "system/content/data/accumulate.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT1,
            template<typename,template<typename>class> class SCT2>
  void GenericEvaluateGradient(
      SCT1<T,VT>& SC,
      Array1DContent<SysInteraction<T,IDT,PT,GT,VT,SCT2> >& SI) {
    assert(IsValid(SC)&&IsValid(SI));
    for(unsigned int i=0;i<SI.size;++i) _EvaluateGradient(SC,SI[i]);
    nullifyGradient(SC.EGData);
    for(unsigned int i=0;i<SI.size;++i)
      accumulateGradient(SC.EGData,SI[i].EGData());
  }

}

#endif

