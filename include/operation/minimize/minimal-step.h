
#ifndef _Minimal_Step_H_
#define _Minimal_Step_H_

#include "data/basic/property-list.h"
#include "data/minimizer/line-minimizer-buffer-base.h"

namespace std {

  template <typename T>
  T MinimalStep(const Vector<T>& Origin, const Vector<T>& Dirc,
                const Vector<unsigned int>& iMask, const unsigned int& dof) {
    assert(IsAvailable(Origin));
    assert(IsAvailable(Dirc));
    assert(IsAvailable(iMask));
    assert(Origin.size==Dirc.size);
    assert(Origin.size==iMask.size);
    T mstep=0., tmd;
    for(unsigned int i=0;i<iMask.size;++i) {
      if(iMask[i]==0) continue;
      tmd=absval(Origin[i]);
      tmd=(tmd<1.?Dirc[i]:Dirc[i]/tmd);
      mstep+=tmd*tmd;
    }
    return RelDelta<T>()*sqroot(dof/mstep);
  }

  template <typename IType,typename PmType,typename T>
  T MinimalStep(const LineMinimizerBufferBase<IType,Vector,PmType,T>& B,
                const Vector<T>& Origin, const Vector<T>& Dirc) {
    assert(IsAvailable(B));
    return MinimalStep(Origin,Dirc,B.MinIMask,B.DOF());
  }

  template <typename IType,typename PmType,typename T>
  T MinimalStep(const LineMinimizerBufferBase<IType,PropertyList,PmType,T>& B,
                const PropertyList<T>& Origin,const PropertyList<T>& Dirc) {
    assert(IsAvailable(B));
    return MinimalStep(static_cast<const Vector<T>&>(Origin),
                       static_cast<const Vector<T>&>(Dirc),
                       static_cast<const Vector<unsigned int>&>(B.MinIMask),
                       B.DOF());
  }

}

#endif
