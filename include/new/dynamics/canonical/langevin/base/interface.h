
#ifndef _Dynamics_Canonical_Langevin_Base_Interface_H_
#define _Dynamics_Canonical_Langevin_Base_Interface_H_

#include "dynamics/canonical/base/interface.h"
#include "dynamics/canonical/langevin/base/data/interface.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,typename OCT,typename RT>
  struct DynamicsCanonicalLangevinBase
      : public DynamicsCanonicalBase<T,VT,OCT> {

    public:

      typedef DynamicsCanonicalLangevinBase<T,VT,OCT,RT>  Type;
      typedef DynamicsCanonicalBase<T,VT,OCT>   ParentType;

      DynamicsCanonicalLangevinBase() {}
      ~DynamicsCanonicalLangevinBase() { clearData(); }

    private:

      DynamicsCanonicalLangevinBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename> class VT,typename OCT,typename RT>
  void release(DynamicsCanonicalLangevinBase<T,VT,OCT,RT>& D) { D.clearData(); }

  template <typename T,template<typename> class VT,typename OCT,typename RT>
  bool IsValid(const DynamicsCanonicalLangevinBase<T,VT,OCT,RT>& D) {
    return D.isvalid();
  }

}

#endif

