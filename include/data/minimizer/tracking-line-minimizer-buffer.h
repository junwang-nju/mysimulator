
#ifndef _Tracking_Line_Minimizer_Buffer_H_
#define _Tracking_Line_Minimizer_Buffer_H_

namespace std {

  template <typename InteractionType,template<typename> class SpaceType,
            template<typename> class IdxType, typename T>
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

    double& TrackingFac() { return MinProperty[TrackingFactor]; }
    const double& TrackingFac() const { return MinProperty[TrackingFactor]; }
  };

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  bool IsAvailable(const TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B){
    typedef LineMinimizerBufferBase<IType,SpType,IdType,T>  LBType;
    return IsAvailable(static_cast<const LBType&>(B))
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void release(TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B) {
    typedef LineMinimizerBufferBase<IType,SpType,IdType,T>  LBType;
    release(static_cast<LBType&>(B));
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void copy(TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B,
            const TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& cB) {
    typedef LineMinimizerBufferBase<IType,SpType,IdType,T>  LBType;
    copy(static_cast<LBType&>(B),static_cast<const LBType&>(cB));
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void refer(TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B,
             const TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& rB) {
    typedef LineMinimizerBufferBase<IType,SpType,IdType,T>  LBType;
    refer(static_cast<LBType&>(B),static_cast<const LBType&>(rB));
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void allocateMinimizerProperty(
      TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B) {
    allocate(B.MinProperty,TrackingLineMinimizerNumberProperty);
  }

}

#endif
