
#ifndef _Reference_Property_List_H_
#define _Reference_Property_List_H_

#include "property-list.h"

namespace std {

  template <typename T>
  class refPropertyList : public PropertyList<T,refVector> {

    public:

      typedef PropertyList<T,refVector>   Type;

  };

}

#endif

