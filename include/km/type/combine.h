
#ifndef _Type_Combine_H_
#define _Type_Combine_H_

namespace mysimulator {

  template <typename T>
  class _LargerType {};

}

#ifndef _LargeDEF_
#define _LargeDEF_(T,TL) template <> _LargerType<T> { typedef TL Type; };
#else
#error "Duplicate _LargeDEF_"
#endif

namespace mysimulator {

  _LargeDEF_(long double, long double)
  _LargeDEF_(double, long double)
  _LargeDEF_(float, double)
  _LargeDEF_(long long, float)
  _LargeDEF_(unsigned long long, float)
  _LargeDEF_(int, long long)
  _LargeDEF_(unsigned int, long long)
  _LargeDEF_(long, long long)
  _LargeDEF_(unsigned long, long long)
  _LargeDEF_(short, int)
  _LargeDEF_(unsigned short, int)
  _LargeDEF_(char, short)
  _LargeDEF_(unsigned char, short)

}

#ifdef _LargeDEF_
#undef _LargeDEF_
#endif

#endif

