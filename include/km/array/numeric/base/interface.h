
#ifndef _Array_Numeric_Base_Interface_H_
#define _Array_Numeric_Base_Interface_H_

#include "array/base/interface.h"
#include "type/is-numeric.h"
#include "basic/sum.h"
#include "basic/abs-sum.h"

namespace mysimulator {

  template <typename T>
  class ArrayNumeric : public ArrayBase<T> {

    public:

      typedef ArrayNumeric<T>   Type;
      typedef ArrayBase<T>      ParentType;
      typedef typename IsNumeric<T>::Type NumericCheck;

      ArrayNumeric() : ParentType() {}
      ~ArrayNumeric() { Clear(*this); }

      typename DataType<ArrayNumeric<T> >::Type Summation() const {
        typedef typename IsSumable<T>::Type   SumCheck;
        typename DataType<ArrayNumeric<T> >::Type sum=0;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;) sum+=_Sum(*(p++));
        return sum;
      }
      typename DataType<ArrayNumeric<T> >::Type AbsSummation() const {
        typename DataType<ArrayNumeric<T> >::Type sum=0;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;) sum+=_AbsSum(*(p++));
        return sum;
      }
      // not checked
      template <typename T1>
      void Scale(const T1& fac) {
        typedef typename IsNumeric<T1>::Type T1NumericCheck;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;)  *(p++)*=fac;
      }

    private:

      ArrayNumeric(const Type&) {}
      Type& operator=(const Type&) {}

  };

  template <typename T>
  void Clear(ArrayNumeric<T>& A) { Clear(static_cast<ArrayBase<T>&>(A)); }

  template <typename T>
  typename DataType<ArrayNumeric<T> >::Type _Sum(const ArrayNumeric<T>& A) {
    return A.Summation();
  }

  template <typename T>
  typename DataType<ArrayNumeric<T> >::Type _AbsSum(const ArrayNumeric<T>& A) {
    return A.AbsSummation();
  }

}

#endif

