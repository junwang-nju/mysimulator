
#ifndef _Interaction_Func_Method_Angle_Gradient_H_
#define _Interaction_Func_Method_Angle_Gradient_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"
#include "array/1d/content/scale.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename GeomType,typename T>
  void GFuncMethodAngle(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, Array1DContent<T>* Grad, Array1DContent<T>* tmvec,
      void (*dfunc)(const T&,const Unique64Bit*,T&)) {
    unsigned int I=idx[0], J=idx[1], K=idx[2];
    T dsqij, dsqjk, dsqki, dij, djk, nri, nrk;
    dsqij=DistanceSQ(tmvec[0],X[I],X[J],Geo);
    dsqjk=DistanceSQ(tmvec[1],X[K],X[J],Geo);
    dsqki=DistanceSQ(tmvec[2],X[K],X[I],Geo);
    T csAngle=(dsqij+dsqjk-dsqki)*0.5, snAngle;
    copy(tmvec[2],tmvec[1]);
    shift(tmvec[2],-csAngle/dsqij,tmvec[0]);
    copy(tmvec[3],tmvec[0]);
    shift(tmvec[3],-csAngle/dsqjk,tmvec[1]);
    dij=sqroot(dsqij);
    djk=sqroot(dsqjk);
    csAngle/=dij*djk;
    snAngle=sqroot(1.-csAngle*csAngle);
    nri=djk*snAngle;
    nrk=dij*snAngle;
    if(nri<=1e-8) {
      COut<<"============="<<Endl;
      COut<<nri<<Endl;
      COut<<csAngle<<"\t"<<snAngle<<Endl;
      COut<<djk<<Endl;
    }
    assert(nri>1e-8);
    assert(nrk>1e-8);
    scale(tmvec[2],1./nri);
    scale(tmvec[3],1./nrk);
    T ef, efi, efk;
    dfunc(csAngle,P,ef);
    efi=-ef/dij;
    efk=-ef/djk;
    shift(Grad[I],+efi,tmvec[2]);
    shift(Grad[J],-efi,tmvec[2]);
    shift(Grad[K],+efk,tmvec[3]);
    shift(Grad[J],-efk,tmvec[3]);
  }

}

#endif

