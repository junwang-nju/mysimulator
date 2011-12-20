
#ifndef _System_Interaction_Allocate_H_
#define _System_Interaction_Allocate_H_

#include "system/interaction/interface.h"

#include "system/content/with-v/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void allocateData(SysInteraction<T,IDT,PT,GT,VT,SysContentWithV>& SI) {}

}

#include "system/content/data/e/allocate.h"
#include "system/content/with-e/interface.h"
#include "system/content/with-ev/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void allocateData(SysInteraction<T,IDT,PT,GT,VT,SysContentWithE>& SI) {
    allocate(SI.EGData);
    allocate(SI.EGData());
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void allocateData(SysInteraction<T,IDT,PT,GT,VT,SysContentWithEV>& SI) {
    allocate(SI.EGData);
    allocate(SI.EGData());
  }

}

#include "system/content/data/g/allocate.h"
#include "system/content/data/eg/allocate.h"
#include "system/content/with-g/interface.h"
#include "system/content/with-gv/interface.h"
#include "system/content/with-eg/interface.h"
#include "system/content/with-egv/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT, typename T1>
  void allocateData(SysInteraction<T,IDT,PT,GT,VT,SysContentWithG>& SI,
                    const VT<T1>& X) {
    allocate(SI.EGData);
    allocate(SI.EGData(),X);
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT, typename T1>
  void allocateData(SysInteraction<T,IDT,PT,GT,VT,SysContentWithGV>& SI,
                    const VT<T1>& X) {
    allocate(SI.EGData);
    allocate(SI.EGData(),X);
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT, typename T1>
  void allocateData(SysInteraction<T,IDT,PT,GT,VT,SysContentWithEG>& SI,
                    const VT<T1>& X) {
    allocate(SI.EGData);
    allocate(SI.EGData(),X);
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT, typename T1>
  void allocateData(SysInteraction<T,IDT,PT,GT,VT,SysContentWithEGV>& SI,
                    const VT<T1>& X) {
    allocate(SI.EGData);
    allocate(SI.EGData(),X);
  }

}

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT, typename T1,
            template<typename,template<typename>class> class SCT>
  void allocateData(SysInteraction<T,IDT,PT,GT,VT,SCT>& SI,
                    const Object<VT<T> >& X) {
    assert(IsValid(X));
    allocateData(SI,X());
  }

}
#endif

