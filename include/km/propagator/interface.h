
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
  Pointer<T>(_props[i][j]->_param[PT##_Src##U])=&_Value_(U);
#else
#error "Duplicate _LoadSrc_"
#endif

#ifndef _LoadSrcArray_
#define _LoadSrcArray_(PT,U) \
  _AllocArray_(U) \
  Pointer<AType>(_props[i][j]->_param[PT##_Src##U])=_PointerArray_(U);
#else
#error "Duplicate _LoadSrcArray_"
#endif

#ifndef _ClearArray_
#define _ClearArray_(U) \
  if(_PointerArray_(U)!=NULL) { \
    delete _PointerArray_(U); _PointerArray_(U)=NULL; \
  }
#else
#error "Duplicate _ClearArray_"
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
              _LoadSrc_(VelVerletConstE,TimeStep)
              if(_massFlag==UniqueMass) {
                _LoadSrc_(VelVerletConstE,Mass)
                _LoadSrc_(VelVerletConstE,NegHTIM)
                _LoadSrc_(VelVerletConstE,VelocitySQ)
              } else if(_massFlag==ArrayMass) {
                _LoadSrcArray_(VelVerletConstE,VelocitySQ)
                _LoadSrcArray_(VelVerletConstE,NegHTIM)
                _LoadSrcArray_(VelVerletConstE,VelocitySQ)
              }
              break;
            case VelVerletLangevin:
              _LoadSrc_(VelVerletLangevin,TimeStep)
              _LoadSrc_(VelVerletLangevin,Temperature)
              _LoadSrcArray_(VelVerletLangevin,RandVector)
              if(Pointer<GRNG>(_PARAM_(GaussRNG))==NULL)
                Pointer<GRNG>(_PARAM_(GaussRNG))=new GRNG;
              Pointer<GRNG>(_props[i][j]._param[VelVerletLangevin_SrcGaussRNG])=
                Pointer<GRNG>(_PARAM_(GaussRNG));
              if(_massFlag==UniqueMass) {
                _LoadSrc_(VelVerletLangevin,Mass)
                _LoadSrc_(VelVerletLangevin,NegHTIM)
                _LoadSrc_(VelVerletLangevin,VelocitySQ)
              } else if(_massFlag==ArrayMass) {
                _LoadSrcArray_(VelVerletLangevin,Mass)
                _LoadSrcArray_(VelVerletLangevin,NegHTIM)
                _LoadSrcArray_(VelVerletLangevin,VelocitySQ)
              }
              if(_fricFlag==UniqueFriction)
                _LoadSrc_(VelVerletLangevin,Friction)
              else if(_fricFlag==ArrayFriction)
                _LoadSrcArray_(VelVerletLangevin,Friction)
              if((_massFlag==UniqueMass)&&(_fricFlag==UniqueFriction)) {
                _LoadSrc_(VelVerletLangevin,RandSize)
                _LoadSrc_(VelVerletLangevin,FacBf)
                _LoadSrc_(VelVerletLangevin,FacAf)
              } else if((_massFlag==ArrayMass)||(_fricFlag==ArrayFriction)) {
                _LoadSrcArray_(VelVerletLangevin,RandSize)
                _LoadSrcArray_(VelVerletLangevin,FacBf)
                _LoadSrcArray_(VelVerletLangevin,FacAf)
              }
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

      //virtual void Evolute(System<T,GT>&)=0;

    protected:

      MassPropertyName                    _massFlag;
      FrictionPropertyName                _fricFlag;
      Array<Unique64Bit>                  _param;
      Array<Array<StepPropagator<T>*> >   _props;
      Array<StepPropagatorBinder<T,GT>*>  _bind;

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
        _ClearArray_(RandVector)
        if(_massFlag==ArrayMass) {
          _ClearArray_(Mass)
          _ClearArray_(NegHTIM)
          _ClearArray_(VelocitySQ)
        }
        if(_fricFlag==ArrayFriction)  _ClearArray_(Friction)
        if((_massFlag==ArrayMass)||(_fricFlag==ArrayFriction)) {
          _ClearArray_(RandSize)
          _ClearArray_(FacBf)
          _ClearArray_(FacAf)
        }
      }

    private:

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
    P._ClearParam();
    P._massFlag=UnknownMassProperty;
    P._fricFlag=UnknownFrictionProperty;
    P._ClearBinder();
    Clear(P._bind);
    P._ClearStepPropagator();
    Clear(P._props);
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

