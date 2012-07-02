
#ifndef _Propagator_Time_MolecularDynamics_Interface_H_
#define _Propagator_Time_MolecularDynamics_Interface_H_

#include "propagator-time/interface.h"
#include "propagator-time/molecular-dynamics/parameter-name.h"
#include "propagator-time/molecular-dynamics/update-name.h"

#ifndef _NAME_
#define _NAME_(U)   MDTime_##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _PARAM_
#define _PARAM_(U)  this->_param[_NAME_(U)]
#else
#error "Duplicate _PARAM_"
#endif

#ifndef _Value_
#define _Value_(RT,U)   Value<RT>(_PARAM_(U))
#else
#error "Duplicate _Value_"
#endif

#ifndef _TValue_
#define _TValue_(U)     _Value_(T,U)
#else
#error "Duplicate _TValue_"
#endif

#ifndef _IValue_
#define _IValue_(U)     _Value_(unsigned int,U)
#else
#error "Duplicate _IValue_"
#endif

namespace mysimulator {

  template <typename T>
  class PropagatorMDTime : public PropagatorTime<T> {

    public:

      typedef PropagatorMDTime<T>   Type;
      typedef PropagatorTime<T>     ParentType;

      PropagatorMDTime() : ParentType() {}
      virtual ~PropagatorMDTime() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=MolecularDynamics;
        this->_param.Allocate(MDTime_NumberParameter);
      }
      virtual bool IsTProperty(unsigned int n) {
        bool fg;
        switch(n) {
          case MDTime_TimeStep:
          case MDTime_NowTime:
          case MDTime_TotalPeriod:
          case MDTime_OutputInterval:
            fg=true;  break;
          default:
            fg=false;
        }
        return fg;
      }
      virtual bool IsUIntProperty(unsigned int n) {
        bool fg;
        switch(n) {
          case MDTime_NowStep:
          case MDTime_NumberStep:
          case MDTime_NumberStepBwOutput:
          case MDTime_NumberOutput:
            fg=true;  break;
          default:
            fg=false;
        }
        return fg;
      }
      virtual void Update(unsigned int n) {
        switch(n) {
          case NTotal_Total_OInterval:
          case NTotal_Total_NBwOutput:
            _TValue_(TimeStep)=_TValue_(TotalPeriod)/_IValue_(NumberStep);
            break;
          case Step_Total_OInterval:
          case Step_Total_NBwOutput:
            _IValue_(NumberStep)=
              static_cast<unsigned int>(_TValue_(TotalPeriod)/
                                        _TValue_(TimeStep));
          case Step_NTotal_OInterval:
          case Step_NTotal_NBwOutput:
            _TValue_(TotalPeriod)=_IValue_(NumberStep)*_TValue_(TimeStep);
            break;
          default:
            fprintf(stderr,"Unknown Update Method!\n");
        }
        switch(n) {
          case Step_Total_OInterval:
          case Step_NTotal_OInterval:
          case NTotal_Total_OInterval:
            _IValue_(NumberStepBwOutput)=
              static_cast<unsigned int>(_TValue_(OutputInterval)/
                                        _TValue_(TimeStep)+0.5);
            if(_IValue_(NumberStepBwOutput)==0) _IValue_(NumberStepBwOutput)=1;
          case Step_Total_NBwOutput:
          case Step_NTotal_NBwOutput:
          case NTotal_Total_NBwOutput:
            _TValue_(OutputInterval)=_IValue_(NumberStepBwOutput)*
                                     _TValue_(TimeStep);
            _IValue_(NumberOutput)=
              _IValue_(NumberStep)/_IValue_(NumberStepBwOutput);
            break;
          default:
            fprintf(stderr,"Unknown Update Method!\n");
        }
      }

    private:

      PropagatorMDTime(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(PropagatorMDTime<T>& PT) {
    typedef typename PropagatorMDTime<T>::ParentType   PType;
    Clear(static_cast<PType&>(PT));
  }

}

#ifdef _IValue_
#undef _IValue_
#endif

#ifdef _TValue_
#undef _TValue_
#endif

#ifdef _Value_
#undef _Value_
#endif

#ifdef _PARAM_
#undef _PARAM_
#endif

#ifdef _NAME_
#undef _NAME_
#endif

#endif

