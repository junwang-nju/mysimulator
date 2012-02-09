
#ifndef _Dynamics_Langevin_Specification_H_
#define _Dynamics_Langevin_Specification_H_

#include "dynamics/interface.h"
#include "dynamics/base/interface.h"
#include "system/propagate/vverlet/langevin/parameter-name.h"
#include "system/property/mass-method-name.h"
#include "system/property/friction-method-name.h"
#include "unique/64bit/copy.h"
#include "array/1d/allocate.h"

#define PName(U)    PtrLgVVerlet##U
#define DName(U)    DatLgVVerlet##U

#define _LinkArray(U,obj) \
  if(!IsSameSize(obj,S.Content().X())) imprint(obj,S.Content().X());\
  S.Propagates[i].Param[DName(U)].ptr[0]=reinterpret_cast<void*>(&(obj));

namespace mysimulator {

  template <typename T, template<typename> class VT,typename OC>
  struct Dynamics<Langevin,T,VT,OC> : public DynamicsBase<T,OC> {

    public:

      typedef Dynamics<Langevin,T,VT,OC>    Type;
      typedef DynamicsBase<T,OC>   ParentType;

      T Temperature;
      VT<T>   RandV;
      VT<T>   Mass;
      VT<T>   Fric;
      VT<T>   NegHTIM;
      VT<T>   RandS;
      VT<T>   Fac1;
      VT<T>   Fac2;

      Dynamics() : ParentType(),  RandV(), Mass(), Fric(), NegHTIM(),
                   RandS(), Fac1(), Fac2() {}
      ~Dynamics() { clearData(); }

      void clearData() {
        release(Fac2); release(Fac1); release(RandS);  release(NegHTIM);
        release(Fric); release(Mass); release(RandV);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid();
      }
      template <typename IDT,typename PT,typename GT,
                template<typename,template<typename>class> class SCT>
      bool ismatch(const System<T,IDT,PT,GT,VT,SCT>& S) const {
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
          S.Propagates[i].Param[PName(TimeStep)].ptr[0]=&(this->TimeStep);
          S.Propagates[i].Param[PName(Temperature)].ptr[0]=&Temperature;
          _LinkArray(RandVector,RandV)
          MMN=static_cast<MassMethodName>(
                  S.Propagates[i].Param[ModLgVVerletMass].u[0]);
          assert(MMN!=UnknownMassFormat);
          if(MMN==ArrayMass) {
            _LinkArray(Mass,Mass)
            _LinkArray(NegHTIM,NegHTIM)
          }
          FMN=static_cast<FrictionMethodName>(
                  S.Propagates[i].Param[ModLgVVerletFriction].u[0]);
          assert(FMN!=UnknownFrictionFormat);
          if(FMN==ArrayFriction) { _LinkArray(Friction,Fric) }
          if((MMN!=GlobalMass)||(FMN!=GlobalFriction)) {
            _LinkArray(RandSize,RandS)
            _LinkArray(Fac1,Fac1)
            _LinkArray(Fac2,Fac2)
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

#undef DName
#undef PName

#endif

