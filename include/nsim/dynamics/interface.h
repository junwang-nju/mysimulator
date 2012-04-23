
#ifndef _Dynamics_Interface_H_
#define _Dynamics_Interface_H_

#include "dynamics/mode-name.h"
#include "system/interface.h"

namespace mysimulator {

  template<typename T,typename IDT,typename PT,typename GT,typename BT,
           template<typename> class CT>
  struct System;

  template <DynamicsModeName DN,typename T,typename GRNGType>
  struct Dynamics {

    public:

      typedef Dynamics<DN,T,GRNGType>   Type;

      Dynamics() {
        fprintf(stderr,"Dynamics Prohibited for Default Type!\n");
      }
      ~Dynamics() { Clear(*this); }

      bool IsValiad() const { return false; }

      template<typename IDT,typename PT,typename GT,typename BT,
               template<typename> class CT>
      void Bind(System<T,IDT,PT,GT,BT,CT>&) {
        fprintf(stderr,"Not Bind for this Dynamics!\n");
      }
      template<typename IDT,typename PT,typename GT,typename BT,
               template<typename> class CT>
      void UnBind(System<T,IDT,PT,GT,BT,CT>&) {
        fprintf(stderr,"Not UnBind for this Dynamics!\n");
      }

    private:

      Dynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <DynamicsModeName DN,typename T,typename GRT>
  void Clear(Dynamics<DN,T,GRT>&) {}

  template <DynamicsModeName DN,typename T,typename GRT,typename IDT,
            typename PT,typename GT,typename BT,template<typename> class CT>
  bool IsMatch(const Dynamics<DN,T,GRT>&,const System<T,IDT,PT,GT,BT,CT>&) {
    return false;
  }

}

#include "dynamics/micro-canonical/vel-verlet/interface.h"

#endif

