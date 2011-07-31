
#ifndef _Array_1D_Content_Cross_H_
#define _Array_1D_Content_Cross_H_

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T1, typename T2, typename T3>
  void _cross(T1* p0, T2* q0, T3* r0, const unsigned int& d1,
              const unsigned int& d2, const unsigned int& d3) {
    T1* p1=p0+d1;
    T1* p2=p1+d1;
    T2* q1=q0+d2;
    T2* q2=q1+d2;
    T3* r1=r0+d3;
    T3* r2=r1+d3;
    T1 u0,u1,u2,v0,v1,v2;
    copy(u0,*q0); copy(u1,*q1);   copy(u2,*q2);
    copy(v0,*r0); copy(v1,*r1);   copy(v2,*r2);
    copy(*p0,u1*v2-u2*v1);
    copy(*p1,u2*v0-u0*v2);
    copy(*p2,u0*v1-u1*v0);
  }

  template <typename T1, typename T2, typename T3>
  void cross(Array1DContent<T1>& A, const Array1DContent<T2>& B,
             const Array1DContent<T3>& C, const int& b1,
             const unsigned int& d1, const int& b2, const unsigned int& d2,
             const int& b3, const unsigned int& d3) {
    assert(IsValid(A,b1,d1,3)&&IsValid(B,b2,d2,3)&&IsValid(C,b3,d3,3));
    T1* p0=A.head+b1;
    T2* q0=const_cast<T2*>(B.head+b2);
    T3* r0=const_cast<T3*>(C.head+b3);
    _cross(p0,q0,r0,d1,d2,d3);
  }

  template <typename T1, typename T2, typename T3>
  void cross(Array1DContent<T1>& A, const Array1DContent<T2>& B,
             const Array1DContent<T3>& C, const int& b1, const int& b2,
             const int& b3) {
    assert(IsValid(A,b1,3)&&IsValid(B,b2,3)&&IsValid(C,b3,3));
    T1* p0=A.head+b1;
    T2* q0=const_cast<T2*>(B.head+b2);
    T3* r0=const_cast<T3*>(C.head+b3);
    _cross(p0,q0,r0,1,1,1);
  }

  template <typename T1, typename T2, typename T3>
  void cross(Array1DContent<T1>& A, const Array1DContent<T2>& B,
             const Array1DContent<T3>& C) {
    assert(IsValid(A,3)&&IsValid(B,3)&&IsValid(C,3));
    T1* p0=A.start;
    T2* q0=const_cast<T2*>(B.start);
    T3* r0=const_cast<T3*>(C.start);
    _cross(p0,q0,r0,1,1,1);
  }

}

#endif

