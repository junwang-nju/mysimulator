
#ifndef _Dynamics_Canonical_Langevin_Base_Link_H_
#define _Dynamics_Canonical_Langevin_Base_Link_H_

#include "dynamics/canonical/langevin/base/interface.h"
#include "dynamics/canonical/base/link.h"
#include "dynamics/canonical/langevin/base/data/link.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,typename OCT,typename RT,
            typename IDT,typename PT,typename GT,
            template<typename,template<typename>class> class SCT>
  void link(DynamicsCanonicalLangevinBase<T,VT,OCT,RT>& D,
            System<T,IDT,PT,GT,VT,SCT> & S) {
    assert(IsValid(S));
    typedef typename DynamicsCanonicalLangevinBase<T,VT,OCT,RT>::ParentType
            Type;
    link(static_cast<Type&>(D),S);
    link(D.CanonicalLangevinBaseData,S);
  }

}

#endif

