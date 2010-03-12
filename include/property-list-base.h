
#ifndef _Property_List_Base_H_
#define _Property_List_Base_H_

#include "data-pack.h"

namespace std {

  template <typename T, template <typename> class VecType>
  class PropertyListBase : public DataPack<T,VecType,VecType,1U> {

    public:

      typedef PropertyListBase<T,VecType>  Type;

      typedef DataPack<T,VecType,VecType,1U>    ParentType;

      PropertyListBase() : ParentType() {}

      PropertyListBase(const Type&) {
        myError("Cannot create from Property List Base");
      }

      ~PropertyListBase() {}

      Type& operator=(const Type& PLB) {
        this->data()=PLB.data();
        return *this;
      }

      Type& operator=(const VectorBase<T>& V) {
        this->data()=V;
        return *this;
      }

      Type& operator=(const T& Value) {
        this->data()=Value;
        return *this;
      }

  };

  template <template <typename> class VecType>
  class PropertyListBase<double,VecType>
    : public DataPack<double,VecType,VecType,1U> {

    public:

      typedef PropertyListBase<double,VecType>  Type;

      typedef DataPack<double,VecType,VecType,1U>    ParentType;

      PropertyListBase() : ParentType() {}

      PropertyListBase(const Type&) {
        myError("Cannot create from Property List Base");
      }

      ~PropertyListBase() {}

      Type& operator=(const Type& PLB) {
        this->data()=PLB.data();
        return *this;
      }

      Type& operator=(const VectorBase<double>& V) {
        this->data()=V;
        return *this;
      }

      Type& operator=(const double& Value) {
        this->data()=Value;
        return *this;
      }

      void scale(const VectorBase<double>& V) { this->data().scale(V); }

      void scale(const Type& PL) { scale(PL.data()); }

      void scale(const double value) { this->data().scale(value); }

      void scale(const VectorBase<double>& V, long nsc,
                 int voff=iZero, long vstep=lOne,
                 int off=iZero, long step=lOne) {
        this->data().scale(V,nsc,voff,vstep,off,step);
      }

      void scale(const double value, long nsc, int off=iZero, long step=lOne) {
        this->data().scale(value,nsc,off,step);
      }

      void shift(const VectorBase<double>& V) { this->data().shift(V); }

      void shift(const Type& PL) { shift(PL.data()); }

      void shift(const double value) { this->data().shift(value); }

      void shift(const double value, const VectorBase<double>& V) {
        this->data().shift(value,V);
      }

      void shift(const double val, const Type& PL) { shift(val,PL.data()); }

      void shift(const VectorBase<double>& V, const double value) {
        shift(value,V);
      }

      void shift(const Type& PL, const double value) { scale(value,PL); }

      void shift(const VectorBase<double>& SfV, const VectorBase<double>& V) {
        this->data().shift(SfV,V);
      }

  };

}

#endif

