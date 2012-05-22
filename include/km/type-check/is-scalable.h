
#ifndef _Type_Check_IsScalable_H_
#define _Type_Check_IsScalable_H_

namespace mysimulator {

  template <typename T1,typename T2>
  class IsScalable {};

}

#ifndef _ScaleDEF_
#define _ScaleDEF_(T1,T2) \
  template <> class IsScalable<T1,T2> { public: IsScalable<T1,T2> Type; };
#else
#error "Duplicate _ScaleDEF_"
#endif

namespace mysimulator {

  _ScaleDEF_(long double, long double)
  _ScaleDEF_(long double, double)
  _ScaleDEF_(long double, float)
  _ScaleDEF_(long double, long long)
  _ScaleDEF_(long double, unsigned long long)
  _ScaleDEF_(long double, int)
  _ScaleDEF_(long double, unsigned int)
  _ScaleDEF_(long double, long)
  _ScaleDEF_(long double, unsigned long)
  _ScaleDEF_(long double, short)
  _ScaleDEF_(long double, unsigned short)
  _ScaleDEF_(long double, char)
  _ScaleDEF_(long double, unsigned char)

  _ScaleDEF_(double, double)
  _ScaleDEF_(double, float)
  _ScaleDEF_(double, long long)
  _ScaleDEF_(double, unsigned long long)
  _ScaleDEF_(double, int)
  _ScaleDEF_(double, unsigned int)
  _ScaleDEF_(double, long)
  _ScaleDEF_(double, unsigned long)
  _ScaleDEF_(double, short)
  _ScaleDEF_(double, unsigned short)
  _ScaleDEF_(double, char)
  _ScaleDEF_(double, unsigned char)

  _ScaleDEF_(float, float)
  _ScaleDEF_(float, long long)
  _ScaleDEF_(float, unsigned long long)
  _ScaleDEF_(float, int)
  _ScaleDEF_(float, unsigned int)
  _ScaleDEF_(float, long)
  _ScaleDEF_(float, unsigned long)
  _ScaleDEF_(float, short)
  _ScaleDEF_(float, unsigned short)
  _ScaleDEF_(float, char)
  _ScaleDEF_(float, unsigned char)

  _ScaleDEF_(long long, long long)
  _ScaleDEF_(long long, int)
  _ScaleDEF_(long long, unsigned int)
  _ScaleDEF_(long long, long)
  _ScaleDEF_(long long, unsigned long)
  _ScaleDEF_(long long, short)
  _ScaleDEF_(long long, unsigned short)
  _ScaleDEF_(long long, char)
  _ScaleDEF_(long long, unsigned char)

  _ScaleDEF_(unsigned long long, unsigned long long)
  _ScaleDEF_(unsigned long long, unsigned int)
  _ScaleDEF_(unsigned long long, unsigned long)
  _ScaleDEF_(unsigned long long, unsigned short)
  _ScaleDEF_(unsigned long long, unsigned char)

  _ScaleDEF_(int, int)
  _ScaleDEF_(int, long)
  _ScaleDEF_(int, short)
  _ScaleDEF_(int, unsigned short)
  _ScaleDEF_(int, char)
  _ScaleDEF_(int, unsigned char)

  _ScaleDEF_(unsigned int, unsigned int)
  _ScaleDEF_(unsigned int, unsigned long)
  _ScaleDEF_(unsigned int, unsigned short)
  _ScaleDEF_(unsigned int, unsigned char)

  _ScaleDEF_(long, int)
  _ScaleDEF_(long, long)
  _ScaleDEF_(long, short)
  _ScaleDEF_(long, unsigned short)
  _ScaleDEF_(long, char)
  _ScaleDEF_(long, unsigned char)

  _ScaleDEF_(unsigned long, unsigned int)
  _ScaleDEF_(unsigned long, unsigned long)
  _ScaleDEF_(unsigned long, unsigned short)
  _ScaleDEF_(unsigned long, unsigned char)

  _ScaleDEF_(short, short)
  _ScaleDEF_(short, char)
  _ScaleDEF_(short, unsigned char)

  _ScaleDEF_(unsigned short, unsigned short)
  _ScaleDEF_(unsigned short, unsigned char)

  _ScaleDEF_(char, char)

  _ScaleDEF_(unsigned char, unsigned char)

}

#ifdef _ScaleDEF_
#undef _ScaleDEF_
#endif

namespace mysimulator {

  template <typename T> class ArrayNumeric;

  template <typename T1,typename T2>
  class IsScalable<ArrayNumeric<T1>,T2> {
    public: typedef IsScalable<ArrayNumeric<T1>,T2>   Type;
  };

  template <typename T1,typename T2>
  class IsScalable<ArrayNumeric<T1>,ArrayNumeric<T2> > {
    public: IsScalable<ArrayNumeric<T1>,ArrayNumeric<T2> >    Type;
  };

}

#endif

