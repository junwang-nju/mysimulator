
#ifndef _Distance_Evaluate_Direct_H_
#define _Distance_Evaluate_Direct_H_

#include "distance-evaluate-base.h"
#include "distance-displacement-calc.h"

namespace std {

  struct DistanceEvalDirect;

  void release(DistanceEvalDirect&);
  void assign(DistanceEvalDirect&, const DistanceEvalDirect&);

  struct DistanceEvalDirect : public DistanceEvalBase {

    typedef DistanceEvalDirect  Type;
    typedef DistanceEvalBase    ParentType;

    Vector<double> displacementvec;

    DistanceEvalDirect() : ParentType(), displacementvec() {}
    DistanceEvalDirect(const Type&) {
      myError("Cannot create from Distance Evaluate Direct");
    }
    Type& operator=(const Type& DED) { assign(*this,DED); return *this; }
    ~DistanceEvalDirect() { release(*this); }

  };

  bool IsDistanceEvalMethod(const DistanceEvalDirect&) { return true; }

  void release(DistanceEvalDirect& DED) {
    release(DED.displacementvec);
    release(static_cast<DistanceEvalBase&>(DED));
  }

  void assign(DistanceEvalDirect& dest, const DistanceEvalDirect& src) {
    assign(static_cast<DistanceEvalBase&>(dest),
           static_cast<const DistanceEvalBase&>(src));
  }

  void allocate(DistanceEvalDirect& DED, const unsigned int dim) {
    allocate(static_cast<DistanceEvalBase&>(DED),dim);
    DED.displacementvec()=DED.displacement;
    DED.displacementvec.size=DED.size;
    DED.displacementvec.state=Reference;
  }

  void refer(DistanceEvalDirect& dest, const DistanceEvalDirect& src) {
    refer(static_cast<DistanceEvalBase&>(dest),
          static_cast<const DistanceEvalBase&>(src));
    dest.displacementvec()=dest.displacement;
    dest.displacementvec.size=dest.size;
    dest.displacementvec.state=Reference;
  }

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

