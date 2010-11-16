
#ifndef _Build_Parameter_LJ1012Cut_H_
#define _Build_Parameter_LJ1012Cut_H_

#include "data/name/parameter-lj1012cut.h"
#include "data/basic/unique-parameter.h"

namespace std {

  void BuildParameterLJ1012Cut(UniqueParameter* prm) {
    double r0rc,r0rc2,r0rcTEN,r0rcTLF,rc2;
    rc2=prm[LJ1012CutCutR].d;
    rc2*=rc2;
    r0rc=prm[LJ1012CutCutR].d/prm[LJ1012CutEqRadius].d;
    r0rc2=r0rc*r0rc;
    r0rcTEN=r0rc2*r0rc2;
    r0rcTEN*=r0rcTEN;
    r0rcTEN*=r0rc2;
    r0rcTLF=r0rcTEN*r0rc2;
    copy(prm[LJ1012CutRealRadiusSQ],rc2*(r0rcTEN*r0rc-1.)/(r0rcTLF*r0rc-1.));
  }

}

#include "data/basic/vector.h"

namespace std {
}

#endif

