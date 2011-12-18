
#ifndef _Dynamics_Langevin_Specification_H_
#define _Dynamics_Langevin_Specification_H_

#include "dynamics/interface.h"
#include "dynamics/base/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,typename OC>
  struct Dynamics<Langevin,T,VT,OC> : public DynamicsBase<T> {

    public:

      typedef Dynamics<Langevin,T,VT,OC>    Type;
      typedef DynamicsBase<T>   ParentType;

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
        release(gFac1); release

    private:

      Dynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

