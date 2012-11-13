
#ifndef _Basic_SSE_Value_Type_H_
#define _Basic_SSE_Value_Type_H_

#ifndef __SSE4_1__
#error  "\nSSE4.1 is REQUIRED for following codes! use -msse4.1!\n"
#endif

#include <emmintrin.h>
#include <smmintrin.h>
#include "basic/sse/valid.h"

namespace mysimulator {

  template <typename T>
  class __sse_value {
    public:
      static_assert(__mono_sse_valid<T>::FLAG,
                    "Not SSE type matching this Type!\n");
  };

  template <>
  class __sse_value<double> { public: typedef __m128d   Type; };

  template <>
  class __sse_value<float> { public: typedef __m128    Type;  };

  template <>
  class __sse_value<int> { public: typedef __m128i    Type;   };

  template <>
  class __sse_value<long> { public: typedef __m128i    Type;  };

}

#endif

