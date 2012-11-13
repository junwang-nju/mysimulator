
#ifndef _Basic_SSE_Valid_H_
#define _Basic_SSE_Valid_H_

namespace mysimulator {

  template <typename T>
  class __mono_sse_valid { public: static const bool FLAG; };

  template <>
  const bool __mono_sse_valid<double>::FLAG = true;

  template <>
  const bool __mono_sse_valid<float>::FLAG = true;

  template <>
  const bool __mono_sse_valid<int>::FLAG = true;

  template <>
  const bool __mono_sse_valid<long>::FLAG = true;

}

#endif

