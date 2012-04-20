
#ifndef _System_Evaluate_Both_H_
#define _System_Evaluate_Both_H_

#include "system/interaction/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT1,
            template<typename,template<typename>class> class SCT2>
  void _EvaluateBoth(SCT1<T,VT>&, SysInteraction<T,IDT,PT,GT,BT,VT,SCT2>&) {
    Error("No Energy or Gradient Calculation are available for this System!");
  }

}

#define _EvalBoth(SCType) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT,\
            template<typename> class VT,\
            template<typename,template<typename>class> class SCT>\
  void _EvaluateBoth(SCT<T,VT>& SC,\
                     SysInteraction<T,IDT,PT,GT,BT,VT,SCType>& SI){\
    assert(IsValid(SC)&&IsValid(SI));\
    nullifyBoth(SI.EGData());\
    SI.WorkB(SI.Func,SC.X(),SI.ID(),SI.Param(),SI.Buffer(),SI.Geom(),\
             SI.EGData().Energy(),SI.EGData().Gradient());\
  }

#include "interaction/calc.h"
#include "system/content/with-eg/interface.h"
#include "system/content/with-egv/interface.h"
#include "system/content/data/nullify.h"

namespace mysimulator {

  _EvalBoth(SysContentWithEG)
  _EvalBoth(SysContentWithEGV)

}

#undef _EvalBoth

#include "system/content/data/accumulate.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT1,
            template<typename,template<typename>class> class SCT2>
  void GenericEvaluateBoth(
      SCT1<T,VT>& SC,
      Array1DContent<SysInteraction<T,IDT,PT,GT,BT,VT,SCT2> >& SI) {
    assert(IsValid(SC)&&IsValid(SI));
    for(unsigned int i=0;i<SI.size;++i) _EvaluateBoth(SC,SI[i]);
    nullifyBoth(SC.EGData);
    for(unsigned int i=0;i<SI.size;++i)
      accumulateBoth(SC.EGData,SI[i].EGData());
  }

}

#endif

