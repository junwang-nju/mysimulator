
#ifndef _Reference_Parameter_Key_H_
#define _Reference_Parameter_Key_H_

#include "parameter-key-base.h"
#include "var-vector.h"

namespace std {

  class refParameterKey
    : public refObject<ParameterKeyBase<refVector>,
                       ParameterKeyBase<varVector> > {

    public:

      typedef refParameterKey Type;

      typedef refObject<ParameterKeyBase<refVector>,
                        ParameterKeyBase<varVector> >   ParentType;

      refParameterKey() : ParentType() {}

      refParameterKey(const Type& P) {
        myError("Cannot create from reference parameter key");
      }

      virtual ~refParameterKey() {}

      Type& operator=(const Type& P) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(P));
        return *this;
      }

      virtual void refer(ParentType& P) {
        if(this->index().IsAvailable()) this->RefInfo().remove_self();
        this->index().refer(P.index());
        this->hash().refer(P.hash());
        P.RefInfo().add_before(this->RefInfo());
      }

      virtual void refer(ObjectWStorage<ParameterKeyBase<varVector> >& P) {
        if(this->index().IsAvailable()) this->RefInfo().remove_self();
        this->index().refer(P.index());
        this->hash().refer(P.hash());
        P.RefList().append(this->RefInfo());
      }

  };

}

#endif

