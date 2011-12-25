
#ifndef _Dynamics_Interface_H_
#define _Dynamics_Interface_H_

#include "dynamics/mode-name.h"
#include "system/interface.h"

namespace mysimulator {

  template <DynamicsModeName DMN, typename T,template<typename> class VecType>
  struct Dynamics {

    public:

      typedef Dynamics<DMN,T,VecType>   Type;

      Dynamics() {}
      ~Dynamics() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }

      template <typename IDType,typename ParamType,typename GeomType,
                template<typename,template<typename>class> class SysContentType>
      void evolute(System<T,IDType,ParamType,GeomType,VecType,SysContentType>&){
        Error("No Dynamics are Available!");
      }

    private:

      Dynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <DynamicsModeName DMN,typename T,template<typename> class VT>
  void release(Dynamics<DMN,T,VT>& D) { D.clearData(); }

  template <DynamicsModeName DMN,typename T,template<typename> class VT>
  bool IsValid(const Dynamics<DMN,T,VT>& D) { return D.isvalid(); }

}

#include "dynamics/micro-canonical/specification.h"

#endif

