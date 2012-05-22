
#ifndef _Basic_Data_Type_H_
#define _Basic_Data_Type_H_

namespace mysimulator {

  template <typename T>
  class DataType {};

}

#define _DataDEF_(T) \
  template <> class DataType<T> { public: typedef T Type; };

namespace mysimulator {

  _DataDEF_(double)

}

#undef _DataDEF_

namespace mysimulator {

  template <typename T> class ArrayNumeric;
  template <typename T> class DataType<ArrayNumeric<T> > {
    public: typedef typename DataType<T>::Type  Type;
  };

}

#endif

