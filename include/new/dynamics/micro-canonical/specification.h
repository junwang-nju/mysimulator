
#ifndef _Dynamics_MicroCanonical_Specification_H_
#define _Dynamics_MicroCanonical_Specification_H_

#include "dynamics/interface.h"
#include "dynamics/base/interface.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "system/property/mass-method-name.h"

namespace mysimulator {

  template <typename T,template<typename> class VT>
  struct Dynamics<MicroCanonical,T,VT> : public DynamicsBase<T> {

    public:

      typedef Dynamics<MicroCanonical,T,VT>   Type;
      typedef DynamicsBase<T>   ParentType;

      Array1D<T> gMass;
      Array1D<T> gNegHTIM;
      VT<T> vMass;
      VT<T> vNegHTIM;

      Dynamics() : ParentType(),
                   gMass(0), gNegHTIM(0), vMass(), vNegHTIM() {}
      ~Dynamics() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        release(vMass); release(vNegHTIM);
        gMass=0;  gNegHTIM=0;
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid();
      }

      template <typename IDT,typename PT,typename GT,
                template<typename,template<typename>class> class SCT>
      void bind(System<T,IDT,PT,GT,VT,SCT>& S) {
        assert((S.EvoluteMode==8)||(S.EvoluteMode==10));
        for(unsigned int i=0;i<S.Propagates.size;++i) {
          S.Propagates[i].Param[CEVVerletTimeStep].value<T>()=this->TimeStep;
          switch(S.Propagates[i].Param[CEVVerletMassMode].u[0]) {
            case GlobalMass:
              assert(gMass.size>=S.Propagates.size);
              assert(gNegHTIM.size>=S.Propagates.size);
              S.Propagates[i].Param[CEVVerletMassData].ptr[0]=
                reinterpret_cast<void*>(&(gMass[i]));
              S.Propagates[i].Param[CEVVerletNegHTimeIMassData].ptr[0]=
                reinterpret_cast<void*>(&(gNegHTIM[i]));
              break;
            case ArrayMass:
              assert(IsValid(vMass));
              assert(IsValid(vNegHTIM));
              S.Propagates[i].Param[CEVVerletMassData].ptr[0]=
                reinterpret_cast<void*>(&vMass);
              S.Propagates[i].Param[CEVVerletNegHTimeIMassData].ptr[0]=
                reinterpret_cast<void*>(&vNegHTIM);
              break;
            default:
              Error("Unknown Mass Mode!");
          }
        }
        S.init();
      }

      template <typename IDT,typename PT,typename GT,
                template<typename,template<typename>class> class SCT>
      void evolute(System<T,IDT,PT,GT,VT,SCT>& S) {
        assert((S.EvoluteMode==8)||(S.EvoluteMode==10));
        for(unsigned int i=0;i<this->NumSteps;++i)  S.evolute();
      }

    private:

      Dynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

