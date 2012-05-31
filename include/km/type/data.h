/**
 * @file data.h
 * @brief Object to Get Type of Internal Data of Array-Like Structure
 *
 * This is used for array-like objects. The GP enables the recursion of array.
 * Thus, the final result is the type which is not array-like.
 *
 * @note presently only the array type with numeric data is implemented 
 *       (including 1D and 2D). Further extension to other objects could
 *       be extended when necessary.
 *
 * @author Jun | junwang.nju@gmai.com
 */

#ifndef _Type_Data_H_
#define _Type_Data_H_

namespace mysimulator {

  /**
   * @class DataType
   * @brief the class to find out data type
   *
   * This is the default form. when input type T is not specialized (such as
   * ArrayNumeric), just give out the original type T as data type.
   */
  template <typename T>
  class DataType {
    public:
      /** @brief definition of default type trait (as input type T) */
      typedef T Type;
  };

  template <typename T> class ArrayNumeric;
  /** @brief specialization of DataType for ArrayNumeric
   *
   * Using intrisic type trait to get basic data type of the ArrayNumeric
   * object. This enables to design specific operations for certain type.
   */
  template <typename T>
  class DataType<ArrayNumeric<T> > {
    public:
      /** @brief definition of type trait Type
       *
       * Just apply the operation to get data type to the element type.
       * this enables recursions of type finding.
       */
      typedef typename DataType<T>::Type  Type;
  };

  template <typename T> class Array2DNumeric;
  /** @brief specialization of DataType for Array2DNumeric
   *
   * Using intrisic type trait to get basic data type of the Array2DNumeric
   * object. This enables to design specific operations for certain type.
   */
  template <typename T>
  class DataType<Array2DNumeric<T> > {
    public:
      /** @brief definition of type trait Type
       *
       * Just apply the operation to get data type to the element type.
       * this enables recursions of type finding.
       */
      typedef typename DataType<T>::Type  Type;
  };

}

#endif

