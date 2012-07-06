
#ifndef _Propagator_Minimizer_Line_Tracking_Interface_H_
#define _Propagator_Minimizer_Line_Tracking_Interface_H_

#include "propagator/minimizer-line/interface.h"
#include "propagator/minimizer-line/name.h"
#include "propagator/minimizer-line/minimal-step.h"
#include "propagator/minimizer-line/tracking/parameter-name.h"

#ifndef _NAME_
#define _NAME_(U) TrackingLineMin_##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _PARAM_
#define _PARAM_(U)  this->_param[_NAME_(U)]
#else
#error "Duplicate _PARAM_"
#endif

#ifndef _VALUE_
#define _VALUE_(RT,U) Value<RT>(_PARAM_(U))
#else
#error "Duplicate _VALUE_"
#endif

#ifndef _PointerVALUE_
#define _PointerVALUE_(RT,U)  (*Pointer<RT>(_PARAM_(U)))
#else
#error "Duplicate _PointerVALUE_"
#endif

namespace mysimulator {

  template <typename T,typename GT>
  class PropagatorTrackingLineMinimizer : public PropagatorLineMinimizer<T,GT> {

    public:

      typedef PropagatorTrackingLineMinimizer<T,GT> Type;
      typedef PropagatorLineMinimizer<T,GT> ParentType;

      PropagatorTrackingLineMinimizer() : ParentType() {}
      virtual ~PropagatorTrackingLineMinimizer() { Clear(*this); }

      virtual void Update() {
        ParentType::Update();
        if(_VALUE_(T,TrackingFac)<1e-8) _VALUE_(T,TrackingFac)=_Golden<T>();
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

    protected:

      virtual void BuildLine() {
        assert(this->_param.IsValid());
        _VALUE_(unsigned int,LineTag)=TrackingLineMinimizer;
        ParentType::BuildLine();
      }

    private:

      PropagatorTrackingLineMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(PropagatorTrackingLineMinimizer<T,GT>& M) {
    typedef typename PropagatorTrackingLineMinimizer<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(M));
  }

}

#ifdef _PointerVALUE_
#undef _PointerVALUE_
#endif

#ifdef _VALUE_
#undef _VALUE_
#endif

#ifdef _PARAM_
#undef _PARAM_
#endif

#ifdef _NAME_
#undef _NAME_
#endif

#endif

