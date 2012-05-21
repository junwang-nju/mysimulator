
#ifndef _Array_Numeric_Base_Interface_H_
#define _Array_Numeric_Base_Interface_H_

#include "array/base/interface.h"
#include "intrinsic-types/abs-value.h"

namespace mysimulator {

  template <typename T>
  class ArrayNumeric : public ArrayBase<T> {

    public:

      typedef ArrayNumeric<T>   Type;
      typedef ArrayBase<T>      ParentType;

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

    private:

      ArrayNumeric(const Type&) {}
      Type& operator=(const Type&) {}

  };

  template <typename T>
  void Clear(ArrayNumeric<T>& A) { Clear(static_cast<ArrayBase<T>&>(A)); }

}

#endif

