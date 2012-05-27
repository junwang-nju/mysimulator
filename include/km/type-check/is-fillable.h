
#ifndef _Basic_Is_Fillable_H_
#define _Basic_Is_Fillable_H_

namespace mysimulator {

  template <typename T1,typename T2>
  class IsFillable {};

}

#ifndef _FillDEF_
#define _FillDEF_(T1,T2) \
  template <> class IsFillable<T1,T2> { \
    public: typedef IsFillable<T1,T2> Type; \
  };
#else
#error "Duplicate _FillDEF_"
#endif

namespace mysimulator {

  _FillDEF_(long double, long double)
  _FillDEF_(long double, double)
  _FillDEF_(long double, float)
  _FillDEF_(long double, long long)
  _FillDEF_(long double, unsigned long long)
  _FillDEF_(long double, int)
  _FillDEF_(long double, unsigned int)
  _FillDEF_(long double, long)
  _FillDEF_(long double, unsigned long)
  _FillDEF_(long double, short)
  _FillDEF_(long double, unsigned short)
  _FillDEF_(long double, char)
  _FillDEF_(long double, unsigned char)

  _FillDEF_(double, double)
  _FillDEF_(double, float)
  _FillDEF_(double, long long)
  _FillDEF_(double, unsigned long long)
  _FillDEF_(double, int)
  _FillDEF_(double, unsigned int)
  _FillDEF_(double, long)
  _FillDEF_(double, unsigned long)
  _FillDEF_(double, short)
  _FillDEF_(double, unsigned short)
  _FillDEF_(double, char)
  _FillDEF_(double, unsigned char)

  _FillDEF_(float, float)
  _FillDEF_(float, long long)
  _FillDEF_(float, unsigned long long)
  _FillDEF_(float, int)
  _FillDEF_(float, unsigned int)
  _FillDEF_(float, long)
  _FillDEF_(float, unsigned long)
  _FillDEF_(float, short)
  _FillDEF_(float, unsigned short)
  _FillDEF_(float, char)
  _FillDEF_(float, unsigned char)

  _FillDEF_(long long, long long)
  _FillDEF_(long long, int)
  _FillDEF_(long long, unsigned int)
  _FillDEF_(long long, long)
  _FillDEF_(long long, unsigned long)
  _FillDEF_(long long, short)
  _FillDEF_(long long, unsigned short)
  _FillDEF_(long long, char)
  _FillDEF_(long long, unsigned char)

  _FillDEF_(unsigned long long, unsigned long long)
  _FillDEF_(unsigned long long, unsigned int)
  _FillDEF_(unsigned long long, unsigned long)
  _FillDEF_(unsigned long long, unsigned short)
  _FillDEF_(unsigned long long, unsigned char)

  _FillDEF_(int, int)
  _FillDEF_(int, long)
  _FillDEF_(int, short)
  _FillDEF_(int, unsigned short)
  _FillDEF_(int, char)
  _FillDEF_(int, unsigned char)

  _FillDEF_(unsigned int, unsigned int)
  _FillDEF_(unsigned int, unsigned long)
  _FillDEF_(unsigned int, unsigned short)
  _FillDEF_(unsigned int, unsigned char)

  _FillDEF_(long, long)
  _FillDEF_(long, int)
  _FillDEF_(long, short)
  _FillDEF_(long, unsigned short)
  _FillDEF_(long, char)
  _FillDEF_(long, unsigned char)

  _FillDEF_(unsigned long, unsigned long)
  _FillDEF_(unsigned long, unsigned int)
  _FillDEF_(unsigned long, unsigned short)
  _FillDEF_(unsigned long, unsigned char)

  _FillDEF_(short, short)
  _FillDEF_(short, char)
  _FillDEF_(short, unsigned char)

  _FillDEF_(unsigned short, unsigned short)
  _FillDEF_(unsigned short, unsigned char)

  _FillDEF_(char, char)

  _FillDEF_(bool, bool)

}

#ifdef _FillDEF_
#undef _FillDEF_
#endif

#endif

