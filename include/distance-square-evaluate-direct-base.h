
#ifndef _Distance_Square_Evaluation_Direct_Base_H_
#define _Distance_Square_Evaluation_Direct_Base_H_

#include "distance-square-evaluate-base.h"

namespace std {

  template <typename DistSqMethod, template <typename> class VecType>
  class DistanceSqEvalDirectBase
    : public DistanceSqEvalBase<DistSqMethod,VecType> {

    public:

      typedef DistanceSqEvalDirectBase<DistSqMethod,VecType>  Type;

      typedef DistanceSqEvalBase<DistSqMethod,VecType>  ParentType;

      DistanceSqEvalDirectBase() : ParentType() {}

      DistanceSqEvalDirectBase(const Type& DEB) {
        myError("Cannot create from direct evaluation base of distance-sq");
      }

      ~DistanceSqEvalDirectBase() {}

      Type& operator=(const Type& DEB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(DEB));
        return *this;
      }

      template <typename iDistSqMethod, template <typename> class iVecType>
      Type& operator=(
          const DistanceSqEvalDirectBase<iDistSqMethod,iVecType>& D) {
        static_cast<ParentType*>(this)->operator=(D);
        return *this;
      }

      template <typename GeomType>
      const double& Distance(
          const VectorBase<double>& va, const VectorBase<double>& vb,
          unsigned int aIdx, unsigned bIdx, const GeomType& Geo) {
        this->runDistanceSqVec()[0]=this->getDistSq().Calc(va,vb,Geo);
        return this->runDistanceSqVec()[0];
      }

      template <typename GeomType>
      const double& DistanceDisplacement(
          const VectorBase<double>& va, const VectorBase<double>& vb,
          unsigned int aIdx, unsigned bIdx, const GeomType& Geo) {
        this->runDistanceSqVec()[0]=this->getDistSq().Calc(va,vb,Geo);
        this->runDisplacement()=this->getDistSq().displacement();
        return this->runDistanceSqVec()[0];
      }

      virtual void update() {}

  };

}

#endif

