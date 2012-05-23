
#ifndef _Type_Data_H_
#define _Type_Data_H_

namespace mysimulator {

  template <typename T>
  class DataType { public:  typedef T Type; };

  template <typename T> class ArrayNumeric;
  template <typename T>
  class DataType<ArrayNumeric<T> > {
    public:
      typedef typename DataType<T>::Type  Type;
  };

}

#endif

