
#ifndef _Variable_Distance_Evaluate_Direct_H_
#define _Variable_Distance_Evaluate_Direct_H_

#include "distance-evaluate-direct-base.h"
#include "var-vector.h"

namespace std {

  class varDistanceEvalDirect : DistanceEvalDirectBase<varVector> {

    public:

      typedef varDistanceEvalDirect   Type;

      typedef DistanceEvalDirectBase<varVector>   ParentType;

      varDistanceEvalDirect() : ParentType() {}

      varDistanceEvalDirect(const unsigned int Dim) : ParentType() {
        allocate(Dim);
      }

      varDistanceEvalDirect(const Type&) {
        myError("Cannot create from Variable Direct Distance Evaluate");
      }

      ~varDistanceEvalDirect() {}

      Type& operator=(const Type& vDED) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vDED));
        return *this;
      }

      template <template <typename> class VecType>
      Type& operator=(const DistanceEvalDirectBase<VecType>& DED) {
        static_cast<ParentType*>(this)->operator=(DED);
        return *this;
      }

      void allocate(const unsigned int Dim) {
        this->DistanceSQVec().allocate(1);
        this->DisplacementVec().allocate(Dim);
      }

  };

}

#endif

