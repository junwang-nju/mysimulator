
#ifndef _Dynamics_Interface_H_
#define _Dynamics_Interface_H_

#include "dynamics/mode-name.h"

namespace mysimulator {

  template <DynamicsModeName DN,typename T,typename GRNGType>
  struct Dynamics {

    public:

      typedef Dynamics<DN,T,GRNGType>   Type;

      bool BindFlag;

      Dynamics() : BindFlag(false) {
        fprintf(stderr,"Dynamics Prohibited for Default Type!\n");
      }
      ~Dynamics() { Clear(*this); }

      bool IsValiad() const { return false; }

    private:

      Dynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <DynamicsModeName DN,typename T,typename GRT>
  void Clear(Dynamics<DN,T<GRT>&) {}

}

#include "system/interface.h"

namespace mysimulator {

  template <DynamicsModeName DN,typename T,typename GRT,typename IDT,
            typename PT,typename GT,typename BT,template<typename> class CT>
  bool IsMatch(const Dynamics<DN,T,GRT>&,const System<T,IDT,PT,GT,BT,CT>&) {
    return false;
  }

}

#include "dynamics/micro-canonical/vel-verlet/interface.h"

#endif

