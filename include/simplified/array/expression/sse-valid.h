
#ifndef _Array_Expression_SSE_Valid_H_
#define _Array_Expression_SSE_Valid_H_

#include "basic/expression/name.h"
#include "basic/sse/valid.h"
#include "basic/type/same-check.h"

namespace mysimulator {

  template <typename EA,typename EB,ExpressionOperationName EN>
  class __array_expression_sse_valid { public: static const bool FLAG; };

  template <typename EA,typename EB,ExpressionOperationName EN>
  const bool __array_expression_sse_valid<EA,EB,EN>::FLAG =
      EA::_is_SSE_valid && EB::_is_SSE_valid &&
      __same_type<typename EA::value_type,typename EB::value_type>::FLAG &&
      __mono_sse_valid<typename EA::value_type>::FLAG;

}

#include "basic/type/intrinsic.h"
#include "basic/expression/result-type.h"

namespace mysimulator {

  template <typename T,typename E,ExpressionOperationName EN>
  class __array_expression_sse_valid<Intrinsic<T>,E,EN> {
    public: static const bool FLAG;
  };

  template <typename T,typename E,ExpressionOperationName EN>
  const bool __array_expression_sse_valid<Intrinsic<T>,E,EN>::FLAG =
      E::_is_SSE_valid && __mono_sse_valid<typename E::value_type>::FLAG &&
      __same_type<
          typename __expression_result<T,typename E::value_type,EN>::Type,
          typename E::value_type>::FLAG;

  template <typename E,typename T,ExpressionOperationName EN>
  class __array_expression_sse_valid<E,Intrinsic<T>,EN> {
    public: static const bool FLAG;
  };

  template <typename E,typename T,ExpressionOperationName EN>
  const bool __array_expression_sse_valid<E,Intrinsic<T>,EN>::FLAG =
      E::_is_SSE_valid && __mono_sse_valid<typename E::value_type>::FLAG &&
      __same_type<
          typename __expression_result<typename E::value_type,T,EN>::Type,
          typename E::value_type>::FLAG;

}

#endif

