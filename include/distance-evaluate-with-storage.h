
#ifndef _Distance_Evaluate_With_Storage_H_
#define _Distance_Evaluate_With_Storage_H_

#include "distance-evaluate-base.h"
#include "distance-displacement-calc.h"
#include "matrix-storage.h"

namespace std {

  struct DistanceEvalWStorage;

  void release(DistanceEvalWStorage&);
  void assign(DistanceEvalWStorage&, const DistanceEvalWStorage&);

  struct DistanceEvalWStorage : public DistanceEvalBase {

    typedef DistanceEvalWStorage  Type;
    typedef DistanceEvalBase      ParentType;

    MatrixStorage<double> distsqmat;

    DistanceEvalWStorage() : ParentType(), distsqmat() {}
    DistanceEvalWStorage(const Type&) {
      myError("Cannot create from Distance Evaluate With Storage");
    }
    Type& operator=(const Type& DEW) { assign(*this,DEW); return *this; }
    ~DistanceEvalWStorage() { release(*this); }

  };

  bool IsDistanceEvalMethod(const DistanceEvalWStorage&) { return true; }

  void release(DistanceEvalWStorage& DEW) {
    release(DEW.distsqmat);
    release(static_cast<DistanceEvalBase&>(DEW));
  }

  void assign(DistanceEvalWStorage& dest, const DistanceEvalWStorage& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(dest.distsqmat,src.distsqmat);
    assign(static_cast<DistanceEvalBase&>(dest),
           static_cast<const DistanceEvalBase&>(src));
  }

  void allocate(DistanceEvalWStorage& DEW,
                const unsigned int dim, const unsigned int nunit) {
    allocate(DEW.distsqmat,nunit);
    allocate(static_cast<DistanceEvalBase&>(DEW),dim);
  }

  void refer(DistanceEvalWStorage& dest, const DistanceEvalWStorage& src) {
    refer(dest.distsqmat,src.distsqmat);
    refer(static_cast<DistanceEvalBase&>(dest),
          static_cast<const DistanceEvalBase&>(src));
  }

  void update(DistanceEvalWStorage& DEW) { refresh(DEW.distsqmat); }

  template <typename GeomType>
  void Evaluate(DistanceEvalWStorage& DEW,
                const double* va, const double* vb,
                const unsigned int aidx, const unsigned int bidx,
                const unsigned int dim, const GeomType& Geo,
                const int aoff=iZero, const long astep=lOne,
                const int boff=iZero, const long bstep=lOne) {
    if(IsUpToDate(DEW.distsqmat,aidx,bidx)) {
      DEW()=DEW.distsqmat(aidx,bidx)();
      DisplacementFunc(va,vb,dim,DEW.displacement,Geo,aoff,astep,boff,bstep);
    } else {
      DistanceDisplacementFunc(va,vb,dim,DEW.displacement,DEW(),Geo,
                               aoff,astep,boff,bstep);
      update(DEW.distsqmat,aidx,bidx,DEW());
    }
  }

  template <typename GeomType>
  void Evaluate(DistanceEvalWStorage& DEW,
                const Vector<double>& va, const Vector<double>& vb,
                const unsigned int aidx, const unsigned int bidx,
                const GeomType& Geo) {
    if(IsUpToDate(DEW.distsqmat,aidx,bidx)) {
      DEW()=DEW.distsqmat(aidx,bidx)();
      DisplacementFunc(va,vb,DEW.displacementvec,Geo);
    } else {
      DistanceDisplacementFunc(va,vb,DEW.displacementvec,DEW(),Geo);
      update(DEW.distsqmat,aidx,bidx,DEW());
    }
  }

}

#endif

