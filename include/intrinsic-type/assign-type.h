
#ifndef _Intrinsic_Type_Assign_Type_H_
#define _Intrinsic_Type_Assign_Type_H_

namespace mysimulator {

  template <typename T1, typename T2>
  struct _Assign {};

  template <typename T1>
  struct _Assign<long double,T1> { typedef long double Type; };

  template <>
  struct _Assign<double,double> { typedef double Type; };
  template <>
  struct _Assign<double,float> { typedef double Type; };
  template <>
  struct _Assign<double,long long> { typedef double Type; };
  template <>
  struct _Assign<double,unsigned long long> { typedef double Type; };
  template <>
  struct _Assign<double,int> { typedef double Type; };
  template <>
  struct _Assign<double,unsigned int> { typedef double Type; };
  template <>
  struct _Assign<double,long> { typedef double Type; };
  template <>
  struct _Assign<double,unsigned long> { typedef double Type; };
  template <>
  struct _Assign<double,short> { typedef double Type; };
  template <>
  struct _Assign<double,unsigned short> { typedef double Type; };
  template <>
  struct _Assign<double,char> { typedef double Type; };
  template <>
  struct _Assign<double,unsigned char> { typedef double Type; };

  template <>
  struct _Assign<float,float> { typedef float Type; };
  template <>
  struct _Assign<float,long long> { typedef float Type; };
  template <>
  struct _Assign<float,unsigned long long> { typedef float Type; };
  template <>
  struct _Assign<float,int> { typedef float Type; };
  template <>
  struct _Assign<float,unsigned int> { typedef float Type; };
  template <>
  struct _Assign<float,long> { typedef float Type; };
  template <>
  struct _Assign<float,unsigned long> { typedef float Type; };
  template <>
  struct _Assign<float,short> { typedef float Type; };
  template <>
  struct _Assign<float,unsigned short> { typedef float Type; };
  template <>
  struct _Assign<float,char> { typedef float Type; };
  template <>
  struct _Assign<float,unsigned char> { typedef float Type; };

  template <>
  struct _Assign<long long,long long> { typedef long long Type; };
  template <>
  struct _Assign<long long,int> { typedef long long Type; };
  template <>
  struct _Assign<long long,unsigned int> { typedef long long Type; };
  template <>
  struct _Assign<long long,long> { typedef long long Type; };
  template <>
  struct _Assign<long long,unsigned long> { typedef long long Type; };
  template <>
  struct _Assign<long long,short> { typedef long long Type; };
  template <>
  struct _Assign<long long,unsigned short> { typedef long long Type; };
  template <>
  struct _Assign<long long,char> { typedef long long Type; };
  template <>
  struct _Assign<long long,unsigned char> { typedef long long Type; };

  template <>
  struct _Assign<unsigned long long, unsigned long long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Assign<unsigned long long, unsigned int> {
    typedef unsigned int Type;
  };
  template <>
  struct _Assign<unsigned long long, unsigned long> {
    typedef unsigned long Type;
  };
  template <>
  struct _Assign<unsigned long long, unsigned short> {
    typedef unsigned short Type;
  };
  template <>
  struct _Assign<unsigned long long, unsigned char> {
    typedef unsigned char Type;
  };

  template <>
  struct _Assign<int,int> { typedef int Type; };
  template <>
  struct _Assign<int,long> { typedef int Type; };
  template <>
  struct _Assign<int,short> { typedef int Type; };
  template <>
  struct _Assign<int,unsigned short> { typedef int Type; };
  template <>
  struct _Assign<int,char> { typedef int Type; };
  template <>
  struct _Assign<int,unsigned char> { typedef int Type; };

  template <>
  struct _Assign<unsigned int,unsigned int> {typedef unsigned int Type;};
  template <>
  struct _Assign<unsigned int,unsigned long>{typedef unsigned int Type;};
  template <>
  struct _Assign<unsigned int,unsigned short> {
    typedef unsigned int Type;
  };
  template <>
  struct _Assign<unsigned int,unsigned char>{typedef unsigned int Type;};

  template <>
  struct _Assign<long,long> { typedef long Type; };
  template <>
  struct _Assign<long,int> { typedef long Type; };
  template <>
  struct _Assign<long,short> { typedef long Type; };
  template <>
  struct _Assign<long,unsigned short> { typedef long Type; };
  template <>
  struct _Assign<long,char> { typedef long Type; };
  template <>
  struct _Assign<long,unsigned char> { typedef long Type; };

  template <>
  struct _Assign<unsigned long,unsigned long> {
    typedef unsigned long Type;
  };
  template <>
  struct _Assign<unsigned long,unsigned int> {
    typedef unsigned long Type;
  };
  template <>
  struct _Assign<unsigned long,unsigned short> {
    typedef unsigned long Type;
  };
  template <>
  struct _Assign<unsigned long,unsigned char> {
    typedef unsigned long Type;
  };

  template <>
  struct _Assign<short,short> { typedef short Type; };
  template <>
  struct _Assign<short,char> { typedef short Type; };
  template <>
  struct _Assign<short,unsigned char> { typedef short Type; };

  template <>
  struct _Assign<unsigned short,unsigned short> {
    typedef unsigned short Type;
  };
  template <>
  struct _Assign<unsigned short,unsigned char> {
    typedef unsigned short Type;
  };

  template <>
  struct _Assign<char,char> { typedef char Type; };

  template <>
  struct _Assign<unsigned char,unsigned char> {
    typedef unsigned char Type;
  };

  template <>
  struct _Assign<bool,bool> { typedef bool Type; };
  template <>
  struct _Assign<bool,long long> { typedef bool Type; };
  template <>
  struct _Assign<bool,unsigned long long> { typedef bool Type; };
  template <>
  struct _Assign<bool,int> { typedef bool Type; };
  template <>
  struct _Assign<bool,unsigned int> { typedef bool Type; };
  template <>
  struct _Assign<bool,long> { typedef bool Type; };
  template <>
  struct _Assign<bool,unsigned long> { typedef bool Type; };
  template <>
  struct _Assign<bool,short> { typedef bool Type; };
  template <>
  struct _Assign<bool,unsigned short> { typedef bool Type; };
  template <>
  struct _Assign<bool,char> { typedef bool Type; };
  template <>
  struct _Assign<bool,unsigned char> { typedef bool Type; };

}

#endif

