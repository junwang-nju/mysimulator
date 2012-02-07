
#ifndef _Dynamics_Canonical_Berendsen_VelocityVerlet_Specification_H_
#define _Dynamics_Canonical_Berendsen_VelocityVerlet_Specification_H_

#include "dynamics/interface.h"
#include "dynamics/canonical/berendsen/base/interface.h"
#include "dynamics/algorithm/vverlet/data/interface.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,typename OCT,typename RT>
  struct Dynamics<BerendsenVVerlet,T,VT,OCT,RT>
      : public DynamicsCanonicalBerendsenBase<T,VT,OCT> {

    public:

      typedef Dynamics<BerendsenVVerlet,T,VT,OCT,RT>  Type;
      typedef DynamicsCanonicalBerendsenBase<T,VT,OCT>  ParentType;

      DynamicsVVerletData<T,VT>   VVerletData;

      Dynamics() : ParentType(), VVerletData() {}
      ~Dynamics() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        release(VVerletData);
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(VVerletData);
      }
      template <typename IDT,typename PT,typename GT,
                template<typename,template<typename>class> class SCT>
      bool ismatch(const System<T,IDT,PT,GT,VT,SCT>& S) const {
        return (S.EvoluteMode==32)||(S.EvoluteMode==34);
      }

    private:

      Dynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

