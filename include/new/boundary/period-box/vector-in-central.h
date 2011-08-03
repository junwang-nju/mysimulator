
#ifndef _Boundary_PeriodBox_Vector_in_Central_H_
#define _Boundary_PeriodBox_Vector_in_Central_H_

#include "boundary/period-box/interface.h"
#include "intrinsic-type/shift.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void shift2central(Array1DContent<T1>& v, const PeriodBox<T2>& B) {
    assert(IsValid(v)&&IsValid(B));
    assert(v.size>=B.dimension());
    T1* p=v.start;
    T2* q=const_cast<T2*>(B.box.start);
    T2* r=const_cast<T2*>(B.hbox.start);
    bool* g=const_cast<bool*>(B.pdflag.start);
    T1* e=p+n;
    for(;p!=e;++p,++q,++r) {
      if(*(g++)) {
        while(*p<-(*r))   shift(*p,cOne,*q);
        while(*p>=*r)     shift(*p,-cOne,*q);
      }
    }
  }

}

#endif

