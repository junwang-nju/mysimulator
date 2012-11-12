
#ifndef _Basic_Type_SSE_Valid_H_
#define _Basic_Type_SSE_Valid_H_

namespace mysimulator {

  template <typename T>
  class _mono_sse_valid { public: static const bool FLAG; };

  template <>
  const bool _mono_sse_valid<double>::FLAG = true;

  template <>
  const bool _mono_sse_valid<float>::FLAG = true;

  template <>
  const bool _mono_sse_valid<int>::FLAG = true;

}

#endif

