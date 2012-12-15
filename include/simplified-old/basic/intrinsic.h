
#ifndef _Basic_Intrinsic_H_
#define _Basic_Intrinsic_H_

#include "basic/type/intrinsic.h"

namespace mysimulator {

  template <typename T>
  class Intrinsic {

    public:

      static_assert(__intrinsic_flag<T>::FG,
                    "The Type T is not an intrinsic Type!\n");
      typedef Intrinsic<T>  Type;
      typedef T value_type;

      static const bool IsFloatPoint;
      static const bool IsUnsigned;
      static const bool IsInteger;
      static const bool IsBool;

    private:

      value_type _data;

    public:

      Intrinsic() : _data(0) {}
      template <typename T1> Intrinsic(const T1& idata) : _data(idata) {}
      Intrinsic(const T& d) : _data(d) {}
      ~Intrinsic() { _data=0; }

      operator T&() { return static_cast<T&>(_data); }
      operator T const&() const { return static_cast<const T&>(_data); }
      Type& operator=(const Type& D) { _data=D._data; return *this; }
      T* operator &() { return &_data; }
      const T* operator &() const { return &_data; }

  };

  typedef Intrinsic<long double>          LDouble;
  typedef Intrinsic<double>               Double;
  typedef Intrinsic<float>                Float;
  typedef Intrinsic<long long>            LLong;
  typedef Intrinsic<unsigned long long>   ULLong;
  typedef Intrinsic<int>                  Int;
  typedef Intrinsic<unsigned int>         UInt;
  typedef Intrinsic<long>                 Long;
  typedef Intrinsic<unsigned long>        ULong;
  typedef Intrinsic<short>                Short;
  typedef Intrinsic<unsigned short>       UShort;
  typedef Intrinsic<char>                 Char;
  typedef Intrinsic<unsigned char>        UChar;
  typedef Intrinsic<bool>                 Bool;

  template <typename T>
  const bool Intrinsic<T>::IsFloatPoint=false;

  template <typename T>
  const bool Intrinsic<T>::IsUnsigned=false;

  template <typename T>
  const bool Intrinsic<T>::IsBool=false;

  template<> const bool LDouble::IsFloatPoint=true;
  template<> const bool Double::IsFloatPoint=true;
  template<> const bool Float::IsFloatPoint=true;

  template<> const bool ULLong::IsUnsigned=true;
  template<> const bool UInt::IsUnsigned=true;
  template<> const bool ULong::IsUnsigned=true;
  template<> const bool UShort::IsUnsigned=true;
  template<> const bool UChar::IsUnsigned=true;

  template<> const bool Bool::IsBool=true;

  template <typename T>
  const bool Intrinsic<T>::IsInteger=!Intrinsic<T>::IsFloatPoint &&
                                     !Intrinsic<T>::IsBool;

}

#include "basic/type/selector.h"
#include "basic/type/sum.h"

namespace mysimulator {

  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>
  operator+(Intrinsic<T1> const& A,Intrinsic<T2> const& B) {
    typedef typename __dual_selector<T1,T2,__sum_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)+((value_type)B));
  }
  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>
  operator+(Intrinsic<T1> const& A,Intrinsic<T2> const&& B) {
    typedef typename __dual_selector<T1,T2,__sum_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)+((value_type)B));
  }
  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>
  operator+(Intrinsic<T1> const&& A,Intrinsic<T2> const& B) {
    typedef typename __dual_selector<T1,T2,__sum_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)+((value_type)B));
  }
  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>
  operator+(Intrinsic<T1> const&& A,Intrinsic<T2> const&& B) {
    typedef typename __dual_selector<T1,T2,__sum_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)+((value_type)B));
  }

}

#include "basic/type/substract.h"

namespace mysimulator {

  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__sub_flag>::Type>
  operator-(Intrinsic<T1> const& A,Intrinsic<T2> const& B) {
    typedef typename __dual_selector<T1,T2,__sub_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)-((value_type)B));
  }
  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__sub_flag>::Type>
  operator-(Intrinsic<T1> const&& A,Intrinsic<T2> const& B) {
    typedef typename __dual_selector<T1,T2,__sub_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)-((value_type)B));
  }
  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__sub_flag>::Type>
  operator-(Intrinsic<T1> const& A,Intrinsic<T2> const&& B) {
    typedef typename __dual_selector<T1,T2,__sub_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)-((value_type)B));
  }
  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__sub_flag>::Type>
  operator-(Intrinsic<T1> const&& A,Intrinsic<T2> const&& B) {
    typedef typename __dual_selector<T1,T2,__sub_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)-((value_type)B));
  }

}

#include "basic/type/multiple.h"

namespace mysimulator {

  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__mul_flag>::Type>
  operator*(Intrinsic<T1> const& A, Intrinsic<T2> const& B) {
    typedef typename __dual_selector<T1,T2,__mul_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)*((value_type)B));
  }
  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__mul_flag>::Type>
  operator*(Intrinsic<T1> const&& A, Intrinsic<T2> const& B) {
    typedef typename __dual_selector<T1,T2,__mul_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)*((value_type)B));
  }
  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__mul_flag>::Type>
  operator*(Intrinsic<T1> const& A, Intrinsic<T2> const&& B) {
    typedef typename __dual_selector<T1,T2,__mul_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)*((value_type)B));
  }
  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__mul_flag>::Type>
  operator*(Intrinsic<T1> const&& A, Intrinsic<T2> const&& B) {
    typedef typename __dual_selector<T1,T2,__mul_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)*((value_type)B));
  }

}

#include "basic/type/divide.h"

namespace mysimulator {

  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__div_flag>::Type>
  operator/(Intrinsic<T1> const& A, Intrinsic<T2> const& B) {
    typedef typename __dual_selector<T1,T2,__div_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)/((value_type)B));
  }
  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__div_flag>::Type>
  operator/(Intrinsic<T1> const& A, Intrinsic<T2> const&& B) {
    typedef typename __dual_selector<T1,T2,__div_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)/((value_type)B));
  }
  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__div_flag>::Type>
  operator/(Intrinsic<T1> const&& A, Intrinsic<T2> const& B) {
    typedef typename __dual_selector<T1,T2,__div_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)/((value_type)B));
  }
  template <typename T1,typename T2>
  Intrinsic<typename __dual_selector<T1,T2,__div_flag>::Type>
  operator/(Intrinsic<T1> const&& A, Intrinsic<T2> const&& B) {
    typedef typename __dual_selector<T1,T2,__div_flag>::Type value_type;
    return Intrinsic<value_type>(((value_type)A)/((value_type)B));
  }

}

#endif

