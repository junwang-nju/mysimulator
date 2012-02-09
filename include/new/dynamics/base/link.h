
#ifndef _Dynamics_Base_Link_H_
#define _Dynamics_Base_Link_H_

#include "dynamics/base/interface.h"
#include "dynamics/base/data/link.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT, typename OC,
            template<typename,template<typename>class> class SCT>
  void link(DynamicsBase<T,VT,OC>& D, System<T,IDT,PT,GT,VT,SCT>& S) {
    link(D.BaseData,S);
    link(D.Output,S);
    assert(D.Output.BaseData._isparentvalid());
    D.Output.BaseData().setNowTime(D.BaseData.NowTime);
  }

}

#endif

