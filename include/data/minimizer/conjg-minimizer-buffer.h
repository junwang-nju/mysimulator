
#ifndef _Minimizer_Conjugate_Gradient_Buffer_H_
#define _Minimizer_Conjugate_Gradient_Buffer_H_

#include "data/basic/unique-parameter.h"
#include "data/name/conjg-minimizer-self-property.h"

namespace std {

  template <typename InteractType, template <typename> class SpaceType,
            typename IdxType, typename T,
            template<typename,template<typename>class,
                     typename,typename> class LineMin>
  struct ConjugateGradientMinimizerBuffer 
    : public LineMin<InteractType,SpaceType,IdxType,T> {
    typedef
    ConjugateGradientMinimizerBuffer<InteractType,SpaceType,IdxType,T,LineMin>
    Type;
    typedef LineMin<InteractType,SpaceType,IdxType,T>  ParentType;
    
    static const unsigned int DefaultMaxIter;
    SpaceType<T> Dirc;
    SpaceType<T> OldMinG;
    Vector<UniqueParameter> selfProperty;
    
    ConjugateGradientMinimizerBuffer() : ParentType(), Dirc(), OldMinG() {}
    ConjugateGradientMinimizerBuffer(const Type& B) {
      myError("Cannot create Conjugate-Gradient Minimizer Buffer");
    }
    Type& operator=(const Type& B) {
      myError("Cannot copy Conjugate-Gradient Minimizer Buffer");
      return *this;
    }
    ~ConjugateGradientMinimizerBuffer() { release(*this); }
    
    T& MaxBeta() { return selfProperty[BetaMaximum].value<T>(); }
    const T& MaxBeta() const { return selfProperty[BetaMaximum].value<T>(); }
  };

  template <typename IType,template <typename> class SpType,
            typename IdType, typename T,
            template <typename,template<typename>class,
                      typename,typename> class LMin>
  const unsigned int
  ConjugateGradientMinimizerBuffer<IType,SpType,IdType,T,LMin>::DefaultMaxIter
  =1000;

  template <typename IType,template <typename> class SpType,
            typename IdType, typename T,
            template <typename,template<typename>class,
                      typename,typename> class LMin>
  bool IsAvailable(
      const ConjugateGradientMinimizerBuffer<IType,SpType,IdType,T,LMin>& B) {
    typedef LMin<IType,SpType,IdType,T> LMType;
    return IsAvailable(static_cast<const LMType&>(B))&&IsAvailable(B.Dirc)&&
           IsAvailable(B.OldMinG);
  }

  template <typename IType,template <typename> class SpType,
            typename IdType, typename T,
            template <typename,template<typename>class,
                      typename,typename> class LineMin>
  void release(
      ConjugateGradientMinimizerBuffer<IType,SpType,IdType,T,LineMin>& B) {
    typedef LineMin<IType,SpType,IdType,T>  LMType;
    release(B.Dirc);
    release(B.OldMinG);
    release(static_cast<LMType&>(B));
  }

  template <typename IType,template <typename> class SpType,
            typename IdType, typename T,
            template <typename,template<typename>class,
                      typename,typename> class LMin>
  void copy(
      ConjugateGradientMinimizerBuffer<IType,SpType,IdType,T,LMin>& B,
      const ConjugateGradientMinimizerBuffer<IType,SpType,IdType,T,LMin>& cB) {
    assert(IsAvailable(B));
    assert(IsAvailable(cB));
    typedef LMin<IType,SpType,IdType,T>  LMType;
    copy(static_cast<LMType&>(B),static_cast<const LMType&>(cB));
    copy(B.Dirc,cB.Dirc);
    copy(B.OldMinG,cB.OldMinG);
  }

  template <typename IType,template <typename> class SpType,
            typename IdType, typename T,
            template <typename,template<typename>class,
                      typename,typename> class LMin>
  void refer(
      ConjugateGradientMinimizerBuffer<IType,SpType,IdType,T,LMin>& B,
      const ConjugateGradientMinimizerBuffer<IType,SpType,IdType,T,LMin>& cB) {
    assert(IsAvailable(cB));
    typedef LMin<IType,SpType,IdType,T>  LMType;
    release(B);
    refer(static_cast<LMType&>(B),static_cast<const LMType&>(cB));
    refer(B.Dirc,cB.Dirc);
    refer(B.OldMinG,cB.OldMinG);
  }

  template <typename IType,template <typename> class SpType,
            typename IdType, typename T,
            template <typename,template<typename>class,
                      typename,typename> class LineMin>
  void allocateMinimizerProperty(
      ConjugateGradientMinimizerBuffer<IType,SpType,IdType,T,LineMin>& B) {
    typedef LineMin<IType,SpType,IdType,T>  LMType;
    allocateMinimizerProperty(static_cast<LMType&>(B));
    allocate(B.selfProperty,ConjugateGradientMinimizerNumberSelfProperty);
    initMinimizerProperty(B);
  }

  template <typename IType,template <typename> class SpType,
            typename IdType, typename T,
            template <typename,template<typename>class,
                      typename,typename> class LineMin>
  void initMinimizerProperty(
      ConjugateGradientMinimizerBuffer<IType,SpType,IdType,T,LineMin>& B) {
    typedef LineMin<IType,SpType,IdType,T>  LMType;
    initMinimizerProperty(static_cast<LMType&>(B));
    B.MaxBeta()=5.0;
  }

}

#endif
