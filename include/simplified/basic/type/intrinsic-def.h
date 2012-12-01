
#ifndef _Basic_Type_Intrinsic_Define_H_
#define _Basic_Type_Intrinsic_Define_H_

#include "basic/type/intrinsic-check.h"

namespace mysimulator {

  template <typename T>
  class Intrinsic {

    public:

      static_assert( __intrinsic<T>::FLAG,
                     "The Type T is not a intrinsic type!\n" );

      typedef Intrinsic<T>   Type;
      typedef T   value_type;

      static const bool IsFloatingPoint;
      static const bool IsUnsigned;
      static const bool IsInteger;
      static const bool IsBool;

    private:

      value_type  _data;

    public:

      Intrinsic() : _data(0) {}
      Intrinsic(T const& d) : _data(d) {}
      Intrinsic(const Type& D) : _data(D._data) {}
      template <typename T1>
      Intrinsic(const T1& idata) : _data(idata) { typedef Intrinsic<T1> IType; }
      template <typename T1>
      Intrinsic(const Intrinsic<T1>& D) : _data(D._data) {}
      ~Intrinsic() { _data = 0; }

      Type& operator=(const Type& I) { _data=I._data; return *this; }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& I) { _data=I._data; return *this; }
      template <typename T1>
      Type& operator=(const T1& D) {
        typedef Intrinsic<T1> IType;
        _data=D;
        return *this;
      }

      operator bool() const { return true; }
      operator T&() { return (T&)_data; }
      operator T const&() const { return (T const&)_data; }
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
  const bool Intrinsic<T>::IsFloatingPoint = false;
  template <typename T>
  const bool Intrinsic<T>::IsUnsigned = false;
  template <typename T>
  const bool Intrinsic<T>::IsInteger =
      ! Intrinsic<T>::IsFloatingPoint && ! Intrinsic<T>::IsBool;
  template <typename T>
  const bool Intrinsic<T>::IsBool = false;

  template <>
  const bool LDouble::IsFloatingPoint = true;
  template <>
  const bool Double::IsFloatingPoint = true;
  template <>
  const bool Float::IsFloatingPoint = true;

  template <>
  const bool ULLong::IsUnsigned = true;
  template <>
  const bool UInt::IsUnsigned = true;
  template <>
  const bool ULong::IsUnsigned = true;
  template <>
  const bool UShort::IsUnsigned = true;
  template <>
  const bool UChar::IsUnsigned = true;

  template <>
  const bool Bool::IsBool = true;

}

#endif

