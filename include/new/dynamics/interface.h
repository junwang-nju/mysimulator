
#ifndef _Dynamics_Interface_H_
#define _Dynamics_Interface_H_

#include "dynamics/mode-name.h"
#include "system/interface.h"

namespace mysimulator {

  template <DynamicsModeName DMN, typename T,template<typename> class VecType,
            typename OutputChannel>
  struct Dynamics {

    public:

      typedef Dynamics<DMN,T,VecType,OutputChannel>   Type;

      Dynamics() {}
      ~Dynamics() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }
      template <typename IDT,typename PT,typename GT,
                template<typename,template<typename>class> class SCT>
      bool ismatch(const System<T,IDT,PT,GT,VecType,SCT>& S) const {
        return false;
      }

      template <typename IDType,typename ParamType,typename GeomType,
                template<typename,template<typename>class> class SysContentType>
      void evolute(System<T,IDType,ParamType,GeomType,VecType,SysContentType>&){
        Error("No Dynamics are Available!");
      }

    private:

      Dynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <DynamicsModeName DMN,typename T,template<typename> class VT,
            typename OC>
  void release(Dynamics<DMN,T,VT,OC>& D) { D.clearData(); }

  template <DynamicsModeName DMN,typename T,template<typename> class VT,
            typename OC>
  bool IsValid(const Dynamics<DMN,T,VT,OC>& D) { return D.isvalid(); }

  template <DynamicsModeName DMN,typename T,template<typename> class VT,
            typename OC,typename IDT,typename PT,typename GT,
            template<typename,template<typename>class> class SCT>
  bool IsMatch(const Dynamics<DMN,T,VT,OC>& D,
               const System<T,IDT,PT,GT,VT,SCT>& S) { return D.ismatch(S); }

}

#include "dynamics/micro-canonical/specification.h"

#endif

