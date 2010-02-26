
#ifndef _Distance_Square_Evaluate_Base_H_
#define _Distance_Square_Evaluate_Base_H_

#include "vector-base.h"

namespace std {

  template <typename DistSqMethod, template <typename> class VecType>
  class DistanceSqEvalBase {

    public:

      typedef DistanceSqEvalBase<DistSqMethod,VecType>  Type;

    protected:

      DistSqMethod  GetDistSq;

      VecType<double> nowDistSq;

      VecType<double> nowDisplacement;

    public:

      DistanceSqEvalBase() : GetDistSq(), nowDistSq(), nowDisplacement() {}

      DistanceSqEvalBase(const Type& DEB) {
        myError("Cannot create from evaluation base of distance-square");
      }

      ~DistanceSqEvalBase() { clear(); }

      void clear() {
        GetDistSq.clear();
        nowDistSq.clear();
        nowDisplacement.clear();
      }

      Type& operator=(const Type& DEB) {
        GetDistSq=DEB.GetDistSq;
        nowDistSq=DEB.nowDistSq;
        nowDisplacement=DEB.nowDisplacement;
        return *this;
      }

      template <typename iDistSqMethod, template <typename> class iVecType>
      Type& operator=(const DistanceSqEvalBase<iDistSqMethod,iVecType>& D) {
        GetDistSq=D.getDistSq();
        nowDistSq[0]=D.distanceSq();
        nowDisplacement=D.displacement();
        return *this;
      }

      const double& distanceSq() const { return nowDistSq[0]; }

      VecType<double>& runDistanceSqVec() { return nowDistSq; }

      const VecType<double>& displacement() const { return nowDisplacement; }

      VecType<double>& runDisplacement() { return nowDisplacement; }

      DistSqMethod& getDistSq() { return GetDistSq; }

      const DistSqMethod& getDistSq() const { return GetDistSq; }

      virtual void update() = 0;

  };

}

#endif

