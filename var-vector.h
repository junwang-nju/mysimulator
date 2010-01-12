
/**
 * @file var-vector.h
 * @brief Vector with variable storage
 *
 * This file contains the declaration for the vector-like class with
 * variable storage. This kind of data structure is widely used, especially
 * for the cases that the size of data is unknown or is larger than
 * stack size. This file contains the methods to operate the internal data.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Variable_Vector_H_
#define _Variable_Vector_H_

#include "memory.h"
#include "ref-vector.h"

namespace std {

  /**
   * @brief the vector with variable storage
   *
   * This defines a vector-like data structure. The internal data could
   * be dynamically allocated. This resembles an array with variable
   * dimension information. This is the most popular data structure
   * used in simulation package. This object could be referred by a
   * refVector object.
   *
   * \a T
   *    The type of data in vector
   */
  template <typename T>
  class varVector : public referableVector<T> {

    public:

      /**
       * @brief alias for type of data
       */
      typedef T               DataType;

      /**
       * @brief alias for the vector type with variable storage
       */
      typedef varVector<T>    Type;

      /**
       * @brief alias for the vector type which could be referred to.
       *
       * This is the type of the parent object.
       */
      typedef referableVector<T>   ParentType;

      /**
       * @brief default initiator
       *
       * Just initiate the parent class with its default initiator.
       */
      varVector() : ParentType() {}

      /**
       * @brief the initiator with dimensional information
       *
       * Just initiate the parent class with default format (no parameter)
       * and allocate the internal data with dimensional information.
       *
       * @param [in] n
       *        The size of internal storage.
       */
      varVector(const uint& n) : ParentType() { allocate(n); }

      /**
       * @brief initiator from another varVector object
       *
       * This is prohibited and just pop up error.
       */
      varVector(const Type& v) { myError("vector copier is prohibited!"); }

      /**
       * @brief destructor
       *
       * Just clear the data with clear() method
       */
      ~varVector() {  clear(); }

      /**
       * @brief clear the internal data
       *
       * Just delete the memory corresponding to the data, and employ
       * the clear() function of the parent class. These operations
       * are only carried out when the internal storage is available.
       */
      void clear() {
        if(!this->isAvailable())  return;
        safe_delete(this->Data);
        static_cast<ParentType*>(this)->clear();
      }

      /**
       * @brief allocate based on dimension information
       *
       * As the first step, the table recording the reference relationship
       * is cleaned up. The internal memory is re-allocated. The corresponding
       * information is updated. When the size of internal storage is same
       * as the expectation before allocation, no newly allocations are
       * carried out.
       *
       * @param [in] n
       *        The expected dimension for the internal array
       *
       * @return the reference to the present object
       */
      Type& allocate(const uint& n) {
        this->rTable.clear();
        if(this->nData!=n) {
          safe_delete(this->Data);
          this->nData=n;
          this->Data=new T[this->nData];
          this->set_HeadTail();
        }
        return *this;
      }

      /**
       * @brief allocate with \c int type parameter.
       *
       * It is implemented by converting the \c int type value to a \c unsigned
       * \c int one as dimensional information.
       *
       * @param [in] n
       *        The \c int type value
       *
       * @return the reference to the present object
       */
      Type& allocate(const int& n) { return allocate(static_cast<uint>(n)); }

      /**
       * @brief allocate based on information of another VectorBase object
       *
       * This function uses the size information of the input VectorBase
       * object as the dimensional information.
       *
       * \a rT
       *    The type of data in input VectorBase object.
       *
       * @param [in] v
       *        The input VectorBase object with \a rT type data
       *
       * @return the reference to the present object
       */
      template <typename rT>
      Type& allocate(const VectorBase<rT>& v) { return allocate(v.size()); }

      template <typename vType>
      Type& Duplicate(const vType& v) { allocate(v).assign(v); return *this; }

      Type& operator=(const Type& v) { this->assign(v); return *this; }

      template <typename inputT>
      Type& operator=(const inputT& v) { this->assign(v); return *this; }

      template <typename inputT>
      Type& operator*=(const inputT& v) { this->scale(v); return *this; }

      template <typename inputT>
      Type& operator+=(const inputT& v) { this->shift(v); return *this; }

      virtual const char* type() { return "Variable Vector"; }

      Type& swap(Type& v) {
        T* tptr;
        uint tmn;
        tptr=this->Data;        this->Data=v.Data;            v.Data=tptr;
        tmn=this->nData;        this->nData=v.nData;          v.nData=tmn;
        this->set_HeadTail();
        v.set_HeadTail();
        this->rTable.swap(v.rTable);
        return *this;
      }

  };

  template <typename T>
  void swap(varVector<T>& va, varVector<T>& vb) { va.swap(vb); }

  template <typename T>
  istream& operator>>(istream& is, varVector<T>& v) {
    uint n;
    is>>n;
    v.allocate(n);
    for(uint i=0;i<n;++i) is>>v[i];
    return is;
  }

}

#endif
