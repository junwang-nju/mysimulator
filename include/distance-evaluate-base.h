
#ifndef _Distance_Evaluate_H_
#define _Distance_Evaluate_H_

#include "vector-base.h"

namespace std {

  template <template <typename> class VecType>
  class DistanceEvalBase {

    public:

      typedef DistanceEvalBase<VecType> Type;

    protected:

      VecType<double> nowDist;

      VecType<double> nowDisplacement;

    public:

      DistanceEvalBase() : nowDist(), nowDisplacement() {}

      DistanceEvalBase(const Type&) {
        myError("Cannot create from Distance Evaluation Base");
      }

      ~DistanceEvalBase() { clear(); }

      void clear() {
        nowDist.clear();
        nowDisplacement.clear();
      }

      Type& operator=(const Type& DEB) {
        nowDist=DEB.nowDist;
        nowDisplacement=DEB.nowDisplacement;
        return *this;
      }

      template <template <typename> class iVecType>
      Type& operator=(const DistanceEvalBase<iVecType>& DEB) {
        nowDist[0]=DEB.DistanceSQ();
        nowDisplacement=DEB.Displacement();
        return *this;
      }

      const double& DistanceSQ() const { return nowDist[0]; }

      VecType<double>& DistanceSQVec() { return nowDist; }

      const VecType<double>& DistanceSQVec() const { return nowDist; }

      const VecType<double>& Displacement() const { return nowDisplacement; }

      VecType<double>& Displacement() { return nowDisplacement; }

      virtual void update() = 0;

  };

}

#endif

