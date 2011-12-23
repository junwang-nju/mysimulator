
#ifndef _Array_2D_Content_Shift_H_
#define _Array_2D_Content_Shift_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/shift.h"

#define _SHIFTC(type) \
  template <typename T>\
  void shift(Array2DContent<T>& A, const type& d) { shift(A.base,d); }

namespace mysimulator {

  _SHIFTC(long double)
  _SHIFTC(double)
  _SHIFTC(float)
  _SHIFTC(long long)
  _SHIFTC(unsigned long long)
  _SHIFTC(int)
  _SHIFTC(unsigned int)
  _SHIFTC(long)
  _SHIFTC(unsigned long)
  _SHIFTC(short)
  _SHIFTC(unsigned short)
  _SHIFTC(char)
  _SHIFTC(unsigned char)

}

#undef _SHIFTC

#define _SHIFT(type) \
  template <typename T>\
  void shift(Array2DContent<T>& A, const type& d, const Array2DContent<T>& B) {\
    shift(A.base,d,B.base);\
  }

namespace mysimulator {

  _SHIFT(long double)
  _SHIFT(double)
  _SHIFT(float)
  _SHIFT(long long)
  _SHIFT(unsigned long long)
  _SHIFT(int)
  _SHIFT(unsigned int)
  _SHIFT(long)
  _SHIFT(unsigned long)
  _SHIFT(short)
  _SHIFT(unsigned short)
  _SHIFT(char)
  _SHIFT(unsigned char)

}

#undef _SHIFT

namespace mysimulator {

  template <typename T,typename T1,typename T2>
  void shift(Array2DContent<T>& A, const Array2DContent<T1>& B1,
             const Array2DContent<T2>& B2) {
    assert(IsSameSize(A,B1)&&IsSameSize(A,B2));
    shift(A.base,B1.base,B2.base);
  }

  template <typename T,typename Tf,typename T1,typename T2>
  void shift(Array2DContent<T>& A, const Tf& u, const Array2DContent<T1>& B1,
             const Array2DContent<T2>& B2) {
    assert(IsSameSize(A,B1)&&IsSameSize(A,B2));
    shift(A.base,u,B1.base,B2.base);
  }

  template <typename T,typename Tu,typename Tv,typename T1,typename T2>
  void scaleshift(Array2DContent<T>& A, const Tu& u, const Tv& v,
                  const Array2DContent<T1>& B1, const Array2DContent<T2>& B2) {
    assert(IsSameSize(A,B1)&&IsSameSize(A,B2));
    scaleshift(A.base,u,v,B1.base,B2.base);
  }

  template <typename T,typename Tu,typename T1,typename T2>
  void scaleshift(Array2DContent<T>& A, const Tu& u, const Array2DContent<T1>& B1,
                  const Array2DContent<T2>& B2) {
    scaleshift(A.base,u,B1.base,B2.base);  
  }

}

#endif

