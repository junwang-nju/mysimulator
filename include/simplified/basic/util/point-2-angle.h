
#ifndef _Basic_Utility_Point_2_Angle_H_
#define _Basic_Utility_Point_2_Angle_H_

#include "geometry/distance/calc.h"
#include "basic/util/arc-cos.h"

namespace mysimulator {

  template <typename T,ArrayKernelName K,typename T1,ArrayKernelName K1,
            typename T2,ArrayKernelName K2>
  typename __dual_selector<T,typename __dual_selector<T1,T2,__sum>::Type,
                           __sum>::Type
  Angle(Array<Intrinsic<T>,K> const& A,Array<Intrinsic<T1>,K1> const& A1,
        Array<Intrinsic<T2>,K2> const& A2) {
    assert((bool)A);
    assert((bool)A1);
    assert((bool)A2);
    assert(A.size()>=3);
    assert(A1.size()>=3);
    assert(A2.size()>=3);
    assert(Intrinsic<T>::IsFloatingPoint);
    assert(Intrinsic<T1>::IsFloatingPoint);
    assert(Intrinsic<T2>::IsFloatingPoint);
    typedef typename __dual_selector<T1,T2,__sum>::Type TT;
    typedef typename __dual_selector<T,TT,__sum>::Type  DT;
    FreeSpace<3> FS;
    Array<Intrinsic<DT>,ArrayKernelName::Direct3D> Dsp(3);
    const SystemKindName PT=SystemKindName::Particle;
    DT a2=DistanceSQ<PT,PT>(Dsp,A,A1,FS);
    DT b2=DistanceSQ<PT,PT>(Dsp,A,A2,FS);
    DT c2=DistanceSQ<PT,PT>(Dsp,A1,A2,FS);
    DT angle=__acos(a2+b2-c2)*0.5/__square_root(a2*b2);
    Dsp.reset();
    return angle;
  }

}

#endif

