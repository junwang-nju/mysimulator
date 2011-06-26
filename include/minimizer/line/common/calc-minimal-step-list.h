
#ifndef _Minimizer_Line_Common_Calc_MinimalStep_List_H_
#define _Minimizer_Line_Common_Calc_MinimalStep_List_H_

#include "list/interface.h"
#include "minimizer/line/common/calc-minimal-step-vector.h"

namespace mysimulator {

  template <typename T>
  T CalcMinimalStep(const List<T>& X, const List<T>& D,
                    const List<unsigned int>& M, const unsigned int& F) {
    assert(IsValid(X)&&IsValid(D)&&IsValid(M));
    return CalcMinimalStep(static_cast<const Vector<T>&>(X),
                           static_cast<const Vector<T>&>(D),
                           static_cast<const Vector<unsigned int>&>(M),F);
  }

}

#endif

