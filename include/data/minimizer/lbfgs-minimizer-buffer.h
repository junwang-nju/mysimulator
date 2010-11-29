
#ifndef _LBFGS_Minimizer_Buffer_H_
#define _LBFGS_Minimizer_Buffer_H_

#include "data/basic/vector.h"
#include <cassert>

namespace std {

  template <typename InteractionType, template <typename> class SpaceType,
            template <typename> class IdxType, typename T,
            template <typename,template<typename>class,
                      template<typename>class,typename> class LineMin,
            unsigned int MaxCorr=6>
  struct LBFGSMinimizerBuffer
    : public LineMin<InteractionType,SpaceType,IdxType,T> {
    typedef
    LBFGSMinimizerBuffer<InteractionType,SpaceType,IdxType,T,LineMin,MaxCorr>
    Type;
    typedef LineMin<InteractionType,SpaceType,IdxType,T>  ParentType;

    static const unsigned int DefaultMaxIter;
    SpaceType<T>  Dirc;
    Vector<SpaceType<T> >  dX;
    Vector<SpaceType<T> >  dG;
    Vector<T>     alpha;
    Vector<T>     rho;
    SpaceType<T>  lastX;
    SpaceType<T>  lastG;

    LBFGSMinimizerBuffer()
        : ParentType(),Dirc(),dX(),dG(),alpha(),rho(),lastX(),lastG() {}
    LBFGSMinimizerBuffer(const Type& B) {
      myError("Cannot create LBFGS Minimizer Buffer");
    }
    Type& operator=(const Type& B) {
      myError("Cannot copy LBFGS Minimizer Buffer");
      return *this;
    }
    ~LBFGSMinimizerBuffer() { release(*this); }
  };

  template <typename IType,template <typename> class SpType,
            template <typename> class IdType, typename T,
            template<typename,template<typename>class,
                     template<typename>class,typename> class LMin,
            unsigned int MCorr>
  const unsigned int
  LBFGSMinimizerBuffer<IType,SpType,IdType,T,LMin,MCorr>::DefaultMaxIter
  =1000;

  template <typename IType,template <typename> class SpType,
            template <typename> class IdType, typename T,
            template<typename,template<typename>class,
                     template<typename>class,typename> class LMin,
            unsigned int MCorr>
  bool IsAvailable(
      const LBFGSMinimizerBuffer<IType,SpType,IdType,T,LMin,MCorr>& B) {
    typedef LMin<IType,SpType,IdType,T> LMType;
    return IsAvailable(static_cast<const LMType&>(B))&&IsAvailable(B.Dirc)&&
           IsAvailable(B.dX)&&IsAvailable(B.dG)&&IsAvailable(B.alpha)&&
           IsAvailable(B.rho)&&IsAvailable(B.lastX)&&IsAvailable(B.lastG);
  }

  template <typename IType,template <typename> class SpType,
            template <typename> class IdType, typename T,
            template<typename,template<typename>class,
                     template<typename>class,typename> class LMin,
            unsigned int MCorr>
  void release(LBFGSMinimizerBuffer<IType,SpType,IdType,T,LMin,MCorr>& B) {
    typedef LMin<IType,SpType,IdType,T> LMType;
    release(B.Dirc);
    release(B.dX);
    release(B.dG);
    release(B.alpha);
    release(B.rho);
    release(B.lastX);
    release(B.lastG);
    release(static_cast<LMType&>(B));
  }

  template <typename IType,template <typename> class SpType,
            template <typename> class IdType, typename T,
            template<typename,template<typename>class,
                     template<typename>class,typename> class LMin,
            unsigned int MCorr>
  void copy(
      LBFGSMinimizerBuffer<IType,SpType,IdType,T,LMin,MCorr>& B,
      const LBFGSMinimizerBuffer<IType,SpType,IdType,T,LMin,MCorr>& cB) {
    assert(IsAvailable(B));
    assert(IsAvailable(cB));
    typedef LMin<IType,SpType,IdType,T> LMType;
    copy(B.Dirc,cB.Dirc);
    copy(B.dX,cB.dX);
    copy(B.dG,cB.dG);
    copy(B.alpha,cB.alpha);
    copy(B.rho,cB.rho);
    copy(B.lastX,cB.lastX);
    copy(B.lastG,cB.lastG);
    copy(static_cast<LMType&>(B),static_cast<const LMType&>(cB));
  }

  template <typename IType,template <typename> class SpType,
            template <typename> class IdType, typename T,
            template<typename,template<typename>class,
                     template<typename>class,typename> class LMin,
            unsigned int MCorr>
  void refer(
      LBFGSMinimizerBuffer<IType,SpType,IdType,T,LMin,MCorr>& B,
      const LBFGSMinimizerBuffer<IType,SpType,IdType,T,LMin,MCorr>& cB) {
    assert(IsAvailable(cB));
    release(B);
    typedef LMin<IType,SpType,IdType,T> LMType;
    refer(B.Dirc,cB.Dirc);
    refer(B.dX,cB.dX);
    refer(B.dG,cB.dG);
    refer(B.alpha,cB.alpha);
    refer(B.rho,cB.rho);
    refer(B.lastX,cB.lastX);
    refer(B.lastG,cB.lastG);
    refer(static_cast<LMType&>(B),static_cast<const LMType&>(cB));
  }

  template <typename IType,template <typename> class SpType,
            template <typename> class IdType, typename T,
            template<typename,template<typename>class,
                     template<typename>class,typename> class LMin,
            unsigned int MCorr>
  void allocateMinimizerProperty(
      LBFGSMinimizerBuffer<IType,SpType,IdType,T,LMin,MCorr>& B) {
    typedef LMin<IType,SpType,IdType,T> LMType;
    allocateMinimizerProperty(static_cast<LMType&>(B));
    allocate(B.dX,MCorr);
    allocate(B.dG,MCorr);
    allocate(B.alpha,MCorr);
    allocate(B.rho,MCorr);
  }

}

#endif

