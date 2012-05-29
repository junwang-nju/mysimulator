
#ifndef _Array2D_Interface_H_
#define _Array2D_Interface_H_

#include "array2d/base/interface.h"
#include "array/interface.h"

namespace mysimulator {

  template <typename T>
  class Array2D : public Array2DBase<T,Array> {

    public:

      typedef Array2D<T>  Type;
      typedef Array2DBase<T,Array>  ParentType;

      Array2D() : ParentType() {}
      ~Array2D() { Clear(*this); }

    private:

      Array2D(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(Array2D<T>& A) {
    Clear(static_cast<Array2DBase<T,Array>&>(A));
  }

  template <typename T>
  void IsSame(const Array2D<T>& A, const Array2D<T>& B) {
    typedef typename Array2D<T>::ParentType   PType;
    return IsSame<T,Array,Array>(static_cast<const PType&>(A),
                                 static_cast<const PType&>(B));
  }

  template <typename T1,typename T2>
  void _Copy(Array2D<T1>& A,const Array2D<T2>& B) { A.Copy(B); }

  template <typename T1,typename T2>
  void _Fill(Array2D<T1>& A,const T2& d) { A.Fill(d); }

  template <typename T>
  void _Imprint(Array2D<T>& A, const Array2D<T>& B) { A.Imprint(B); }

  template <typename T>
  void _SwapContent(Array2D<T>& A, Array2D<T>& B) {
    typedef typename Array2D<T>::ParentType   PType;
    _SwapContent<T,Array,Array>(static_cast<PType&>(A),
                                static_cast<PType&>(B));
  }

  template <typename T> class Array2DNumeric;

  template <typename T1,typename T2>
  void _Copy(Array2D<T1>& A,const Array2DNumeric<T2>& B) { A.Copy(B); }

  template <typename T1,typename T2>
  void _Imprint(Array2D<T1>& A, const Array2DNumeric<T2>& B) { A.Imprint(B); }

  template <typename T>
  void _SwapContent(Array2D<T>& A,Array2DNumeric<T>& B) {
    _SwapContent(static_cast<Array2DBase<T,Array>&>(A),
                 static_cast<Array2DBase<T,Array2DNumeric>&>(B));
  }

}

#endif

