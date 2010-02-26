
#ifndef _Fixed_Distance_Evaluate_Direct_H_
#define _Fixed_Distance_Evaluate_Direct_H_

#include "distance-evaluate-direct-base.h"
#include "fix-vector.h"
#include "ref-vector.h"

namespace std {

  template <unsigned int Dim>
  class fixDistanceEvalDirect : public DistanceEvalDirectBase<refVector> {

    public:

      typedef fixDistanceEvalDirect<Dim>  Type;

      typedef DistanceEvalDirectBase<refVector>   ParentType;

    protected:

      fixVector<double,1> inDistData;

      fixVector<double,Dim> inDispData;

    public:

      fixDistanceEvalDirect() : ParentType() {
        this->DistanceSQVec().refer(inDistData);
        this->DisplacementVec().refer(inDispData);
      }

      fixDistanceEvalDirect(const Type&) {
        myError("Cannot create from Fixed Direct Distance Evaluate");
      }

      ~fixDistanceEvalDirect() {}

      Type& operator=(const Type& fDED) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fDED));
        return *this;
      }

      template <template <typename> class VecType>
      Type& operator=(const DistanceEvalDirectBase<VecType>& DED) {
        static_cast<ParentType*>(this)->operator=(DED);
        return *this;
      }

      void clear() {}

  };

}

#endif

