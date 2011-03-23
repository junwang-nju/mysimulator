
#ifndef _Overlap_H_
#define _Overlap_H_

#include "operation/basic/vector-op.h"

namespace std {

  bool LineSphereOverlap(
      const Vector<double>& v1, const Vector<double>& v2,
      const Vector<double>& vc, const double rc) {
    assert(v1.size==3);
    assert(v2.size==3);
    assert(vc.size==3);
    Vector<double> vline(3), vr(3);
    double l,rcth,rsth2;
    copy(vline,v2);
    shift(vline,-dOne,v1);
    l=norm(vline);
    scale(vline,1./l);
    copy(vr,vc);
    shift(vr,-dOne,v1);
    rcth=dot(vr,vline);
    rsth2=normSQ(vr)-rcth*rcth;
    return (rsth2<rc*rc)&&(l>rcth);
  }

}

#endif

