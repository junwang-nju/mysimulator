
#ifndef _Dynamics_Interface_H_
#define _Dynamics_Interface_H_

#include "dynamics/mode-name.h"
#include "io/error.h"

namespace mysimulator {

  template <DynamicsModeName DN,typename T,template<typename> class VT,
            typename OChannel>
  struct Dynamics {

    public:

      typedef Dynamics<DN,T,VT,OChannel>  Type;

      Dynamics() { Error("This Dynamics Not Available!"); }
      ~Dynamics() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }

      template <typename IDT,typename PT,typename GT,
                template<typename,template<typename>class> class SCT>
      bool ismatch(const System<T,IDT,PT,GT,VT,SCT>& S) const { return false; }

      template <typename IDT,typename PT,typename GT,
                template<typename,template<typename>class> class SCT>
      void evolute(System<T,IDT,PT,GT,VT,SCT>&) {
        Error("No Dynamics to Evolute!");
      }

    private:

      Dynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <DynamicsModeName DN,typename T,template<typename> class VT,
            typename OCT>
  void release(Dynamics<DN,T,VT,OCT>& D) { D.clearData(); }

  template <DynamicsModeName DN,typename T,template<typename> class VT,
            typename OCT>
  bool IsValid(const Dynamics<DN,T,VT,OCT>& D) { return D.isvalid(); }

  template <DynamicsModeName DN,typename T,template<typename> class VT,
            typename OCT,typename IDT,typename PT,typename GT,
            template<typename,template<typename>class> class SCT>
  bool IsMatch(const Dynamics<DN,T,VT,OCT>& D,
               const System<T,IDT,PT,GT,VT,SCT>& S) { return D.ismatch(S); }

}

#endif

