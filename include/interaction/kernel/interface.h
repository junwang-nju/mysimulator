
#ifndef _Interaction_Kernel_Interface_H_
#define _Interaction_Kernel_Interface_H_

#include "interaction/kernel/unit/interface.h"

namespace mysimulator {

  template<template<typename>class DBuffer,typename GeomType,typename T=double>
  struct InteractionKernel {

    typedef InteractionKernel<DBuffer,GeomType,T>    Type;

    Vector<InteractionKernelUnit<DBuffer,GeomType,T> > iunit;
    DBuffer<T> DB;
    GeomType  Geo;

    InteractionKernel() : iunit(), DB(), Geo() {}
    InteractionKernel(const Type&) {
      Error("Copier of InteractionKernel Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for InteractionKernel Disabled!");
      return *this;
    }
    ~InteractionKernel() { clearData(); }

    void clearData() { release(iunit); release(DB); release(Geo); }
    const unsigned int NumInteractionType() const { return iunit.size; }
    const unsigned int NumUnit() const { return DB.UnitNumber(); }
    const unsigned int Dimension() const { return DB.Dimension(); }

  };

  template <template<typename> class DBuffer, typename GeomType, typename T>
  bool IsValid(const InteractionKernel<DBuffer,GeomType,T>& K) {
    return IsValid(K.iunit)&&IsValid(K.DB)&&IsValid(K.Geo);
  }

  template <template<typename> class DBuffer, typename GType, typename T>
  void release(InteractionKernel<DBuffer,GType,T>& K) { K.clearData(); }

}

#endif

