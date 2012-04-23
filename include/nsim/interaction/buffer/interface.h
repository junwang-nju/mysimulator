
#ifndef _Interaction_Buffer_Interface_H_
#define _Interaction_Buffer_Interface_H_

#include "unique/64bit/interface.h"
#include "interaction/func/name.h"
#include "array/2d/interface.h"

#include "interaction/func/impl/pairwise/buffer-name.h"
#include "interaction/func/impl/pairwise/buffer-p2p.h"

#include "interaction/func/impl/angle/buffer-name.h"
#include "interaction/func/impl/angle/buffer-p2p.h"
#include "interaction/func/impl/angle/buffer-getpre.h"

namespace mysimulator {

  template <typename T>
  struct InteractionBuffer {

    public:

      typedef InteractionBuffer<T>  Type;
      typedef void (*P2PFuncType)(const Array1D<T>&,const Array1D<Unique64Bit>&,
                                  Array1D<T>&,bool&);
      typedef void (*GetPreFuncType)(Type&);

      unsigned int            dim;
      InteractionFuncName     tag;
      Array1D<T>              pre;
      Array1D<T>              post;
      Array2D<T>              tmvec;
      Array1D<Type*>          inf;
      bool                    postUpdate;
      P2PFuncType             P2PFunc,P2PDiff,P2PBoth;
      GetPreFuncType          GPreFunc,GPreDiff,GPreBoth;

      InteractionBuffer()
        : dim(0),tag(UnknownInteactionFunc),pre(),post(),tmvec(),inf(),
          postUpdate(true),P2PFunc(NULL),P2PDiff(NULL),P2PBoth(NULL),
          GPreFunc(NULL),GPreDiff(NULL),GPreBoth(NULL) {}
      ~InteractionBuffer() { Clear(*this); }

      bool IsValid() const {
        return (dim>0)&&pre.IsValid()&&post.IsValid()&&tmvec.IsValid()&&
               (P2PFunc!=NULL)&&(P2PDiff!=NULL)&&(P2PBoth!=NULL)&&
               (tag!=UnknownInteactionFunc);
      }

      void Allocate(const InteractionFuncName itag,unsigned int d) {
        Clear(*this);
        dim=d;
        tag=itag;
        switch(tag) {
          case Harmonic:
            pre.Allocate(PairwiseCommonBufferPreSize);
            post.Allocate(HarmonicBufferPostSize);
            tmvec.Allocate(PairwiseCommonBufferNumberVectors,dim);
            P2PFunc=HarmonicPre2Post4Func<T>;
            P2PDiff=HarmonicPre2Post4Diff<T>;
            P2PBoth=HarmonicPre2Post4Both<T>;
            break;
          case LJ612:
            pre.Allocate(PairwiseCommonBufferPreSize);
            post.Allocate(LJ612BufferPostSize);
            tmvec.Allocate(PairwiseCommonBufferNumberVectors,dim);
            P2PFunc=LJ612Pre2Post4Func<T>;
            P2PDiff=LJ612Pre2Post4Diff<T>;
            P2PBoth=LJ612Pre2Post4Both<T>;
            break;
          case LJ612Cut:
            pre.Allocate(PairwiseCommonBufferPreSize);
            post.Allocate(LJ612CutBufferPostSize);
            tmvec.Allocate(PairwiseCommonBufferNumberVectors,dim);
            P2PFunc=LJ612CutPre2Post4Func<T>;
            P2PDiff=LJ612CutPre2Post4Diff<T>;
            P2PBoth=LJ612CutPre2Post4Both<T>;
            break;
          case LJ1012:
            pre.Allocate(PairwiseCommonBufferPreSize);
            post.Allocate(LJ1012BufferPostSize);
            tmvec.Allocate(PairwiseCommonBufferNumberVectors,dim);
            P2PFunc=LJ1012Pre2Post4Func<T>;
            P2PDiff=LJ1012Pre2Post4Diff<T>;
            P2PBoth=LJ1012Pre2Post4Both<T>;
            break;
          case LJ1012Cut:
            pre.Allocate(PairwiseCommonBufferPreSize);
            post.Allocate(LJ1012CutBufferPostSize);
            tmvec.Allocate(PairwiseCommonBufferNumberVectors,dim);
            P2PFunc=LJ1012CutPre2Post4Func<T>;
            P2PDiff=LJ1012CutPre2Post4Diff<T>;
            P2PBoth=LJ1012CutPre2Post4Both<T>;
            break;
            break;
          case Core12:
            pre.Allocate(PairwiseCommonBufferPreSize);
            post.Allocate(Core12BufferPostSize);
            tmvec.Allocate(PairwiseCommonBufferNumberVectors,dim);
            P2PFunc=Core12Pre2Post4Func<T>;
            P2PDiff=Core12Pre2Post4Diff<T>;
            P2PBoth=Core12Pre2Post4Both<T>;
            break;
          case CoreLJ612:
            pre.Allocate(PairwiseCommonBufferPreSize);
            post.Allocate(CoreLJ612BufferPostSize);
            tmvec.Allocate(PairwiseCommonBufferNumberVectors,dim);
            P2PFunc=CoreLJ612Pre2Post4Func<T>;
            P2PDiff=CoreLJ612Pre2Post4Diff<T>;
            P2PBoth=CoreLJ612Pre2Post4Both<T>;
            break;
          case Coulomb:
            pre.Allocate(PairwiseCommonBufferPreSize);
            post.Allocate(CoulombBufferPostSize);
            tmvec.Allocate(PairwiseCommonBufferNumberVectors,dim);
            P2PFunc=CoulombPre2Post4Func<T>;
            P2PDiff=CoulombPre2Post4Diff<T>;
            P2PBoth=CoulombPre2Post4Both<T>;
            break;
          case DistCoulomb:
            pre.Allocate(PairwiseCommonBufferPreSize);
            post.Allocate(DistCoulombBufferPostSize);
            tmvec.Allocate(PairwiseCommonBufferNumberVectors,dim);
            P2PFunc=DistCoulombPre2Post4Func<T>;
            P2PDiff=DistCoulombPre2Post4Diff<T>;
            P2PBoth=DistCoulombPre2Post4Both<T>;
            break;
          case AngleHarmonic:
            pre.Allocate(AngleCommonBufferPreSize);
            post.Allocate(AngleHarmonicBufferPostSize);
            tmvec.Allocate(AngleCommonBufferNumberVectors,dim);
            P2PFunc=AngleHarmonicPre2Post4Func<T>;
            P2PDiff=AngleHarmonicPre2Post4Diff<T>;
            P2PBoth=AngleHarmonicPre2Post4Both<T>;
            break;
          case DihedralPeriodic:
            break;
          default:
            fprintf(stderr,"Unknown Interaction Func Name!\n");
        }
        postUpdate=true;
      }

      void GetPreFunc() { GPreFunc(*this); }
      void GetPreDiff() { GPreDiff(*this); }
      void GetPreBoth() { GPreBoth(*this); }
      void Pre2PostFunc(const Array1D<Unique64Bit>& P) {
        P2PFunc(pre,P,post,postUpdate);
      }
      void Pre2PostDiff(const Array1D<Unique64Bit>& P) {
        P2PDiff(pre,P,post,postUpdate);
      }
      void Pre2PostBoth(const Array1D<Unique64Bit>& P) {
        P2PBoth(pre,P,post,postUpdate);
      }

    private:

      InteractionBuffer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionBuffer<T>& Buf) {
    Buf.GPreBoth=NULL; Buf.GPreDiff=NULL; Buf.GPreFunc=NULL; Buf.P2PBoth=NULL;
    Buf.P2PDiff=NULL; Buf.P2PFunc=NULL; Buf.postUpdate=true; Clear(Buf.inf);
    Clear(Buf.tmvec); Clear(Buf.post); Clear(Buf.pre); Buf.dim=0;
    Buf.tag=UnknownInteactionFunc;
  }

  template <typename T>
  void ClearFlag(InteractionBuffer<T>& Buf) { Buf.postUpdate=true; }

  template <typename T>
  void ClearFlag(Array1D<InteractionBuffer<T> >& Buf) {
    for(unsigned int i=0;i<Buf.Size();++i)  ClearFlag(Buf[i]);
  }

}

#endif

