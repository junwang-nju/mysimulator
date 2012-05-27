
#ifndef _Type_Check_IsCopyable_H_
#define _Type_Check_IsCopyable_H_

namespace mysimulator {

  template <typename T1, typename T2>
  class IsCopyable {};

}

#ifndef _CopyDEF_
#define _CopyDEF_(T1,T2) \
  template <> class IsCopyable<T1,T2> { \
    public: typedef IsCopyable<T1,T2> Type; \
  };
#else
#error "Duplicate _CopyDEF_"
#endif

namespace mysimulator {

  _CopyDEF_(long double, long double)
  _CopyDEF_(long double, double)
  _CopyDEF_(long double, float)
  _CopyDEF_(long double, long long)
  _CopyDEF_(long double, unsigned long long)
  _CopyDEF_(long double, int)
  _CopyDEF_(long double, unsigned int)
  _CopyDEF_(long double, long)
  _CopyDEF_(long double, unsigned long)
  _CopyDEF_(long double, short)
  _CopyDEF_(long double, unsigned short)
  _CopyDEF_(long double, char)
  _CopyDEF_(long double, unsigned char)

  _CopyDEF_(double, double)
  _CopyDEF_(double, float)
  _CopyDEF_(double, long long)
  _CopyDEF_(double, unsigned long long)
  _CopyDEF_(double, int)
  _CopyDEF_(double, unsigned int)
  _CopyDEF_(double, long)
  _CopyDEF_(double, unsigned long)
  _CopyDEF_(double, short)
  _CopyDEF_(double, unsigned short)
  _CopyDEF_(double, char)
  _CopyDEF_(double, unsigned char)

  _CopyDEF_(float, float)
  _CopyDEF_(float, long long)
  _CopyDEF_(float, unsigned long long)
  _CopyDEF_(float, int)
  _CopyDEF_(float, unsigned int)
  _CopyDEF_(float, long)
  _CopyDEF_(float, unsigned long)
  _CopyDEF_(float, short)
  _CopyDEF_(float, unsigned short)
  _CopyDEF_(float, char)
  _CopyDEF_(float, unsigned char)

  _CopyDEF_(long long, long long)
  _CopyDEF_(long long, int)
  _CopyDEF_(long long, unsigned int)
  _CopyDEF_(long long, long)
  _CopyDEF_(long long, unsigned long)
  _CopyDEF_(long long, short)
  _CopyDEF_(long long, unsigned short)
  _CopyDEF_(long long, char)
  _CopyDEF_(long long, unsigned char)

  _CopyDEF_(unsigned long long, unsigned long long)
  _CopyDEF_(unsigned long long, unsigned int)
  _CopyDEF_(unsigned long long, unsigned long)
  _CopyDEF_(unsigned long long, unsigned short)
  _CopyDEF_(unsigned long long, unsigned char)

  _CopyDEF_(int, int)
  _CopyDEF_(int, long)
  _CopyDEF_(int, short)
  _CopyDEF_(int, unsigned short)
  _CopyDEF_(int, char)
  _CopyDEF_(int, unsigned char)

  _CopyDEF_(unsigned int, unsigned int)
  _CopyDEF_(unsigned int, unsigned long)
  _CopyDEF_(unsigned int, unsigned short)
  _CopyDEF_(unsigned int, unsigned char)

  _CopyDEF_(long, long)
  _CopyDEF_(long, int)
  _CopyDEF_(long, short)
  _CopyDEF_(long, unsigned short)
  _CopyDEF_(long, char)
  _CopyDEF_(long, unsigned char)

  _CopyDEF_(unsigned long, unsigned long)
  _CopyDEF_(unsigned long, unsigned int)
  _CopyDEF_(unsigned long, unsigned short)
  _CopyDEF_(unsigned long, unsigned char)

  _CopyDEF_(short, short)
  _CopyDEF_(short, char)
  _CopyDEF_(short, unsigned char)

  _CopyDEF_(unsigned short, unsigned short)
  _CopyDEF_(unsigned short, unsigned char)

  _CopyDEF_(char, char)

  _CopyDEF_(unsigned char, unsigned char)

  _CopyDEF_(bool, bool)
  _CopyDEF_(bool, long long)
  _CopyDEF_(bool, unsigned long long)
  _CopyDEF_(bool, int)
  _CopyDEF_(bool, unsigned int)
  _CopyDEF_(bool, long)
  _CopyDEF_(bool, unsigned long)
  _CopyDEF_(bool, short)
  _CopyDEF_(bool, unsigned short)
  _CopyDEF_(bool, char)
  _CopyDEF_(bool, unsigned char)

}

#ifdef _CopyDEF_
#undef _CopyDEF_
#endif

namespace mysimulator {

  template <typename T>
  class IsCopyable<T*,T*> {
    public: typedef IsCopyable<T*,T*>   Type;
  };

  template <typename T>
  class IsCopyable<void*,T*> {
    public: typedef IsCopyable<void*,T*>  Type;
  };

  template <typename T>
  class IsCopyable<T*,void*> {
    public: typedef IsCopyable<T*,void*>  Type;
  };

  template <typename T> class ArrayData;
  template <typename T1, typename T2>
  class IsCopyable<ArrayData<T1>,ArrayData<T2> > {
    public: typedef IsCopyable<ArrayData<T1>,ArrayData<T2> >    Type;
  };

}

#endif

