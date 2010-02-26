
#ifndef _Reference_Distance_Square_Evaluate_Direct_H_
#define _Reference_Distance_Square_Evaluate_Direct_H_

#include "distance-square-evaluate-direct-base.h"
#include "ref-vector.h"
#include "var-vector.h"
#include "ref-distance-square.h"
#include "var-distance-square.h"

namespace std {

  template <typename DistSqMethod=varDistanceSq,
            template <typename> class VecType=varVector>
  class refDistanceSqEvalDirect
    : public refObject<DistanceSqEvalDirectBase<refDistanceSq<VecType>,
                                                refVector>,
                       DistanceSqEvalDirectBase<DistSqMethod,VecType> > {

    public:

      typedef refDistanceSqEvalDirect<DistSqMethod,VecType> Type;

      typedef refObject<DistanceSqEvalDirectBase<refDistanceSq<VecType>,
                                                 refVector>,
                        DistanceSqEvalDirectBase<DistSqMethod,VecType> >
              ParentType;

      refDistanceSqEvalDirect() : ParentType() {}

      refDistanceSqEvalDirect(const Type& rDED) {
        myError("Cannot create from reference direct evaluator of DistSq");
      }

      ~refDistanceSqEvalDirect() {}

      Type& operator=(const Type& rDED) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(rDED));
        return *this;
      }

      template <typename iDistSqMethod, template <typename> class iVecType>
      Type& operator=(
          const DistanceSqEvalDirectBase<iDistSqMethod,iVecType>& D) {
        static_cast<ParentType*>(this)->operator=(D);
        return *this;
      }

      virtual void refer(ParentType& rDED) {
        if(this->runDistanceSqVec().IsAvailable())
          this->RefInfo().remove_self();
        this->getDistSq().refer(rDED.getDistSq());
        this->runDistanceSqVec().refer(rDED.runDistanceSqVec());
        this->runDisplacement().refer(rDED.runDisplacement());
        rDED.RefInfo().add_before(this->RefInfo());
      }

      virtual void refer(
          ObjectWStorage<DistanceSqEvalDirectBase<DistSqMethod,VecType> >& D) {
        if(this->runDistanceSqVec().IsAvailable())
          this->RefInfo().remove_self();
        this->getDistSq().refer(D.getDistSq());
        this->runDistanceSqVec().refer(D.runDistanceSqVec());
        this->runDisplacement().refer(D.runDisplacement());
        D.RefList().append(this->RefInfo());
      }

  };

}

#endif

