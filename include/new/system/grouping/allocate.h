
#ifndef _System_Grouping_Allocate_H_
#define _System_Grouping_Allocate_H_

#include "system/grouping/interface.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void allocate(SysGrouping<T,IDT,PT,GT,VT,SCT>& SG,
                const SystemGroupingMethodName& GM, const unsigned int& nid) {
    release(SG);
    allocate(SG.MerIDRange,nid);
    if(GM==SystemFixPosition) {}
    else if(GM==SystemMinimizeLineRegular)
      allocate(SG.Param,1u);
    else Error("Unknown System Grouping Method Name!");
  }

}

#endif

