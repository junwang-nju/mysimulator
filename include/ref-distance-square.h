
#ifndef _Reference_Distance_Square_H_
#define _Reference_Distance_Square_H_

#include "distance-square-base.h"
#include "ref-object.h"
#include "ref-vector.h"
#include "var-vector.h"

namespace std {

  template <template <typename> class VecType=varVector>
  class refDistanceSq
    : public refObject<DistanceSqBase<refVector>,DistanceSqBase<VecType> > {

    public:

      typedef refDistanceSq<VecType>  Type;

      typedef refObject<DistanceSqBase<refVector>,DistanceSqBase<VecType> >
              ParentType;

      refDistanceSq() : ParentType() {}

      refDistanceSq(const Type& rD) {
        myError("Cannot create from reference distance-square functor");
      }

      ~refDistanceSq() {}

      Type& operator=(const Type& rD) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(rD));
        return *this;
      }

      virtual void refer(ParentType& rD) {
        if(this->displacement().IsAvailable())  this->RefInfo().remove_self();
        this->displacement().refer(rD.displacement());
        rD.RefInfo().add_before(this->RefInfo());
      }

      virtual void refer(ObjectWStorage<DistanceSqBase<VecType> >& D) {
        if(this->displacement().IsAvailable())  this->RefInfo().remove_self();
        this->displacement().refer(D.displacement());
        D.RefList().append(this->RefInfo());
      }

  };
}

#endif

