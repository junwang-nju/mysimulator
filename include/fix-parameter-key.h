
#ifndef _Fixed_Parameter_Key_H_
#define _Fixed_Parameter_Key_H_

#include "parameter-key-base.h"
#include "ref-vector.h"

namespace std {

  template <unsigned int NIdx>
  class fixParameterKey : public ParameterKeyBase<refVector> {

    public:

      typedef fixParameterKey<NIdx>   Type;

      typedef ParameterKeyBase<refVector>   ParentType;

  };

}

#endif

