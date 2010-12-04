
#ifndef _Tracking_Line_Minimizer_Buffer_H_
#define _Tracking_Line_Minimizer_Buffer_H_

#include "data/minimizer/line-minimizer-buffer-base.h"
#include "data/name/tracking-line-minimizer-property.h"

namespace std {

  template <typename InteractionType,template<typename> class SpaceType,
            typename IdxType, typename T>
  struct TrackingLineMinimizerBuffer
    : public LineMinimizerBufferBase<InteractionType,SpaceType,IdxType,T> {
    typedef TrackingLineMinimizerBuffer<InteractionType,SpaceType,IdxType,T>
            Type;
    typedef LineMinimizerBufferBase<InteractionType,SpaceType,IdxType,T>
            ParentType;
    
    TrackingLineMinimizerBuffer() : ParentType() {}
    TrackingLineMinimizerBuffer(const Type& B) {
      myError("Cannot create Tracking Line Minimizer Buffer");
    }
    Type& operator=(const Type& B) {
      myError("Cannot copy Tracking Line Minimizer Buffer");
      return *this;
    }
    ~TrackingLineMinimizerBuffer() { release(*this); }

    T& TrackingFac() {
      typedef UniqueParameter UT;
      return static_cast<UT&>(this->MinProperty[TrackingFactor]).value<T>();
    }
    const T& TrackingFac() const {
      typedef UniqueParameter UT;
      return
      static_cast<const UT&>(this->MinProperty[TrackingFactor]).value<T>();
    }
  };

  template <typename IType,template<typename> class SpType,
            typename IdType,typename T>
  bool IsAvailable(const TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B){
    typedef LineMinimizerBufferBase<IType,SpType,IdType,T>  LBType;
    return IsAvailable(static_cast<const LBType&>(B));
  }

  template <typename IType,template<typename> class SpType,
            typename IdType,typename T>
  void release(TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B) {
    typedef LineMinimizerBufferBase<IType,SpType,IdType,T>  LBType;
    release(static_cast<LBType&>(B));
  }

  template <typename IType,template<typename> class SpType,
            typename IdType,typename T>
  void copy(TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B,
            const TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& cB) {
    typedef LineMinimizerBufferBase<IType,SpType,IdType,T>  LBType;
    copy(static_cast<LBType&>(B),static_cast<const LBType&>(cB));
  }

  template <typename IType,template<typename> class SpType,
            typename IdType,typename T>
  void refer(TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B,
             const TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& rB) {
    typedef LineMinimizerBufferBase<IType,SpType,IdType,T>  LBType;
    refer(static_cast<LBType&>(B),static_cast<const LBType&>(rB));
  }

  template <typename IType,template<typename> class SpType,
            typename IdType,typename T>
  void allocateMinimizerProperty(
      TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B) {
    allocate(B.MinProperty,TrackingLineMinimizerNumberProperty);
    initMinimizerProperty(B);
  }

  template <typename IType,template<typename> class SpType,
            typename IdType,typename T>
  void initMinimizerProperty(
      TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B) {
    typedef LineMinimizerBufferBase<IType,SpType,IdType,T>  LBType;
    initMinimizerProperty(static_cast<LBType&>(B));
    B.TrackingFac()=GoldValue<T>();
  }

}

#endif
