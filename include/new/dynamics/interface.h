
#ifndef _Dynamics_Interface_H_
#define _Dynamics_Interface_H_

#include "dynamics/mode-name.h"
#include "system/interface.h"
#include "random/box-muller/interface.h"
#include "random/mt/interface.h"

namespace mysimulator {

  template <DynamicsModeName DN,typename T,template<typename> class VT,
            typename OChannel,
            typename RNGType=BoxMuller<MersenneTwister<dSFMT,19937> > >
  struct Dynamics {

    public:

      typedef Dynamics<DN,T,VT,OChannel,RNGType>  Type;

      bool BindFlag;

      Dynamics() : BindFlag(false) { Error("This Dynamics Not Available!"); }
      ~Dynamics() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }

      template <typename IDT,typename PT,typename GT,
                template<typename,template<typename>class> class SCT>
      bool ismatch(const System<T,IDT,PT,GT,VT,SCT>& S) const { return false; }

    private:

      Dynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <DynamicsModeName DN,typename T,template<typename> class VT,
            typename OCT,typename RT>
  void release(Dynamics<DN,T,VT,OCT,RT>& D) { D.clearData(); }

  template <DynamicsModeName DN,typename T,template<typename> class VT,
            typename OCT,typename RT>
  bool IsValid(const Dynamics<DN,T,VT,OCT,RT>& D) { return D.isvalid(); }

  template <DynamicsModeName DN,typename T,template<typename> class VT,
            typename OCT,typename RT,typename IDT,typename PT,typename GT,
            template<typename,template<typename>class> class SCT>
  bool IsMatch(const Dynamics<DN,T,VT,OCT,RT>& D,
               const System<T,IDT,PT,GT,VT,SCT>& S) { return D.ismatch(S); }

}

#include "dynamics/micro-canonical/vverlet/specification.h"
#include "dynamics/canonical/langevin/vverlet/specification.h"
#include "dynamics/canonical/berendsen/vverlet/specification.h"

#endif

