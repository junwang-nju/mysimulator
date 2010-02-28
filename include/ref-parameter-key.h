
#ifndef _Reference_Parameter_Key_H_
#define _Reference_Parameter_Key_H_

#include "parameter-key-base.h"
#include "ref-vector.h"

namespace std {

  class refParameterKey : public ParameterKeyBase<refVector> {

    public:

      typedef refParameterKey   Type;

      typedef ParameterKeyBase<refVector>   ParentType;

      refParameterKey() : ParentType() {}

      refParameterKey(const Type&) {
        myError("Cannot create from reference Parameter Key");
      }

      ~refParameterKey() {}

      Type& operator=(const Type& rPK) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(rPK));
        return *this;
      }

      template <template <typename> class VecType>
      Type& operator=(const ParameterKeyBase<VecType>& PK) {
        static_cast<ParentType*>(this)->operator=(PK);
        return *this;
      }

      template <template <typename> class VecType>
      void refer(const ParameterKeyBase<VecType>& PK) {
        this->index.refer(PK.index());
      }

  };

}

#endif

