
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

    protected:

      fixVector<unsigned int,NIdx>  inIndex;

    public:

      fixParameterKey() : ParentType() { this->index().refer(inIndex); }

      fixParameterKey(const Type&) {
        myError("Cannot create from fixed Parameter Key");
      }

      ~fixParameterKey() {}

      Type& operator=(const Type& fPK) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fPK));
        return *this;
      }

      template <template <typename> class VecType>
      Type& operator=(const ParameterKeyBase<VecType>& PK) {
        static_cast<ParentType*>(this)->operator=(PK);
        return *this;
      }

      void clear() {}

  };

}

#endif

