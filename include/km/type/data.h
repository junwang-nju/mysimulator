/**
 * @file data.h
 * @brief Object to Get Type of Internal Data of Array-Like Structure
 *
 * This is used for array-like objects. The GP enables the recursion of array.
 * Thus, the final result is the type which is not array-like.
 *
 * @author Jun | junwang.nju@gmai.com
 */

#ifndef _Type_Data_H_
#define _Type_Data_H_

namespace mysimulator {

  template <typename T>
  class DataType { public:  typedef T Type; };

  template <typename T> class ArrayData;
  template <typename T>
  class DataType<ArrayData<T> > {
    public:
      typedef typename DataType<T>::Type  Type;
  };

  template <typename T> class ArrayNumeric;
  template <typename T>
  class DataType<ArrayNumeric<T> > {
    public:
      typedef typename DataType<T>::Type  Type;
  };

  template <typename T> class Array2DNumeric;
  template <typename T>
  class DataType<Array2DNumeric<T> > {
    public:
      typedef typename DataType<T>::Type  Type;
  };

}

#endif

