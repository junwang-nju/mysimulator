
#ifndef _Propagator_Time_MolecularDynamics_Interface_H_
#define _Propagator_Time_MolecularDynamics_Interface_H_

#include "propagator-time/interface.h"
#include "propagator-time/molecular-dynamics/parameter-name.h"
#include "propagator-time/molecular-dynamics/update-name.h"

#define _NAME_(U)   MDTime_##U
#define _PARAM_(U)  this->_param[_NAME_(U)]
#define _Value_(RT,U)   Value<RT>(_PARAM_(U))
#define _TValue_(U)     _Value_(T,U)
#define _IValue_(U)     _Value_(unsigned int,U)

namespace mysimulator {

  template <typename T>
  class PropagatorMDTime : public PropagatorTime<T> {

    public:

      typedef PropagatorMDTime<T>   Type;
      typedef PropagatorTime<T>     ParentType;

      PropagatorMDTime() : ParentType() {}
      ~PropagatorMDTime() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=MolecularDynamics;
        this->_param.Allocate(MDTime_NumberParameter);
        this->_flag.Allocate(MDTime_NumberParameter);
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
            fg=true;
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

#endif

