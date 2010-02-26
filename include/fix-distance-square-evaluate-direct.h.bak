
#ifndef _Fixed_Distance_Square_Evaluate_Direct_H_
#define _Fixed_Distance_Square_Evaluate_Direct_H_

#include "distance-square-evaluate-direct-base.h"
#include "object-with-storage.h"
#include "fix-vector.h"
#include "ref-vector.h"
#include "fix-distance-square.h"

namespace std {

  template <unsigned int Dim>
  class fixDistanceSqEvalDirect
    : public ObjectWStorage<DistanceSqEvalDirectBase<fixDistanceSq<Dim>,
                                                     refVector> > {

    public:

      typedef fixDistanceSqEvalDirect   Type;

      typedef ObjectWStorage<DistanceSqEvalDirectBase<fixDistanceSq<Dim>,
                                                      refVector> >
              ParentType;

    protected:

      fixVector<double,1> DistSqData;

      fixVector<double,Dim> DisplacementData;

    public:

      fixDistanceSqEvalDirect() : ParentType() {
        this->runDistanceSqVec().refer(DistSqData);
        this->runDisplacement().refer(DisplacementData);
      }

      fixDistanceSqEvalDirect(const Type& fDED) {
        myError("Cannot create from fixed direct evaluator of DistSq");
      }

      ~fixDistanceSqEvalDirect() {}

      Type& operator=(const Type& fDED) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fDED));
        return *this;
      }

      template <typename DistSqMethod, template <typename> class VecType>
      Type& operator=(
          const DistanceSqEvalDirectBase<DistSqMethod,VecType>& DED) {
        static_cast<ParentType*>(this)->operator=(DED);
        return *this;
      }

      void clear() {}

  };
}

#endif

