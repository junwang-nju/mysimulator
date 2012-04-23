
#ifndef _System_Content_Data_G_Interface_H_
#define _System_Content_Data_G_Interface_H_

#include "array/2d/imprint.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentDataG {

    public:

      typedef SystemContentDataG<T>   Type;

      Array2D<T>  Gradient;

      SystemContentDataG() : Gradient() {}
      ~SystemContentDataG() { Clear(*this); }

      bool IsValid() const { return Gradient.IsValid(); }

      void Allocate() { fprintf(stderr,"Not Available!\n"); }
      void Allocate(const Array2D<T>& X) {
        Clear(*this);
        Imprint(Gradient,X);
      }
      void Refer(const Type& D) { Gradient.Refer(D.Gradient); }
      void Refer(const Type& D,unsigned int b,unsigned int n) {
        Gradient.Refer(D.Gradient,b,n);
      }

    private:

      SystemContentDataG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(SystemContentDataG<T>& D) { Clear(D.Gradient); }

}

#endif

