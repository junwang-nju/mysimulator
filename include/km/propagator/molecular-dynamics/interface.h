
#ifndef _Propagator_MolecularDynamics_Interface_H_
#define _Propagator_MolecularDynamics_Interface_H_

#include "propagator/interface.h"
#include "propagator/molecular-dynamics/parameter-name.h"

#define _NAME_(U) PropagatorMD_##U
#define _PARAM_(U) this->_param[_NAME_(U)]
#define _Pointer_(RT,U) Pointer<RT>(_PARAM_(U))
#define _ClearPointer_(RT,U) \
  if(_Pointer_(RT,U)!=NULL) { delete _Pointer_(RT,U); _Pointer_(RT,U)=NULL; }

namespace mysimulator {

  template <typename T,typename GT>
  class PropagatorMD : public Propagator<T,GT> {

    public:

      typedef PropagatorMD<T,GT>  Type;
      typedef Propagator<T,GT>    ParentType;
      typedef Array2DNumeric<T>   AType;
      template <typename T1,typename GT1>
      friend void Clear(PropagatorMD<T1,GT>&);

      PropagatorMD() : ParentType(), _massFlag(UnknownMassProperty),
                       _fricFlag(UnknownFrictionProperty) {}
      virtual ~PropagatorMD() { Clear(*this); }

      virtual void Allocate(const Array<StepPropagatorName>& PN, ...) {
        Clear(*this);
        this->_tag=MolecularDynamics;
        unsigned int fg=_Flag(PN);
        va_list vl;
        va_start(vl,PN);
        if(fg&1)
          _massFlag=static_cast<MassPropertyName>(va_arg(vl,unsigned int));
        if(fg&2)
          _fricFlag=static_cast<FrictionPropertyName>(va_arg(vl,unsigned int));
        _props.Allocate(PN.Size());
        for(unsigned int i=0;i<PN.Size();++i) _IntroduceStep(_props[i],PN[i]);
        _bind=NULL;
        Introduce(_bind,_props);
        this->_param.Allocate(PropagatorMD_NumberParameter);
        this->_time=new PropagatorMDTime;
        this->_time->Allocate();
        _Pointer_(T,TimeStep)=const_cast<T*>(&(_time->TimeStep()));
        _Pointer_(Random,GaussRNG)=NULL;
        if(fg&4) {
          RandomName RN1=static_cast<RandomName>(va_arg(vl,unsigned int));
          switch(RN1) {
            case BoxMullerRNG:
              RandomName RN2=static_cast<RandomName>(va_arg(vl,unsigned int));
              unsigned int n=0;
              switch(RN2) {
                case MTDSFMTRNG:
                case MTSFMTRNG:
                  n=va_arg(vl,unsigned int);
                case MTStandardRNG:
                  Introduce(_Pointer_(Random,GaussRNG),RN1,RN2,n);
                  break;
                default:
                  fprintf(stderr,"Unknown Uniform RNG!\n");
              }
              break;
            default:
              fprintf(stderr,"Unknown Gaussian RNG!\n");
          }
        }
        for(unsigned int i=0;i<_props.Size();++i) {
          _props[i]->_Load(_param);
          _props[i]->_Init();
        }
        va_end(vl);
      }

      virtual void IntroduceSystem(System<T,GT>& S) {
        for(unsigned int i=0;i<this->_props.Size();++i) {
          this->_props[i]->IntroduceX(S.Location());
          this->_props[i]->IntroduceG(S.Gradient());
          this->_props[i]->IntroduceV(S.Velocity());
        }
      }

    protected:

      MassPropertyName _massFlag;
      FrictionPropertyName  _fricFlag;

      virtual void _ClearParameter() {
        if(!_param.IsValid()) return;
        _ClearPointer_(T,Temperature)
        _ClearPointer_(Random,GaussRNG)
        _ClearPointer_(AType,RandVector)
        _ClearPointer_(T,RelaxTime)
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

      unsigned int _Flag(const Array<StepPropagatorName>& PN) {
        unsigned int fg=0;
        for(unsigned int i=0;i<PN.Size();++i)
          switch(PN[i]) {
            case VelVerletConstE:
            case VelVerletBerendsen:
              fg|=1;
              break;
            case VelVerletLangevin:
              fg|=7;
              break;
            case FixPosition:
              break;
            default:
              fprintf(stderr,"Improper StepPropagator\n");
          }
        return fg;
      }
      void _IntroduceStep(StepPropagator<T>* P,StepPropagatorName PN) {
        switch(PN) {
          case VelVerletConstE:
          case VelVerletBerendsen:
            Introduce(P,PN,_massFlag); break;
          case VelVerletLangevin:
            Introduce(P,PN,_massFlag,_fricFlag);  break;
          case FixPosition:
            Introduce(P,PN);  break;
          default:
            fprintf(stderr,"StepPropagator Not Suitable for MD!\n");
        }
      }

      PropagatorMD(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(PropagatorMD<T,GT>& P) {
    typedef typename PropagatorMD<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(P));
    P._massFlag=UnknownMassProperty;
    P._fricFlag=UnknownFrictionProperty;
  }

}

#endif

