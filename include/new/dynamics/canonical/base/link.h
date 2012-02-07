
#ifndef _Dynamics_Canonical_Base_Link_H_
#define _Dynamics_Canonical_Base_Link_H_

#include "dynamics/canonical/base/interface.h"
#include "dynamics/base/link.h"
#include "dynamics/canonical/base/data/link.h"

namespace mysimulator {

  template <typename T, template<typename> class VT, typename OCT,
            typename IDT,typename PT,typename GT,
            template<typename,template<typename>class> class SCT>
  void link(DynamicsCanonicalBase<T,VT,OCT>& D,System<T,IDT,PT,GT,VT,SCT>& S) {
    assert(IsValid(S));
    typedef typename DynamicsCanonicalBase<T,VT,OCT>::ParentType Type;
    link(static_cast<Type&>(D),S);
    link(D.CanonicalData,S);
  }

}

#endif

