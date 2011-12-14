
#ifndef _Array_2D_Content_Refer_H_
#define _Array_2D_Content_Refer_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/refer.h"

namespace mysimulator {

  template <typename T>
  void refer(Array2DContent<T>& A, const Array2DContent<T>& cA,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(cA));
    assert(partb<parte);
    assert((partb>=cA.infra.first)&&(parte<=cA.infra.last));
    release(A);
    int begin,end;
    begin=cA.infra[partb].start-cA.base.start;
    end=cA.infra[parte].start-cA.base.start+cA.infra[parte].size;
    refer(A.base,cA.base,begin,end,0);
    refer(A.infra,cA.infra,partb,parte,newb);
  }

  template <typename T>
  void refer(Array2DContent<T>& A, const Array2DContent<T>& cA,
             const int& partb, const int& parte) {
    refer(A,cA,partb,parte,partb);
  }

  template <typename T>
  void refer(Array2DContent<T>& A, const Array2DContent<T>& cA) {
    refer(A,cA,cA.first,cA.last);
  }

  template <typename T>
  void refer(Array2DContent<T>& A, const Array2DContent<T>& cA,
             const unsigned int& n) {
    refer(A,cA,cA.first,cA.first+n-1);
  }

}

#endif

