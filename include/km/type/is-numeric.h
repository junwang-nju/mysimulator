
#ifndef _Type_IsNumeric_H_
#define _Type_IsNumeric_H_

namespace mysimulator {

  template <typename T>
  class IsNumeric { public: static const bool Flag; };

  template <typename T> const bool IsNumeric<T>::Flag=false;

}

#ifndef _NumDEF_
#define _NumDEF_(T) template <> const bool IsNumeric<T>::Flag=true;
#else
#error "Duplicate _NumDEF_"
#endif

namespace mysimulator {

  _NumDEF_(long double)
  _NumDEF_(double)
  _NumDEF_(float)
  _NumDEF_(long long)
  _NumDEF_(unsigned long long)
  _NumDEF_(int)
  _NumDEF_(unsigned int)
  _NumDEF_(long)
  _NumDEF_(unsigned long)
  _NumDEF_(short)
  _NumDEF_(unsigned short)
  _NumDEF_(char)
  _NumDEF_(unsigned char)

}

#ifdef _NumDEF_
#undef _NumDEF_
#endif

#endif

