
#ifndef _Type_Data_H_
#define _Type_Data_H_

namespace mysimulator {

  template <typename T>
  class DataType {};

}

#ifndef _DataDEF_
#define _DataDEF_(T) \
  template <> class DataType<T> { public: typedef T Type; };
#else
#error "Duplicate _DataDEF_"
#endif

namespace mysimulator {

  _DataDEF_(long double)
  _DataDEF_(double)
  _DataDEF_(float)
  _DataDEF_(long long)
  _DataDEF_(unsigned long long)
  _DataDEF_(int)
  _DataDEF_(unsigned int)
  _DataDEF_(long)
  _DataDEF_(unsigned long)
  _DataDEF_(short)
  _DataDEF_(unsigned short)
  _DataDEF_(char)
  _DataDEF_(unsigned char)
  _DataDEF_(bool)

}

#ifdef _DataDEF_
#undef _DataDEF_
#endif

#endif

