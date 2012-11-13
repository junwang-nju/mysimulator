
#ifndef _Array_Expession_Result_Typel_H_
#define _Array_Expession_Result_Typel_H_

#include "basic/type/intrinsic-check.h"
#include "basic/expression/name.h"

namespace mysimulator {

  template <typename T1,typename T2,ExpressionOperationName EN>
  class __array_expression_result {};

}

#include "basic/type/selector.h"
#include "basic/type/sum.h"

namespace mysimulator {

  template <typename T1,typename T2>
  class __array_expression_result<T1,T2,ExpressionOperationName::Sum> {
    public:
      typedef typename __dual_selector<T1,T2,__sum>::Type   Type;
  };

}

#include "basic/type/substract.h"

namespace mysimulator {

  template <typename T1,typename T2>
  class __array_expression_result<T1,T2,ExpressionOperationName::Substract> {
    public:
      typedef typename __dual_selector<T1,T2,__sub>::Type   Type;
  };

}

#include "basic/type/multiple.h"

namespace mysimulator {

  template <typename T1,typename T2>
  class __array_expression_result<T1,T2,ExpressionOperationName::Multiple> {
    public:
      typedef typename __dual_selector<T1,T2,__mul>::Type   Type;
  };

}

#include "basic/type/divide.h"

namespace mysimulator {

  template <typename T1,typename T2>
  class __array_expression_result<T1,T2,ExpressionOperationName::Divide> {
    public:
      typedef typename __dual_selector<T1,T2,__div>::Type   Type;
  };

}

#endif

