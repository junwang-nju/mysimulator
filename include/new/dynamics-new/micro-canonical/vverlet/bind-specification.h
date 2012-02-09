
#ifndef _Dynamics_MicroCanonical_VelocityVerlet_Bind_Specification_H_
#define _Dynamics_MicroCanonical_VelocityVerlet_Bind_Specification_H_

#include "dynamics/micro-canonical/vverlet/specification.h"
#include "dynamics/base/link.h"
#include "dynamics/algorithm/vverlet/data/link.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            typename OCT,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void bind(Dynamics<MicroCanonicalVVerlet,T,VT,OCT>& D,
            System<T,IDT,PT,GT,VT,SCT>& S) {
    assert(IsValid(D)&&IsValid(S));
    assert(!D.BindFlag);
    typedef typename Dynamics<MicroCanonicalVVerlet,T,VT,OCT>::ParentType Type;
    link(static_cast<Type&>(D),S);
    link(D.VVerletData,S);
    D.BindFlag=true;
    S.init();
  }

  template <typename T,typename IDT,typename PT,typename GT,
            typename OCT,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void unbind(Dynamics<MicroCanonicalVVerlet,T,VT,OCT>& D,
              System<T,IDT,PT,GT,VT,SCT>& S) {
    assert(IsValid(D)&&IsValid(S));
    assert(D.BindFlag);
    S.clear();
    B.BindFlag=false;
  }

}

#endif

