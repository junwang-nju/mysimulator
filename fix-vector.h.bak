
/**
 * @file fix-vector.h
 * @brief the vector with a fix dimension
 *
 * This file declares the vector with fix dimension. This kind of data
 * may be in stack and can be operated more efficiently. Since the
 * dimension is fixed, allocation and free methods cannot be defined
 * for this object.
 *
 * @author Jun Wang (junwang.nju@gamil.com)
 */

#ifndef _Fixed_Vector_H_
#define _Fixed_Vector_H_

#include "referable-vector.h"

namespace std {

  /**
   * @brief the vector class with fix dimension
   *
   * This is a class with fixed size. The memory in this object can be
   * accessed efficiently. Several methods are defined for this kind
   * of object. It is a child class of vector which could be referable.
   *
   * \a T
   *    The type of data in vector object
   *
   * \a ND
   *    The number of elements in the vector
   */
  template <typename T, uint ND>
  class fixVector : public referableVector<T> {

    private:

      /**
       * @brief the internal array
       */
      T runData[ND];

    public:

      /**
       * @brief alias of the type of data in the vector
       */
      typedef T                         DataType;

      /**
       * @brief alias for the vector with fixed dimension
       */
      typedef fixVector<T,ND>           Type;

      /**
       * @brief the parent vector which could be referred to
       */
      typedef referableVector<T>        ParentType;

      /**
       * @brief default initiator
       *
       * Just initiate the internal pointer with the internal array.
       * Then update the head and tail pointers.
       */
      fixVector() : ParentType() {
        this->Data=runData;
        this->nData=ND;
        this->set_HeadTail();
      }

      /**
       * @brief initiator with another fixVector object
       *
       * It is prohibited by popping up an error.
       *
       * @param [in] v
       *        The input fixVector object.
       */
      fixVector(const Type& v) { myError("vector copier is prohibited!"); }

      /**
       * @brief destructor
       *
       * It is implemented with the clear() method of the parent class.
       */
      ~fixVector() { this->clear(); }

      /**
       * @brief duplicate from another VectorBase object
       *
       * It is implemented with the assign() method of the parent class.
       *
       * @param [in] v
       *        The input VectorBase object
       *
       * @return the reference to the present object
       */
      Type& Duplicate(const VectorBase<T>& v) {
        this->assign(v);
        return *this;
      }

      /**
       * @brief copier from another fixVector object
       *
       * It is implemented with the assign() method of the parent class.
       *
       * @param [in] v
       *        The input VectorBase object
       *
       * @return the reference to the present object
       */
      Type& operator=(const Type& v) { this->assign(v); return *this; }

      /**
       * @brief copier from another \a inputT object
       *
       * It is implemented with the assign() method of the parent class.
       *
       * \a inputT
       *    The type of input object
       *
       * @param [in] v
       *        The input \a inputT object
       *
       * @return the reference to the present object
       */
      template <typename inputT>
      Type& operator=(const inputT& v) { this->assign(v); return *this; }

      /**
       * @brief scale with another \a inputT object
       *
       * It is implemented with the scale() method of the parent class.
       *
       * \a inputT
       *    The type of input object
       *
       * @param [in] v
       *        The input \a inputT object
       *
       * @return the reference to the present object
       */
      template <typename inputT>
      Type& operator*=(const inputT& v) { this->scale(v); return *this; }

      /**
       * @brief shift with another \a inputT object
       *
       * It is implemented with the shift() method of the parent class.
       *
       * \a inputT
       *    The type of input object
       *
       * @param [in] v
       *        The input \a inputT object
       *
       * @return the reference to the present object
       */
      template <typename inputT>
      Type& operator+=(const inputT& v) { this->shift(v); return *this; }

      /**
       * @brief the type string of fixVector object
       *
       * Just give out a string indicating a vector with fixed dimension.
       *
       * @return the const pointer to the type string
       */
      virtual const char* type() { return "Fixed Vector"; }

  };

  /**
   * @brief input vector from istream
   *
   * Just read the elements one by one.
   *
   * \a T
   *    The type of data in vector
   *
   * \a N
   *    The number of elements in vector (namely the dimension of vector)
   *
   * @param [in,out] is
   *        The input istream
   *
   * @param [out] v
   *        The vector to contain input data
   *
   * @return the istream after input
   */
  template <typename T, uint N>
  istream& operator>>(istream& is, fixVector<T,N>& v) {
    for(uint i=0;i<N;++i) is>>v[i];
    return is;
  }

}

#endif
