
#ifndef _Tracking_Line_Minimizer_Buffer_H_
#define _Tracking_Line_Minimizer_Buffer_H_

#include "data/minimizer/line-minimizer-buffer-base.h"
#include "data/name/tracking-line-minimizer-property.h"

namespace std {

  template <typename InteractionType,template<typename> class SpaceType,
            typename ParameterType, typename T>
  struct TrackingLineMinimizerBuffer
    : public
      LineMinimizerBufferBase<InteractionType,SpaceType,ParameterType,T> {
    typedef
      TrackingLineMinimizerBuffer<InteractionType,SpaceType,ParameterType,T>
      Type;
    typedef LineMinimizerBufferBase<InteractionType,SpaceType,ParameterType,T>
            ParentType;
    
    TrackingLineMinimizerBuffer() : ParentType() {}
    TrackingLineMinimizerBuffer(const Type& B) {
      Error("Cannot create Tracking Line Minimizer Buffer");
    }
    Type& operator=(const Type& B) {
      Error("Cannot copy Tracking Line Minimizer Buffer");
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
            typename PmType,typename T>
  bool IsAvailable(const TrackingLineMinimizerBuffer<IType,SpType,PmType,T>& B){
    typedef LineMinimizerBufferBase<IType,SpType,PmType,T>  LBType;
    return IsAvailable(static_cast<const LBType&>(B));
  }

  template <typename IType,template<typename> class SpType,
            typename PmType,typename T>
  void release(TrackingLineMinimizerBuffer<IType,SpType,PmType,T>& B) {
    typedef LineMinimizerBufferBase<IType,SpType,PmType,T>  LBType;
    release(static_cast<LBType&>(B));
  }

  template <typename IType,template<typename> class SpType,
            typename PmType,typename T>
  void copy(TrackingLineMinimizerBuffer<IType,SpType,PmType,T>& B,
            const TrackingLineMinimizerBuffer<IType,SpType,PmType,T>& cB) {
    typedef LineMinimizerBufferBase<IType,SpType,PmType,T>  LBType;
    copy(static_cast<LBType&>(B),static_cast<const LBType&>(cB));
  }

  template <typename IType,template<typename> class SpType,
            typename PmType,typename T>
  void refer(TrackingLineMinimizerBuffer<IType,SpType,PmType,T>& B,
             const TrackingLineMinimizerBuffer<IType,SpType,PmType,T>& rB) {
    typedef LineMinimizerBufferBase<IType,SpType,PmType,T>  LBType;
    refer(static_cast<LBType&>(B),static_cast<const LBType&>(rB));
  }

  template <typename IType,template<typename> class SpType,
            typename PmType,typename T>
  void allocateMinimizerProperty(
      TrackingLineMinimizerBuffer<IType,SpType,PmType,T>& B) {
    allocate(B.MinProperty,TrackingLineMinimizerNumberProperty);
    initMinimizerProperty(B);
  }

  template <typename IType,template<typename> class SpType,
            typename PmType,typename T>
  void initMinimizerProperty(
      TrackingLineMinimizerBuffer<IType,SpType,PmType,T>& B) {
    typedef LineMinimizerBufferBase<IType,SpType,PmType,T>  LBType;
    initMinimizerProperty(static_cast<LBType&>(B));
    B.TrackingFac()=GoldValue<T>();
  }

}

#endif
