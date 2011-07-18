
#ifndef _Intrinsic_Type_Reflection_Single_H_
#define _Intrinsic_Type_Reflection_Single_H_

#define _TYPE(type) typedef type Type
#define SINGLE_STRUCT(type) \
  template<> struct _Single<type> { _TYPE(type); }

namespace mysimulator {

  template <typename T>
  struct _Single {};

  //template <> struct _Single<long double> { _TYPE(long double); };
  SINGLE_STRUCT(long double);
  SINGLE_STRUCT(double);
  SINGLE_STRUCT(float);
  SINGLE_STRUCT(long long);
  SINGLE_STRUCT(unsigned long long);
  SINGLE_STRUCT(int);
  SINGLE_STRUCT(unsigned int);
  SINGLE_STRUCT(long);
  SINGLE_STRUCT(unsigned long);
  SINGLE_STRUCT(short);
  SINGLE_STRUCT(unsigned short);
  SINGLE_STRUCT(char);
  SINGLE_STRUCT(unsigned char);
  SINGLE_STRUCT(bool);
  template <typename T> struct _Single<T*> { typedef T* Type; };

}

#undef SINGLE_STRUCT
#undef _TYPE

#endif

