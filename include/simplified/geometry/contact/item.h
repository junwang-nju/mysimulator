
#ifndef _Geometry_Contact_Item_H_
#define _Geometry_Contact_Item_H_

#include <algorithm>

namespace mysimulator {

  class ContactItem {

    public:

      typedef ContactItem   Type;

      unsigned int  I;
      unsigned int  J;
      unsigned int  Kind;
      double        Distance;
      double        Weight;

      ContactItem() : I(0), J(0), Kind(0), Distance(0), Weight(0) {}
      ContactItem(const Type& CI) : ContactItem() { operator=(CI); }
      ~ContactItem() { reset(); }

      operator bool() const { return true; }
      void reset() { I=0; J=0; Kind=0; Distance=0.; Weight=0.; }

      Type operator=(const Type& CI) {
        I=CI.I;
        J=CI.J;
        Kind=CI.Kind;
        Distance=CI.Distance;
        Weight=CI.Weight;
        return *this;
      }

      void swap(Type& CI) {
        std::swap(I,CI.I);
        std::swap(J,CI.J);
        std::swap(Kind,CI.Kind);
        std::swap(Distance,CI.Distance);
        std::swap(Weight,CI.Weight);
      }

  };

}

namespace std {

  void swap(mysimulator::ContactItem& A, mysimulator::ContactItem& B) {
    A.swap(B);
  }

}

#endif

