
#ifndef _Line_Minimizer_Buffer_Base_H_
#define _Line_Minimizer_Buffer_Base_H_

#include "data/name/line-minimizer-property-name.h"
#include "data/minimizer/minimizer-buffer-base.h"

namespace std {

  template <typename InteractionType,template<typename> class SpaceType,
            template<typename> class IdxType, typename T>
  struct LineMinimizerBufferBase
    : public MinimizerBufferBase<InteractionType,SpaceDataType,IdxType,T> {
    typedef LineMinimizerBufferBase<InteractionType,SpaceDataType,IdxType,T>
            Type;
    typedef MinimizerBufferBase<InteractionType,SpaceType,IdxType,T>
            ParentType;

    SpaceType<T> RunX;
    SpaceType<T> RunG;
    
    LineMinimizerBufferBase() : ParentType(), RunX(), RunG() {}
    LineMinimizerBufferBase(const Type& B) {
      myError("Cannot create Line Minimizer Buffer Base");
    }
    Type& operator=(const Type& B) {
      myError("Cannot copy Line Minimizer Buffer Base");
      return *this;
    }
    ~LineMinimizerBufferBase() { release(*this); }

    unsigned int& LSearchCount() { return MinProperty[LineSearchCount].u; }
    const unsigned int& LSearchCount() const {
      return MinProperty[LineSearchCount].u;
    }
    double& RunE() { return MinProperty[RunningEnergy].d; }
    const double& RunE() const { return MinProperty[RunningEnergy].d; }
    double& RunPrj() { return MinProperty[RunningProject].d; }
    const double& RunPrj() const { return MinProperty[RunningProject].d; }
    double& DecFac() { return MinProperty[DecreaseFactor].d; }
    const double& DecFac() const { return MinProperty[DecreaseFactor].d; }
    double& CurvFac() { return MinProperty[CurvatureFactor].d; }
    const double& CurvFac() const { return MinProperty[CurvatureFactor].d; }
    double& GradThreshold() { return MinProperty[GradientThreshold].d; }
    const double& GradThreshold() const {
      return MinProperty[GradientThreshold].d;
    }
  };

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  bool IsAvailable(LineMinimizerBufferBase<IType,SpType,IdType,T>& B) {
    typedef MinimizerBufferBase<IType,SpType,IdType,T>  MBType;
    return IsAvailable(static_cast<const MBType&>(B))&&
           IsAvailable(B.RunX)&&IsAvailable(B.RunG);
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void release(LineMinimizerBufferBase<IType,SpType,IdType,T>& B) {
    typedef MinimizerBufferBase<IType,SpType,IdType,T>  MBType;
    release(B.RunX);
    release(B.RunG);
    release(static_cast<MBType&>(B));
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void copy(LineMinimizerBufferBase<IType,SpType,IdType,T>& B,
            const LineMinimizerBufferBase<IType,SpType,IdType,B>& cB) {
    typedef MinimizerBufferBase<IType,SpType,IdType,T>  MBType;
    assert(IsAvailable(B));
    assert(IsAvailable(cB));
    copy(B.RunX,cB.RunX);
    copy(B.RunG,cB.RunG);
    copy(static_cast<MBType&>(B),static_cast<const MBType&>(cB));
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void refer(LineMinimizerBufferBase<IType,SpType,IdType,T>& B,
             const LineMinimizerBufferBase<IType,SpType,IdType,T>& rB) {
    typedef MinimizerBufferBase<IType,SpType,IdType,T>  MBType;
    assert(IsAvailable(rB));
    release(B);
    refer(B.RunX,rB.RunX);
    refer(B.RunG,rB.RunG);
    refer(static_cast<MBType&>(B),static_cast<const MBType&>(rB));
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void allocateMinimizerProperty(
      LineMinimizerBufferBase<IType,SpType,IdType,T>& B) {
    allocate(B.MinProperty,LineMinimizerNumberProperty);
    initMinimizerProperty(B);
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void initMinimizerProperty(LineMinimizerBufferBase<IType,SpType,IdType,T>& B){
    B.LSearchCount()=0;
    B.DecFac()=1e-4;
    B.CurvFac()=0.4;
    B.GradThreshold()=RelDelta<T>();
  }
}

#endif
