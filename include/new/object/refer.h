
#ifndef _Object_Refer_H_
#define _Object_Refer_H_

#include "object/interface.h"
#include "pointer/refer.h"

namespace mysimulator {

  template <typename T>
  void refer(Object<T>& O, Object<T>& cO) {
    typedef typename Object<T>::ParentType  Type;
    assert(IsValid(cO));
    release(O);
    refer(static_cast<Type&>(O),static_cast<Type&>(cO));
  }

  template <typename T>
  void refer(Object<T>& O, const T* const& p) {
    assert(IsValid(*p));
    release(O);
    refer(static_cast<typename Object<T>::ParentType&>(O),p);
  }

  template <typename T>
  void refer(Object<T>& O, const T& d) {
    release(O);
    refer(static_cast<typename Object<T>::ParentType&>(O),d);
  }

}

#endif

