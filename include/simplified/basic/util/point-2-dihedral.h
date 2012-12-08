
#ifndef _Basic_Utility_Point_2_Dihedral_H_
#define _Basic_Utility_Point_2_Dihedral_H_

#include "geometry/distance/calc.h"
#include "basic/util/arc-cos.h"

namespace mysimulator {

  template <typename T1,ArrayKernelName K1,typename T2,ArrayKernelName K2,
            typename T3,ArrayKernelName K3,typename T4,ArrayKernelName K4>
  typename __dual_selector<
    typename __dual_selector<T1,T2,__sum>::Type,
    typename __dual_selector<T3,T4,__sum>::Type,__sum>::Type
  Dihedral(
      Array<Intrinsic<T1>,K1> const& A1, Array<Intrinsic<T2>,K2> const& A2,
      Array<Intrinsic<T3>,K3> const& A3, Array<Intrinsic<T4>,K4> const& A4) {
    assert((bool)A1);
    assert((bool)A2);
    assert((bool)A3);
    assert((bool)A4);
    assert(A1.size()>=3);
    assert(A2.size()>=3);
    assert(A3.size()>=3);
    assert(A4.size()>=3);
    assert(Intrinsic<T1>::IsFloatingPoint);
    assert(Intrinsic<T2>::IsFloatingPoint);
    assert(Intrinsic<T3>::IsFloatingPoint);
    assert(Intrinsic<T4>::IsFloatingPoint);
    typedef typename __dual_selector<T1,T2,__sum>::Type TT1;
    typedef typename __dual_selector<T3,T4,__sum>::Type TT2;
    typedef typename __dual_selector<TT1,TT2,__sum>::Type DT;
    Array<Intrinsic<DT>,ArrayKernelName::Direct3D>
      B1(3),B2(3),B3(3),N1(3),N2(3),Ax(3);
    FreeSpace<3> FS;
    const SystemKindName PT=SystemKindName::Particle;
    DisplacementCalc<PT,PT>(B1,A2,A1,FS);
    DisplacementCalc<PT,PT>(B2,A3,A2,FS);
    DisplacementCalc<PT,PT>(B3,A4,A3,FS);
    cross(N1,B1,B2);
    cross(N2,B2,B3);
    DT lN1=NormSQ(N1);
    DT lN2=NormSQ(N2);
    DT csDih=Dot(N1,N2)/__square_root(lN1*lN2);
    cross(Ax,N1,N2);
    DT Dih=__acos(csDih)*(Dot(Ax,B2)>0?1:-1);
    Ax.reset();
    N2.reset();
    N1.reset();
    B3.reset();
    B2.reset();
    B1.reset();
    return Dih;
  }

}

#endif

