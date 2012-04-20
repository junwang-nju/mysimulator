
#ifndef _Interaction_Buffer_Allocate_H_
#define _Interaction_Buffer_Allocate_H_

#include "interaction/buffer/interface.h"
#include "array/1d/allocate.h"
#include "array/2d/allocate.h"

#include "interaction/func/impl/pairwise/buffer-name.h"
#include "interaction/func/impl/angle/buffer-name.h"

#include "interaction/func/impl/pairwise/buffer-p2p.h"
#include "interaction/func/impl/angle/buffer-p2p.h"

#include "interaction/func/impl/angle/buffer-getpre.h"

namespace mysimulator {

  template <typename T>
  void allocate(InteractionBuffer<T>& B, const InteractionFuncName& itag,
                unsigned int dim) {
    release(B);
    B.dim=dim;
    B.tag=itag;
    switch(itag) {
      case Harmonic:
        B.pre=allocate<T>(PairwiseCommonBufferPreSize);
        B.post=allocate<T>(HarmonicBufferPostSize);
        B.tmvec=allocate<T>(PairwiseCommonBufferNumberVectors,dim);
        B.P2PFunc=HarmonicPre2Post4Func<T>;
        B.P2PDiff=HarmonicPre2Post4Diff<T>;
        B.P2PBoth=HarmonicPre2Post4Both<T>;
        break;
      case LJ612:
        B.pre=allocate<T>(PairwiseCommonBufferPreSize);
        B.post=allocate<T>(LJ612BufferPostSize);
        B.tmvec=allocate<T>(PairwiseCommonBufferNumberVectors,dim);
        B.P2PFunc=LJ612Pre2Post4Func<T>;
        B.P2PDiff=LJ612Pre2Post4Diff<T>;
        B.P2PBoth=LJ612Pre2Post4Both<T>;
        break;
      case LJ612Cut:
        B.pre=allocate<T>(PairwiseCommonBufferPreSize);
        B.post=allocate<T>(LJ612CutBufferPostSize);
        B.tmvec=allocate<T>(PairwiseCommonBufferNumberVectors,dim);
        B.P2PFunc=LJ612CutPre2Post4Func<T>;
        B.P2PDiff=LJ612CutPre2Post4Diff<T>;
        B.P2PBoth=LJ612CutPre2Post4Both<T>;
        break;
      case LJ1012:
        B.pre=allocate<T>(PairwiseCommonBufferPreSize);
        B.post=allocate<T>(LJ1012BufferPostSize);
        B.tmvec=allocate<T>(PairwiseCommonBufferNumberVectors,dim);
        B.P2PFunc=LJ1012Pre2Post4Func<T>;
        B.P2PDiff=LJ1012Pre2Post4Diff<T>;
        B.P2PBoth=LJ1012Pre2Post4Both<T>;
        break;
      case LJ1012Cut:
        B.pre=allocate<T>(PairwiseCommonBufferPreSize);
        B.post=allocate<T>(LJ1012CutBufferPostSize);
        B.tmvec=allocate<T>(PairwiseCommonBufferNumberVectors,dim);
        B.P2PFunc=LJ1012CutPre2Post4Func<T>;
        B.P2PDiff=LJ1012CutPre2Post4Diff<T>;
        B.P2PBoth=LJ1012CutPre2Post4Both<T>;
        break;
      case Core12:
        B.pre=allocate<T>(PairwiseCommonBufferPreSize);
        B.post=allocate<T>(Core12BufferPostSize);
        B.tmvec=allocate<T>(PairwiseCommonBufferNumberVectors,dim);
        B.P2PFunc=Core12Pre2Post4Func<T>;
        B.P2PDiff=Core12Pre2Post4Diff<T>;
        B.P2PBoth=Core12Pre2Post4Both<T>;
        break;
      case CoreLJ612:
        B.pre=allocate<T>(PairwiseCommonBufferPreSize);
        B.post=allocate<T>(CoreLJ612BufferPostSize);
        B.tmvec=allocate<T>(PairwiseCommonBufferNumberVectors,dim);
        B.P2PFunc=CoreLJ612Pre2Post4Func<T>;
        B.P2PDiff=CoreLJ612Pre2Post4Diff<T>;
        B.P2PBoth=CoreLJ612Pre2Post4Both<T>;
        break;
      case Coulomb:
        B.pre=allocate<T>(PairwiseCommonBufferPreSize);
        B.post=allocate<T>(CoulombBufferPostSize);
        B.tmvec=allocate<T>(PairwiseCommonBufferNumberVectors,dim);
        B.P2PFunc=CoulombPre2Post4Func<T>;
        B.P2PDiff=CoulombPre2Post4Diff<T>;
        B.P2PBoth=CoulombPre2Post4Both<T>;
        break;
      case DistCoulomb:
        B.pre=allocate<T>(PairwiseCommonBufferPreSize);
        B.post=allocate<T>(DistCoulombBufferPostSize);
        B.tmvec=allocate<T>(PairwiseCommonBufferNumberVectors,dim);
        B.P2PFunc=DistCoulombPre2Post4Func<T>;
        B.P2PDiff=DistCoulombPre2Post4Diff<T>;
        B.P2PBoth=DistCoulombPre2Post4Both<T>;
        break;
      case AngleHarmonic:
        B.pre=allocate<T>(AngleCommonBufferPreSize);
        B.post=allocate<T>(AngleHarmonicBufferPostSize);
        B.tmvec=allocate<T>(AngleCommonBufferNumberVectors,dim);
        B.inf=allocate<InteractionBuffer<T>*>(AngleCommonBufferInfSize);
        B.P2PFunc=AngleHarmonicPre2Post4Func<T>;
        B.P2PDiff=AngleHarmonicPre2Post4Diff<T>;
        B.P2PBoth=AngleHarmonicPre2Post4Both<T>;
        B.GPreFunc=AngleCommonGetPre4Func<T>;
        B.GPreDiff=AngleCommonGetPre4Diff<T>;
        B.GPreBoth=AngleCommonGetPre4Both<T>;
        break;
      default:
        fprintf(stderr,"Unknown Interaction Func Name!");
    }
    B.postUpdate=true;
  }

}

#endif

