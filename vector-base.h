
#ifndef _Vector_Base_H_
#define _Vector_Base_H_

#include "vector-base-baisc.h"

namespace std {

  template <typename T>
  class VectorBase : public VectorBaseBasic<T> {
    public:
      typedef T DataType;
      typedef VectorBaseBasic<T>  Type;
      typedef VectorBase<T> ParentType;
      VectorBase() : ParentType() {}
      VectorBase(const Type& V) {
        myError("Cannot create from VectorBase");
      }
      Type& operator=(const Type& V) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(V));
        return *this;
      }
      ~VectorBase() {}
  };

  template <>
  class VectorBase<double> : public VectorBaseBasic<double> {
    public:
      typedef double  DataType;
      typedef VectorBase<double>  Type;
      typedef VectorBaseBasic<double> ParentType;
      VectorBase() : ParentType() {}
      VectorBase(const Type& V) {
        myError("Cannot create from VectorBase of double");
      }
      Type& operator=(const Type& V) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(V));
        return *this;
      }
      ~VectorBase() {}
      template <typename inputT>
      Type& operator+=(const inputT& V) { return shift(V); }
      template <typename inputT>
      Type& operator*=(const inputT& V) { return scale(V); }
      Type& scale(const Type& V);
      Type& scale(const double value);
      Type& scale(const Type& V, long nsc, int voff=iZero, long vstep=lOne,
                                           int off=iZero, long step=lOne);
      Type& scale(const double& value,long nsc,int off=iZero,long step=lOne);
      Type& shift(const Type& V);
      Type& shift(const double value);
      Type& shift(const double value, const Type& V);
      Type& shift(const Type& SfV, const Type& V);
      Type& shift(const double SfF, const Type& SfV, const Type& V);
      Type& shift(const double& value, const Type& V, long nsh,
                  int voff=iZero,long vstep=lOne,int off=iZero,long step=lOne);
      Type& shift(const double& value, long nsf, int off=iZero, long step=lOne);
      Type& scaleshift(const double ScF, const double SfF, const Type& V);
      Type& scaleshift(const double ScF, const double SfF, const Type& SfV,
                       const Type& V);
      Type& scaleshift(const double& ScF, const double& SfF, const Type& V,
                       long nss, int voff=iZero, long vstep=lOne,
                       int off=iZero, long step=lOne);
      Type& scaleshift(const double& ScF, const double& SfF, const Type& SfV,
                       const Type& V, long nss,
                       int Sfoff=iZero, long Sfstep=lOne,
                       int voff=iZero, long vstep=lOne,
                       int off=iZero, long step=lOne);
  };

}

#endif

