
#ifndef _Variable_Property_List_H_
#define _Variable_Property_List_H_

#include "property-list.h"

namespace std {

  template <typename T>
  class varPropertyList : public PropertyList<T,varVector> {

    public:

      typedef PropertyList<T,varVector>   Type;

  };

}

#endif

