
#ifndef _Intrinsic_Type_Operation_Type_H_
#define _Intrinsic_Type_Operation_Type_H_

namespace mysimulator {

  template <typename Ta, typename Tb>
  struct _Operation {};

  template <>
  struct _Operation<long double,long double> { typedef long double Type; };
  template <>
  struct _Operation<long double,double> { typedef long double Type; };
  template <>
  struct _Operation<long double,float> { typedef long double Type; };
  template <>
  struct _Operation<long double,long long> { typedef long double Type; };
  template <>
  struct _Operation<long double,unsigned long long> {typedef long double Type;};
  template <>
  struct _Operation<long double,int> { typedef long double Type; };
  template <>
  struct _Operation<long double,unsigned int> { typedef long double Type; };
  template <>
  struct _Operation<long double,long> { typedef long double Type; };
  template <>
  struct _Operation<long double,unsigned long> { typedef long double Type; };
  template <>
  struct _Operation<long double,short> { typedef long double Type; };
  template <>
  struct _Operation<long double,unsigned short> { typedef long double Type; };
  template <>
  struct _Operation<long double,char> { typedef long double Type; };
  template <>
  struct _Operation<long double,unsigned char> { typedef long double Type; };

  template <>
  struct _Operation<double,long double> { typedef long double Type; };
  template <>
  struct _Operation<double,double> { typedef double Type; };
  template <>
  struct _Operation<double,float> { typedef double Type; };
  template <>
  struct _Operation<double,long long> { typedef double Type; };
  template <>
  struct _Operation<double,unsigned long long>{ typedef double Type; };
  template <>
  struct _Operation<double,int> { typedef double Type; };
  template <>
  struct _Operation<double,unsigned int> { typedef double Type; };
  template <>
  struct _Operation<double,long> { typedef double Type; };
  template <>
  struct _Operation<double,unsigned long> { typedef double Type; };
  template <>
  struct _Operation<double,short> { typedef double Type; };
  template <>
  struct _Operation<double,unsigned short> { typedef double Type; };
  template <>
  struct _Operation<double,char> { typedef double Type; };
  template <>
  struct _Operation<double,unsigned char> { typedef double Type; };

  template <>
  struct _Operation<float,long double> { typedef long double Type; };
  template <>
  struct _Operation<float,double> { typedef double Type; };
  template <>
  struct _Operation<float,float> { typedef double Type; };
  template <>
  struct _Operation<float,long long> { typedef float Type; };
  template <>
  struct _Operation<float,unsigned long long>{ typedef float Type; };
  template <>
  struct _Operation<float,int> { typedef float Type; };
  template <>
  struct _Operation<float,unsigned int> { typedef float Type; };
  template <>
  struct _Operation<float,long> { typedef float Type; };
  template <>
  struct _Operation<float,unsigned long> { typedef float Type; };
  template <>
  struct _Operation<float,short> { typedef float Type; };
  template <>
  struct _Operation<float,unsigned short> { typedef float Type; };
  template <>
  struct _Operation<float,char> { typedef float Type; };
  template <>
  struct _Operation<float,unsigned char> { typedef float Type; };

  template <>
  struct _Operation<long long,long double> { typedef long double Type; };
  template <>
  struct _Operation<long long,double> { typedef double Type; };
  template <>
  struct _Operation<long long,float> { typedef float Type; };
  template <>
  struct _Operation<long long,long long> { typedef long long Type; };
  template <>
  struct _Operation<long long,unsigned long long>{
    typedef unsigned long long Type;
  };
  template <>
  struct _Operation<long long,int> { typedef long long Type; };
  template <>
  struct _Operation<long long,unsigned int> { typedef long long Type; };
  template <>
  struct _Operation<long long,long> { typedef long long Type; };
  template <>
  struct _Operation<long long,unsigned long> { typedef long long Type; };
  template <>
  struct _Operation<long long,short> { typedef long long Type; };
  template <>
  struct _Operation<long long,unsigned short> { typedef long long Type; };
  template <>
  struct _Operation<long long,char> { typedef long long Type; };
  template <>
  struct _Operation<long long,unsigned char> { typedef long long Type; };

  template <>
  struct _Operation<unsigned long long,long double> {typedef long double Type;};
  template <>
  struct _Operation<unsigned long long,double> { typedef double Type; };
  template <>
  struct _Operation<unsigned long long,float> { typedef float Type; };
  template <>
  struct _Operation<unsigned long long,long long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Operation<unsigned long long,unsigned long long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Operation<unsigned long long,int>{ typedef unsigned long long Type; };
  template <>
  struct _Operation<unsigned long long,unsigned int> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Operation<unsigned long long,long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Operation<unsigned long long,unsigned long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Operation<unsigned long long,short> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Operation<unsigned long long,unsigned short> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Operation<unsigned long long,char> {typedef unsigned long long Type;};
  template <>
  struct _Operation<unsigned long long,unsigned char> {
    typedef unsigned long long Type;
  };

  template <>
  struct _Operation<int,long double> { typedef long double Type; };
  template <>
  struct _Operation<int,double> { typedef double Type; };
  template <>
  struct _Operation<int,float> { typedef float Type; };
  template <>
  struct _Operation<int,long long> { typedef long long Type; };
  template <>
  struct _Operation<int,unsigned long long>{ typedef unsigned long long Type; };
  template <>
  struct _Operation<int,int> { typedef int Type; };
  template <>
  struct _Operation<int,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Operation<int,long> { typedef int Type; };
  template <>
  struct _Operation<int,unsigned long> { typedef unsigned long Type; };
  template <>
  struct _Operation<int,short> { typedef int Type; };
  template <>
  struct _Operation<int,unsigned short> { typedef int Type; };
  template <>
  struct _Operation<int,char> { typedef int Type; };
  template <>
  struct _Operation<int,unsigned char> { typedef int Type; };

  template <>
  struct _Operation<unsigned int,long double> { typedef long double Type; };
  template <>
  struct _Operation<unsigned int,double> { typedef double Type; };
  template <>
  struct _Operation<unsigned int,float> { typedef float Type; };
  template <>
  struct _Operation<unsigned int,long long> { typedef long long Type; };
  template <>
  struct _Operation<unsigned int,unsigned long long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Operation<unsigned int,int> { typedef unsigned int Type; };
  template <>
  struct _Operation<unsigned int,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Operation<unsigned int,long> { typedef unsigned int Type; };
  template <>
  struct _Operation<unsigned int,unsigned long> { typedef unsigned long Type; };
  template <>
  struct _Operation<unsigned int,short> { typedef unsigned int Type; };
  template <>
  struct _Operation<unsigned int,unsigned short> { typedef unsigned int Type; };
  template <>
  struct _Operation<unsigned int,char> { typedef unsigned int Type; };
  template <>
  struct _Operation<unsigned int,unsigned char> { typedef unsigned int Type; };

  template <>
  struct _Operation<long,long double> { typedef long double Type; };
  template <>
  struct _Operation<long,double> { typedef double Type; };
  template <>
  struct _Operation<long,float> { typedef float Type; };
  template <>
  struct _Operation<long,long long> { typedef long long Type; };
  template <>
  struct _Operation<long,unsigned long long> {typedef unsigned long long Type;};
  template <>
  struct _Operation<long,int> { typedef int Type; };
  template <>
  struct _Operation<long,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Operation<long,long> { typedef long Type; };
  template <>
  struct _Operation<long,unsigned long> { typedef unsigned long Type; };
  template <>
  struct _Operation<long,short> { typedef long Type; };
  template <>
  struct _Operation<long,unsigned short> { typedef long Type; };
  template <>
  struct _Operation<long,char> { typedef long Type; };
  template <>
  struct _Operation<long,unsigned char> { typedef long Type; };

  template <>
  struct _Operation<unsigned long,long double> { typedef long double Type; };
  template <>
  struct _Operation<unsigned long,double> { typedef double Type; };
  template <>
  struct _Operation<unsigned long,float> { typedef float Type; };
  template <>
  struct _Operation<unsigned long,long long> { typedef long long Type; };
  template <>
  struct _Operation<unsigned long,unsigned long long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Operation<unsigned long,int> { typedef unsigned long Type; };
  template <>
  struct _Operation<unsigned long,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Operation<unsigned long,long> { typedef unsigned long Type; };
  template <>
  struct _Operation<unsigned long,unsigned long>{ typedef unsigned long Type; };
  template <>
  struct _Operation<unsigned long,short> { typedef unsigned long Type; };
  template <>
  struct _Operation<unsigned long,unsigned short> {typedef unsigned long Type;};
  template <>
  struct _Operation<unsigned long,char> { typedef unsigned long Type; };
  template <>
  struct _Operation<unsigned long,unsigned char>{ typedef unsigned long Type; };

  template <>
  struct _Operation<short,long double> { typedef long double Type; };
  template <>
  struct _Operation<short,double> { typedef double Type; };
  template <>
  struct _Operation<short,float> { typedef float Type; };
  template <>
  struct _Operation<short,long long> { typedef long long Type; };
  template <>
  struct _Operation<short,unsigned long long>{typedef unsigned long long Type;};
  template <>
  struct _Operation<short,int> { typedef int Type; };
  template <>
  struct _Operation<short,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Operation<short,long> { typedef long Type; };
  template <>
  struct _Operation<short,unsigned long> { typedef unsigned long Type; };
  template <>
  struct _Operation<short,short> { typedef short Type; };
  template <>
  struct _Operation<short,unsigned short> { typedef unsigned short Type; };
  template <>
  struct _Operation<short,char> { typedef short Type; };
  template <>
  struct _Operation<short,unsigned char> { typedef short Type; };

  template <>
  struct _Operation<unsigned short,long double> { typedef long double Type; };
  template <>
  struct _Operation<unsigned short,double> { typedef double Type; };
  template <>
  struct _Operation<unsigned short,float> { typedef float Type; };
  template <>
  struct _Operation<unsigned short,long long> { typedef long long Type; };
  template <>
  struct _Operation<unsigned short,unsigned long long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Operation<unsigned short,int> { typedef int Type; };
  template <>
  struct _Operation<unsigned short,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Operation<unsigned short,long> { typedef long Type; };
  template <>
  struct _Operation<unsigned short,unsigned long> {typedef unsigned long Type;};
  template <>
  struct _Operation<unsigned short,short> { typedef unsigned short Type; };
  template <>
  struct _Operation<unsigned short,unsigned short> {
    typedef unsigned short Type;
  };
  template <>
  struct _Operation<unsigned short,char> { typedef unsigned short Type; };
  template <>
  struct _Operation<unsigned short,unsigned char>{typedef unsigned short Type;};

  template <>
  struct _Operation<char,long double> { typedef long double Type; };
  template <>
  struct _Operation<char,double> { typedef double Type; };
  template <>
  struct _Operation<char,float> { typedef float Type; };
  template <>
  struct _Operation<char,long long> { typedef long long Type; };
  template <>
  struct _Operation<char,unsigned long long> {typedef unsigned long long Type;};
  template <>
  struct _Operation<char,int> { typedef int Type; };
  template <>
  struct _Operation<char,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Operation<char,long> { typedef long Type; };
  template <>
  struct _Operation<char,unsigned long> { typedef unsigned long Type; };
  template <>
  struct _Operation<char,short> { typedef short Type; };
  template <>
  struct _Operation<char,unsigned short> { typedef unsigned short Type; };
  template <>
  struct _Operation<char,char> { typedef char Type; };
  template <>
  struct _Operation<char,unsigned char> { typedef unsigned char Type; };

  template <>
  struct _Operation<unsigned char,long double> { typedef long double Type; };
  template <>
  struct _Operation<unsigned char,double> { typedef double Type; };
  template <>
  struct _Operation<unsigned char,float> { typedef float Type; };
  template <>
  struct _Operation<unsigned char,long long> { typedef long long Type; };
  template <>
  struct _Operation<unsigned char,unsigned long long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Operation<unsigned char,int> { typedef int Type; };
  template <>
  struct _Operation<unsigned char,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Operation<unsigned char,long> { typedef long Type; };
  template <>
  struct _Operation<unsigned char,unsigned long>{ typedef unsigned long Type; };
  template <>
  struct _Operation<unsigned char,short> { typedef short Type; };
  template <>
  struct _Operation<unsigned char,unsigned short>{typedef unsigned short Type;};
  template <>
  struct _Operation<unsigned char,char> { typedef unsigned char Type; };
  template <>
  struct _Operation<unsigned char,unsigned char>{ typedef unsigned char Type; };

}

#endif

