
#ifndef _Reference_Distance_Evaluate_Direct_H_
#define _Reference_Distance_Evaluate_Direct_H_

#include "distance-evaluate-direct-base.h"
#include "ref-vector.h"

namespace std {

  class refDistanceEvalDirect : public DistanceEvalDirectBase<refVector> {

    public :

      typedef refDistanceEvalDirect   Type;

      typedef DistanceEvalDirectBase<refVector>   ParentType;

      refDistanceEvalDirect() : ParentType() {}

      refDistanceEvalDirect(const Type&) {
        myError("Cannot create from Reference Direct Distance Evaluate");
      }

      ~refDistanceEvalDirect() {}

      Type& operator=(const Type& rDED) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(rDED));
        return *this;
      }

      template <template <typename> class VecType>
      Type& operator=(const DistanceEvalDirectBase<VecType>& DED) {
        static_cast<ParentType*>(this)->operator=(DED);
        return *this;
      }

      template <template <typename> class VecType>
      void refer(const DistanceEvalDirectBase<VecType>& DED) {
        this->DistanceSQVec().refer(DED.DistanceSQVec());
        this->Displacement().refer(DED.Displacement());
      }

  };

}

#endif

