
#ifndef _Array_1D_Interface_H_
#define _Array_1D_Interface_H_

#include "array/format/interface.h"
#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  struct Array1D : public ArrayFormat<T,Array1DContent> {

    public:

      typedef Array1D<T>    Type;
      typedef ArrayFormat<T,Array1DContent>   ParentType;

      Array1D() : ParentType() {}
      ~Array1D() { this->clearData(); }

    private:

      Array1D(const Type&) {}
      Type& operator=(const Type&) { return *this; }
  };

  template <typename T>
  bool IsValid(const Array1D<T>& A) { return A.isvalid(); }

  template <typename T>
  void release(Array1D<T>& A) { A.clearData(); }

}

#endif

