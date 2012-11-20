
#ifndef _System_Vec_Type_Selector_H_
#define _System_Vec_Type_Selector_H_

#include "array/kernel/name.h"

namespace mysimulator {

  template <unsigned int D>
  class __system_vec_type { public: static const ArrayKernelName NAME; };

  template <unsigned int D>
  const ArrayKernelName __system_vec_type<D>::NAME = ArrayKernelName::Simple;

  template <>
  const ArrayKernelName __system_vec_type<3>::NAME = ArrayKernelName::Direct3D;

  template <>
  const ArrayKernelName __system_vec_type<2>::NAME = ArrayKernelName::Direct2D;

}

#endif

