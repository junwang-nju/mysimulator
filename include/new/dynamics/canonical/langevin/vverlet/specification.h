
#ifndef _Dynamics_Canonical_Langevin_VelocityVerlet_Specification_H_
#define _Dynamics_Canonical_Langevin_VelocityVerlet_Specification_H_

#include "dynamics/interface.h"
#include "dynamics/canonical/langevin/base/interface.h"
#include "dynamics/canonical/langevin/vverlet/data/interface.h"
#include "dynamics/algorithm/vverlet/data/interface.h"

namespace mysimulator {
  
  template <typename T,template<typename>class VT,typename OCT,typename RT>
  struct Dynamics<LangevinVVerlet,T,VT,OCT,RT>
      : public DynamicsCanonicalLangevinBase<T,VT,OCT,RT> {

    public:

      typedef Dynamics<LangevinVVerlet,T,VT,OCT,RT> Type;
      typedef DynamicsCanonicalLangevinBase<T,VT,OCT,RT>  ParentType;

      DynamicsCanonicalLangevinVVerletData<T,VT> CanonicalLangevinVVerletData;
      DynamicsVVerletData<T,VT> VVerletData;

      Dynamics()
        : ParentType(), CanonicalLangevinVVerletData(), VVerletData() {}
      ~Dynamics() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        release(CanonicalLangevinVVerletData); release(VVerletData);
      }

      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(CanonicalLangevinVVerletData)&&IsValid(VVerletData);
      }

      template <typename IDT,typename PT, typename GT,
                template<typename,template<typename>class> class SCT>
      bool ismatch(const System<T,IDT,PT,GT,VT,SCT>& S) const {
        return (S.EvoluteMode==16)||(S.EvoluteMode==18);
      }

    private:

      Dynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif
