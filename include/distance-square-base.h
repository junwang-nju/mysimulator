
#ifndef _Distance_Square_Base_H_
#define _Distance_Square_Base_H_

#include "vector-op.h"

namespace std {

  template <template <typename> class VecType>
  class DistanceSqBase {

    public:

      typedef DistanceSqBase<VecType>   Type;

    protected:

      VecType<double> Displacement;

    public:

      DistanceSqBase() : Displacement() {}

      DistanceSqBase(const Type& D) {
        myError("Cannot create from distance square functor");
      }

      ~DistanceSqBase() {}

      Type& operator=(const Type& D) {
        Displacement=D.Displacement;
        return *this;
      }

      VecType<double>& displacement() { return Displacement; }

      const VecType<double>& displacement() const { return Displacement; }

      void clear() { Displacement.clear(); }

      template <typename GeomType>
      void CalcDisplacement(const VectorBase<double>& va,
                            const VectorBase<double>& vb, const GeomType& Geo){
        DisplacementFunc(va,vb,Displacement,Geo);
      }

      template <typename GeomType>
      double Calc(const VectorBase<double>& va, const VectorBase<double>& vb,
                  const GeomType& Geo) {
        CalcDisplacement(va,vb,Geo);
        return normSQ(Displacement);
      }

  };

}

#endif

