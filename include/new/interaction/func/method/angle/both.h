
#ifndef _Interaction_Func_Mehtod_Angle_Both_H_
#define _Interaction_Func_Mehtod_Angle_Both_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"
#include "array/1d/content/scale.h"
#include "intrinsic-type/square-root.h"
#include "interaction/func/impl/common/parameter/name.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void BFuncMethodAngle(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, Array1DContent<T>* Grad,
      Array1DContent<T>* tmvec,
      void (*bfunc)(const T*,const Unique64Bit*,T*,T*)) {
    assert(IsValid(tmvec));
    T* buffer=reinterpret_cast<T*>(P[InteractionBuffer].ptr[0]);
    unsigned int I=idx[0], J=idx[1], K=idx[2];
    T csAngle,ivdij,ivdjk;
    if(buffer==NULL) {
      T dsqij, dsqjk, dsqki, dij, djk, inri, inrk;
      dsqij=DistanceSQ(tmvec[0],X[I],X[J],Geo);
      dsqjk=DistanceSQ(tmvec[1],X[K],X[J],Geo);
      dsqki=DistanceSQ(tmvec[2],X[K],X[I],Geo);
      csAngle=(dsqij+dsqjk-dsqki)*0.5;
      copy(tmvec[2],tmvec[1]);
      shift(tmvec[2],-csAngle/dsqij,tmvec[0]);
      copy(tmvec[3],tmvec[0]);
      shift(tmvec[3],-csAngle/dsqjk,tmvec[1]);
      dij=sqroot(dsqij);
      djk=sqroot(dsqjk);
      ivdij=1./dij;
      ivdjk=1./djk;
      csAngle*=ivdij*ivdjk;
      T snAngle=sqroot(1.-csAngle*csAngle);
      assert(snAngle>1e-8);
      T ivsnAngle=1./snAngle;
      inri=ivdjk*ivsnAngle;
      inrk=ivdij*ivsnAngle;
      scale(tmvec[2],inri);
      scale(tmvec[3],inrk);
    } else {
      csAngle=*buffer;
      ivdij=*(buffer+1);
      ivdjk=*(buffer+2);
      _copy(tmvec[2].start,buffer+3,tmvec[2].size);
      _copy(tmvec[3].start,buffer+3+tmvec[2].size,tmvec[3].size);
    }
    T ee,ef,efi,efk;
    bfunc(&csAngle,P,&ee,&ef);
    Energy+=ee;
    efi=-ef*ivdij;
    efk=-ef*ivdjk;
    shift(Grad[I],+efi,tmvec[2]);
    shift(Grad[J],-efi,tmvec[2]);
    shift(Grad[K],+efk,tmvec[3]);
    shift(Grad[J],-efk,tmvec[3]);
  }

}

#endif

