
#ifndef _Minimizer_Buffer_Base_H_
#define _Minimizer_Buffer_Base_H_

#include "data/basic/unique-parameter.h"
#include "data/name/minimizer-property.h"

namespace std {

  template <typename InteractionType,template <typename> class SpaceType,
            typename ParameterType, typename T>
  struct MinimizerBufferBase {
    InteractionType F;
    SpaceType<T> MinX;
    ParameterType MinParam;
    SpaceType<T> MinDMask;
    SpaceType<unsigned int> MinIMask;
    Vector<UniqueParameter> MinProperty;
    SpaceType<T> MinG;

    typedef MinimizerBufferBase<InteractionType,SpaceType,ParameterType,T>
            Type;
    
    MinimizerBufferBase()
      : F(),MinX(),MinParam(),MinDMask(),MinIMask(),MinProperty(),MinG() {}
    MinimizerBufferBase(const Type& B) {
      myError("Cannot create Minimizer Buffer Base");
    }
    Type& operator=(const Type& B) {
      myError("Cannot copy Minimizer Buffer Base");
      return *this;
    }
    ~MinimizerBufferBase() { release(*this); }

    T& MinEnergy() { return MinProperty[MinimalEnergy].value<T>(); }
    const T& MinEnergy() const { return MinProperty[MinimalEnergy].value<T>(); }
    T& MinProject() { return MinProperty[ProjectInMinimization].value<T>(); }
    const T& MinProject() const {
      return MinProperty[ProjectInMinimization].value<T>();
    }
    T& MinMove() { return MinProperty[MoveInMinimization].value<T>(); }
    const T& MinMove() const {
      return MinProperty[MoveInMinimization].value<T>();
    }
    unsigned int& GCalcCount() { return MinProperty[GradientCount].u; }
    const unsigned int& GCalcCount() const {
      return MinProperty[GradientCount].u;
    }
    T& SearchScale() { return MinProperty[Scale4Search].value<T>(); }
    const T& SearchScale()const{ return MinProperty[Scale4Search].value<T>(); }
    unsigned int& DOF() { return MinProperty[DegreeFreedom].u; }
    const unsigned int& DOF() const { return MinProperty[DegreeFreedom].u; }
  };

  template <typename IType,template<typename> class SpType,
            typename IdType,typename T>
  bool IsAvailable(const MinimizerBufferBase<IType,SpType,IdType,T>& B) {
    return IsAvailable(B.F)&&IsAvailable(B.MinX)&&IsAvailable(B.MinParam)&&
           IsAvailable(B.MinDMask)&&IsAvailable(B.MinIMask)&&
           IsAvailable(B.MinProperty)&&IsAvailable(B.MinG);
  }

  template <typename IType,template<typename> class SpType,
            typename PmType,typename T>
  void release(MinimizerBufferBase<IType,SpType,PmType,T>& B) {
    release(B.F);
    release(B.MinX);
    release(B.MinParam);
    release(B.MinDMask);
    release(B.MinIMask);
    release(B.MinProperty);
    release(B.MinG);
  }

  template <typename IType,template<typename> class SpType,
            typename PmType,typename T>
  void copy(MinimizerBufferBase<IType,SpType,PmType,T>& B,
            const MinimizerBufferBase<IType,SpType,PmType,T>& cB) {
    assert(IsAvailable(B));
    assert(IsAvailable(cB));
    copy(B.F,cB.F);
    copy(B.MinX,cB.MinX);
    copy(B.MinParam,cB.MinParam);
    copy(B.MinDMask,cB.MinDMask);
    copy(B.MinIMask,cB.MinIMask);
    copy(B.MinProperty,cB.MinProperty);
    copy(B.MinG,cB.MinG);
  }

  template <typename IType,template<typename> class SpType,
            typename PmType,typename T>
  void refer(MinimizerBufferBase<IType,SpType,PmType,T>& B,
             const MinimizerBufferBase<IType,SpType,PmType,T>& rB) {
    assert(IsAvailable(rB));
    release(B);
    refer(B.F,rB.F);
    refer(B.MinX,rB.MinX);
    refer(B.MinParam,rB.MinParam);
    refer(B.MinDMask,rB.MinDMask);
    refer(B.MinIMask,rB.MinIMask);
    refer(B.MinProperty,rB.MinProperty);
    refer(B.MinG,rB.MinG);
  }

  template <typename IType,template<typename> class SpType,
            typename PmType,typename T>
  void allocateMinimizerProperty(MinimizerBufferBase<IType,SpType,PmType,T>& B){
    allocate(B.MinProperty,MinimizerNumberProperty);
    initMinimizerProperty(B);
  }

  template <typename IType,template<typename> class SpType,
            typename PmType,typename T>
  void initMinimizerProperty(MinimizerBufferBase<IType,SpType,PmType,T>& B) {
    B.GCalcCount()=0;
    B.SearchScale()=0.1;
  }

}

#endif

