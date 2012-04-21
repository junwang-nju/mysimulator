
#ifndef _Intrinsic_Type_Reflection_Dual_H_
#define _Intrinsic_Type_Reflection_Dual_H_

#define _ASSIGN(type) typedef type AssignType
#define _COMBINE(type) typedef type CombineType

#define DUAL_STRUCT_BOTH(typeA,typeB) \
  template<> struct _Dual<typeA,typeB> { _ASSIGN(typeA); _COMBINE(typeA); }
#define DUAL_STRUCT_ASSIGNONLY(typeA,typeB) \
  template<> struct _Dual<typeA,typeB> { _ASSIGN(typeA); }
#define DUAL_STRUCT_COMBINEONLY(typeA,typeB) \
  template<> struct _Dual<typeA,typeB> { _COMBINE(typeB); }
#define DUAL_STRUCT_NULL(typeA,typeB) \
  template<> struct _Dual<typeA,typeB> { }

namespace mysimulator {

  template <typename T1, typename T2>
  struct _Dual {};

  DUAL_STRUCT_BOTH(long double,long double);
  DUAL_STRUCT_BOTH(long double,double);
  DUAL_STRUCT_BOTH(long double,float);
  DUAL_STRUCT_BOTH(long double,long long);
  DUAL_STRUCT_BOTH(long double,unsigned long long);
  DUAL_STRUCT_BOTH(long double,int);
  DUAL_STRUCT_BOTH(long double,unsigned int);
  DUAL_STRUCT_BOTH(long double,long);
  DUAL_STRUCT_BOTH(long double,unsigned long);
  DUAL_STRUCT_BOTH(long double,short);
  DUAL_STRUCT_BOTH(long double,unsigned short);
  DUAL_STRUCT_BOTH(long double,char);
  DUAL_STRUCT_BOTH(long double,unsigned char);

  DUAL_STRUCT_COMBINEONLY(double,long double);
  DUAL_STRUCT_BOTH(double,double);
  DUAL_STRUCT_BOTH(double,float);
  DUAL_STRUCT_BOTH(double,long long);
  DUAL_STRUCT_BOTH(double,unsigned long long);
  DUAL_STRUCT_BOTH(double,int);
  DUAL_STRUCT_BOTH(double,unsigned int);
  DUAL_STRUCT_BOTH(double,long);
  DUAL_STRUCT_BOTH(double,unsigned long);
  DUAL_STRUCT_BOTH(double,short);
  DUAL_STRUCT_BOTH(double,unsigned short);
  DUAL_STRUCT_BOTH(double,char);
  DUAL_STRUCT_BOTH(double,unsigned char);

  DUAL_STRUCT_COMBINEONLY(float,long double);
  DUAL_STRUCT_COMBINEONLY(float,double);
  DUAL_STRUCT_BOTH(float,float);
  DUAL_STRUCT_BOTH(float,long long);
  DUAL_STRUCT_BOTH(float,unsigned long long);
  DUAL_STRUCT_BOTH(float,int);
  DUAL_STRUCT_BOTH(float,unsigned int);
  DUAL_STRUCT_BOTH(float,long);
  DUAL_STRUCT_BOTH(float,unsigned long);
  DUAL_STRUCT_BOTH(float,short);
  DUAL_STRUCT_BOTH(float,unsigned short);
  DUAL_STRUCT_BOTH(float,char);
  DUAL_STRUCT_BOTH(float,unsigned char);

  DUAL_STRUCT_COMBINEONLY(long long,long double);
  DUAL_STRUCT_COMBINEONLY(long long,double);
  DUAL_STRUCT_COMBINEONLY(long long,float);
  DUAL_STRUCT_BOTH(long long,long long);
  DUAL_STRUCT_NULL(long long,unsigned long long);
  DUAL_STRUCT_BOTH(long long,int);
  DUAL_STRUCT_BOTH(long long,unsigned int);
  DUAL_STRUCT_BOTH(long long,long);
  DUAL_STRUCT_BOTH(long long,unsigned long);
  DUAL_STRUCT_BOTH(long long,short);
  DUAL_STRUCT_BOTH(long long,unsigned short);
  DUAL_STRUCT_BOTH(long long,char);
  DUAL_STRUCT_BOTH(long long,unsigned char);

  DUAL_STRUCT_COMBINEONLY(unsigned long long,long double);
  DUAL_STRUCT_COMBINEONLY(unsigned long long,double);
  DUAL_STRUCT_COMBINEONLY(unsigned long long,float);
  DUAL_STRUCT_NULL(unsigned long long,long long);
  DUAL_STRUCT_BOTH(unsigned long long,unsigned long long);
  DUAL_STRUCT_NULL(unsigned long long,int);
  DUAL_STRUCT_BOTH(unsigned long long,unsigned int);
  DUAL_STRUCT_NULL(unsigned long long,long);
  DUAL_STRUCT_BOTH(unsigned long long,unsigned long);
  DUAL_STRUCT_NULL(unsigned long long,short);
  DUAL_STRUCT_BOTH(unsigned long long,unsigned short);
  DUAL_STRUCT_NULL(unsigned long long,char);
  DUAL_STRUCT_BOTH(unsigned long long,unsigned char);

  DUAL_STRUCT_COMBINEONLY(int,long double);
  DUAL_STRUCT_COMBINEONLY(int,double);
  DUAL_STRUCT_COMBINEONLY(int,float);
  DUAL_STRUCT_COMBINEONLY(int,long long);
  DUAL_STRUCT_NULL(int,unsigned long long);
  DUAL_STRUCT_BOTH(int,int);
  DUAL_STRUCT_NULL(int,unsigned int);
  DUAL_STRUCT_BOTH(int,long);
  DUAL_STRUCT_NULL(int,unsigned long);
  DUAL_STRUCT_BOTH(int,short);
  DUAL_STRUCT_BOTH(int,unsigned short);
  DUAL_STRUCT_BOTH(int,char);
  DUAL_STRUCT_BOTH(int,unsigned char);

  DUAL_STRUCT_COMBINEONLY(unsigned int,long double);
  DUAL_STRUCT_COMBINEONLY(unsigned int,double);
  DUAL_STRUCT_COMBINEONLY(unsigned int,float);
  DUAL_STRUCT_COMBINEONLY(unsigned int,long long);
  DUAL_STRUCT_COMBINEONLY(unsigned int,unsigned long long);
  DUAL_STRUCT_NULL(unsigned int,int);
  DUAL_STRUCT_BOTH(unsigned int,unsigned int);
  DUAL_STRUCT_NULL(unsigned int,long);
  DUAL_STRUCT_BOTH(unsigned int,unsigned long);
  DUAL_STRUCT_NULL(unsigned int,short);
  DUAL_STRUCT_BOTH(unsigned int,unsigned short);
  DUAL_STRUCT_NULL(unsigned int,char);
  DUAL_STRUCT_BOTH(unsigned int,unsigned char);

  DUAL_STRUCT_COMBINEONLY(long,long double);
  DUAL_STRUCT_COMBINEONLY(long,double);
  DUAL_STRUCT_COMBINEONLY(long,float);
  DUAL_STRUCT_COMBINEONLY(long,long long);
  DUAL_STRUCT_NULL(long,unsigned long long);
  DUAL_STRUCT_BOTH(long,int);
  DUAL_STRUCT_NULL(long,unsigned int);
  DUAL_STRUCT_BOTH(long,long);
  DUAL_STRUCT_NULL(long,unsigned long);
  DUAL_STRUCT_BOTH(long,short);
  DUAL_STRUCT_BOTH(long,unsigned short);
  DUAL_STRUCT_BOTH(long,char);
  DUAL_STRUCT_BOTH(long,unsigned char);

  DUAL_STRUCT_COMBINEONLY(unsigned long,long double);
  DUAL_STRUCT_COMBINEONLY(unsigned long,double);
  DUAL_STRUCT_COMBINEONLY(unsigned long,float);
  DUAL_STRUCT_COMBINEONLY(unsigned long,long long);
  DUAL_STRUCT_COMBINEONLY(unsigned long,unsigned long long);
  DUAL_STRUCT_NULL(unsigned long,int);
  DUAL_STRUCT_BOTH(unsigned long,unsigned int);
  DUAL_STRUCT_NULL(unsigned long,long);
  DUAL_STRUCT_BOTH(unsigned long,unsigned long);
  DUAL_STRUCT_NULL(unsigned long,short);
  DUAL_STRUCT_BOTH(unsigned long,unsigned short);
  DUAL_STRUCT_NULL(unsigned long,char);
  DUAL_STRUCT_BOTH(unsigned long,unsigned char);

  DUAL_STRUCT_COMBINEONLY(short,long double);
  DUAL_STRUCT_COMBINEONLY(short,double);
  DUAL_STRUCT_COMBINEONLY(short,float);
  DUAL_STRUCT_COMBINEONLY(short,long long);
  DUAL_STRUCT_NULL(short,unsigned long long);
  DUAL_STRUCT_COMBINEONLY(short,int);
  DUAL_STRUCT_NULL(short,unsigned int);
  DUAL_STRUCT_COMBINEONLY(short,long);
  DUAL_STRUCT_NULL(short,unsigned long);
  DUAL_STRUCT_BOTH(short,short);
  DUAL_STRUCT_NULL(short,unsigned short);
  DUAL_STRUCT_BOTH(short,char);
  DUAL_STRUCT_BOTH(short,unsigned char);

  DUAL_STRUCT_COMBINEONLY(unsigned short,long double);
  DUAL_STRUCT_COMBINEONLY(unsigned short,double);
  DUAL_STRUCT_COMBINEONLY(unsigned short,float);
  DUAL_STRUCT_COMBINEONLY(unsigned short,long long);
  DUAL_STRUCT_COMBINEONLY(unsigned short,unsigned long long);
  DUAL_STRUCT_COMBINEONLY(unsigned short,int);
  DUAL_STRUCT_COMBINEONLY(unsigned short,unsigned int);
  DUAL_STRUCT_COMBINEONLY(unsigned short,long);
  DUAL_STRUCT_COMBINEONLY(unsigned short,unsigned long);
  DUAL_STRUCT_NULL(unsigned short,short);
  DUAL_STRUCT_BOTH(unsigned short,unsigned short);
  DUAL_STRUCT_NULL(unsigned short,char);
  DUAL_STRUCT_BOTH(unsigned short,unsigned char);

  DUAL_STRUCT_COMBINEONLY(char,long double);
  DUAL_STRUCT_COMBINEONLY(char,double);
  DUAL_STRUCT_COMBINEONLY(char,float);
  DUAL_STRUCT_COMBINEONLY(char,long long);
  DUAL_STRUCT_NULL(char,unsigned long long);
  DUAL_STRUCT_COMBINEONLY(char,int);
  DUAL_STRUCT_NULL(char,unsigned int);
  DUAL_STRUCT_COMBINEONLY(char,long);
  DUAL_STRUCT_NULL(char,unsigned long);
  DUAL_STRUCT_COMBINEONLY(char,short);
  DUAL_STRUCT_NULL(char,unsigned short);
  DUAL_STRUCT_BOTH(char,char);
  DUAL_STRUCT_NULL(char,unsigned char);

  DUAL_STRUCT_COMBINEONLY(unsigned char,long double);
  DUAL_STRUCT_COMBINEONLY(unsigned char,double);
  DUAL_STRUCT_COMBINEONLY(unsigned char,float);
  DUAL_STRUCT_COMBINEONLY(unsigned char,long long);
  DUAL_STRUCT_COMBINEONLY(unsigned char,unsigned long long);
  DUAL_STRUCT_COMBINEONLY(unsigned char,int);
  DUAL_STRUCT_COMBINEONLY(unsigned char,unsigned int);
  DUAL_STRUCT_COMBINEONLY(unsigned char,long);
  DUAL_STRUCT_COMBINEONLY(unsigned char,unsigned long);
  DUAL_STRUCT_COMBINEONLY(unsigned char,short);
  DUAL_STRUCT_COMBINEONLY(unsigned char,unsigned short);
  DUAL_STRUCT_NULL(unsigned char,char);
  DUAL_STRUCT_BOTH(unsigned char,unsigned char);


  DUAL_STRUCT_BOTH(bool,bool);
  DUAL_STRUCT_ASSIGNONLY(bool,long long);
  DUAL_STRUCT_ASSIGNONLY(bool,unsigned long long);
  DUAL_STRUCT_ASSIGNONLY(bool,int);
  DUAL_STRUCT_ASSIGNONLY(bool,unsigned int);
  DUAL_STRUCT_ASSIGNONLY(bool,long);
  DUAL_STRUCT_ASSIGNONLY(bool,unsigned long);
  DUAL_STRUCT_ASSIGNONLY(bool,short);
  DUAL_STRUCT_ASSIGNONLY(bool,unsigned short);
  DUAL_STRUCT_ASSIGNONLY(bool,char);
  DUAL_STRUCT_ASSIGNONLY(bool,unsigned char);

  DUAL_STRUCT_BOTH(void*,void*);
  template <typename T>
  struct _Dual<void*,T*> { _ASSIGN(void*); _COMBINE(void*); };
  template <typename T>
  struct _Dual<T*,void*> { _ASSIGN(T*); _COMBINE(T*); };
  template <typename T>
  struct _Dual<T*,T*> { _ASSIGN(T*); _COMBINE(T*); };
  template <typename T1, typename T2>
  struct _Dual<T1*,T2*> {};

}

#undef  DUAL_STRUCT_NULL
#undef  DUAL_STRUCT_COMBINEONLY
#undef  DUAL_STRUCT_ASSIGNONLY
#undef  DUAL_STRUCT_BOTH
#undef  _COMBINE
#undef  _ASSIGN

#endif

