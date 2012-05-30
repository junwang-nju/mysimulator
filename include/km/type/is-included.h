
#ifndef _Type_IsIncluded_H_
#define _Type_IsIncluded_H_

namespace mysimulator {

  template <typename T1, typename T2>
  class IsIncluded { public: static const bool Flag; };

  template <typename T1, typename T2>
  const bool IsIncluded<T1,T2>::Flag=false;

}

#ifndef _IncDEF_
#define _IncDEF_(T1,T2) \
  template <> const bool IsIncluded<T1,T2>::Flag=true;
#else
#error "Duplicate _IncDEF_"
#endif

namespace mysimulator {

  _IncDEF_(long double, long double)
  _IncDEF_(long double, double)
  _IncDEF_(long double, float)
  _IncDEF_(long double, long long)
  _IncDEF_(long double, unsigned long long)
  _IncDEF_(long double, int)
  _IncDEF_(long double, unsigned int)
  _IncDEF_(long double, long)
  _IncDEF_(long double, unsigned long)
  _IncDEF_(long double, short)
  _IncDEF_(long double, unsigned short)
  _IncDEF_(long double, char)
  _IncDEF_(long double, unsigned char)

  _IncDEF_(double, double)

}

#ifdef _IncDEF_
#undef _IncDEF_
#endif

#endif

