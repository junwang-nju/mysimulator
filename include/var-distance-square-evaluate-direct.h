
#ifndef _Variable_Distance_Square_Evaluate_Direct_H_
#define _Variable_Distance_Square_Evaluate_Direct_H_

#include "distance-square-evaluate-direct-base.h"
#include "object-with-storage.h"
#include "var-vector.h"
#include "var-distance-square.h"

namespace std {

  class varDistanceSqEvalDirect
    : public ObjectWStorage<
               DistanceSqEvalDirectBase<varDistanceSq,varVector> > {

    public:

      typedef varDistanceSqEvalDirect   Type;

      typedef ObjectWStorage<
                DistanceSqEvalDirectBase<varDistanceSq,varVector> >
              ParentType;

      varDistanceSqEvalDirect() : ParentType() {}

      varDistanceSqEvalDirect(const Type& vDED) {
        myError("Cannot create from variable direct evaluator for DistSq");
      }

      ~varDistanceSqEvalDirect() {}

      Type& operator=(const Type& vDED) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vDED));
        return *this;
      }

      template <typename DistSqMethod, template <typename> class VecType>
      Type& operator=(
          const DistanceSqEvalDirectBase<DistSqMethod,VecType>& D) {
        static_cast<ParentType*>(this)->operator=(D);
        return *this;
      }

      void allocate(unsigned int Dim) {
        this->getDistSq().allocate(Dim);
        this->runDistanceSqVec().allocate(Dim);
        this->runDisplacement().allocate(Dim);
      }

  };

}

#endif

