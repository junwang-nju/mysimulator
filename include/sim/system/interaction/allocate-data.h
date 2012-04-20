
#ifndef _System_Interaction_AllocateData_H_
#define _System_Interaction_AllocateData_H_

#include "system/interaction/interface.h"
#include "system/content/with-v/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT>
  void allocateData(SystemInteraction<T,IDT,PT,GT,BT,SystemContentWithV>&) {}

}

#include "system/content/data/e/allocate.h"
#include "system/content/with-e/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT>
  void allocateData(SystemInteraction<T,IDT,PT,GT,BT,SystemContentWithE>& I) {
    allocate(I.EGData);
  }

}

#include "system/content/with-ev/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT>
  void allocateData(SystemInteraction<T,IDT,PT,GT,BT,SystemContentWithEV>& I) {
    allocate(I.EGData);
  }

}

#endif

