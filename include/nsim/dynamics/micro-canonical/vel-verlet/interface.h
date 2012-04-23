
#ifndef _Dynamics_MicroCanonical_VelVerlet_Interface_H_
#define _Dynamics_MicroCanonical_VelVerlet_Interface_H_

#include "dynamics/interface.h"
#include "dynamics/base/interface.h"
#include "dynamics/algorithm/vel-verlet/data/interface.h"

namespace mysimulator {

  template <typename T,typename GRNGType>
  struct Dynamics<MicroCanonicalVelVerlet,T,GRNGType>
      : public DynamicsBase<T> {

    public:

      typedef Dynamics<MicroCanonicalVelVerlet,T,GRNGType>  Type;
      typedef DynamicsBase<T>   ParentType;

      DynamicsVelVerletData<T> AltData;

      Dynamics() : ParentType(), AltData() {}
      ~Dynamics() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType&>(this)->IsValid()&&
               AltData.IsValid();
      }

      template <typename IDT,typename PT,typename GT,typename BT,
                template<typename> class CT>
      void Bind(System<T,IDT,PT,GT,BT,CT>& S) {
        assert(S.IsValid());
        assert(!(this->BindFlag));
        S._Clear();
        static_cast<ParentType*>(this)->Link(S);
        AltData.Link(S);
        this->BindFlag=true;
        S._Init();
      }

      template <typename IDT,typename PT,typename GT,typename BT,
                template<typename> class CT>
      void UnBind(System<T,IDT,PT,GT,BT,CT>& S) {
        assert(S.IsValid());
        assert(this->BindFlag);
        S._Clear();
        this->BindFlag=false;
      }

    private:

      Dynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GRT>
  void Clear(Dynamics<MicroCanonicalVelVerlet,T,GRT>& D) {
    typedef Dynamics<MicroCanonicalVelVerlet,T,GRT> Type;
    Clear(static_cast<typename Type::ParentType&>(D));
    Clear(D.AltData);
  }

  template <typename T,typename GRT,typename IDT,typename PT,typename GT,
            typename BT,template<typename> class CT>
  bool IsMatch(const Dynamics<MicroCanonicalVelVerlet,T,GRT>& D,
               const System<T,IDT,PT,GT,BT,CT>& S) {
    return (S.EvoluteMode==8)||(S.EvoluteMode=10);
  }

}

#endif

