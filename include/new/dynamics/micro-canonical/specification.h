
#ifndef _Dynamics_MicroCanonical_Specification_H_
#define _Dynamics_MicroCanonical_Specification_H_

#include "dynamics/interface.h"
#include "dynamics/base/interface.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "system/property/mass-method-name.h"
#include "unique/64bit/copy.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,typename OC>
  struct Dynamics<MicroCanonical,T,VT,OC> : public DynamicsBase<T,OC> {

    public:

      typedef Dynamics<MicroCanonical,T,VT,OC>   Type;
      typedef DynamicsBase<T,OC>   ParentType;

      Array1D<T> gMass;
      Array1D<T> gNegHTIM;
      VT<T> vMass;
      VT<T> vNegHTIM;

      Dynamics() : ParentType(),
                   gMass(), gNegHTIM(), vMass(), vNegHTIM() {}
      ~Dynamics() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        release(vMass); release(vNegHTIM);
        release(gMass); release(gNegHTIM);
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid();
      }

      template <typename IDT,typename PT,typename GT,
                template<typename,template<typename>class> class SCT>
      void bind(System<T,IDT,PT,GT,VT,SCT>& S) {
        assert(ismatch(S));
        bindOutput(*this,S);
        for(unsigned int i=0;i<S.Propagates.size;++i) {
          S.Propagates[i].Param[CEVVerletTimeStep].ptr[0]=
            &(this->TimeStep);
          switch(S.Propagates[i].Param[CEVVerletMassMode].u[0]) {
            case GlobalMass:
              if(gMass.size<S.Propagates.size)
                allocate(gMass,S.Propagates.size);
              if(gNegHTIM.size<S.Propagates.size)
                allocate(gNegHTIM,S.Propagates.size);
              S.Propagates[i].Param[CEVVerletMassData].ptr[0]=
                reinterpret_cast<void*>(&(gMass[i]));
              S.Propagates[i].Param[CEVVerletNegHTimeIMassData].ptr[0]=
                reinterpret_cast<void*>(&(gNegHTIM[i]));
              break;
            case ArrayMass: // assume various propagates share same mass
              if(!IsSameSize(vMass,S.Content().X()))
                imprint(vMass,S.Content().X());
              if(!IsSameSize(vNegHTIM,S.Content().X()))
                imprint(vNegHTIM,S.Content().X());
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
      void unbind(System<T,IDT,PT,GT,VT,SCT>& S) { S.clear(); }

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

