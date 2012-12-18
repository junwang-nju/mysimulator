
#ifndef _Geometry_Contact_Method_Def_H_
#define _Geometry_Contact_Method_Def_H_

#include "geometry/contact/method/name.h"

namespace mysimulator {

  template <ContactMethodName CMN>
  class ContactMethod {

    public:

      typedef ContactMethod<ContactMethodName>  Type;

      ContactMethod() = delete;
      ContactMethod(const Type&) = delete;
      ~ContactMethod() { }

      Type& operator=(const Type&) = delete;

  };

}

#endif

