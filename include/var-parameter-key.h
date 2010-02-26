
#ifndef _Variable_Parameter_Key_H_
#define _Variable_Parameter_Key_H_

#include "parameter-key-base.h"
#include "var-vector.h"

namespace std {

  class varParameterKey : public ParameterKeyBase<varVector> {

    public:

      typedef varParameterKey   Type;

      typedef ParameterKeyBase<varVector>   ParentType;

      varParameterKey() : ParentType() {}

      varParameterKey(const unsigned int NI) : ParentType() { allocate(NI); }

      varParameterKey(const Type&) {
        myError("Cannot create from Variable Parameter Key");
      }

      ~varParameterKey() {}

      Type& operator=(const Type& vPK) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vPK));
        return *this;
      }

      template <template <typename> class VecType>
      Type& operator=(const ParameterKeyBase<VecType>& PK) {
        static_cast<ParentType*>(this)->operator=(PK);
        return *this;
      }

      void allocate(const unsigned int NIdx) { this->index().allocate(NIdx); }

  };

}

#endif

