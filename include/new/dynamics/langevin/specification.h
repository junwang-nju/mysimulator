
#ifndef _Dynamics_Langevin_Specification_H_
#define _Dynamics_Langevin_Specification_H_

#include "dynamics/interface.h"
#include "dynamics/base/interface.h"
#include "system/propagate/vverlet/langevin/parameter-name.h"
#include "system/property/mass-method-name.h"
#include "system/property/friction-method-name.h"
#include "unique/64bit/copy.h"
#include "array/1d/allocate.h"

#define _LinkElement(name,obj) \
  if(obj.size<S.Propagates.size)  allocate(obj,S.Propagates.size);\
  S.Propagates[i].Param[name].ptr[0]=reinterpret_cast<void*>(&(obj[i]));

#define _LinkArray(name,obj) \
  if(!IsSameSize(obj,S.Content().X())) imprint(obj,S.Content().X());\
  S.Propagates[i].Param[name].ptr[0]=reinterpret_cast<void*>(&obj);

namespace mysimulator {

  template <typename T, template<typename> class VT,typename OC>
  struct Dynamics<Langevin,T,VT,OC> : public DynamicsBase<T,OC> {

    public:

      typedef Dynamics<Langevin,T,VT,OC>    Type;
      typedef DynamicsBase<T,OC>   ParentType;

      Array1D<T> gMass;
      Array1D<T> gFric;
      Array1D<T> gNegHTIM;
      Array1D<T> gRandS;
      Array1D<T> gFac1;
      Array1D<T> gFac2;
      VT<T>   vRandV;
      VT<T>   vMass;
      VT<T>   vFric;
      VT<T>   vNegHTIM;
      VT<T>   vRandS;
      VT<T>   vFac1;
      VT<T>   vFac2;

      Dynamics() : ParentType(), gMass(), gFric(), gNegHTIM(), gRandS(),
                   gFac1(), gFac2(), vRandV(), vMass(), vFric(), vNegHTIM(),
                   vRandS(), vFac1(), vFac2() {}
      ~Dynamics() { clearData(); }

      void clearData() {
        release(vFac2); release(vFac1); release(vRandS);  release(vNegHTIM);
        release(vFric); release(vMass); release(vRandV);  release(gFac2);
        release(gFac1); release(gRandS); release(gNegHTIM); release(gFric);
        release(gMass); static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() { return static_cast<ParentType*>(this)->isvalid(); }
      template <typename IDT,typename PT,typename GT,
                template<typename,template<typename>class> class SCT>
      bool ismatch(const System<T,IDT,PT,GT,VT,SCT>& S) {
        return (S.EvoluteMode==16)||(S.EvoluteMode==18);
      }

      template <typename IDT,typename PT,typename GT,
                template<typename,template<typename>class> class SCT>
      void bind(System<T,IDT,PT,GT,VT,SCT>& S) {
        assert(ismatch(S));
        bindOutput(*this,S);
        MassMethodName MMN;
        FrictionMethodName  FMN;
        for(unsigned int i=0;i<S.Propagates.size;++i) {
          S.Propagates[i].Param[LgVVerletTimeStep].ptr[0]=&(this->TimeStep);
          _LinkArray(LgVVerletRandVectorData,vRandV)
          MMN=S.Propagates[i].Param[LgVVerletMassMode].u[0];
          if(MMN==GlobalMass) {
            _LinkElement(LgVVerletMassData,gMass)
            _LinkElement(LgVVerletNegHTIMData,gNegHTIM)
          } else if(MMN=ArrayMass) {
            _LinkArray(LgVVerletMassData,vMass)
            _LinkArray(LgVVerletNegHTIMData,vNegHTIM)
          } else Error("Unknown Mass Mode!");
          FMN=S.Propagates[i].Param[LgVVerletFrictionMode].u[0];
          if((MMN==GlobalMass)&&(FMN=GlobalFriction)) {
            _LinkElement(LgVVerletFrictionData,gFric)
            _LinkElement(LgVVerletRandSizeData,gRandS)
            _LinkElement(LgVVerletFac1Data,gFac1)
            _LinkElement(LgVVerletFac2Data,gFac2)
          } else {
            _LinkArray(LgVVerletFrictionData,vFric)
            _LinkArray(LgVVerletRandSizeData,vRandS)
            _LinkArray(LgVVerletFac1Data,vFac1)
            _LinkArray(LgVVerletFac2Data,vFac2)
          }
        }
        S.init();
      }

      template <typename IDT,typename PT,typename GT,
                template<typename,template<typename>class> class SCT>
      void unbind(System<T,IDT,PT,GT,VT,SCT>& S) { S.clear(); }

    private:

      Dynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#undef _LinkArray
#undef _LinkElement

#endif

