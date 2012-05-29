
#ifndef _Propagator_Minimizer_Line_Interface_H_
#define _Propagator_Minimizer_Line_Interface_H_

#include "propagator/minimizer-base/interface.h"
#include "propagator/minimizer-line/parameter-name.h"
#include "propagator-minimizer-line-condition/interface.h"
#include "basic/constant.h"

#ifndef _NAME_
#define _NAME_(U) LineMin_##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _PARAM_
#define _PARAM_(U) this->_param[_NAME_(U)]
#else
#error "Duplicate _PARAM_"
#endif

#ifndef _VALUE_
#define _VALUE_(RT,U) Value<RT>(_PARAM_(U))
#else
#error "Duplicate _VALUE_"
#endif

namespace mysimulator {

  template <typename T,typename GT> class PropagatorLineMinimizer;
  template <typename T,typename GT> void Clear(PropagatorLineMinimizer<T,GT>&);

  template <typename T, typename GT>
  class PropagatorLineMinimizer : public PropagatorBaseMinimizer<T,GT> {

    public:

      typedef PropagatorLineMinimizer<T,GT>     Type;
      typedef PropagatorBaseMinimizer<T,GT>   ParentType;
      friend void Clear<T,GT>(PropagatorLineMinimizer<T,GT>&);

      PropagatorLineMinimizer()
        : ParentType(), _backupX(), _backupG(), _Condition(NULL) {}
      virtual ~PropagatorLineMinimizer() { Clear(*this); }

      virtual bool IsValid() const { 
        return ParentType::IsValid()&&_backupX.IsValid()&&_backupG.IsValid();
      }

      virtual void IntroduceSystem(System<T,GT>& S) {
        ParentType::IntroduceSystem(S);
        _backupX.Imprint(S.Location());
        _backupG.Imprint(S.Location());
      }
      virtual void DetachSystem() {
        ParentType::DetachSystem();
        Clear(_backupX);
        Clear(_backupG);
      }

      virtual void Update() {
        ParentType::Update();
        assert(this->_param.IsValid());
        if(_VALUE_(unsigned int,MaxStep)==0) _VALUE_(unsigned int,MaxStep)=1000;
        if(_VALUE_(T,DecreaseFac)<1e-8) _VALUE_(T,DecreaseFac)=1e-4;
        if(_VALUE_(T,CurvatureFac)<1e-8)  _VALUE_(T,CurvatureFac)=0.4;
        if(_VALUE_(T,GradThreshold)<_RelDelta<T>())
          _VALUE_(T,GradThreshold)=_RelDelta<T>();
        LineMinimizerConditionName LCN;
        LCN=static_cast<LineMinimizerConditionName>(
            _VALUE_(unsigned int,ConditionTag));
        if(LCN==UnknownCondition)
          _VALUE_(unsigned int,ConditionTag)=StrongWolfe;
        LCN=static_cast<LineMinimizerConditionName>(
            _VALUE_(unsigned int,ConditionTag));
        if((_Condition==NULL)||(_Condition->Name()!=LCN))
          _SetCondition(LCN);
      }

      virtual void Allocate(const Array<StepPropagatorName>& PN,...) {
        Clear(*this);
        assert(_Flag(PN)==1);
        this->_props.Allocate(PN.Size());
        for(unsigned int i=0;i<this->_props.Size();++i)
          Introduce(this->_props[i],PN[i]);
        this->_bind=NULL;
        Introduce(this->_bind,this->_props);
        this->_time=NULL;
        this->_output=NULL;
      }

    protected:

      Array2DNumeric<T> _backupX;
      Array2DNumeric<T> _backupG;
      LineMinimizerCondition<T>* _Condition;

      virtual void BuildLine() {
        assert(this->_param.IsValid());
        for(unsigned int i=0;i<this->_props.Size();++i) {
          this->_props[i]->Load(this->_param);
          this->_props[i]->Init();
        }
      }

      virtual void IndependentModule() = 0;

    private:

      PropagatorLineMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      void _SetCondition(const LineMinimizerConditionName CN) {
        assert(this->_param.IsValid());
        Introduce(_Condition,CN);
        _VALUE_(unsigned int,ConditionTag)=CN;
      }

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

  template <typename T, typename GT>
  void Clear(PropagatorLineMinimizer<T,GT>& P) {
    if(P._Condition!=NULL) { delete P._Condition; P._Condition=NULL; }
    Clear(P._backupX);
    Clear(P._backupG);
    typedef typename PropagatorLineMinimizer<T,GT>::ParentType  PType;
    Clear(static_cast<PType&>(P));
  }

}

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

