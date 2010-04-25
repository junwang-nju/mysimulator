
#ifndef _Distance_Evaluate_Base_H_
#define _Distance_Evaluate_Base_H_

#include "storage-state-name.h"
#include "error-proc.h"
#include "vector-impl.h"

namespace std {

  struct DistanceEvalBase;

  void assign(DistanceEvalBase&, const DistanceEvalBase&);
  void release(DistanceEvalBase&);

  struct DistanceEvalBase {

    typedef DistanceEvalBase  Type;

    double* displacement;
    double* distance;
    unsigned int size;
    unsigned int state;

    DistanceEvalBase()
      : displacement(NULL), distance(NULL), size(0), state(Unused) {}
    DistanceEvalBase(const Type&) {
      myError("Cannot create from Distance Evaluate Base");
    }
    Type& operator=(const Type& DEB) { assign(*this,DEB); return *this; }
    ~DistanceEvalBase() { release(*this); }

    double& operator()() { return *distance; }
    const double& operator()() const { return *distance; }

  };

  bool IsAvailable(const DistanceEvalBase& DEB) {
    return IsAvailable(DEB.distance);
  }

  void release(DistanceEvalBase& DEB) {
    if(DEB.state==Allocated) {
      safe_delete_array(DEB.displacement);
      safe_delete(DEB.distance);
    } else {
      DEB.displacement=NULL;
      DEB.distance=NULL;
    }
    DEB.size=0;
    DEB.state=Unused;
  }

  void assign(DistanceEvalBase& dest, const DistanceEvalBase& src) {
    assert(IsAvailable(src));
    assert(IsAvailable(dest));
    dest()=src();
    unsigned int n=(dest.size<src.size?dest.size:src.size);
    assign(dest.displacement,src.displacement,n);
  }

  void allocate(DistanceEvalBase& DEB, const unsigned int dim) {
    release(DEB);
    DEB.displacement=new double[dim];
    DEB.distance=new double;
    DEB.size=dim;
    DEB.state=Allocated;
  }

  void refer(DistanceEvalBase& dest, const DistanceEvalBase& src) {
    release(dest);
    dest.displacement=src.displacement;
    dest.distance=src.distance;
    dest.size=src.size;
    dest.state=Reference;
  }

}

#endif

