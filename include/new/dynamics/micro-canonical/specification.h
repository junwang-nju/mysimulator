
#ifndef _Dynamics_MicroCanonical_Specification_H_
#define _Dynamics_MicroCanonical_Specification_H_

#include "dynamics/interface.h"
#include "dynamics/base/interface.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "system/property/mass-method-name.h"
#include "unique/64bit/copy.h"
#include "array/1d/allocate.h"

#define PName(U)    PtrCEVVerlet##U
#define DName(U)    DatCEVVerlet##U

#define _LinkArray(U,obj) \
  if(!IsSameSize(obj,S.Content().X())) imprint(obj,S.Content().X());\
  S.Propagates[i].Param[DName(U)].ptr[0]=reinterpret_cast<void*>(&obj);

namespace mysimulator {

  template <typename T,template<typename> class VT,typename OC>
  struct Dynamics<MicroCanonical,T,VT,OC> : public DynamicsBase<T,OC> {

    public:

      typedef Dynamics<MicroCanonical,T,VT,OC>   Type;
      typedef DynamicsBase<T,OC>   ParentType;

      VT<T> Mass;
      VT<T> NegHTIM;

      Dynamics() : ParentType(), Mass(), NegHTIM() {}
      ~Dynamics() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        release(Mass); release(NegHTIM);
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
          S.Propagates[i].Param[PName(TimeStep)].ptr[0]=&(this->TimeStep);
          switch(S.Propagates[i].Param[ModCEVVerletMass].u[0]) {
            case GlobalMass:
              break;
            case ArrayMass:
              _LinkArray(Mass,Mass)
              _LinkArray(NegHTIM,NegHTIM)
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

#undef _LinkArray

#undef DName
#undef PName

#endif

