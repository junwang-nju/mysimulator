
#ifndef _Reference_Parameter_List_H_
#define _Reference_Parameter_List_H_

#include "parameter-list-base.h"
#include "ref-vector.h"

namespace std {

  class refParameterList : public ParameterListBase<refVector> {

    public:

      typedef refParameterList    Type;

      typedef ParameterListBase<refVector>  ParentType;

      refParameterList() : ParentType() {}

      refParameterList(const Type&) {
        myError("Cannot create from reference Parameter List");
      }

      ~refParameterList() {}

      Type& operator=(const Type& rPL) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(rPL));
        return *this;
      }

      template <template <typename> class VecType>
      Type& operator=(const ParameterListBase<VecType>& PL) {
        static_cast<ParentType*>(this)->operator=(PL);
        return *this;
      }

      template <template <typename> class VecType>
      void refer(const ParameterListBase<VecType>& PL) {
        this->keylist().refer(PL.keylist());
        this->valuelist().refer(PL.valuelist());
        this->ptrhashtree()=PL.ptrhashtree();
      }

  };

}

#endif

