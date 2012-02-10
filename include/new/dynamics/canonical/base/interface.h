
#ifndef _Dynamics_Canonical_Base_Interface_H_
#define _Dynamics_Canonical_Base_Interface_H_

#include "dynamics/base/interface.h"
#include "dynamics/canonical/base/data/interface.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,typename OChannel>
  struct DynamicsCanonicalBase : public DynamicsBase<T,VT,OChannel> {

    public:

      typedef DynamicsCanonicalBase<T,VT,OChannel>    Type;
      typedef DynamicsBase<T,VT,OChannel>             ParentType;

      DynamicsCanonicalBaseData<T>  CanonicalData;

      DynamicsCanonicalBase() : ParentType(), CanonicalData() {}
      ~DynamicsCanonicalBase() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData(); release(CanonicalData);
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(CanonicalData);
      }

    private:

      DynamicsCanonicalBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename> class VT,typename OCT>
  void release(DynamicsCanonicalBase<T,VT,OCT>& D) { D.clearData(); }

  template <typename T,template<typename> class VT,typename OCT>
  bool IsValid(const DynamicsCanonicalBase<T,VT,OCT>& D) { return D.isvalid(); }

}

#endif

