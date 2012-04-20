
#ifndef _System_Interaction_AllocateData_H_
#define _System_Interaction_AllocateData_H_

#include "system/interaction/interface.h"
#include "system/content/with-v/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT>
  void allocateData(SystemInteraction<T,IDT,PT,GT,BT,SystemContentWithV>&) {}

}

#ifndef _ETypeAlloc
#define _ETypeAlloc(CType) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT> \
  void allocateData(SystemInteraction<T,IDT,PT,GT,BT,CType>& I) { \
    allocate(I.EGData); \
  }
#else
#error "Duplicate Definition for _ETypeAlloc"
#endif

#include "system/content/data/e/allocate.h"
#include "system/content/with-e/interface.h"
#include "system/content/with-ev/interface.h"

namespace mysimulator {

  _ETypeAlloc(SystemContentWithE)
  _ETypeAlloc(SystemContentWithEV)

}

#ifdef _ETypeAlloc
#undef _ETypeAlloc
#endif

#ifndef _GTypeAlloc
#define _GTypeAlloc(CType) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT> \
  void allocateData(SystemInteraction<T,IDT,PT,GT,BT,CType>& I, const T** X) { \
    allocate(I.EGData,X); \
  }
#else
#error "Duplicate Definition for _GTypeAlloc"
#endif

#include "system/content/with-g/interface.h"
#include "system/content/with-gv/interface.h"
#include "system/content/data/g/allocate.h"

namespace mysimulator {

  _GTypeAlloc(SystemContentWithG)
  _GTypeAlloc(SystemContentWithGV)

}

#include "system/content/with-eg/interface.h"
#include "system/content/with-egv/interface.h"
#include "system/content/data/eg/allocate.h"

namespace mysimulator {

  _GTypeAlloc(SystemContentWithEG)
  _GTypeAlloc(SystemContentWithEGV)

}

#ifdef _GTypeAlloc
#undef _GTypeAlloc
#endif

#endif

