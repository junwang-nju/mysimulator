
#ifndef _Basic_Type_Intrinsic_H_
#define _Basic_Type_Intrinsic_H_

#include "basic/type/intrinsic-def.h"

#include "basic/type/selector.h"
#include "basic/type/sum.h"

namespace mysimulator {

  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__sum>::Type>
  operator+(Intrinsic<T1> const& A, Intrinsic<T2> const& B) {
    typedef typename __dual_selector<T1,T2,__sum>::Type vtype;
    return Intrinsic<vtype>((vtype)A+(vtype)B);
  }

}

#include "basic/type/substract.h"

namespace mysimulator {

  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__sub>::Type>
  operator-(Intrinsic<T1> const& A, Intrinsic<T2> const& B) {
    typedef typename __dual_selector<T1,T2,__sub>::Type vtype;
    return Intrinsic<vtype>((vtype)A-(vtype)B);
  }

}

#include "basic/type/multiple.h"

namespace mysimulator {

  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__mul>::Type>
  operator*(Intrinsic<T1> const& A, Intrinsic<T2> const& B) {
    typedef typename __dual_selector<T1,T2,__mul>::Type vtype;
    return Intrinsic<vtype>((vtype)A*(vtype)B);
  }

}

#include "basic/type/divide.h"

namespace mysimulator {

  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__div>::Type>
  operator/(Intrinsic<T1> const& A, Intrinsic<T2> const& B) {
    typedef typename __dual_selector<T1,T2,__div>::Type vtype;
    return Intrinsic<vtype>((vtype)A/(vtype)B);
  }
}

#endif

