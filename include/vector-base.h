
#ifndef _Vector_Base_H_
#define _Vector_Base_H_

#include "vector-base-basic.h"

namespace std {

  template <typename T>
  class VectorBase : public VectorBaseBasic<T> {
    public:
      typedef T DataType;
      typedef VectorBase<T>  Type;
      typedef VectorBaseBasic<T> ParentType;
      VectorBase() : ParentType() {}
      VectorBase(const Type& V) { myError("Cannot create from VectorBase"); }
      Type& operator=(const Type& V) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(V));
        return *this;
      }
      Type& operator=(const T& V) {
        static_cast<ParentType*>(this)->operator=(V);
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
      Type& operator=(const double V) {
        static_cast<ParentType*>(this)->operator=(V);
        return *this;
      }
      virtual ~VectorBase() {}
      void scale(const Type& V);
      void scale(const double value);
      void scale(const Type& V, long nsc, int voff=iZero, long vstep=lOne,
                                          int off=iZero, long step=lOne);
      void scale(const double& value,long nsc,int off=iZero,long step=lOne);
      void shift(const Type& V);
      void shift(const double value);
      void shift(const double value, const Type& V);
      void shift(const Type& V, const double value);
      void shift(const Type& SfV, const Type& V);
      void shift(const double SfF, const Type& SfV, const Type& V);
      void shift(const double& value, const Type& V, long nsh,
                 int voff=iZero,long vstep=lOne,int off=iZero,long step=lOne);
      void shift(const double& value, long nsf, int off=iZero, long step=lOne);
      void scaleshift(const double ScF, const double SfF, const Type& V);
      void scaleshift(const double ScF, const double SfF, const Type& SfV,
                      const Type& V);
      void scaleshift(const double& ScF, const double& SfF, const Type& V,
                      long nss, int voff=iZero, long vstep=lOne,
                      int off=iZero, long step=lOne);
      void scaleshift(const double& ScF, const double& SfF, const Type& SfV,
                      const Type& V, long nss,
                      int Sfoff=iZero, long Sfstep=lOne,
                      int voff=iZero, long vstep=lOne,
                      int off=iZero, long step=lOne);
  };

}

#endif

