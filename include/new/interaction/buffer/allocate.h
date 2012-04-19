
#ifndef _Interaction_Buffer_Allocate_H_
#define _Interaction_Buffer_Allocate_H_

#include "interaction/buffer/interface.h"
#include "interaction/func/name.h"
#include "array/1d/allocate.h"
#include "array/2d/allocate.h"

#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "interaction/func/impl/dihedral/common/buffer/pre-name.h"

#include "interaction/func/impl/pairwise/common/buffer/vec-name.h"
#include "interaction/func/impl/angle/common/buffer/vec-name.h"
#include "interaction/func/impl/dihedral/common/buffer/vec-name.h"

#include "interaction/func/impl/angle/common/buffer/inf-name.h"
#include "interaction/func/impl/dihedral/common/buffer/inf-name.h"

#include "interaction/func/impl/pairwise/harmonic/buffer/post-name.h"
#include "interaction/func/impl/pairwise/harmonic/buffer/p2p-4func.h"
#include "interaction/func/impl/pairwise/harmonic/buffer/p2p-4diff.h"
#include "interaction/func/impl/pairwise/harmonic/buffer/p2p-4both.h"

#include "interaction/func/impl/pairwise/core12/buffer/post-name.h"
#include "interaction/func/impl/pairwise/core12/buffer/p2p-4func.h"
#include "interaction/func/impl/pairwise/core12/buffer/p2p-4diff.h"
#include "interaction/func/impl/pairwise/core12/buffer/p2p-4both.h"

#include "interaction/func/impl/pairwise/corelj612/buffer/post-name.h"
#include "interaction/func/impl/pairwise/corelj612/buffer/p2p-4func.h"
#include "interaction/func/impl/pairwise/corelj612/buffer/p2p-4diff.h"
#include "interaction/func/impl/pairwise/corelj612/buffer/p2p-4both.h"

#include "interaction/func/impl/pairwise/lj612/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj612/buffer/p2p-4func.h"
#include "interaction/func/impl/pairwise/lj612/buffer/p2p-4diff.h"
#include "interaction/func/impl/pairwise/lj612/buffer/p2p-4both.h"

#include "interaction/func/impl/pairwise/lj612cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj612cut/buffer/p2p-4func.h"
#include "interaction/func/impl/pairwise/lj612cut/buffer/p2p-4diff.h"
#include "interaction/func/impl/pairwise/lj612cut/buffer/p2p-4both.h"

#include "interaction/func/impl/pairwise/lj1012/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/p2p-4func.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/p2p-4diff.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/p2p-4both.h"

#include "interaction/func/impl/pairwise/lj1012cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj1012cut/buffer/p2p-4func.h"
#include "interaction/func/impl/pairwise/lj1012cut/buffer/p2p-4diff.h"
#include "interaction/func/impl/pairwise/lj1012cut/buffer/p2p-4both.h"

#include "interaction/func/impl/pairwise/coulomb/buffer/post-name.h"
#include "interaction/func/impl/pairwise/coulomb/buffer/p2p-4func.h"
#include "interaction/func/impl/pairwise/coulomb/buffer/p2p-4diff.h"
#include "interaction/func/impl/pairwise/coulomb/buffer/p2p-4both.h"

#include "interaction/func/impl/pairwise/dist-coulomb/buffer/post-name.h"
#include "interaction/func/impl/pairwise/dist-coulomb/buffer/p2p-4func.h"
#include "interaction/func/impl/pairwise/dist-coulomb/buffer/p2p-4diff.h"
#include "interaction/func/impl/pairwise/dist-coulomb/buffer/p2p-4both.h"

#include "interaction/func/impl/angle/common/buffer/getpre-4func.h"
#include "interaction/func/impl/angle/common/buffer/getpre-4diff.h"
#include "interaction/func/impl/angle/common/buffer/getpre-4both.h"

#include "interaction/func/impl/angle/harmonic/buffer/post-name.h"
#include "interaction/func/impl/angle/harmonic/buffer/p2p-4func.h"
#include "interaction/func/impl/angle/harmonic/buffer/p2p-4diff.h"
#include "interaction/func/impl/angle/harmonic/buffer/p2p-4both.h"

#include "interaction/func/impl/dihedral/common/buffer/getpre-4func.h"
#include "interaction/func/impl/dihedral/common/buffer/getpre-4diff.h"
#include "interaction/func/impl/dihedral/common/buffer/getpre-4both.h"

#include "interaction/func/impl/dihedral/periodic/buffer/post-name.h"
#include "interaction/func/impl/dihedral/periodic/buffer/p2p-4func.h"
#include "interaction/func/impl/dihedral/periodic/buffer/p2p-4diff.h"
#include "interaction/func/impl/dihedral/periodic/buffer/p2p-4both.h"

namespace mysimulator {

  template <typename T>
  void allocate(InteractionBuffer<T>& B, const InteractionFuncName& tag,
                const unsigned int& dim) {
    release(B);
    switch(tag) {
      case Harmonic:
        allocate(B.pre,PairwiseCommonBufferPreSize);
        allocate(B.post,HarmonicBufferPostSize);
        allocate(B.tmvec,PairwiseCommonBufferNumberVectors,dim);
        release(B.inf);
        B.P2PFunc=HarmonicPre2Post4Func<T>;
        B.P2PDiff=HarmonicPre2Post4Diff<T>;
        B.P2PBoth=HarmonicPre2Post4Both<T>;
        B.GetPreFunc=NULL;
        B.GetPreDiff=NULL;
        B.GetPreBoth=NULL;
        break;
      case Core12:
        allocate(B.pre,PairwiseCommonBufferPreSize);
        allocate(B.post,Core12BufferPostSize);
        allocate(B.tmvec,PairwiseCommonBufferNumberVectors,dim);
        release(B.inf);
        B.P2PFunc=Core12Pre2Post4Func<T>;
        B.P2PDiff=Core12Pre2Post4Diff<T>;
        B.P2PBoth=Core12Pre2Post4Both<T>;
        B.GetPreFunc=NULL;
        B.GetPreDiff=NULL;
        B.GetPreBoth=NULL;
        break;
      case CoreLJ612:
        allocate(B.pre,PairwiseCommonBufferPreSize);
        allocate(B.post,CoreLJ612BufferPostSize);
        allocate(B.tmvec,PairwiseCommonBufferNumberVectors,dim);
        release(B.inf);
        B.P2PFunc=CoreLJ612Pre2Post4Func<T>;
        B.P2PDiff=CoreLJ612Pre2Post4Diff<T>;
        B.P2PBoth=CoreLJ612Pre2Post4Both<T>;
        B.GetPreFunc=NULL;
        B.GetPreDiff=NULL;
        B.GetPreBoth=NULL;
        break;
      case LJ612:
        allocate(B.pre,PairwiseCommonBufferPreSize);
        allocate(B.post,LJ612BufferPostSize);
        allocate(B.tmvec,PairwiseCommonBufferNumberVectors,dim);
        release(B.inf);
        B.P2PFunc=LJ612Pre2Post4Func<T>;
        B.P2PDiff=LJ612Pre2Post4Diff<T>;
        B.P2PBoth=LJ612Pre2Post4Both<T>;
        B.GetPreFunc=NULL;
        B.GetPreDiff=NULL;
        B.GetPreBoth=NULL;
        break;
      case LJ612Cut:
        allocate(B.pre,PairwiseCommonBufferPreSize);
        allocate(B.post,LJ612CutBufferPostSize);
        allocate(B.tmvec,PairwiseCommonBufferNumberVectors,dim);
        release(B.inf);
        B.P2PFunc=LJ612CutPre2Post4Func<T>;
        B.P2PDiff=LJ612CutPre2Post4Diff<T>;
        B.P2PBoth=LJ612CutPre2Post4Both<T>;
        B.GetPreFunc=NULL;
        B.GetPreDiff=NULL;
        B.GetPreBoth=NULL;
        break;
      case LJ1012:
        allocate(B.pre,PairwiseCommonBufferPreSize);
        allocate(B.post,LJ1012BufferPostSize);
        allocate(B.tmvec,PairwiseCommonBufferNumberVectors,dim);
        release(B.inf);
        B.P2PFunc=LJ1012Pre2Post4Func<T>;
        B.P2PDiff=LJ1012Pre2Post4Diff<T>;
        B.P2PBoth=LJ1012Pre2Post4Both<T>;
        B.GetPreFunc=NULL;
        B.GetPreDiff=NULL;
        B.GetPreBoth=NULL;
        break;
      case LJ1012Cut:
        allocate(B.pre,PairwiseCommonBufferPreSize);
        allocate(B.post,LJ1012CutBufferPostSize);
        allocate(B.tmvec,PairwiseCommonBufferNumberVectors,dim);
        release(B.inf);
        B.P2PFunc=LJ1012CutPre2Post4Func<T>;
        B.P2PDiff=LJ1012CutPre2Post4Diff<T>;
        B.P2PBoth=LJ1012CutPre2Post4Both<T>;
        B.GetPreFunc=NULL;
        B.GetPreDiff=NULL;
        B.GetPreBoth=NULL;
        break;
      case Coulomb:
        allocate(B.pre,PairwiseCommonBufferPreSize);
        allocate(B.post,CoulombBufferPostSize);
        allocate(B.tmvec,PairwiseCommonBufferNumberVectors,dim);
        release(B.inf);
        B.P2PFunc=CoulombPre2Post4Func<T>;
        B.P2PDiff=CoulombPre2Post4Diff<T>;
        B.P2PBoth=CoulombPre2Post4Both<T>;
        B.GetPreFunc=NULL;
        B.GetPreDiff=NULL;
        B.GetPreBoth=NULL;
        break;
      case distCoulomb:
        allocate(B.pre,PairwiseCommonBufferPreSize);
        allocate(B.post,DistCoulombBufferPostSize);
        allocate(B.tmvec,PairwiseCommonBufferNumberVectors,dim);
        release(B.inf);
        B.P2PFunc=DistCoulombPre2Post4Func<T>;
        B.P2PDiff=DistCoulombPre2Post4Diff<T>;
        B.P2PBoth=DistCoulombPre2Post4Both<T>;
        B.GetPreFunc=NULL;
        B.GetPreDiff=NULL;
        B.GetPreBoth=NULL;
        break;
      case AngleHarmonic:
        allocate(B.pre,AngleCommonBufferPreSize);
        allocate(B.post,AngleHarmonicBufferPostSize);
        allocate(B.tmvec,AngleCommonBufferNumberVectors);
        allocate(B.inf,AngleCommonBufferInfSize);
        B.P2PFunc=AngleHarmonicPre2Post4Func<T>;
        B.P2PDiff=AngleHarmonicPre2Post4Diff<T>;
        B.P2PBoth=AngleHarmonicPre2Post4Both<T>;
        B.GetPreFunc=AngleCommonGetPre4Func<T>;
        B.GetPreDiff=AngleCommonGetPre4Diff<T>;
        B.GetPreBoth=AngleCommonGetPre4Both<T>;
        break;
      case DihedralPeriodic:
        allocate(B.pre,DihedralCommonBufferPreSize);
        allocate(B.post,DihedralPeriodicBufferPostSize);
        allocate(B.tmvec,DihedralCommonBufferNumberVectors);
        allocate(B.inf,DihedralCommonBufferInfSize);
        B.P2PFunc=DihedralPeriodicPre2Post4Func<T>;
        B.P2PDiff=DihedralPeriodicPre2Post4Diff<T>;
        B.P2PBoth=DihedralPeriodicPre2Post4Both<T>;
        B.GetPreFunc=DihedralCommonGetPre4Func<T>;
        B.GetPreDiff=DihedralCommonGetPre4Diff<T>;
        B.GetPreBoth=DihedralCommonGetPre4Both<T>;
        break;
      default:
        Error("Unknown Interaction Function Name!");
    }
    B.postUpdate=true;
  }

}

#endif

