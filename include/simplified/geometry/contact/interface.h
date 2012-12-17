
#ifndef _Geometry_Contact_Interface_H_
#define _Geometry_Contact_Interface_H_

#include "geometry/contact/item.h"
#include "array/interface.h"

namespace mysimulator {

  class Contact : public Array<ContactItem> {

    public:

      typedef Contact   Type;
      typedef Array<ContactItem>  ParentType;

      Contact() : ParentType() {}
      Contact(const Type& C) : ParentType((ParentType const&)C) {}
      Contact(Type&& C) : ParentType((ParentType&&)C) {}
      ~Contact() { ParentType::reset(); }

      Type& operator=(const Type& C) {
        assert(ParentType::size()==C.size());
        ParentType::operator=((ParentType const&)C);
        return *this;
      }

  };

}

#endif

