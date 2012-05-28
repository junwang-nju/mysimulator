
#ifndef _Propagator_Interface_H_
#define _Propagator_Interface_H_

#include "propagator/parameter-name.h"
#include "step-propagator-binder/interface.h"
#include "random/box-muller/interface.h"
#include "random/mt-standard/interface.h"
#include "propagator-time/interface.h"
#include "propagator-output/interface.h"
#include "system/interface.h"

#ifndef _NAME_
#define _NAME_(U) Propagator##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _PARAM_
#define _PARAM_(U)  _param[_NAME_(U)]
#else
#error "Duplicate _PARAM_"
#endif

#ifndef _Value_
#define _Value_(U)  Value<T>(_PARAM_(U))
#else
#error "Duplicate _Value_"
#endif

#ifndef _PointerArray_
#define _PointerArray_(U) Pointer<AType>(_PARAM_(U))
#else
#error "Duplicate _PointerArray_"
#endif

#ifndef _AllocArray_
#define _AllocArray_(U) if(_PointerArray_(U)==NULL) _PointerArray_(U)=new AType;
#else
#error "Duplicate _AllocArray_"
#endif

#ifndef _LoadSrc_
#define _LoadSrc_(PT,U) \
  Pointer<T>(_props[i][j]->Parameter(PT##_Src##U))=&_Value_(U);
#else
#error "Duplicate _LoadSrc_"
#endif

#ifndef _LoadSrcArray_
#define _LoadSrcArray_(PT,U) \
  _AllocArray_(U) \
  Pointer<AType>(_props[i][j]->Parameter(PT##_Src##U))=_PointerArray_(U);
#else
#error "Duplicate _LoadSrcArray_"
#endif

#ifndef _ClearPointer_
#define _ClearPointer_(RT,U) \
  if(Pointer<RT>(_PARAM_(U))!=NULL) { \
    delete Pointer<RT>(_PARAM_(U)); Pointer<RT>(_PARAM_(U))=NULL; \
  }
#else
#error "Duplicate _ClearPointer_"
#endif

namespace mysimulator {

  template <typename T,typename GT,
            typename GRNG=BoxMuller<MersenneTwisterStandard> >
  class Propagator {

    public:

      typedef Propagator<T,GT,GRNG>    Type;
      typedef Array2DNumeric<T>   AType;
      template <typename T1,typename GT1,typename GR1>
      friend void Clear(Propagator<T1,GT1,GR1>&);

      Propagator()
        : _massFlag(UnknownMassProperty), _fricFlag(UnknownFrictionProperty),
          _param(), _props(), _bind(), _time(), _out(NULL) {}
      virtual ~Propagator() { Clear(*this); }

      bool IsValid() const {
        return _props.IsValid()&&_bind.IsValid()&&_time.IsValid()&&
               _param.IsValid()&&(_out!=NULL);
      }

      void Allocate(const Array<Array<StepPropagatorName> >& PN) {
        assert(PN.IsValid());
        _ClearStepPropagator();
        _props.Allocate(PN.Size());
        for(unsigned int i=0;i<PN.Size();++i) {
          _props[i].Allocate(PN[i].Size());
          for(unsigned int j=0;j<PN[i].Size();++j) {
            _props[i][j]=NULL;
            _IntroduceStep(_props[i][j],PN[i][j]);
          }
        }
        _ClearBinder();
        _bind.Allocate(_props.Size());
        for(unsigned int i=0;i<_bind.Size();++i) {
          _bind[i]=NULL;
          Introduce(_bind[i],_props[i]);
        }
        _ClearParam();
        _param.Allocate(PropagatorNumberParameter);
        Pointer<T>(_PARAM_(TimeStep))=const_cast<T*>(&(_time.TimeStep()));
        Pointer<Random>(_PARAM_(GaussRNG))=new GRNG;
        for(unsigned int i=0;i<_props.Size();++i)
        for(unsigned int j=0;j<_props[i].Size();++j) {
          _props[i][j]->Load(_param);
          _props[i][j]->Init();
        }
      }

      MassPropertyName MassFlag() const { return _massFlag; }
      FrictionPropertyName FrictionFlag() const { return _fricFlag; }
      StepPropagator<T>*& Steps(unsigned int m,unsigned int n) {
        assert(_props.IsValid());
        return _props[m][n];
      }
      const StepPropagator<T>* Steps(unsigned int m,unsigned int n) const {
        assert(_props.IsValid());
        return _props[m][n];
      }
      Unique64Bit& Parameter(PropagatorParameterName n) { return _param[n]; }
      const Unique64Bit& Parameter(PropagatorParameterName n) const {
        return _param[n];
      }
      const T KineticEnergy() const { return _Value_(KineticEnergy); }
      PropagatorTime<T>& Time() { return _time; }
      const PropagatorTime<T>& Time() const { return _time; }
      PropagatorOutput<T,GT,GRNG>*& Output() { return _out; }
      const PropagatorOutput<T,GT,GRNG>* const& Output() const { return _out; }

      void SetMassFlag(MassPropertyName MPN) { _massFlag=MPN; }
      void SetFrictionFlag(FrictionPropertyName FPN) { _fricFlag=FPN; }
      void UpdateKineticEnergy() {
        T ke=0;
        for(unsigned int i=0;i<_props.Size();++i)
        for(unsigned int j=0;j<_props[i].Size();++j) {
          assert(_props[i][j]->IsDynamics());
          _props[i][j]->Update4();
          ke+=Value<double>(_props[i][j]->KineticEnergy());
        }
        _Value_(KineticEnergy)=ke;
      }
      void Update() {
        assert(_props.IsValid());
        for(unsigned int i=0;i<_props.Size();++i)
        for(unsigned int j=0;j<_props[i].Size();++j)
          _props[i][j]->Update();
      }

      void SetOutputTime(const T& ot) {
        assert(_out!=NULL);
        _out->SetTime(ot,_time.TimeStep(),_time.TotalStep());
      }
      void SetOutputTime(unsigned int n) {
        assert(_out!=NULL);
        _out->SetTime(n,_time.TimeStep(),_time.TotalStep());
      }

      virtual void IntroduceSystem(System<T,GT>&) = 0;
      virtual void Evolute(System<T,GT>&) = 0;

    protected:

      MassPropertyName                    _massFlag;
      FrictionPropertyName                _fricFlag;
      Array<Unique64Bit>                  _param;
      Array<Array<StepPropagator<T>*> >   _props;
      Array<StepPropagatorBinder<T,GT>*>  _bind;
      PropagatorTime<T>                   _time;
      PropagatorOutput<T,GT,GRNG>*        _out;

      void _ClearStepPropagator() {
        for(unsigned int i=0;i<_props.Size();++i)
        for(unsigned int j=0;j<_props[i].Size();++j)
          if(_props[i][j]!=NULL) { delete _props[i][j]; _props[i][j]=NULL; }
      }
      void _ClearBinder() {
        for(unsigned int i=0;i<_bind.Size();++i)
          if(_bind[i]!=NULL)  { delete _bind[i]; _bind[i]=NULL; }
      }
      void _ClearParam() {
        if(!_param.IsValid()) return;
        _ClearPointer_(T,Temperature)
        _ClearPointer_(Random,GaussRNG)
        _ClearPointer_(AType,RandVector)
        _ClearPointer_(T,Step)
        if(_massFlag==UniqueMass) {
          _ClearPointer_(T,Mass)
          _ClearPointer_(T,NegHTIM)
          _ClearPointer_(T,VelocitySQ)
        } else if(_massFlag==ArrayMass) {
          _ClearPointer_(AType,Mass)
          _ClearPointer_(AType,NegHTIM)
          _ClearPointer_(AType,VelocitySQ)
        }
        if(_fricFlag==UniqueFriction) {
          _ClearPointer_(T,Friction)
        } else if(_fricFlag==ArrayFriction) {
          _ClearPointer_(AType,Friction)
        }
        if((_massFlag==UniqueMass)&&(_fricFlag==UniqueFriction)) {
          _ClearPointer_(T,RandSize)
          _ClearPointer_(T,FacBf)
          _ClearPointer_(T,FacAf)
        } else if((_massFlag==ArrayMass)||(_fricFlag==ArrayFriction)) {
          _ClearPointer_(AType,RandSize)
          _ClearPointer_(AType,FacBf)
          _ClearPointer_(AType,FacAf)
        }
      }

    private:

      void _IntroduceStep(StepPropagator<T>*& P,const StepPropagatorName PN) {
        switch(PN) {
          case VelVerletConstE: Introduce(P,PN,_massFlag);  break;
          case VelVerletLangevin: Introduce(P,PN,_massFlag,_fricFlag); break;
          case FixPosition: Introduce(P,PN);  break;
          default:
            fprintf(stderr,"Unknown StepPropagator Name!\n");
        }
      }

      Propagator(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT,typename GRNG>
  void Clear(Propagator<T,GT,GRNG>& P) {
    P._ClearParam();
    P._massFlag=UnknownMassProperty;
    P._fricFlag=UnknownFrictionProperty;
    P._ClearBinder();
    Clear(P._bind);
    P._ClearStepPropagator();
    Clear(P._props);
    Clear(P._time);
    if(P._out!=NULL) { delete P._out; P._out=NULL; }
  }

}

#ifdef _ClearArray_
#undef _ClearArray_
#endif

#ifdef _LoadSrcArray_
#undef _LoadSrcArray_
#endif

#ifdef _LoadSrc_
#undef _LoadSrc_
#endif

#ifdef _AllocArray_
#undef _AllocArray_
#endif

#ifdef _PointerArray_
#undef _PointerArray_
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

