
#ifndef _Propagator_Minimizer_Line_Tracking_Interface_H_
#define _Propagator_Minimizer_Line_Tracking_Interface_H_

#include "propagator/minimizer/line/interface.h"
#include "propagator/minimizer/line/name.h"
#include "propagator/minimizer/line/minimal-step.h"
#include "propagator/minimizer/line/tracking/parameter-name.h"

#define _NAME_(U) TrackingLineMin_##U
#define _PARAM_(U)  this->_param[_NAME_(U)]
#define _VALUE_(RT,U) Value<RT>(_PARAM_(U))
#define _PointerVALUE_(RT,U)  (*Pointer<RT>(_PARAM_(U)))

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
        for(unsigned int i=0;i<this->_props.Size();++i) {
          this->_props[i]->Load(this->_param);
          this->_props[i]->Init();
        }
        this->_time=NULL;
        this->_output=NULL;
      }

      virtual unsigned int Evolute(System<T,GT>& S) {
        assert(this->IsValid());
        // assume Proj is Calculated!
        assert(this->Proj<=0);
        const T mstep=MinimalStep(S.Location(),S.Velocity(),this->DOF);
        _PointerVALUE_(T,Step)=_VALUE_(T,SearchScale);
        T rstep=_PointerVALUE_(T,Step);
        T c1pj=_VALUE_(T,DecreaseFac)*this->Proj;
        T c2pj=_VALUE_(T,CurvatureFac)*this->Proj;
        unsigned int state=0;
        this->_backupX.BlasCopy(S.Location());
        T _backupE=S.Energy();
        T _backupPrj=this->Proj;
        for(unsigned int i=0;i<_VALUE_(unsigned int,MaxStep);++i) {
          this->_bind->Evolute(S.Location(),S.Energy(),S.Gradient(),
                               S.InteractionGroup(0),this->_props);
          _VALUE_(unsigned int,GCalcCount)++;
          this->Proj=BlasDot(S.Gradient(),S.Velocity());
          if(this->_Condition->Check(S.Energy(),this->Proj,_backupE,
                                     c1pj,c2pj,rstep)) {
            this->Move=rstep;
            state=1;
            break;
          }
          if(_PointerVALUE_(T,Step)*this->Proj>0)
            _PointerVALUE_(T,Step)*=-_VALUE_(T,TrackingFac);
          rstep+=_PointerVALUE_(T,Step);
          if(AbsVal(_PointerVALUE_(T,Step))<mstep) { state=2; break; }
        }
        if(state!=0)
          if(S.Energy()>_backupE) {
            S.Location().BlasCopy(this->_backupX);
            S.Energy()=_backupE;
            this->Proj=_backupPrj;
          }
        return state;
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

