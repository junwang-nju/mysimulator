
#ifndef _System_Content_Base_Interface_H_
#define _System_Content_Base_Interface_H_

#include "array/2d/release.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentBase {

    public:
      
      typedef SystemContentBase<T>  Type;

      T** X;

      SystemContentBase() : X(NULL) {}
      ~SystemContentBase() { clearData(); }

      void clearData() { release(X); }
      bool isvalid() const { return X!=NULL; }

    private:

      SystemContentBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(SystemContentBase<T>& C) { C.clearData(); }

  template <typename T>
  void IsValid(const SystemContentBase<T>& C) { return C.isvalid(); }

}

#endif

