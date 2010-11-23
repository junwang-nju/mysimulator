
#ifndef _Minimizer_Buffer_Base_H_
#define _Minimizer_Buffer_Base_H_

#include "data/basic/unique-parameter.h"
#include "data/name/minimizer-property-name.h"

namespace std {

  template <typename InteractionType,template <typename> class SpaceType,
            template <typename> class IdxType, typedef T>
  struct MinimizerBufferBase {
    InteractionType F;
    SpaceType<T> MinX;
    IdxType<unsigned int> MinIdx;
    SpaceType<T> MinDMask;
    SpaceType<unsigned int> MinIMask;
    Vector<UniqueParameter> MinProperty;
    SpaceType MinG;

    typedef MinimizerBufferBase<InteractionType,SpaceType,IdxType,T>  Type;
    
    MinimizerBufferBase()
      : F(), MinX(), MinIdx(), MinDMask(), MinIMask(), MinProperty(), MinG() {}
    MinimizerBufferBase(const Type& B) {
      myError("Cannot create Minimizer Buffer Base");
    }
    Type& operator=(const Type& B) {
      myError("Cannot copy Minimizer Buffer Base");
      return *this;
    }
    ~MinimizerBufferBase() { release(*this); }

    T& MinEnergy() { return MinProperty[MinimalEnergy]<T>(); }
    const T& MinEnergy() const { return MinProperty[MinimalEnergy]<T>(); }
    T& MinProject() { return MinProperty[ProjectInMinimization]<T>(); }
    const T& MinProject() const {
      return MinProperty[ProjectInMinimization]<T>();
    }
    T& MinMove() { return MinProperty[MoveInMinimization]<T>(); }
    const T& MinMove() const { return MinProperty[MoveInMinimization]<T>(); }
    unsigned int& GCalcCount() { return MinProperty[GradientCount].u; }
    const unsigned int& GCalcCount() const {
      return MinProperty[GradientCount].u;
    }
    double& SearchScale() { return MinProperty[Scale4Search].d; }
    const double& SearchScale() const { return MinProperty[Scale4Search].d; }
    unsigned int& DOF() { return MinProperty[DegreeFreedom].u; }
    const unsigned int& DOF() const { return MinProperty[DegreeFreedom].u; }
  };

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  bool IsAvailable(const MinimizerBufferBase<IType,SpType,IdType,T>& B) {
    return IsAvailable(B.F)&&IsAvailable(B.MinX)&&IsAvailable(B.MinIdx)&&
           IsAvailable(B.MinDMask)&&IsAvailable(B.MinIMask)&&
           IsAvailable(B.MinProperty)&&IsAvailable(B.MinG);
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void release(MinimizerBufferBase<IType,SpType,IdType,T>& B) {
    release(B.F);
    release(B.MinX);
    release(B.MinIdx);
    release(B.MinDMask);
    release(B.MinIMask);
    release(B.MinProperty);
    release(B.MinG);
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void copy(MinimizerBufferBase<IType,SpType,IdType,T>& B,
            const MinimizerBufferBase<IType,SpType,IdType,T>& cB) {
    assert(IsAvailable(B));
    assert(IsAvailable(cB));
    copy(B.F,cB.F);
    copy(B.MinX,cB.MinX);
    copy(B.MinIdx,cB.MinIdx);
    copy(B.MinDMask,cB.MinDMask);
    copy(B.MinIMask,cB.MinIMask);
    copy(B.MinProperty,cB.MinProperty);
    copy(B.MinG,cB.MinG);
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void refer(MinimizerBufferBase<IType,SpType,IdType,T>& B,
             const MinimizerBufferBase<IType,SpType,IdType,T>& rB) {
    assert(IsAvailable(rB));
    release(B);
    refer(B.F,rB.F);
    refer(B.MinX,rB.MinX);
    refer(B.MinIdx,rB.MinIdx);
    refer(B.MinDMask,rB.MinDMask);
    refer(B.MinIMask,rB.MinIMask);
    refer(B.MinProperty,rB.MinProperty);
    refer(B.MinG,rB.MinG);
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void allocateMinimizerProperty(MinimizerBufferBase<IType,SpType,IdType,T>& B){
    allocate(B.MinProperty,MinimizerNumberProperty);
    B.GCalcCount()=0;
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void GenerateNewLocation(
      const MinimizerBufferBase<IType,SpType,IdType,T>& B,
      const SpType& Origin, const SpType& Dirc, const T& step,
      SpType& Dest, T& DestY, SpType& DestG, T& DestPrj) {
    copy(Dest,Origin);
    shift(Dest,step,Dirc);
    DestY=0.;
    copy(DestG,0.);
    CalcInteraction(B.F,Dest,B.MinIdx,DestY,DestG);
    scale(DestG,B.MinDMask);
    ++(B.GCalcCount());
    DestPrj=dot(DestG,Dirc);
  }

}

#endif

