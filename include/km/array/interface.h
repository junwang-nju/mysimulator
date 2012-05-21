
#ifndef _Array_Interface_H_
#define _Array_Interface_H_

#include "array/base/interface.h"

namespace mysimulator {

  template <typename T>
  class Array : public ArrayBase<T> {

    public:

      typedef Array<T>      Type;
      typedef ArrayBase<T>  ParentType;

      Array() : ParentType() {}
      ~Array() { Clear(*this); }

    private:

      Array(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(Array<T>& A) { Clear(static_cast<ArrayBase<T>&>(A)); }

}

#endif

