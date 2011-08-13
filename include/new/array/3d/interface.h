
#ifndef _Array_3D_Interface_H_
#define _Array_3D_Interface_H_

#include "array/format/interface.h"
#include "array/3d/content/interface.h"

namespace mysimulator {

  template <typename T>
  struct Array3D : public ArrayFormat<T,Array3DContent> {

    public:

      typedef Array3D<T>    Type;
      typedef ArrayFormat<T,Array3DContent>   ParentType;

      Pointer<Array1DContent<T> > subdata2d;
      Pointer<Array2DContent<T> > subdata3d;

      Array3D() : ParentType(), subdata2d(), subdata3d() {}
      ~Array3D() { clearData(); }

      void clearData() {
        release(*static_cast<ParentType*>(this));
        release(subdata2d);
        release(subdata3d);
      }
      void isvalid() const {
        return IsValid(*static_cast<ParentType*>(this))&&IsValid(subdata2d)&&
               IsValid(subdata3d);
      }

    private:

      Array3D(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  bool IsValid(const Array3D<T>& A) { return A.isvalid(); }

  template <typename T>
  void release(Array3D<T>& A) { A.clearData(); }

}

#endif

