
#ifndef _Geometry_Contact_Method_C_Alpha_H_
#define _Geometry_Contact_Method_C_Alpha_H_

#include "geometry/contact/method/def.h"

namespace mysimulator {

  template <>
  class ContactMethod<CAlphaDistance> {

    public:

      typedef ContactMethod<CAlphaDistance>   Type;

      static const ContactMethodName Name = CAlphaDistance;

    private:

      double _threshold;

      ContactMethod() : _threshold(0) {}
      ~ContactMethod() { reset(); }

      operator bool() const { return true; }
      double Threshold() const { return _threshold; }
      void reset() { _threshold=0.; }

      void SetThreshold(double th) { _threshold=th; }

  };

}

#endif

