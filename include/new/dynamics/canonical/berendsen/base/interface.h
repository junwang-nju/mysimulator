
#ifndef _Dynamics_Canonical_Berendsen_Base_Interface_H_
#define _Dynamics_Canonical_Berendsen_Base_Interface_H_

#include "dynamics/canonical/base/interface.h"
#include "dynamics/canonical/berendsen/base/data/interface.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,typename OCT>
  struct DynamicsCanonicalBerendsenBase
      : public DynamicsCanonicalBase<T,VT,OCT> {

    public:

      typedef DynamicsCanonicalBerendsenBase<T,VT,OCT>  Type;
      typedef DynamicsCanonicalBase<T,VT,OCT>   ParentType;

      DynamicsCanonicalBerendsenBaseData<T,VT> CanonicalBerendsenBaseData;

      DynamicsCanonicalBerendsenBase() : CanonicalBerendsenBaseData() {}
      ~DynamicsCanonicalBerendsenBase() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        release(CanonicalBerendsenBaseData);
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(CanonicalBerendsenBaseData);
      }

    private:

      DynamicsCanonicalBerendsenBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename> class VT,typename OCT>
  void release(DynamicsCanonicalBerendsenBase<T,VT,OCT>& D) {
    D.clearData();
  }

  template <typename T,template<typename> class VT,typename OCT>
  bool IsValid(const DynamicsCanonicalBerendsenBase<T,VT,OCT>& D) {
    return D.isvalid();
  }

}

#include "dynamics/output/energy/interface.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,
            typename OST,typename IDT,typename PT,typename GT,
            template<typename,template<typename>class> class SCT>
  struct
  DynamicsCanonicalBerendsenBase<T,VT,
                                 DynamicsOutputEnergy<OST,T,IDT,PT,GT,VT,SCT> >
    : public
      DynamicsCanonicalBase<T,VT,DynamicsOutputEnergy<OST,T,IDT,PT,GT,VT,SCT> >{

    public:

      typedef DynamicsOutputEnergy<OST,T,IDT,PT,GT,VT,SCT>  OutputType;
      typedef DynamicsCanonicalBerendsenBase<T,VT,OutputType> Type;
      typedef DynamicsCanonicalBase<T,VT,OutputType>  ParentType;

      DynamicsCanonicalBerendsenBaseData4EnergyOut<T>
        CanonicalBerendsenBaseData;

      DynamicsCanonicalBerendsenBase()
        : ParentType(), CanonicalBerendsenBaseData() {}
      ~DynamicsCanonicalBerendsenBase() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        release(CanonicalBerendsenBaseData);
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(CanonicalBerendsenBaseData);
      }

    private:

      DynamicsCanonicalBerendsenBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

