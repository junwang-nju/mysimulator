
#ifndef _Functional_LJ1012Cut_Diff_H_
#define _Functional_LJ1012Cut_Diff_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/lj1012cut/parameter/name.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ1012Cut(const T& dsq,const UniqueParameter64Bit* prm,T& diff) {
    if(dsq>prm[LJ1012CutCutRSq].value<T>())   diff=0;
    else {
      T ivd2=1./dsq;
      T ivd=sqroot(ivd2);
      T sgr2=prm[LJ1012CutRealRadiusSq].value<T>()*ivd2;
      T sgr10;
      sgr10=sgr2*sgr2;
      sgr10*=sgr10;
      sgr10*=sgr2;
      diff=prm[LJ1012CutSixtyRealEnergyDepth].value<T>()*sgr10*(1.-sgr2)*ivd2;
      diff-=prm[LJ1012CutKc].value<T>()*ivd;
    }
  }

}

#endif

