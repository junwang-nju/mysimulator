
#ifndef _Distance_Evaluate_Base_H_
#define _Distance_Evaluate_Base_H_

#include "storage-state-name.h"
#include "error-proc.h"
#include "vector.h"

namespace std {

  struct DistanceEvalBase;

  void assign(DistanceEvalBase&, const DistanceEvalBase&);
  void release(DistanceEvalBase&);

  struct DistanceEvalBase {

    typedef DistanceEvalBase  Type;

    double* displacement;
    double* distancesq;
    unsigned int size;
    Vector<double> displacementvec;
    unsigned int state;

    DistanceEvalBase()
      : displacement(NULL), distancesq(NULL), size(0),
        displacementvec(), state(Unused) {}
    DistanceEvalBase(const Type&) {
      myError("Cannot create from Distance Evaluate Base");
    }
    Type& operator=(const Type& DEB) { assign(*this,DEB); return *this; }
    ~DistanceEvalBase() { release(*this); }

    double& operator()() { return *distancesq; }
    const double& operator()() const { return *distancesq; }

  };

  bool IsAvailable(const DistanceEvalBase& DEB) {
    return IsAvailable(DEB.distancesq);
  }

  void release(DistanceEvalBase& DEB) {
    if(DEB.state==Allocated) {
      safe_delete_array(DEB.displacement);
      safe_delete(DEB.distancesq);
    } else {
      DEB.displacement=NULL;
      DEB.distancesq=NULL;
    }
    release(DEB.displacementvec);
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
    DEB.distancesq=new double;
    DEB.size=dim;
    refer(DEB.displacementvec,DEB.displacement,DEB.size);
    DEB.state=Allocated;
  }

  void refer(DistanceEvalBase& dest, const DistanceEvalBase& src) {
    release(dest);
    dest.displacement=src.displacement;
    dest.distancesq=src.distancesq;
    dest.size=src.size;
    refer(dest.displacementvec,dest.displacement,dest.size);
    dest.state=Reference;
  }

  template <typename T>
  bool IsDistanceEvalMethod(const T&) { return false; }

  bool IsDistanceEvalMethod(const DistanceEvalBase&) { return true; }

}

#endif

