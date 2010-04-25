
#ifndef _Distance_Evaluate_Direct_H_
#define _Distance_Evaluate_Direct_H_

#include "distance-evaluate-base.h"
#include "distance-displacement-calc.h"

namespace std {

  struct DistanceEvalDirect : public DistanceEvalBase {

    typedef DistanceEvalDirect  Type;
    typedef DistanceEvalBase    ParentType;

    DistanceEvalDirect() : ParentType() {}
    DistanceEvalDirect(const Type&) {
      myError("Cannot create from Distance Evaluate Direct");
    }
    Type& operator=(const Type& DED) { assign(*this,DED); return *this; }
    ~DistanceEvalDirect() { release(*this); }

  };

  bool IsDistanceEvalMethod(const DistanceEvalDirect&) { return true; }

  void update(DistanceEvalDirect&) {}

  template <typename GeomType>
  void Evaluate(DistanceEvalDirect& DED,
                const double* va, const double* vb,
                const unsigned int aidx, const unsigned int bidx,
                const unsigned int dim, const GeomType& Geo,
                const int aoff=iZero, const long astep=lOne,
                const int boff=iZero, const long bstep=lOne) {
    DistanceDisplacementFunc(va,vb,dim,DED.displacement,DED(),Geo,
                             aoff,astep,boff,bstep);
  }

  template <typename GeomType>
  void Evaluate(DistanceEvalDirect& DED,
                const Vector<double>& va, const Vector<double>& vb,
                const unsigned int aidx, const unsigned int bidx,
                const GeomType& Geo) {
    DistanceDisplacementFunc(va,vb,DED.displacementvec,DED(),Geo);
  }

}

#endif

