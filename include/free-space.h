
#ifndef _Free_Space_H_
#define _Free_Space_H_

#include "error-proc.h"
#include "geometry-name.h"
#include "displacement-direct.h"

namespace std {

  struct FreeSpace {

    typedef FreeSpace Type;

    static const unsigned int TypeID;

    FreeSpace() {}
    FreeSpace(const  Type&) { myError("Cannot create from Free Space"); }
    Type& operator=(const Type&) { return *this; }
    ~FreeSpace() {}

  };

  const unsigned int FreeSpace::TypeID=FreeSpaceType;

  bool IsAvailable(const FreeSpace&) { return true; }
  bool IsGeometry(const FreeSpace&) { return true; }

  void assign(FreeSpace& dest, const FreeSpace& src) {}
  void release(FreeSpace&) {}
  void allocate(FreeSpace&, const unsigned int dim) {}
  void refer(FreeSpace& dest, const FreeSpace& src) {}

  void DisplacementFunc(const double* va, const double* vb,
                        const unsigned int dim, double* Dsp,
                        const FreeSpace& FS,
                        const int aoff=iZero, const long astep=lOne,
                        const int boff=iZero, const long bstep=lOne,
                        const int doff=iZero, const long dstep=lOne) {
    DisplacementFunc(va,vb,dim,Dsp,aoff,astep,boff,bstep,doff,dstep);
  }

  void DisplacementFunc(const Vector<double>& va, const Vector<double>& vb,
                        Vector<double>& Dsp, const FreeSpace& FS) {
    DisplacementFunc(va,vb,Dsp);
  }

}

#endif

