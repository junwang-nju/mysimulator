
#ifndef _System_Content_Base_Interface_H_
#define _System_Content_Base_Interface_H_

#include "array/2d/imprint.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentBase {

    public:

      typedef SystemContentBase<T>  Type;

      Array2D<T>  X;

      SystemContentBase() : X() {}
      ~SystemContentBase() { Clear(*this); }

      bool IsValid() const { return X.IsValid(); }

      template <typename T1>
      void Allocate(const Array2D<T1>& iX) {
        Clear(*this);
        ImprintStructure(X,iX);
      }
      void Refer(Type& D) { X.Refer(D.X); }
      void Refer(Type& D,unsigned int b,unsigned int n) { X.Refer(D.X,b,n); }

    private:

      SystemContentBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(SystemContentBase<T>& C) { Clear(C.X); }

}

#endif

