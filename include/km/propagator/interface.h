
#ifndef _Propagator_Interface_H_
#define _Propagator_Interface_H_

#include "step-propagator-binder/interface.h"
#include "propagator/parameter-name.h"
#include "random/box-muller/interface.h"
#include "random/mt-standard/interface.h"

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

#ifndef _Pointer_
#define _Pointer_(U)  Pointer<T>(_PARAM_(U))
#else
#error "Duplicate _Pointer_"
#endif

#ifndef _PointerArray_
#define _PointerArray_(U) Pointer<AType>(_PARAM_(U))
#else
#error "Duplicate _PointerArray_"
#endif

#ifndef _Alloc_
#define _Alloc_(U) if(_Pointer_(U)==NULL)  _Pointer_(U)=new T;
#else
#error "Duplicate _Alloc_"
#endif

#ifndef _AllocArray_
#define _AllocArray_(U) if(_PointerArray_(U)==NULL) _PointerArray_(U)=new AType;
#else
#error "Duplicate _AllocArray_"
#endif

#ifndef _CpySrc_
#define _CpySrc_(PT,U) Copy(_props[i][j]->_param[PT##_Src##U],_PARAM_(U));
#else
#error "Duplicate _CpySrc_"
#endif

namespace mysimulator {

  template <typename T,typename GT,
            typename GRNG=BoxMuller<MersenneTwisterStandard> >
  class Propagator {

    public:

      typedef Propagator<T,GT,GRNG>    Type;
      typedef Array2DNumeric<T>   AType;
      template <typename T1,typename GT1>
      friend void Clear(Propagator<T1,GT1>&);

      Propagator()
        : _massFlag(UnknownMassProperty), _fricFlag(UnknownFrictionProperty),
          _param(), _props(), _bind() {}
      ~Propagator() { Clear(*this); }

      bool IsValid() const { return _props.IsValid()&&_bind.IsValid(); }

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
        _param.Allocate(PropagatorNumberParameter);
        for(unsigned int i=0;i<_props.Size();++i)
        for(unsigned int j=0;j<_props[i].Size();++j) {
          switch(_props[i][j]->_tag) {
            case VelVerletConstE:
              _Alloc_(TimeStep)
              _CpySrc_(VelVerletConstE,TimeStep)
              if(_massFlag==UniqueMass) {
                _Alloc_(Mass)
                _Alloc_(NegHTIM)
                _Alloc_(VelocitySQ)
              } else if(_massFlag==ArrayMass) {
                _AllocArray_(Mass)
                _AllocArray_(NegHTIM)
                _AllocArray_(VelocitySQ)
              }
              _CpySrc_(VelVerletConstE,Mass)
              _CpySrc_(VelVerletConstE,NegHTIM)
              _CpySrc_(VelVerletConstE,VelocitySQ)
              break;
            case VelVerletLangevin:
              _Alloc_(TimeStep)
              _Alloc_(Temperature)
              _AllocArray_(RandVector)
              if(Pointer<GRNG>(_PARAM_(GaussRNG))==NULL)
                Pointer<GRNG>(_PARAM_(GaussRNG))=new GRNG;
              if(_massFlag==UniqueMass) {
                _Alloc_(Mass)
                _Alloc_(NegHTIM)
                _Alloc_(VelocitySQ)
              } else if(_massFlag==ArrayMass) {
                _AllocArray_(Mass)
                _AllocArray_(NegHTIM)
                _AllocArray_(VelocitySQ)
              }
              if(_fricFlag==UniqueFriction)
                _Alloc_(Friction)
              else if(_fricFlag==ArrayFriction)
                _AllocArray_(Friction)
              if((_massFlag==UniqueMass)&&(_fricFlag==UniqueFriction)) {
                _Alloc_(RandSize)
                _Alloc_(FacBf)
                _Alloc_(FacAf)
              } else if((_massFlag==ArrayMass)||(_fricFlag==ArrayFriction)) {
                _AllocArray_(RandSize)
                _AllocArray_(FacBf)
                _AllocArray_(FacAf)
              }
              _CpySrc_(VelVerletLangevin,TimeStep)
              _CpySrc_(VelVerletLangevin,Temperature)
              _CpySrc_(VelVerletLangevin,RandVector)
              _CpySrc_(VelVerletLangevin,GaussRNG)
              _CpySrc_(VelVerletLangevin,Mass)
              _CpySrc_(VelVerletLangevin,NegHTIM)
              _CpySrc_(VelVerletLangevin,VelocitySQ)
              _CpySrc_(VelVerletLangevin,Friction)
              _CpySrc_(VelVerletLangevin,RandSize)
              _CpySrc_(VelVerletLangevin,FacBf)
              _CpySrc_(VelVerletLangevin,FacAf)
              break;
            default:
              fprintf(stderr,"Unknown StepPropagator Name!\n");
          }
          _props[i][j].Init();
        }
      }

      void SetMassFlag(MassPropertyName MPN) { _massFlag=MPN; }
      void SetFrictionFlag(FrictionPropertyName FPN) { _fricFlag=FPN; }
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

      virtual void Evolute(System<T,GT>&)=0;

    protected:

      MassPropertyName                    _massFlag;
      FrictionPropertyName                _fricFlag;
      Array<Unique64Bit>                  _param;
      Array<Array<StepPropagator<T>*> >   _props;
      Array<StepPropagatorBinder<T,GT>*>  _bind;

    private:

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
      }
      void _IntroduceStep(StepPropagator<T>*& P,const StepPropagatorName PN) {
        switch(PN) {
          case VelVerletConstE: Introduce(P,PN,_massFlag);  break;
          case VelVerletLangevin: Introduce(P,PN,_massFlag,_fricFlag); break;
          default:
            fprintf(stderr,"Unknown StepPropagator Name!\n");
        }
      }

      Propagator(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT,typename GRNG>
  void Clear(Propagator<T,GT,GRNG>& P) {
    ///////// _param not processed!!!!
    P._massFlag=UnknownMassProperty;
    P._fricFlag=UnknownFrictionProperty;
    P._ClearBinder();
    Clear(P._bind);
    P._ClearStepPropagator();
    Clear(P._props);
  }

}

#ifdef _CpySrc_
#undef _CpySrc_
#endif

#ifdef _AllocArray_
#undef _AllocArray_
#endif

#ifdef _Alloc_
#undef _Alloc_
#endif

#ifdef _PointerArray_
#undef _PointerArray_
#endif

#ifdef _Pointer_
#undef _Pointer_
#endif

#undef _PARAM_
#endif

#ifdef _NAME_
#undef _NAME_
#endif

#endif

