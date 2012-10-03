
#ifndef _Array_Expression_Sum_H_
#define _Array_Expression_Sum_H_

namespace mysimulator {

  template <typename EA,typename EB>
  class ArraySum  {};

  template <typename EA, typename EB>
  ArraySum<EA,EB> const operator+(const EA& a,const EB& b) {
    return ArraySum<EA,EB>(a,b);
  }

}

#include "array/expression.h"
#include "basic/type/sum.h"
#include "basic/type/selector.h"

namespace mysimulator {

  enum class ArrayFormat;
  template <typename T,ArrayFormat AF> class Array;

  template <typename T1,ArrayFormat AF1,typename T2,ArrayFormat AF2>
  class ArraySum<Array<T1,AF1>,Array<T2,AF2>>
    : public ArrayExpression<ArraySum<Array<T1,AF1>,Array<T2,AF2>>,
                             typename __dual_selector<T1,T2,__sum_flag>::Type> {

    public:

      typedef ArraySum<Array<T1,AF1>,Array<T2,AF2>>   Type;
      typedef typename __dual_selector<T1,T2,__sum_flag>::Type  value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef T1* pointer1;
      typedef T2* pointer2;

    private:

      Array<T1,AF1> const& _A;
      Array<T2,AF2> const& _B;

    public:

      ArraySum(Array<T1,AF1> const& A, Array<T2,AF2> const& B) : _A(A),_B(B) {}
      operator bool() const { return (bool)_A&&(bool)_B; }
      size_type size() const { return _A.size()<_B.size()?_A.size():_B.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)_A[i] + (value_type)_B[i];
      }
      pointer1 first()  const { return _A.head(); }
      pointer2 second() const { return _B.head(); }

  };

  template <typename T,ArrayFormat AF,
            template<typename,typename> class ArrayOp,typename EA,typename EB>
  class ArraySum<Array<T,AF>,ArrayOp<EA,EB>>
    : public ArrayExpression<
                ArraySum<Array<T,AF>,ArrayOp<EA,EB>>,
                typename __dual_selector<T,
                                         typename ArrayOp<EA,EB>::value_type,
                                         __sum_flag>::Type> {

    public:

      typedef ArraySum<Array<T,AF>,ArrayOp<EA,EB>>  Type;
      typedef
      typename __dual_selector<T,
                               typename ArraySum<EA,EB>::value_type,
                               __sum_flag>::Type
               value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef Array<T,AF> const& const_reference1;
      typedef ArrayOp<EA,EB> const& const_reference2;

    private:

      Array<T,AF> const& _A;
      ArrayOp<EA,EB> const& _B;

    public:

      ArraySum(Array<T,AF> const& A, ArrayOp<EA,EB> const& B) : _A(A),_B(B) {}
      operator bool() const { return (bool)_A && (bool)_B; }
      size_type size() const { return _A.size()<_B.size()?_A.size():_B.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)_A[i] + (value_type)_B[i];
      }
      const_reference1 first()  const { return _A; }
      const_reference2 second() const { return _B; }

  };

  template <template<typename,typename> class ArrayOp,typename EA,typename EB,
            typename T,ArrayFormat AF>
  class ArraySum<ArrayOp<EA,EB>,Array<T,AF>>
    : public ArrayExpression<
                ArraySum<ArrayOp<EA,EB>,Array<T,AF>>,
                typename __dual_selector<T,
                                         typename ArrayOp<EA,EB>::value_type,
                                         __sum_flag>::Type> {

    public:

      typedef ArraySum<ArrayOp<EA,EB>,Array<T,AF>>    Type;
      typedef
      typename __dual_selector<T,
                               typename ArraySum<EA,EB>::value_type,
                               __sum_flag>::Type
               value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef ArrayOp<EA,EB> const& const_reference1;
      typedef Array<T,AF> const& const_reference2;

    private:

      ArrayOp<EA,EB> const& _A;
      Array<T,AF> const& _B;

    public:

      ArraySum(ArrayOp<EA,EB> const& A,Array<T,AF> const& B) : _A(A),_B(B) {}
      operator bool() const { return (bool)_A && (bool)_B; }
      size_type size() const { return _A.size()<_B.size()?_A.size():_B.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)_A[i] + (value_type)_B[i];
      }
      const_reference1 first()  const { return _A; }
      const_reference2 second() const { return _B; }

  };

  template <template<typename,typename>class ArrayOp1,typename EA1,typename EB1,
            template<typename,typename>class ArrayOp2,typename EA2,typename EB2>
  class ArraySum<ArrayOp1<EA1,EB1>,ArrayOp2<EA2,EB2>>
    : public ArrayExpression<
             ArraySum<ArrayOp1<EA1,EB1>,ArrayOp2<EA2,EB2>>,
             typename __dual_selector<typename ArrayOp1<EA1,EB1>::value_type,
                                      typename ArrayOp2<EA2,EB2>::value_type,
                                      __sum_flag>::Type> {

    public:

      typedef ArraySum<ArrayOp1<EA1,EB1>,ArrayOp2<EA2,EB2>> Type;
      typedef
      typename __dual_selector<typename ArrayOp1<EA1,EB1>::value_type,
                               typename ArrayOp2<EA2,EB2>::value_type,
                               __sum_flag>::Type
               value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef ArrayOp1<EA1,EB1> const& const_reference1;
      typedef ArrayOp2<EA2,EB2> const& const_reference2;

    private:

      ArrayOp1<EA1,EB1> const& _A;
      ArrayOp2<EA2,EB2> const& _B;

    public:

      ArraySum(ArrayOp1<EA1,EB1> const& A,ArrayOp2<EA2,EB2> const& B)
        : _A(A),_B(B) {}
      operator bool() const { return (bool)_A && (bool)_B; }
      size_type size() const { return _A.size()<_B.size()?_A.size():_B.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)_A[i] + (value_type)_B[i];
      }
      const_reference1 first() const { return _A; }
      const_reference2 second() const { return _B; }

  };


}

#include "basic/type/intrinsic.h"

namespace mysimulator {

  template <typename T1,typename T2,ArrayFormat AF2>
  class ArraySum<T1,Array<T2,AF2>>
    : public ArrayExpression<ArraySum<T1,Array<T2,AF2>>,
                             typename __dual_selector<T1,T2,__sum_flag>::Type> {

    static_assert(__intrinsic_flag<T1>::FG,
                  "Only Intrinsic Type Permitted for this type!\n");

    public:

      typedef ArraySum<T1,Array<T2,AF2>>  Type;
      typedef typename __dual_selector<T1,T2,__sum_flag>::Type  value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef T1* pointer1;
      typedef T2* pointer2;

    private:

      T1 const& _A;
      Array<T2,AF2> const& _B;

    public:

      ArraySum(T1 const& A,Array<T2,AF2> const& B) : _A(A),_B(B) {}
      operator bool() const { return (bool)_B; }
      size_type size() const { return _B.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)_A+(value_type)_B[i];
      }
      pointer1 first()    const { return const_cast<pointer1>(&_A); }
      pointer2 second()   const { return _B.head(); }

  };

  template <typename T1,ArrayFormat AF1,typename T2>
  class ArraySum<Array<T1,AF1>,T2>
    : public ArrayExpression<ArraySum<Array<T1,AF1>,T2>,
                             typename __dual_selector<T1,T2,__sum_flag>::Type> {

    static_assert(__intrinsic_flag<T2>::FG,
                  "Only Intrinsic Type Permitted for this type!\n");

    public:

      typedef ArraySum<Array<T1,AF1>,T2>  Type;
      typedef typename __dual_selector<T1,T2,__sum_flag>::Type  value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef T1* pointer1;
      typedef T2* pointer2;

    private:

      Array<T1,AF1> const& _A;
      T2 const& _B;

    public:

      ArraySum(Array<T1,AF1> const& A,T2 const& B) : _A(A),_B(B) {}
      operator bool() const { return (bool)_A; }
      size_type size() const { return _A.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)_A[i] + (value_type)_B;
      }
      pointer1 first()  const { return _A.head(); }
      pointer2 second() const { return const_cast<pointer2>(&_B); }

  };

  template <typename T,
            template<typename,typename> class ArrayOp,typename EA,typename EB>
  class ArraySum<T,ArrayOp<EA,EB>>
    : public ArrayExpression<
                ArraySum<T,ArrayOp<EA,EB>>,
                typename __dual_selector<T,
                                         typename ArrayOp<EA,EB>::value_type,
                                         __sum_flag>::Type> {

    public:

      typedef ArraySum<T,ArrayOp<EA,EB>>  Type;
      typedef
      typename __dual_selector<T,
                               typename ArrayOp<EA,EB>::value_type,
                               __sum_flag>::Type
               value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef T* pointer1;
      typedef ArrayOp<EA,EB>  const& const_reference2;

    private:

      T const& _A;
      ArrayOp<EA,EB> const& _B;

    public:

      ArraySum(T const& A,ArrayOp<EA,EB> const& B) : _A(A),_B(B) {}
      operator bool() const { return (bool)_B; }
      size_type size() const { return _B.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)_A+(value_type)_B[i];
      }
      pointer1 first()    const { return const_cast<pointer1>(&_A); }
      const_reference2 second() const { return _B; }

  };

  template <template<typename,typename> class ArrayOp,typename EA,typename EB,
            typename T>
  class ArraySum<ArrayOp<EA,EB>,T>
    : public ArrayExpression<
                ArraySum<ArrayOp<EA,EB>,T>,
                typename __dual_selector<typename ArrayOp<EA,EB>::value_type,
                                         T,__sum_flag>::Type> {

    public:

      typedef ArraySum<ArrayOp<EA,EB>,T>  Type;
      typedef
      typename __dual_selector<typename ArrayOp<EA,EB>::value_type,
                               T,
                               __sum_flag>::Type
      value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef ArrayOp<EA,EB> const& const_reference1;
      typedef T* pointer2;

    private:

      ArrayOp<EA,EB>  const& _A;
      T const& _B;

    public:

      ArraySum(ArrayOp<EA,EB> const& A, T const& B) : _A(A),_B(B) {}
      operator bool() const { return (bool)_A; }
      size_type size() const { return _A.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)_A[i] + (value_type)_B;
      }
      const_reference1 first() const { return _A; }
      pointer2 second() const { return const_cast<pointer2>(&_B); }

  };

}

#endif

