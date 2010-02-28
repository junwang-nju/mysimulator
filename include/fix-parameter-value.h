
#ifndef _Fixed_Parameter_Value_H_
#define _Fixed_Parameter_Value_H_

#include "fix-vector.h"

namespace std {

  template <unsigned int N>
  class fixParameterValue : public fixVector<double,N> {

    public:

      typedef fixParameterValue<N>    Type;

      typedef fixVector<double,N>     ParentType;

      fixParameterValue() : ParentType() {}

      fixParameterValue(const Type&) {
        myError("Cannot create from fixed Parameter Value");
      }

      ~fixParameterValue() {}

      Type& operator=(const Type& fPV) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fPV));
        return *this;
      }

      template <typename iType>
      Type& operator=(const iType& PV) {
        static_cast<ParentType*>(this)->operator=(PV);
        return *this;
      }

  };

}

#endif

