
#ifndef _Minimizer_Steepest_Descent_Buffer_H_
#define _Minimizer_Steepest_Descent_Buffer_H_

#include "operation/basic/error-proc.h"
#include <cassert>

namespace std {

  template <typename InteractionType, template <typename> class SpaceType,
            template <typename> class IdxType, typename T,
            template <typename,template<typename>class,
                      template<typename>class,typename> class LineMin>
  struct SteepestDescentMinimizerBuffer
    : public LineMin<InteractionType,SpaceType,IdxType,T> {
    typedef
    SteepestDescentMinimizerBuffer<InteractionType,SpaceType,IdxType,T,LineMin>
    Type;
    typedef LineMin<InteractionType,SpaceType,IdxType,T>  ParentType;

    static const unsigned int DefaultMaxIter;
    SpaceType<T>  Dirc;

    SteepestDescentMinimizerBuffer() : ParentType(), Dirc() {}
    SteepestDescentMinimizerBuffer(const Type& M) {
      myError("Cannot create Steepest Descent Minimizer");
    }
    Type& operator=(const Type& M) {
      myError("Cannot copy Steepest Descent Minimizer");
      return *this;
    }
    ~SteepestDescentMinimizerBuffer() { release(*this); }
  };

  template <typename IType, template <typename> class SpType,
            template <typename> class IdType, typename T,
            template<typename,template<typename>class,
                     template<typename>class,typename> class LineMin>
  const unsigned int
  SteepestDescentMinimizerBuffer<IType,SpType,IdType,T,LineMin>::DefaultMaxIter
  =10000;

  template <typename IType, template <typename> class SpType,
            template <typename> class IdType, typename T,
            template<typename,template<typename>class,
                     template<typename>class,typename> class LineMin>
  bool IsAvailable(
      const SteepestDescentMinimizerBuffer<IType,SpType,IdType,T,LineMin>& M) {
    typedef LineMin<IType,SpType,IdType,T>  LMType;
    return IsAvailable(static_cast<const LMType&>(M))&&IsAvailable(M.Dirc);
  }

  template <typename IType, template <typename> class SpType,
            template <typename> class IdType, typename T,
            template <typename,template <typename> class,
                      template <typename> class,typename T> class LineMin>
  void release(
      SteepestDescentMinimizerBuffer<IType,SpType,IdType,T,LineMin>& M) {
    typedef LineMin<IType,SpType,IdType,T>    LMType;
    release(M.Dirc);
    release(static_cast<LMType&>(M));
  }

  template <typename IType, template <typename> class SpType,
            template <typename> class IdType, typename T,
            template <typename,template <typename> class,
                      template <typename> class,typename T> class LineMin>
  void copy(
      SteepestDescentMinimizerBuffer<IType,SpType,IdType,T,LineMin>& M,
      const SteepestDescentMinimizerBuffer<IType,SpType,IdType,T,LineMin>& cM){
    typedef LineMin<IType,SpType,IdType,T>  LMType;
    assert(IsAvailable(M));
    assert(IsAvailable(cM));
    copy(M.Dirc,cM.Dirc);
    copy(static_cast<LMType&>(M),static_cast<const LMType&>(cM));
  }

  template <typename IType, template <typename> class SpType,
            template <typename> class IdType, typename T,
            template <typename,template <typename> class,
                      template <typename> class,typename T> class LineMin>
  void refer(
      SteepestDescentMinimizerBuffer<IType,SpType,IdType,T,LineMin>& M,
      const SteepestDescentMinimizerBuffer<IType,SpType,IdType,T,LineMin>& rM){
    typedef LineMin<IType,SpType,IdType,T>  LMType;
    assert(IsAvailable(rM));
    release(M);
    refer(M.Dirc,rM.Dirc);
    refer(static_cast<LMType&>(M),static_cast<const LMType&>(rM));
  }
}

#endif
