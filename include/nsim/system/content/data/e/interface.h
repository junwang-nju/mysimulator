
#ifndef _System_Content_Data_E_Interface_H_
#define _System_Content_Data_E_Interface_H_

#include "array/2d/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentDataE {

    public:

      typedef SystemContentDataE<T>   Type;

      Array1D<T>  Energy;

      SystemContentDataE() : Energy() {}
      ~SystemContentDataE() { Clear(*this); }

      bool IsValid() const { return Energy.IsValid(); }

      void Allocate() {
        Clear(*this);
        Energy.Allocate(1);
      }
      void Allocate(const Array2D<T>&) { Allocate(); }
      void Refer(const Type& D) { Energy.Refer(D.Energy); }
      void Refer(const Type& D,unsigned int b,unsigned int n) { Refer(D); }

    private:

      SystemContentDataE(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(SystemContentDataE<T>& D) { Clear(D.Energy); }
}

#endif

