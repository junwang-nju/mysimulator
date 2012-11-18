
#ifndef _Array_2D_Expression_Operation_H_
#define _Array_2D_Expression_Operation_H_

#include "array-2d/interface.h"
#include "array-2d/expression/sum.h"
#include "array-2d/expression/substract.h"
#include "array-2d/expression/multiple.h"
#include "array-2d/expression/divide.h"

namespace mysimulator {

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,typename E>
  Array2DSum<Array2D<Intrinsic<T>,DK,LK,true>,E>
  operator+(Array2D<Intrinsic<T>,DK,LK,true> const& A, E const& B) {
    return Array2DSum<Array2D<Intrinsic<T>,DK,LK,true>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DSum<Array2DSum<EA,EB>,E>
  operator+(Array2DSum<EA,EB> const& A,E const& B) {
    return Array2DSum<Array2DSum<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DSum<Array2DSub<EA,EB>,E>
  operator+(Array2DSub<EA,EB> const& A,E const& B) {
    return Array2DSum<Array2DSub<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DSum<Array2DMul<EA,EB>,E>
  operator+(Array2DMul<EA,EB> const& A,E const& B) {
    return Array2DSum<Array2DMul<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DSum<Array2DDiv<EA,EB>,E>
  operator+(Array2DDiv<EA,EB> const& A,E const& B) {
    return Array2DSum<Array2DDiv<EA,EB>,E>(A,B);
  }
  template <typename T,typename T1,ArrayKernelName DK,ArrayKernelName LK>
  Array2DSum<Intrinsic<T>,Array2D<Intrinsic<T1>,DK,LK,true>>
  operator+(Intrinsic<T> const& A,Array2D<Intrinsic<T1>,DK,LK,true> const& B) {
    return Array2DSum<Intrinsic<T>,Array2D<Intrinsic<T1>,DK,LK,true>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DSum<Intrinsic<T>,Array2DSum<EA,EB>>
  operator+(Intrinsic<T> const& A,Array2DSum<EA,EB> const& B) {
    return Array2DSum<Intrinsic<T>,Array2DSum<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DSum<Intrinsic<T>,Array2DSub<EA,EB>>
  operator+(Intrinsic<T> const& A,Array2DSub<EA,EB> const& B) {
    return Array2DSum<Intrinsic<T>,Array2DSub<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DSum<Intrinsic<T>,Array2DMul<EA,EB>>
  operator+(Intrinsic<T> const& A,Array2DMul<EA,EB> const& B) {
    return Array2DSum<Intrinsic<T>,Array2DMul<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DSum<Intrinsic<T>,Array2DDiv<EA,EB>>
  operator+(Intrinsic<T> const& A,Array2DDiv<EA,EB> const& B) {
    return Array2DSum<Intrinsic<T>,Array2DDiv<EA,EB>>(A,B);
  }

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,typename E>
  Array2DSub<Array2D<Intrinsic<T>,DK,LK,true>,E>
  operator-(Array2D<Intrinsic<T>,DK,LK,true> const& A, E const& B) {
    return Array2DSub<Array2D<Intrinsic<T>,DK,LK,true>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DSub<Array2DSum<EA,EB>,E>
  operator-(Array2DSum<EA,EB> const& A,E const& B) {
    return Array2DSub<Array2DSum<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DSub<Array2DSub<EA,EB>,E>
  operator-(Array2DSub<EA,EB> const& A,E const& B) {
    return Array2DSub<Array2DSub<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DSub<Array2DMul<EA,EB>,E>
  operator-(Array2DMul<EA,EB> const& A,E const& B) {
    return Array2DSub<Array2DMul<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DSub<Array2DDiv<EA,EB>,E>
  operator-(Array2DDiv<EA,EB> const& A,E const& B) {
    return Array2DSub<Array2DDiv<EA,EB>,E>(A,B);
  }
  template <typename T,typename T1,ArrayKernelName DK,ArrayKernelName LK>
  Array2DSub<Intrinsic<T>,Array2D<Intrinsic<T1>,DK,LK,true>>
  operator-(Intrinsic<T> const& A,Array2D<Intrinsic<T1>,DK,LK,true> const& B) {
    return Array2DSub<Intrinsic<T>,Array2D<Intrinsic<T1>,DK,LK,true>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DSub<Intrinsic<T>,Array2DSum<EA,EB>>
  operator-(Intrinsic<T> const& A,Array2DSum<EA,EB> const& B) {
    return Array2DSub<Intrinsic<T>,Array2DSum<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DSub<Intrinsic<T>,Array2DSub<EA,EB>>
  operator-(Intrinsic<T> const& A,Array2DSub<EA,EB> const& B) {
    return Array2DSub<Intrinsic<T>,Array2DSub<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DSub<Intrinsic<T>,Array2DMul<EA,EB>>
  operator-(Intrinsic<T> const& A,Array2DMul<EA,EB> const& B) {
    return Array2DSub<Intrinsic<T>,Array2DMul<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DSub<Intrinsic<T>,Array2DDiv<EA,EB>>
  operator-(Intrinsic<T> const& A,Array2DDiv<EA,EB> const& B) {
    return Array2DSub<Intrinsic<T>,Array2DDiv<EA,EB>>(A,B);
  }

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,typename E>
  Array2DMul<Array2D<Intrinsic<T>,DK,LK,true>,E>
  operator*(Array2D<Intrinsic<T>,DK,LK,true> const& A, E const& B) {
    return Array2DMul<Array2D<Intrinsic<T>,DK,LK,true>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DMul<Array2DSum<EA,EB>,E>
  operator*(Array2DSum<EA,EB> const& A,E const& B) {
    return Array2DMul<Array2DSum<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DMul<Array2DSub<EA,EB>,E>
  operator*(Array2DSub<EA,EB> const& A,E const& B) {
    return Array2DMul<Array2DSub<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DMul<Array2DMul<EA,EB>,E>
  operator*(Array2DMul<EA,EB> const& A,E const& B) {
    return Array2DMul<Array2DMul<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DMul<Array2DDiv<EA,EB>,E>
  operator*(Array2DDiv<EA,EB> const& A,E const& B) {
    return Array2DMul<Array2DDiv<EA,EB>,E>(A,B);
  }
  template <typename T,typename T1,ArrayKernelName DK,ArrayKernelName LK>
  Array2DMul<Intrinsic<T>,Array2D<Intrinsic<T1>,DK,LK,true>>
  operator*(Intrinsic<T> const& A,Array2D<Intrinsic<T1>,DK,LK,true> const& B) {
    return Array2DMul<Intrinsic<T>,Array2D<Intrinsic<T1>,DK,LK,true>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DMul<Intrinsic<T>,Array2DSum<EA,EB>>
  operator*(Intrinsic<T> const& A,Array2DSum<EA,EB> const& B) {
    return Array2DMul<Intrinsic<T>,Array2DSum<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DMul<Intrinsic<T>,Array2DSub<EA,EB>>
  operator*(Intrinsic<T> const& A,Array2DSub<EA,EB> const& B) {
    return Array2DMul<Intrinsic<T>,Array2DSub<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DMul<Intrinsic<T>,Array2DMul<EA,EB>>
  operator*(Intrinsic<T> const& A,Array2DMul<EA,EB> const& B) {
    return Array2DMul<Intrinsic<T>,Array2DMul<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DMul<Intrinsic<T>,Array2DDiv<EA,EB>>
  operator*(Intrinsic<T> const& A,Array2DDiv<EA,EB> const& B) {
    return Array2DMul<Intrinsic<T>,Array2DDiv<EA,EB>>(A,B);
  }

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,typename E>
  Array2DDiv<Array2D<Intrinsic<T>,DK,LK,true>,E>
  operator/(Array2D<Intrinsic<T>,DK,LK,true> const& A, E const& B) {
    return Array2DDiv<Array2D<Intrinsic<T>,DK,LK,true>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DDiv<Array2DSum<EA,EB>,E>
  operator/(Array2DSum<EA,EB> const& A,E const& B) {
    return Array2DDiv<Array2DSum<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DDiv<Array2DSub<EA,EB>,E>
  operator/(Array2DSub<EA,EB> const& A,E const& B) {
    return Array2DDiv<Array2DSub<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DDiv<Array2DMul<EA,EB>,E>
  operator/(Array2DMul<EA,EB> const& A,E const& B) {
    return Array2DDiv<Array2DMul<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  Array2DDiv<Array2DDiv<EA,EB>,E>
  operator/(Array2DDiv<EA,EB> const& A,E const& B) {
    return Array2DDiv<Array2DDiv<EA,EB>,E>(A,B);
  }
  template <typename T,typename T1,ArrayKernelName DK,ArrayKernelName LK>
  Array2DDiv<Intrinsic<T>,Array2D<Intrinsic<T1>,DK,LK,true>>
  operator/(Intrinsic<T> const& A,Array2D<Intrinsic<T1>,DK,LK,true> const& B) {
    return Array2DDiv<Intrinsic<T>,Array2D<Intrinsic<T1>,DK,LK,true>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DDiv<Intrinsic<T>,Array2DSum<EA,EB>>
  operator/(Intrinsic<T> const& A,Array2DSum<EA,EB> const& B) {
    return Array2DDiv<Intrinsic<T>,Array2DSum<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DDiv<Intrinsic<T>,Array2DSub<EA,EB>>
  operator/(Intrinsic<T> const& A,Array2DSub<EA,EB> const& B) {
    return Array2DDiv<Intrinsic<T>,Array2DSub<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DDiv<Intrinsic<T>,Array2DMul<EA,EB>>
  operator/(Intrinsic<T> const& A,Array2DMul<EA,EB> const& B) {
    return Array2DDiv<Intrinsic<T>,Array2DMul<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  Array2DDiv<Intrinsic<T>,Array2DDiv<EA,EB>>
  operator/(Intrinsic<T> const& A,Array2DDiv<EA,EB> const& B) {
    return Array2DDiv<Intrinsic<T>,Array2DDiv<EA,EB>>(A,B);
  }

}

#endif

