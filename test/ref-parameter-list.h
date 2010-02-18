
#ifndef _Reference_Parameter_List_H_
#define _Reference_Parameter_List_H_

#include "parameter-list-base.h"
#include "ref-object.h"

namespace std {

  class refParameterList
    : public refObject<ParameterListBase<refVector>,
                       ParameterListBase<varVector> > {

    public:
    
      typedef refParameterList    Type;
      
      typedef refObject<ParameterListBase<refVector>,
                        ParameterListBase<varVector> >  ParentType;

      refParameterList() : ParentType() {}

      refParameterList(const Type& P) {
        myError("Cannot create from reference parameter list");
      }

      ~refParameterList() {}

      Type& operator=(const Type& P) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(P));
        return *this;
      }

      virtual void refer(ParentType& P) {
        if(this->keylist().IsAvailable()) this->RefInfo().remove_self();
        this->keylist().refer(P.keylist());
        this->valuelist().refer(P.valuelist());
        this->hashtree().refer(P.hashtree());
        P.RefInfo().add_before(this->RefInfo());
      }

      virtual void refer(ObjectWStorage<ParameterListBase<varVector> >& P) {
        if(this->keylist().IsAvailable()) this->RefInfo().remove_self();
        this->keylist().refer(P.keylist());
        this->valuelist().refer(P.valuelist());
        this->hashtree().refer(P.hashtree());
        P.RefList().append(this->RefInfo());
      }

  };

}

#endif
