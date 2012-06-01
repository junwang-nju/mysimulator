
#ifndef _Propagator_MolecularDynamics_Interface_H_
#define _Propagator_MolecularDynamics_Interface_H_

#include "propagator/interface.h"
#include "propagator/molecular-dynamics/parameter-name.h"

#ifndef _NAME_
#define _NAME_(U) PropagatorMD_##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _PARAM_
#define _PARAM_(U) this->_param[_NAME_(U)]
#else
#error "Duplicate _PARAM_"
#endif

#ifndef _Pointer_
#define _Pointer_(RT,U) Pointer<RT>(_PARAM_(U))
#else
#error "Duplicate _Pointer_"
#endif

#ifndef _ClearPointer_
#define _ClearPointer_(RT,U) \
  if(_Pointer_(RT,U)!=NULL) { delete _Pointer_(RT,U); _Pointer_(RT,U)=NULL; }
#else
#error "Duplicate _ClearPointer_"
#endif

namespace mysimulator {

  template <typename T,typename GT> class PropagatorMD;
  template <typename T,typename GT> void Clear(PropagatorMD<T,GT>&);

  template <typename T,typename GT>
  class PropagatorMD : public Propagator<T,GT> {

    public:

      typedef PropagatorMD<T,GT>  Type;
      typedef Propagator<T,GT>    ParentType;
      typedef Array2DNumeric<T>   AType;
      friend void Clear<T,GT>(PropagatorMD<T,GT>&);

      PropagatorMD() : ParentType(), _massFlag(UnknownMassProperty),
                       _fricFlag(UnknownFrictionProperty) {}
      virtual ~PropagatorMD() { Clear(*this); }

      virtual bool IsValid() const {
        return ParentType::IsValid()&&(this->_time!=NULL)&&
               (this->_output!=NULL);
      }

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
        this->_props.Allocate(PN.Size());
        for(unsigned int i=0;i<PN.Size();++i) this->_props[i]=NULL;
        for(unsigned int i=0;i<PN.Size();++i)
          _IntroduceStep(this->_props[i],PN[i]);
        this->_bind=NULL;
        Introduce(this->_bind,this->_props);
        this->_param.Allocate(PropagatorMD_NumberParameter);
        Introduce(this->_time,MolecularDynamics);
        _Pointer_(T,TimeStep)=const_cast<T*>(&(this->Time(MDTime_TimeStep)));
        _Pointer_(Random,GaussRNG)=NULL;
        if(fg&4) {
          RandomName RN1=static_cast<RandomName>(va_arg(vl,unsigned int));
          RandomName RN2=UnknownRNG;
          unsigned int n=0;
          switch(RN1) {
            case BoxMullerRNG:
              RN2=static_cast<RandomName>(va_arg(vl,unsigned int));
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
        for(unsigned int i=0;i<this->_props.Size();++i) {
          this->_props[i]->Load(this->_param);
          this->_props[i]->Init();
        }
        va_end(vl);
      }

      virtual unsigned int Evolute(System<T,GT>& S) {
        this->_output->Write(this->Time(MDTime_NowTime),S,this);
        unsigned int no=this->IntTime(MDTime_NumberOutput);
        unsigned int dno=this->IntTime(MDTime_NumberStepBwOutput);
        T dOT=this->Time(MDTime_OutputInterval);
        for(unsigned int i=0;i<no;++i) {
          for(unsigned int k=0;k<dno;++k)
            this->_bind->Evolute(S.Location(),S.Energy(),S.Gradient(),
                                 S.InteractionGroup(0),this->_props);
          this->Time(MDTime_NowTime)+=dOT;
          this->IntTime(MDTime_NowStep)+=dno;
          this->_output->Write(this->Time(MDTime_NowTime),S,this);
        }
        unsigned int nt=this->IntTime(MDTime_NowStep);
        unsigned int tt=this->IntTime(MDTime_NumberStep);
        if(nt<tt) {
          for(unsigned int i=nt;i<tt;++i)
            this->_bind->Evolute(S.Location(),S.Energy(),S.Gradient(),
                                 S.InteractionGroup(0),this->_props);
          this->Time(MDTime_NowTime)=this->Time(MDTime_TotalPeriod);
          this->Time(MDTime_NowStep)=tt;
          this->_output->Write(this->Time(MDTime_NowTime),S,this);
        }
        return 1;
      }

      virtual const T KineticEnergy() const {
        assert(this->_param.IsValid());
        return Value<T>(this->Parameter(PropagatorMD_KineticEnergy));
      }
      virtual void UpdateKineticEnergy() {
        assert(this->_props.IsValid());
        assert(this->_param.IsValid());
        T ke=0;
        unsigned int n=this->_props.Size();
        for(unsigned int i=0;i<n;++i) {
          assert(this->_props[i]->IsDynamics());
          this->_props[i]->Update4();
          ke+=Value<double>(this->_props[i]->KineticEnergy());
        }
        Value<T>(this->Parameter(PropagatorMD_KineticEnergy))=ke;
      }

    protected:

      MassPropertyName _massFlag;
      FrictionPropertyName  _fricFlag;

      virtual void _ClearParameter() {
        if(!this->_param.IsValid()) return;
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
            case VelVerletConstVelocity:
              break;
            default:
              fprintf(stderr,"Improper StepPropagator\n");
          }
        return fg;
      }
      void _IntroduceStep(StepPropagator<T>*& P,StepPropagatorName PN) {
        switch(PN) {
          case VelVerletConstE:
          case VelVerletBerendsen:
            Introduce(P,PN,_massFlag); break;
          case VelVerletLangevin:
            Introduce(P,PN,_massFlag,_fricFlag);  break;
          case FixPosition:
          case VelVerletConstVelocity:
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

#ifdef _ClearPointer_
#undef _ClearPointer_
#endif

#ifdef _Pointer_
#undef _Pointer_
#endif

#ifdef _PARAM_
#undef _PARAM_
#endif

#ifdef _NAME_
#undef _NAME_
#endif

#endif

