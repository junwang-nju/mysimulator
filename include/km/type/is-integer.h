
#ifndef _Type_IsInteger_H_
#define _Type_IsInteger_H_

namespace mysimulator {

  template <typename T>
  class IsInteger { public: static const bool Flag; };

  template <typename T> const bool IsInteger<T>::Flag=false;

}

#ifndef _IntDEF_
#define _IntDEF_(T) template <> const bool IsInteger<T>::Flag=true;
#else
#error "Duplicate _IntDEF_"
#endif

namespace mysimulator {

  _IntDEF_(long long)
  _IntDEF_(unsigned long long)
  _IntDEF_(int)
  _IntDEF_(unsigned int)
  _IntDEF_(long)
  _IntDEF_(unsigned long)
  _IntDEF_(short)
  _IntDEF_(unsigned short)
  _IntDEF_(char)
  _IntDEF_(unsigned char)

}

#ifdef _IntDEF_
#undef _IntDEF_
#endif

#endif

