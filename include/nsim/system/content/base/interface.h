
#ifndef _System_Content_Base_Interface_H_
#define _System_Content_Base_Interface_H_

#include "array/2d/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentBase {

    public:

      typedef SystemContentBase<T>  Type;

      Array2D<T>  X;

      SystemContentBase() : X() {}
      ~SystemContentBase() { Clear(); }

      void Clear() { X.Clear(); }
      bool IsValid() const { return X.IsValid(); }

      void Refer(const Type& D) { X.Refer(D.X); }
      void Refer(const Type& D,unsigned int b,unsigned int n) {
        X.Refer(D.X,b,n);
      }

    private:

      SystemContentBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

