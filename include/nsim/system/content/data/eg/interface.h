
#ifndef _System_Content_Data_EG_Interface_H_
#define _System_Content_Data_EG_Interface_H_

#include "array/2d/imprint.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentDataEG {

    public:

      typedef SystemContentDataEG<T>  Type;

      Array1D<T>    Energy;
      Array2D<T>    Gradient;

      SystemContentDataEG() : Energy(), Gradient() {}
      ~SystemContentDataEG() { Clear(); }

      void Clear() { Energy.Clear(); Gradient.Clear(); }
      bool IsValid() const { return Energy.IsValid()&&Gradient.IsValid(); }

      void Allocate() { fprintf(stderr,"Not Available!\n"); }
      void Allocate(const Array2D<T>& X) {
        Clear();
        Energy.Allocate(1);
        Imprint(Gradient,X);
      }
      void Refer(const Type& D) {
        Energy.Refer(D.Energy);
        Gradient.Refer(D.Gradient);
      }
      void Refer(const Type& D,unsigned int b,unsigned int n) {
        Energy.Refer(D.Energy);
        Gradient.Refer(D.Gradient,b,n);
      }

    private:

      SystemContentDataEG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

