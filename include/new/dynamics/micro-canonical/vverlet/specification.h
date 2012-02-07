
#ifndef _Dynamics_MicroCanonical_VelocityVerlet_Specification_H_
#define _Dynamics_MicroCanonical_VelocityVerlet_Specification_H_

#include "dynamics/interface.h"
#include "dynamics/algorithm/vverlet/data/interface.h"
#include "dynamics/base/interface.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,typename OChannel,
            typename RNGType>
  struct Dynamics<MicroCanonicalVVerlet,T,VT,OChannel,RNGType>
      : public DynamicsBase<T,VT,OChannel> {

    public:

      typedef Dynamics<MicroCanonicalVVerlet,T,VT,OChannel,RNGType> Type;
      typedef DynamicsBase<T,VT,OChannel>   ParentType;

      DynamicsVVerletData<T,VT> VVerletData;

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
        return (S.EvoluteMode==8)||(S.EvoluteMode==10);
      }

    private:

      Dynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

