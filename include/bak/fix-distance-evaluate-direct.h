
#ifndef _Fixed_Distance_Evaluate_Direct_H_
#define _Fixed_Distance_Evaluate_Direct_H_

#include "distance-evaluate-direct.h"
#include "fix-vector.h"
#include "ref-vector.h"

namespace std {

  template <unsigned int Dim>
  class fixDistanceEvalDirect : public DistanceEvalDirect<refVector> {

    public:

      typedef fixDistanceEvalDirect<Dim>  Type;

      typedef DistanceEvalDirect<refVector>   ParentType;

    protected:

      fixVector<double,1> inDistData;

      fixVector<double,Dim> inDispData;

    public:

      fixDistanceEvalDirect() : ParentType() {
        this->DistanceSQVec().refer(inDistData);
        this->Displacement().refer(inDispData);
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
      Type& operator=(const DistanceEvalDirect<VecType>& DED) {
        static_cast<ParentType*>(this)->operator=(DED);
        return *this;
      }

      void clear() {}

  };

}

#endif

