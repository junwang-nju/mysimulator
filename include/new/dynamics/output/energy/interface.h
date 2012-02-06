
#ifndef _Dynamics_Output_Energy_Interface_H_
#define _Dynamics_Output_Energy_Interface_H_

#include "dynamics/output/base/interface.h"
#include "system/evaluate/energy.h"
#include "system/interface.h"
#include "system/property/kinetic-energy.h"
#include "system/property/mass-method-name.h"
#include "object/refer.h"

namespace mysimulator {

  template <typename OST, typename T, typename IDT, typename PT,
            typename GT, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  struct DynOutputEnergy : public DynOutputBase<OST,T> {

    public:

      typedef DynOutputEnergy<OST,T,IDT,PT,GT,VT,SCT>   Type;
      typedef DynOutputBase<OST,T>    ParentType;

      Object<System<T,IDT,PT,GT,VT,SCT> >   S;
      VT<T> VelocitySQ;

      DynOutputEnergy() : ParentType(), S(), VelocitySQ() {}
      ~DynOutputEnergy() { clearData(); }

      void clearData() {
        release(VelocitySQ);  release(S);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&IsValid(S)&&
               IsValid(VelocitySQ);
      }

      virtual void write() {
        assert(isvalid());
        (this->OS)<<(this->NowTime());
        GenericEvaluateEnergy(S().Content(),S().Interactions);
        for(unsigned int i=0;i<S().Interactions.size;++i)
          (this->OS)<<"\t"<<S().Interactions[i].EGData().Energy();
        (this->OS)<<"\t"<<S().Content().EGData.Energy();
        T ke,ske;
        ske=0;
        for(unsigned int i=0;i<S().Propagates.size;++i) {
          ke=KineticEnergy(S().Propagates[i]);
          ske+=ke;
          (this->OS)<<"\t"<<ke;
        }
        (this->OS)<<"\t"<<ske;
      }

    private:

      DynOutputEnergy(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

