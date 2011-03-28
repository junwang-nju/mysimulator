
#ifndef _Intrinsic_Type_Product_Type_H_
#define _Intrinsic_Type_Product_Type_H_

namespace mysimulator {

  template <typename Ta, typename Tb>
  struct _Product {};

  template <>
  struct _Product<long double,long double> { typedef long double Type; };
  template <>
  struct _Product<long double,double> { typedef long double Type; };
  template <>
  struct _Product<long double,float> { typedef long double Type; };
  template <>
  struct _Product<long double,long long> { typedef long double Type; };
  template <>
  struct _Product<long double,unsigned long long>{ typedef long double Type; };
  template <>
  struct _Product<long double,int> { typedef long double Type; };
  template <>
  struct _Product<long double,unsigned int> { typedef long double Type; };
  template <>
  struct _Product<long double,long> { typedef long double Type; };
  template <>
  struct _Product<long double,unsigned long> { typedef long double Type; };
  template <>
  struct _Product<long double,short> { typedef long double Type; };
  template <>
  struct _Product<long double,unsigned short> { typedef long double Type; };
  template <>
  struct _Product<long double,char> { typedef long double Type; };
  template <>
  struct _Product<long double,unsigned char> { typedef long double Type; };

  template <>
  struct _Product<double,long double> { typedef long double Type; };
  template <>
  struct _Product<double,double> { typedef double Type; };
  template <>
  struct _Product<double,float> { typedef double Type; };
  template <>
  struct _Product<double,long long> { typedef double Type; };
  template <>
  struct _Product<double,unsigned long long>{ typedef double Type; };
  template <>
  struct _Product<double,int> { typedef double Type; };
  template <>
  struct _Product<double,unsigned int> { typedef double Type; };
  template <>
  struct _Product<double,long> { typedef double Type; };
  template <>
  struct _Product<double,unsigned long> { typedef double Type; };
  template <>
  struct _Product<double,short> { typedef double Type; };
  template <>
  struct _Product<double,unsigned short> { typedef double Type; };
  template <>
  struct _Product<double,char> { typedef double Type; };
  template <>
  struct _Product<double,unsigned char> { typedef double Type; };

  template <>
  struct _Product<float,long double> { typedef long double Type; };
  template <>
  struct _Product<float,double> { typedef double Type; };
  template <>
  struct _Product<float,float> { typedef double Type; };
  template <>
  struct _Product<float,long long> { typedef float Type; };
  template <>
  struct _Product<float,unsigned long long>{ typedef float Type; };
  template <>
  struct _Product<float,int> { typedef float Type; };
  template <>
  struct _Product<float,unsigned int> { typedef float Type; };
  template <>
  struct _Product<float,long> { typedef float Type; };
  template <>
  struct _Product<float,unsigned long> { typedef float Type; };
  template <>
  struct _Product<float,short> { typedef float Type; };
  template <>
  struct _Product<float,unsigned short> { typedef float Type; };
  template <>
  struct _Product<float,char> { typedef float Type; };
  template <>
  struct _Product<float,unsigned char> { typedef float Type; };

  template <>
  struct _Product<long long,long double> { typedef long double Type; };
  template <>
  struct _Product<long long,double> { typedef double Type; };
  template <>
  struct _Product<long long,float> { typedef float Type; };
  template <>
  struct _Product<long long,long long> { typedef long long Type; };
  template <>
  struct _Product<long long,unsigned long long>{ typedef long long Type; };
  template <>
  struct _Product<long long,int> { typedef long long Type; };
  template <>
  struct _Product<long long,unsigned int> { typedef long long Type; };
  template <>
  struct _Product<long long,long> { typedef long long Type; };
  template <>
  struct _Product<long long,unsigned long> { typedef long long Type; };
  template <>
  struct _Product<long long,short> { typedef long long Type; };
  template <>
  struct _Product<long long,unsigned short> { typedef long long Type; };
  template <>
  struct _Product<long long,char> { typedef long long Type; };
  template <>
  struct _Product<long long,unsigned char> { typedef long long Type; };

  template <>
  struct _Product<unsigned long long,long double> { typedef long double Type; };
  template <>
  struct _Product<unsigned long long,double> { typedef double Type; };
  template <>
  struct _Product<unsigned long long,float> { typedef float Type; };
  template <>
  struct _Product<unsigned long long,long long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Product<unsigned long long,unsigned long long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Product<unsigned long long,int> { typedef unsigned long long Type; };
  template <>
  struct _Product<unsigned long long,unsigned int> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Product<unsigned long long,long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Product<unsigned long long,unsigned long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Product<unsigned long long,short> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Product<unsigned long long,unsigned short> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Product<unsigned long long,char> { typedef unsigned long long Type; };
  template <>
  struct _Product<unsigned long long,unsigned char> {
    typedef unsigned long long Type;
  };

  template <>
  struct _Product<int,long double> { typedef long double Type; };
  template <>
  struct _Product<int,double> { typedef double Type; };
  template <>
  struct _Product<int,float> { typedef float Type; };
  template <>
  struct _Product<int,long long> { typedef long long Type; };
  template <>
  struct _Product<int,unsigned long long>{ typedef unsigned long long Type; };
  template <>
  struct _Product<int,int> { typedef int Type; };
  template <>
  struct _Product<int,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Product<int,long> { typedef int Type; };
  template <>
  struct _Product<int,unsigned long> { typedef unsigned long Type; };
  template <>
  struct _Product<int,short> { typedef int Type; };
  template <>
  struct _Product<int,unsigned short> { typedef int Type; };
  template <>
  struct _Product<int,char> { typedef int Type; };
  template <>
  struct _Product<int,unsigned char> { typedef int Type; };

  template <>
  struct _Product<unsigned int,long double> { typedef long double Type; };
  template <>
  struct _Product<unsigned int,double> { typedef double Type; };
  template <>
  struct _Product<unsigned int,float> { typedef float Type; };
  template <>
  struct _Product<unsigned int,long long> { typedef long long Type; };
  template <>
  struct _Product<unsigned int,unsigned long long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Product<unsigned int,int> { typedef unsigned int Type; };
  template <>
  struct _Product<unsigned int,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Product<unsigned int,long> { typedef unsigned int Type; };
  template <>
  struct _Product<unsigned int,unsigned long> { typedef unsigned long Type; };
  template <>
  struct _Product<unsigned int,short> { typedef unsigned int Type; };
  template <>
  struct _Product<unsigned int,unsigned short> { typedef unsigned int Type; };
  template <>
  struct _Product<unsigned int,char> { typedef unsigned int Type; };
  template <>
  struct _Product<unsigned int,unsigned char> { typedef unsigned int Type; };

  template <>
  struct _Product<long,long double> { typedef long double Type; };
  template <>
  struct _Product<long,double> { typedef double Type; };
  template <>
  struct _Product<long,float> { typedef float Type; };
  template <>
  struct _Product<long,long long> { typedef long long Type; };
  template <>
  struct _Product<long,unsigned long long>{ typedef unsigned long long Type; };
  template <>
  struct _Product<long,int> { typedef int Type; };
  template <>
  struct _Product<long,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Product<long,long> { typedef long Type; };
  template <>
  struct _Product<long,unsigned long> { typedef unsigned long Type; };
  template <>
  struct _Product<long,short> { typedef long Type; };
  template <>
  struct _Product<long,unsigned short> { typedef long Type; };
  template <>
  struct _Product<long,char> { typedef long Type; };
  template <>
  struct _Product<long,unsigned char> { typedef long Type; };

  template <>
  struct _Product<unsigned long,long double> { typedef long double Type; };
  template <>
  struct _Product<unsigned long,double> { typedef double Type; };
  template <>
  struct _Product<unsigned long,float> { typedef float Type; };
  template <>
  struct _Product<unsigned long,long long> { typedef long long Type; };
  template <>
  struct _Product<unsigned long,unsigned long long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Product<unsigned long,int> { typedef unsigned long Type; };
  template <>
  struct _Product<unsigned long,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Product<unsigned long,long> { typedef unsigned long Type; };
  template <>
  struct _Product<unsigned long,unsigned long> { typedef unsigned long Type; };
  template <>
  struct _Product<unsigned long,short> { typedef unsigned long Type; };
  template <>
  struct _Product<unsigned long,unsigned short> { typedef unsigned long Type; };
  template <>
  struct _Product<unsigned long,char> { typedef unsigned long Type; };
  template <>
  struct _Product<unsigned long,unsigned char> { typedef unsigned long Type; };

  template <>
  struct _Product<short,long double> { typedef long double Type; };
  template <>
  struct _Product<short,double> { typedef double Type; };
  template <>
  struct _Product<short,float> { typedef float Type; };
  template <>
  struct _Product<short,long long> { typedef long long Type; };
  template <>
  struct _Product<short,unsigned long long>{ typedef unsigned long long Type; };
  template <>
  struct _Product<short,int> { typedef int Type; };
  template <>
  struct _Product<short,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Product<short,long> { typedef long Type; };
  template <>
  struct _Product<short,unsigned long> { typedef unsigned long Type; };
  template <>
  struct _Product<short,short> { typedef short Type; };
  template <>
  struct _Product<short,unsigned short> { typedef unsigned short Type; };
  template <>
  struct _Product<short,char> { typedef short Type; };
  template <>
  struct _Product<short,unsigned char> { typedef short Type; };

  template <>
  struct _Product<unsigned short,long double> { typedef long double Type; };
  template <>
  struct _Product<unsigned short,double> { typedef double Type; };
  template <>
  struct _Product<unsigned short,float> { typedef float Type; };
  template <>
  struct _Product<unsigned short,long long> { typedef long long Type; };
  template <>
  struct _Product<unsigned short,unsigned long long>{ typedef unsigned long long Type; };
  template <>
  struct _Product<unsigned short,int> { typedef int Type; };
  template <>
  struct _Product<unsigned short,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Product<unsigned short,long> { typedef long Type; };
  template <>
  struct _Product<unsigned short,unsigned long> { typedef unsigned long Type; };
  template <>
  struct _Product<unsigned short,short> { typedef unsigned short Type; };
  template <>
  struct _Product<unsigned short,unsigned short> {
    typedef unsigned short Type;
  };
  template <>
  struct _Product<unsigned short,char> { typedef unsigned short Type; };
  template <>
  struct _Product<unsigned short,unsigned char>{ typedef unsigned short Type; };

  template <>
  struct _Product<char,long double> { typedef long double Type; };
  template <>
  struct _Product<char,double> { typedef double Type; };
  template <>
  struct _Product<char,float> { typedef float Type; };
  template <>
  struct _Product<char,long long> { typedef long long Type; };
  template <>
  struct _Product<char,unsigned long long>{ typedef unsigned long long Type; };
  template <>
  struct _Product<char,int> { typedef int Type; };
  template <>
  struct _Product<char,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Product<char,long> { typedef long Type; };
  template <>
  struct _Product<char,unsigned long> { typedef unsigned long Type; };
  template <>
  struct _Product<char,short> { typedef short Type; };
  template <>
  struct _Product<char,unsigned short> { typedef unsigned short Type; };
  template <>
  struct _Product<char,char> { typedef char Type; };
  template <>
  struct _Product<char,unsigned char> { typedef unsigned char Type; };

  template <>
  struct _Product<unsigned char,long double> { typedef long double Type; };
  template <>
  struct _Product<unsigned char,double> { typedef double Type; };
  template <>
  struct _Product<unsigned char,float> { typedef float Type; };
  template <>
  struct _Product<unsigned char,long long> { typedef long long Type; };
  template <>
  struct _Product<unsigned char,unsigned long long> {
    typedef unsigned long long Type;
  };
  template <>
  struct _Product<unsigned char,int> { typedef int Type; };
  template <>
  struct _Product<unsigned char,unsigned int> { typedef unsigned int Type; };
  template <>
  struct _Product<unsigned char,long> { typedef long Type; };
  template <>
  struct _Product<unsigned char,unsigned long> { typedef unsigned long Type; };
  template <>
  struct _Product<unsigned char,short> { typedef short Type; };
  template <>
  struct _Product<unsigned char,unsigned short>{ typedef unsigned short Type; };
  template <>
  struct _Product<unsigned char,char> { typedef unsigned char Type; };
  template <>
  struct _Product<unsigned char,unsigned char> { typedef unsigned char Type; };

}

#endif

