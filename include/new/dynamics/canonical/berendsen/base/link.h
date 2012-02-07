
#ifndef _Dynamics_Canonical_Berendsen_Base_Link_H_
#define _Dynamics_Canonical_Berendsen_Base_Link_H_

#include "dynamics/canonical/berendsen/base/interface.h"
#include "system/propagate/interface.h"
#include "dynamics/canonical/base/link.h"
#include "dynamics/canonical/berendsen/base/data/link.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,typename OCT,
            typename IDT,typename PT,typename GT,
            template<typename,template<typename>class> class SCT>
  void link(DynamicsCanonicalBerendsenBase<T,VT,OCT>& D,
            System<T,IDT,PT,GT,VT,SCT>& S) {
    assert(IsValid(S));
    typedef typename DynamicsCanonicalBerendsenBase<T,VT,OCT>::ParentType  Type;
    link(static_cast<Type&>(D),S);
    link(D.CanonicalBerendsenBaseData,S);
  }

}

#endif

