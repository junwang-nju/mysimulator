
#ifndef _Line_Minimizer_Buffer_Base_H_
#define _Line_Minimizer_Buffer_Base_H_

#include "data/name/line-minimizer-property-name.h"
#include "data/minimizer/minimizer-buffer-base.h"

namespace std {

  template <typename InteractionType,template<typename> class SpaceType,
            typename IdxType, typename T>
  struct LineMinimizerBufferBase
    : public MinimizerBufferBase<InteractionType,SpaceType,IdxType,T> {
    typedef LineMinimizerBufferBase<InteractionType,SpaceType,IdxType,T>
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

    unsigned int& LSearchCount() {
      return this->MinProperty[LineSearchCount].u;
    }
    const unsigned int& LSearchCount() const {
      return this->MinProperty[LineSearchCount].u;
    }
    T& RunE() {
      typedef UniqueParameter UT;
      return static_cast<UT&>(this->MinProperty[RunningEnergy]).value<T>();
    }
    const T& RunE() const {
      typedef UniqueParameter UT;
      return
      static_cast<const UT&>(this->MinProperty[RunningEnergy]).value<T>();
    }
    T& RunPrj(){
      typedef UniqueParameter UT;
      return static_cast<UT&>(this->MinProperty[RunningProject]).value<T>();
    }
    const T& RunPrj() const {
      typedef UniqueParameter UT;
      return
      static_cast<const UT&>(this->MinProperty[RunningProject]).value<T>();
    }
    T& DecFac() {
      typedef UniqueParameter UT;
      return static_cast<UT&>(this->MinProperty[DecreaseFactor]).value<T>();
    }
    const T& DecFac() const {
      typedef UniqueParameter UT;
      return
      static_cast<const UT&>(this->MinProperty[DecreaseFactor]).value<T>();
    }
    T& CurvFac() {
      typedef UniqueParameter UT;
      return static_cast<UT&>(this->MinProperty[CurvatureFactor]).value<T>();
    }
    const T& CurvFac() const {
      typedef UniqueParameter UT;
      return
      static_cast<const UT&>(this->MinProperty[CurvatureFactor]).value<T>();
    }
    T& GradThreshold() {
      typedef UniqueParameter UT;
      return static_cast<UT&>(this->MinProperty[GradientThreshold]).value<T>();
    }
    const T& GradThreshold() const {
      typedef UniqueParameter UT;
      return
      static_cast<const UT&>(this->MinProperty[GradientThreshold]).value<T>();
    }
  };

  template <typename IType,template<typename> class SpType,
            typename IdType,typename T>
  bool IsAvailable(LineMinimizerBufferBase<IType,SpType,IdType,T>& B) {
    typedef MinimizerBufferBase<IType,SpType,IdType,T>  MBType;
    return IsAvailable(static_cast<const MBType&>(B))&&
           IsAvailable(B.RunX)&&IsAvailable(B.RunG);
  }

  template <typename IType,template<typename> class SpType,
            typename IdType,typename T>
  void release(LineMinimizerBufferBase<IType,SpType,IdType,T>& B) {
    typedef MinimizerBufferBase<IType,SpType,IdType,T>  MBType;
    release(B.RunX);
    release(B.RunG);
    release(static_cast<MBType&>(B));
  }

  template <typename IType,template<typename> class SpType,
            typename IdType,typename T>
  void copy(LineMinimizerBufferBase<IType,SpType,IdType,T>& B,
            const LineMinimizerBufferBase<IType,SpType,IdType,T>& cB) {
    typedef MinimizerBufferBase<IType,SpType,IdType,T>  MBType;
    assert(IsAvailable(B));
    assert(IsAvailable(cB));
    copy(B.RunX,cB.RunX);
    copy(B.RunG,cB.RunG);
    copy(static_cast<MBType&>(B),static_cast<const MBType&>(cB));
  }

  template <typename IType,template<typename> class SpType,
            typename IdType,typename T>
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
            typename IdType,typename T>
  void allocateMinimizerProperty(
      LineMinimizerBufferBase<IType,SpType,IdType,T>& B) {
    allocate(B.MinProperty,LineMinimizerNumberProperty);
    initMinimizerProperty(B);
  }

  template <typename IType,template<typename> class SpType,
            typename IdType,typename T>
  void initMinimizerProperty(LineMinimizerBufferBase<IType,SpType,IdType,T>& B){
    typedef MinimizerBufferBase<IType,SpType,IdType,T>  MBType;
    initMinimizerProperty(static_cast<MBType&>(B));
    B.LSearchCount()=0;
    B.DecFac()=1e-4;
    B.CurvFac()=0.4;
    B.GradThreshold()=RelDelta<T>();
  }
}

#endif
