
#ifndef _Array_2D_Interface_H_
#define _Array_2D_Interface_H_

#include "array/format/interface.h"
#include "array/2d/content/interface.h"

namespace mysimulator {

  template <typename T>
  struct Array2D : public ArrayFormat<T,Array2DContent> {

    public:

      typedef Array2D<T>    Type;
      typedef ArrayFormat<T,Array2DContent>   ParentType;

      Pointer<Array1DContent<T> > subdata;

      Array2D() : ParentType(), subdata() {}
      ~Array2D() { clearData(); }

      void clearData() {
        release(*static_cast<ParentType*>(this));
        release(subdata);
      }
      bool isvalid() const {
        return IsValid(*static_cast<const ParentType*>(this))&&IsValid(subdata);
      }

    private:

      Array2D(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  bool IsValid(const Array2D<T>& A) { return A.isvalid(); }

  template <typename T>
  void release(Array2D<T>& A) { A.clearData(); }

}

#endif

