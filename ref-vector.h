
/**
 * @file ref-vector.h
 * @brief Vector to refer to another storage
 *
 * This file defines a data structure which refers to another vector-like
 * data structure. This kind of data structure is light-weight (without
 * allocation of data). It could be used to define aliases and set up
 * higher-order data structures.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Reference_Vector_H_
#define _Reference_Vector_H_

#include "referable-vector.h"

namespace std {

  /**
   * @brief the data structure referring to vector-like data structure
   *
   * This class uses the basic structure of VectorBase class. Its content
   * is a kind of reference to another vector-like data structure. To use
   * the VectorBase class as parent makes this class have the same interface
   * as regular vectors, though some kinds of operations are not defined.
   * to enable the validation of reference, a table is used to record
   * reference information.
   *
   * \a T
   *    The type of data in the related storage
   */
  template <typename T>
  class refVector : public VectorBase<T> {

    public:

      /**
       * @brief flag indicating if this object could be referred to
       *
       * Since the refVector object is different from regular vector (without
       * internal storage), it could not be referred to. This flag is
       * introduced as an indicator.
       */
      static const uint IsReferable;

      /**
       * @brief alias for the type of data in vector
       */
      typedef T             DataType;

      /**
       * @brief alias for the refVector class
       */
      typedef refVector<T>  Type;

      /**
       * @brief alias for the parent VectorBase class
       */
      typedef VectorBase<T> ParentType;

      /**
       * @brief the pointer to the table with reference information
       *
       * This pointer is used to point to the table in the object
       * which is referred by this refVector class. To use a pointer
       * may keep the synchronization of the reference information.
       */
      ReferTable<T>* pTable;

      /**
       * @brief the location in the table with reference information
       *
       * This variable records the the location (order) of the present
       * reference in the table with reference information.
       */
      int inTable;

      /**
       * @brief default initiator
       *
       * Just initiate the parent class with no parameters, and initiate
       * the pointer for reference table with NULL and set the location
       * with -1 indicating there are no targets.
       */
      refVector() : ParentType(), pTable(NULL), inTable(-1) {}

      /**
       * @brief initiator from another refVector object
       *
       * This is prohibited by popping up an error.
       *
       * @param [in] v
       *        The input refVector object
       */
      refVector(const Type& v) { myError("vector copier is prohibited!"); }

      /**
       * @brief destructor
       *
       * Just invoke the clear() method.
       */
      ~refVector() { clear(); }

      void clear() {
        static_cast<ParentType*>(this)->clear();
        pTable=NULL;
        inTable=-1;
      }

      Type& operator=(const Type& v) { this->assign(v); return *this; }

      template <typename inputT>
      Type& operator=(const inputT& v) { this->assign(v); return *this; }

      template <typename inputT>
      Type& operator*=(const inputT& v) { this->scale(v); return *this; }

      template <typename inputT>
      Type& operator+=(const inputT& v) { this->shift(v); return *this; }

      virtual const char* type() { return "Reference Vector"; }

      Type& refer(const referableVector<T>& v,
                  const uint& offset, const uint& sz) {
        assert(v.rTable.count()<ReferTable<T>::MaxRefInstance);
        assert(offset+sz<=v.size());
        if(this->isAvailable()) {
          if(inTable!=static_cast<int>(pTable->count())-1)
            pTable->refinst[inTable]=pTable->refinst[pTable->count()-1];
          pTable->dec();
          pTable=NULL;
          inTable=-1;
        }
        this->Data=const_cast<T*>(v.data()+offset);
        this->nData=sz;
        this->set_HeadTail();
        pTable=const_cast<ReferTable<T>*>(&(v.rTable));
        pTable->refinst[pTable->count()]=this;
        inTable=pTable->count();
        pTable->inc();
        return *this;
      }

      Type& refer(const referableVector<T>& v) {
        return refer(v,uZero,v.size());
      }

      Type& swap(Type& v) {
        T* tptr;
        uint m;
        tptr=this->Data;  this->Data=v.Data;    v.Data=tptr;
        m=this->nData;    this->nData=v.nData;  v.nData=m;
        this->set_HeadTail();
        v.set_HeadTail();
        ReferTable<T>* rptr;
        rptr=pTable;      pTable=v.pTable;      v.pTable=rptr;
        m=inTable;        inTable=v.inTable;    v.inTable=m;
        return *this;
      }

  };

  template <typename T>
  const uint refVector<T>::IsReferable=0;

  template <typename T>
  void swap(refVector<T>& va, refVector<T>& vb) { va.swap(vb); }

  template <typename T>
  istream& operator>>(istream& is, refVector<T>& v) {
    assert(v.isAvailable());
    uint n=v.size();
    for(uint i=0;i<n;++i)   is>>v[i];
    return is;
  }

}

#endif

