
#ifndef _Intrinsic_Type_Shift_Type_Check_H_
#define _Intrinsic_Type_Shift_Type_Check_H_

namespace mysimulator {

  template <typename T, typename T1, typename T2>
  struct ShiftCheck {
  };

  template <typename T1, typename T2>
  struct ShiftCheck<long double,T1,T2> { typedef long double Type; };

  template <>
  struct ShiftCheck<double,double,double> { typedef double Type; }
  template <>
  struct ShiftCheck<double,double,float> { typedef double Type; }
  template <>
  struct ShiftCheck<double,double,long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,double,unsigned long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,double,int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,double,unsigned int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,double,long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,double,unsigned long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,double,short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,double,unsigned short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,double,char> { typedef double Type; }
  template <>
  struct ShiftCheck<double,double,unsigned char> { typedef double Type; }

  template <>
  struct ShiftCheck<double,float,double> { typedef double Type; }
  template <>
  struct ShiftCheck<double,float,float> { typedef double Type; }
  template <>
  struct ShiftCheck<double,float,long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,float,unsigned long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,float,int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,float,unsigned int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,float,long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,float,unsigned long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,float,short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,float,unsigned short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,float,char> { typedef double Type; }
  template <>
  struct ShiftCheck<double,float,unsigned char> { typedef double Type; }

  template <>
  struct ShiftCheck<double,long long,double> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long long,float> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long long,long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long long,unsigned long long>{ typedef double Type; }
  template <>
  struct ShiftCheck<double,long long,int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long long,unsigned int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long long,long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long long,unsigned long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long long,short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long long,unsigned short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long long,char> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long long,unsigned char> { typedef double Type; }

  template <>
  struct ShiftCheck<double,unsigned long long,double> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long long,float> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long long,long long>{ typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long long,unsigned long long> {
    typedef double Type;
  }
  template <>
  struct ShiftCheck<double,unsigned long long,int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long long,unsigned int> {
    typedef double Type;
  }
  template <>
  struct ShiftCheck<double,unsigned long long,long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long long,unsigned long> {
    typedef double Type;
  }
  template <>
  struct ShiftCheck<double,unsigned long long,short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long long,unsigned short> {
    typedef double Type;
  }
  template <>
  struct ShiftCheck<double,unsigned long long,char> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long long,unsigned char> {
    typedef double Type;
  }

  template <>
  struct ShiftCheck<double,int,double> { typedef double Type; }
  template <>
  struct ShiftCheck<double,int,float> { typedef double Type; }
  template <>
  struct ShiftCheck<double,int,long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,int,unsigned long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,int,int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,int,unsigned int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,int,long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,int,unsigned long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,int,short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,int,unsigned short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,int,char> { typedef double Type; }
  template <>
  struct ShiftCheck<double,int,unsigned char> { typedef double Type; }

  template <>
  struct ShiftCheck<double,unsigned int,double> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned int,float> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned int,long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned int,unsigned long long> {
    typedef double Type;
  }
  template <>
  struct ShiftCheck<double,unsigned int,int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned int,unsigned int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned int,long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned int,unsigned long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned int,short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned int,unsigned short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned int,char> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned int,unsigned char> { typedef double Type; }

  template <>
  struct ShiftCheck<double,long,double> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long,float> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long,long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long,unsigned long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long,int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long,unsigned int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long,long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long,unsigned long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long,short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long,unsigned short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long,char> { typedef double Type; }
  template <>
  struct ShiftCheck<double,long,unsigned char> { typedef double Type; }

  template <>
  struct ShiftCheck<double,unsigned long,double> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long,float> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long,long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long,unsigned long long> {
    typedef double Type;
  }
  template <>
  struct ShiftCheck<double,unsigned long,int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long,unsigned int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long,long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long,unsigned long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long,short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long,unsigned short>{ typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long,char> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned long,unsigned char> { typedef double Type; }

  template <>
  struct ShiftCheck<double,short,double> { typedef double Type; }
  template <>
  struct ShiftCheck<double,short,float> { typedef double Type; }
  template <>
  struct ShiftCheck<double,short,long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,short,unsigned long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,short,int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,short,unsigned int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,short,long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,short,unsigned long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,short,short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,short,unsigned short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,short,char> { typedef double Type; }
  template <>
  struct ShiftCheck<double,short,unsigned char> { typedef double Type; }

  template <>
  struct ShiftCheck<double,unsigned short,double> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned short,float> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned short,long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned short,unsigned long long> {
    typedef double Type;
  }
  template <>
  struct ShiftCheck<double,unsigned short,int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned short,unsigned int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned short,long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned short,unsigned long>{ typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned short,short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned short,unsigned short>{typedef double Type;}
  template <>
  struct ShiftCheck<double,unsigned short,char> { typedef double Type; }
  template <>
  struct ShiftCheck<double,unsigned short,unsigned char>{ typedef double Type; }

  template <>
  struct ShiftCheck<double,char,double> { typedef double Type; }
  template <>
  struct ShiftCheck<double,char,float> { typedef double Type; }
  template <>
  struct ShiftCheck<double,char,long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,char,unsigned long long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,char,int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,char,unsigned int> { typedef double Type; }
  template <>
  struct ShiftCheck<double,char,long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,char,unsigned long> { typedef double Type; }
  template <>
  struct ShiftCheck<double,char,short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,char,unsigned short> { typedef double Type; }
  template <>
  struct ShiftCheck<double,char,char> { typedef double Type; }
  template <>
  struct ShiftCheck<double,char,unsigned char> { typedef double Type; }

}

#endif

