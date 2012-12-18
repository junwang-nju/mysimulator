
#ifndef _Geometry_Contact_Method_C_Alpha_H_
#define _Geometry_Contact_Method_C_Alpha_H_

#include "geometry/contact/method/def.h"
#include "geometry/contact/method/base.h"

namespace mysimulator {

  template <>
  class ContactMethod<ContactMethodName::CAlphaDistance>
      : public ContactMethodBase {

    public:

      typedef ContactMethod<ContactMethodName::CAlphaDistance>   Type;
      typedef ContactMethodBase   ParentType;

      static const ContactMethodName Name = ContactMethodName::CAlphaDistance;

    private:

      double _threshold;

    public:

      ContactMethod() : ParentType(), _threshold(0) {}
      ContactMethod(const Type& M) : ParentType((ParentType const&)M),
                                     _threshold(M._threshold) {}
      ~ContactMethod() { reset(); }

      Type& operator=(const Type& M) {
        ParentType::operator=((ParentType const&)M);
        _threshold=M._threshold;
        return *this;
      }

      operator bool() const { return true; }
      double Threshold() const { return _threshold; }
      void reset() { ParentType::reset(); _threshold=0.; }

      void SetThreshold(double th) { _threshold=th; }

  };

}

#endif

