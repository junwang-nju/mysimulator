
#ifndef _Array_Numeric_Base_Interface_H_
#define _Array_Numeric_Base_Interface_H_

#include "array/base/interface.h"
#include "intrinsic-types/abs-value.h"
#include "type-check/is-numeric.h"

namespace mysimulator {

  template <typename T>
  class ArrayNumeric : public ArrayBase<T> {

    public:

      typedef ArrayNumeric<T>   Type;
      typedef ArrayBase<T>      ParentType;
      typedef typename IsNumeric<T>::Type NumericCheck;

      ArrayNumeric() : ParentType() {}
      ~ArrayNumeric() { Clear(*this); }

      T Summation() const {
        T sum=0;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;) sum+=*(p++);
        return sum;
      }
      T AbsSummation() const {
        T sum=0;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;) sum+=absval(*(p++));
        return sum;
      }
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

}

#endif

