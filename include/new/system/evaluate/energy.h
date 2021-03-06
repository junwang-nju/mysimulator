
#ifndef _System_Evaluate_Energy_H_
#define _System_Evaluate_Energy_H_

#include "system/interaction/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT1,
            template<typename,template<typename>class> class SCT2>
  void _EvaluateEnergy(SCT1<T,VT>&, SysInteraction<T,IDT,PT,GT,BT,VT,SCT2>&) {
    Error("No Energy Calculation are available for this System!");
  }

}

#define _EvalEnergy(ISCT) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT,\
            template<typename> class VT,\
            template<typename,template<typename>class> class SCT>\
  void _EvaluateEnergy(SCT<T,VT>& SC,\
                       SysInteraction<T,IDT,PT,GT,BT,VT,ISCT>& SI){\
    assert(IsValid(SC)&&IsValid(SI));\
    nullifyEnergy(SI.EGData());\
    SI.WorkE(SI.Func,SC.X(),SI.ID(),SI.Param(),SI.Buffer(),SI.Geom(),\
             SI.EGData().Energy());\
  }

#include "interaction/calc.h"
#include "system/content/with-e/interface.h"
#include "system/content/with-ev/interface.h"
#include "system/content/with-eg/interface.h"
#include "system/content/with-egv/interface.h"
#include "system/content/data/nullify.h"

namespace mysimulator {

  _EvalEnergy(SysContentWithE)
  _EvalEnergy(SysContentWithEV)
  _EvalEnergy(SysContentWithEG)
  _EvalEnergy(SysContentWithEGV)

}

#undef _EvalEnergy

#include "system/content/data/accumulate.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT1,
            template<typename,template<typename>class> class SCT2>
  void GenericEvaluateEnergy(
      SCT1<T,VT>& SC,
      Array1DContent<SysInteraction<T,IDT,PT,GT,BT,VT,SCT2> >& SI) {
    assert(IsValid(SC)&&IsValid(SI));
    for(unsigned int i=0;i<SI.size;++i) _EvaluateEnergy(SC,SI[i]);
    nullifyEnergy(SC.EGData);
    for(unsigned int i=0;i<SI.size;++i)
      accumulateEnergy(SC.EGData,SI[i].EGData());
  }

}

#endif

