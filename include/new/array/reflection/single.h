
#ifndef _Array_Reflection_Single_H_
#define _Array_Reflection_Single_H_

#define _OPERATE(type)  typedef type OperateType;
#define _SINGLE_STRUCT(type,typeA) \
  template <> struct _Single_Array<typeA> { _OPERATE(type); }

#include "linear-algebra/blas.h"

namespace mysimulator {

  template <typename T>
  struct _Single_Array {};

  _SINGLE_STRUCT(double,double);
  _SINGLE_STRUCT(double,long long);
  _SINGLE_STRUCT(double,unsigned long long);

  _SINGLE_STRUCT(float,float);
  _SINGLE_STRUCT(float,int);
  _SINGLE_STRUCT(float,unsigned int);
  _SINGLE_STRUCT(float,long);
  _SINGLE_STRUCT(float,unsigned long);

}

#undef _SINGLE_STRUCT
#undef _OPERATE

#endif

