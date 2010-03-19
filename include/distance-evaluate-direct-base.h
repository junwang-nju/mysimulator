
#ifndef _Distance_Evaluate_Direct_Base_H_
#define _Distance_Evaluate_Direct_Base_H_

#include "distance-evaluate-base.h"
#include "distance-displacement-calc.h"

namespace std {

  template <template <typename> class VecType>
  class DistanceEvalDirectBase : public DistanceEvalBase<VecType> {

    public:

      typedef DistanceEvalDirectBase<VecType>   Type;

      typedef DistanceEvalBase<VecType>   ParentType;

      static const unsigned int DistanceEvalMethod;

      DistanceEvalDirectBase() : ParentType() {}

      DistanceEvalDirectBase(const Type&) {
        myError("Cannot create from Direct Distance Evaluate Base");
      }

      ~DistanceEvalDirectBase() {}

      Type& operator=(const Type& DEDB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(DEDB));
        return *this;
      }

      template <template <typename> class iVecType>
      Type& operator=(const DistanceEvalDirectBase<iVecType>& DEDB) {
        static_cast<ParentType*>(this)->operator=(DEDB);
        return *this;
      }

      template <typename GeomType>
      void Evaluate(const VectorBase<double>& va, const VectorBase<double>& vb,
                    const unsigned int aIdx, const unsigned int bIdx,
                    const GeomType& Geo) {
        DistanceDisplacementFunc(va,vb,this->Displacement(),
                                 this->DistanceSQVec()[0],Geo);
      }

      virtual void update() {}

  };

  template <template <typename> class VecType>
  const unsigned int
  DistanceEvalDirectBase<VecType>::DistanceEvalMethod=1;

}

#endif

