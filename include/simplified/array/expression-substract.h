
#ifndef _Array_Expression_Substract_H_
#define _Array_Expression_Substract_H_

#include "basic/type/substract.h"
#include "basic/type/selector.h"
#include "array/expression.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArraySub
    : public ArrayExpression<
                ArraySub<EA,EB>,
                typename __dual_selector<typename EA::value_type,
                                         typename EB::value_type,
                                         __sub_flag>::Type> {

    public:

      static_assert(!__intrinsic_flag<EA>::FG && !__intrinsic_flag<EB>::FG,
                    "For intrinsic type, please use Intrinsic<T>!\n");

      typedef ArraySub<EA,EB>   Type;
      typedef typename __dual_selector<typename EA::value_type,
                                       typename EB::value_type,
                                       __sub_flag>::Type
              value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef EA const& const_referenceA;
      typedef EB const& const_referenceB;
      typedef EA const&& const_lreferenceA;
      typedef EB const&& const_lreferenceB;

    private:

      const_referenceA _A;
      const_referenceB _B;

    public:

      ArraySub(const_referenceA A,const_referenceB B) : _A(A),_B(B) {}
      ArraySub(const_referenceA A,const_lreferenceB B) : _A(A),_B(B) {}
      ArraySub(const_lreferenceA A,const_referenceB B) : _A(A),_B(B) {}
      ArraySub(const_lreferenceA A,const_lreferenceB B) : _A(A),_B(B) {}
      operator bool() const { return (bool)_A && (bool)_B; }
      size_type size() const { return _A.size()<_B.size()?_A.size():_B.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)_A[i] - (value_type)_B[i];
      }
      const_referenceA first()  const { return _A; }
      const_referenceB second() const { return _B; }

  };

  template <typename EA,typename EB>
  ArraySub<EA,EB> const operator-(const EA& a, const EB& b) {
    return ArraySub<EA,EB>(a,b);
  }

}

#include "basic/intrinsic.h"

namespace mysimulator {

  template <typename T,typename E>
  class ArraySub<Intrinsic<T>,E>
    : public ArrayExpression<
                ArraySub<Intrinsic<T>,E>,
                typename __dual_selector<T,typename E::value_type,
                                         __sub_flag>::Type> {

    public:

      typedef ArraySub<Intrinsic<T>,E>  Type;
      typedef
        typename __dual_selector<T,typename E::value_type,__sub_flag>::Type
        value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef T const& const_referenceA;
      typedef E const& const_referenceB;
      typedef Intrinsic<T> const& const_ireferenceA;
      typedef T const&& const_lreferenceA;
      typedef E const&& const_lreferenceB;
      typedef Intrinsic<T> const&& const_lireferenceA;

    private:

      const_referenceA  _A;
      const_referenceB  _B;

    public:

      ArraySub(const_referenceA A,const_referenceB B) : _A(A),_B(B) {}
      ArraySub(const_ireferenceA A,const_referenceB B) : _A(A),_B(B) {}
      ArraySub(const_lreferenceA A,const_referenceB B) : _A(A),_B(B) {}
      ArraySub(const_lireferenceA A,const_referenceB B) : _A(A),_B(B) {}
      ArraySub(const_referenceA A,const_lreferenceB B) : _A(A),_B(B) {}
      ArraySub(const_ireferenceA A,const_lreferenceB B) : _A(A),_B(B) {}
      ArraySub(const_lreferenceA A,const_lreferenceB B) : _A(A),_B(B) {}
      ArraySub(const_lireferenceA A,const_lreferenceB B) : _A(A),_B(B) {}
      operator bool() const { return (bool)_B; }
      size_type size() const { return _B.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)_A-(value_type)_B[i];
      }
      const_referenceA first()  const { return _A; }
      const_referenceB second() const { return _B; }

  };

  template <typename E,typename T>
  class ArraySub<E,Intrinsic<T>>
    : public ArrayExpression<
                ArraySub<E,Intrinsic<T>>,
                typename __dual_selector<typename E::value_type,T,
                                         __sub_flag>::Type> {

    public:

      typedef ArraySub<E,Intrinsic<T>>  Type;
      typedef
        typename __dual_selector<typename E::value_type,T,__sub_flag>::Type
        value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef E const& const_referenceA;
      typedef T const& const_referenceB;
      typedef Intrinsic<T> const& const_ireferenceB;
      typedef E const&& const_lreferenceA;
      typedef T const&& const_lreferenceB;
      typedef Intrinsic<T> const&& const_lireferenceB;

    private:

      const_referenceA  _A;
      const_referenceB  _B;

    public:

      ArraySub(const_referenceA A,const_referenceB B) : _A(A),_B(B) {}
      ArraySub(const_referenceA A,const_ireferenceB B) : _A(A),_B(B) {}
      ArraySub(const_referenceA A,const_lreferenceB B) : _A(A),_B(B) {}
      ArraySub(const_referenceA A,const_lireferenceB B) : _A(A),_B(B) {}
      ArraySub(const_lreferenceA A,const_referenceB B) : _A(A),_B(B) {}
      ArraySub(const_lreferenceA A,const_ireferenceB B) : _A(A),_B(B) {}
      ArraySub(const_lreferenceA A,const_lreferenceB B) : _A(A),_B(B) {}
      ArraySub(const_lreferenceA A,const_lireferenceB B) : _A(A),_B(B) {}
      operator bool() const { return (bool)_B; }
      size_type size() const { return _A.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)_A[i]-(value_type)_B;
      }
      const_referenceA first()  const { return _A; }
      const_referenceB second() const { return _B; }

  };

  template <typename T1,typename T2>
  class ArraySub<Intrinsic<T1>,Intrinsic<T2>>
    : public ArrayExpression<
                ArraySub<Intrinsic<T1>,Intrinsic<T2>>,
                typename __dual_selector<T1,T2,__sub_flag>::Type> {

    public:

      typedef ArraySub<Intrinsic<T1>,Intrinsic<T2>>   Type;
      typedef typename __dual_selector<T1,T2,__sub_flag>::Type  value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef T1 const& const_referenceA;
      typedef T2 const& const_referenceB;
      typedef Intrinsic<T1> const& const_ireferenceA;
      typedef Intrinsic<T2> const& const_ireferenceB;
      typedef T1 const&& const_lreferenceA;
      typedef T2 const&& const_lreferenceB;
      typedef Intrinsic<T1> const&& const_lireferenceA;
      typedef Intrinsic<T2> const&& const_lireferenceB;

    private:

      const_referenceA _A;
      const_referenceB _B;
      value_type _R;

    public:

      ArraySub(const_referenceA A,const_referenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_lreferenceA A,const_referenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_ireferenceA A,const_referenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_lireferenceA A,const_referenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_referenceA A,const_lreferenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_lreferenceA A,const_lreferenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_ireferenceA A,const_lreferenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_lireferenceA A,const_lreferenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_referenceA A,const_ireferenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_lreferenceA A,const_ireferenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_ireferenceA A,const_ireferenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_lireferenceA A,const_ireferenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_referenceA A,const_lireferenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_lreferenceA A,const_lireferenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_ireferenceA A,const_lireferenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      ArraySub(const_lireferenceA A,const_lireferenceB B)
        : _A(A),_B(B),_R((value_type)_A-(value_type)_B) {}
      operator bool() const { return true; }
      size_type size() const { return 0xFFFFFFFFU; }
      value_type operator[](size_type i) const { return _R; }
      const_referenceA first()  const { return _A; }
      const_referenceB second() const { return _B; }
      value_type result() const { return _R; }

  };

}

#endif

