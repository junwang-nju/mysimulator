
#ifndef _Propagator_Minimizer_Line_Tracking_Interface_H_
#define _Propagator_Minimizer_Line_Tracking_Interface_H_

#include "propagator/minimizer/line/interface.h"
#include "propagator/minimizer/line/name.h"
#include "propagator/minimizer/line/tracking/parameter-name.h"

#define _NAME_(U) TrackingLineMin_##U
#define _PARAM_(U)  this->_param[_NAME_(U)]
#define _VALUE_(RT,U) Value<RT>(_PARAM_(U))

namespace mysimulator {

  template <typename T,typename GT>
  class PropagatorTrackingLineMinimizer : public PropagatorLineMinimizer<T,GT> {

    public:

      typedef PropagatorTrackingLineMinimizer<T,GT> Type;
      typedef PropagatorLineMinimizer<T,GT> ParentType;

      PropagatorTrackingLineMinimizer() : ParentType() {}
      virtual ~PropagatorTrackingLineMinimizer() { Clear(*this); }

      virtual void Allocate(const Array<StepPropagatorName>& PN,...) {
        Clear(*this);
        this->_tag=LineMinimizer;
        assert(_Flag(PN)==1);
        this->_props.Allocate(PN.Size());
        for(unsigned int i=0;i<this->_props.Size();++i)
          Introduce(this->_props[i],PN[i]);
        this->_bind=NULL;
        Introduce(this->_bind,this->_props);
        this->_param.Allocate(TrackingLineMin_NumberParameter);
        _VALUE_(unsigned int,LineTag)=TrackingLineMinimizer;
        this->_SetCondition(StrongWolfe);
        Pointer<T>(this->_param[TrackingLineMin_Step])=&(this->Step);
        for(unsigned int i=0;i<this->_props.Size();++i) {
          this->_props[i]->Load(this->_param);
          this->_props[i]->Init();
        }
        this->_time=NULL;
        this->_output=NULL;
      }

      virtual void Evolute(System<T,GT>& S) {
      }

    private:

      PropagatorTrackingLineMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      unsigned int _Flag(const Array<StepPropagatorName>& PN) {
        unsigned int fg=1;
        for(unsigned int i=0;i<PN.Size();++i) {
          switch(PN[i]) {
            case MinimizerShiftLine:
            case FixPosition:
              break;
            default:
              fprintf(stderr,"Improper StepPropagator\n");
              fg=0;
          }
          if(fg==0) break;
        }
        return fg;
      }

  };

  template <typename T,typename GT>
  void Clear(PropagatorTrackingLineMinimizer<T,GT>& M) {
    typedef typename PropagatorTrackingLineMinimizer<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(M));
  }

}

#endif

