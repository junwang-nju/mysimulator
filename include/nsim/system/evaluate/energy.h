
#ifndef _System_Evaluate_Energy_H_
#define _System_Evaluate_Energy_H_

#include "system/interaction/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT1,template<typename> class CT2>
  void _EvalEnergy(const CT1<T>&,SystemInteraction<T,IDT,PT,GT,BT,CT2>&) {
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
  void _EvalEnergy(const CT<T>& C,SystemInteraction<T,IDT,PT,GT,BT,RCT>& SI) { \
    assert(C.IsValid()&&SI.IsValid()); \
    NullifyEnergy(SI.EGData); \
    SI.Calc(C.X,SI.EGData.Energy[0]); \
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

#include "system/content/data/append.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template <typename> class CT, template <typename> class CT2>
  void EvaluateEnergy(CT<T>& C,
                      Array1D<SystemInteraction<T,IDT,PT,GT,BT,CT2> >& SI) {
    assert(C.IsValid()&&SI.IsValid());
    for(unsigned int i=0;i<SI.Size();++i) _EvalEnergy(C,SI[i]);
    NullifyEnergy(C.EGData);
    for(unsigned int i=0;i<SI.Size();++i) AppendEnergy(C.EGData,SI[i].EGData);
  }

}

#endif

