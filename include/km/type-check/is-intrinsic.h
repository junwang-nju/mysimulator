
#ifndef _Type_Check_IsIntrinsic_H_
#define _Type_Check_IsIntrinsic_H_

namespace mysimulator {

  template <typename T>
  class IsIntrinsic {};

}

#ifndef _IntrinsicDEF_
#define _IntrinsicDEF_(T) \
  template <> class IsIntrinsic<T> { public: typedef IsIntrinsic<T> Type; };
#else
#error "Duplicate _IntrinsicDEF_"
#endif

namespace mysimulator {

  _IntrinsicDEF_(long double)
  _IntrinsicDEF_(double)
  _IntrinsicDEF_(float)
  _IntrinsicDEF_(long long)
  _IntrinsicDEF_(unsigned long long)
  _IntrinsicDEF_(int)
  _IntrinsicDEF_(unsigned int)
  _IntrinsicDEF_(long)
  _IntrinsicDEF_(unsigned long)
  _IntrinsicDEF_(short)
  _IntrinsicDEF_(unsigned short)
  _IntrinsicDEF_(char)
  _IntrinsicDEF_(unsigned char)

  _IntrinsicDEF_(bool)

}

#ifdef _IntrinsicDEF_
#undef _IntrinsicDEF_
#endif

namespace mysimulator {

  template <typename T>
  class IsIntrinsic<T*> { public: typedef IsIntrinsic<T*> Type; };

}

#endif

