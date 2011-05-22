
#ifndef _Single_Operation_Type_H_
#define _Single_Operation_Type_H_

namespace mysimulator {

  template <typename T>
  struct _SingleOp {};

  template <> struct _SingleOp<long double> { typedef long double Type; };
  template <> struct _SingleOp<double> { typedef double Type; };
  template <> struct _SingleOp<float> { typedef float Type; };
  template <> struct _SingleOp<int> { typedef int Type; };
  template <> struct _SingleOp<unsigned int> { typedef unsigned int Type; };
  template <> struct _SingleOp<long> { typedef long Type; };
  template <> struct _SingleOp<unsigned long> { typedef unsigned long Type; };
  template <> struct _SingleOp<long long> { typedef long long Type; };
  template <> struct _SingleOp<unsigned long long> {
    typedef unsigned long long Type;
  };
  template <> struct _SingleOp<short> { typedef short Type; };
  template <> struct _SingleOp<unsigned short> { typedef unsigned short Type; };
  template <> struct _SingleOp<char> { typedef char Type; };
  template <> struct _SingleOp<unsigned char> { typedef unsigned char Type; };
  template <> struct _SingleOp<bool> { typedef bool Type; };
  template <> struct _SingleOp<void*> { typedef void* Type; };
  template <typename T> struct _SingleOp<T*> { typedef T* Type; };

}

#endif

