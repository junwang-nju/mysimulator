
#ifndef _Step_Propagator_Dynamics_VelVerlet_Berendsen_Interface_H_
#define _Step_Propagator_Dynamics_VelVerlet_Berendsen_Interface_H_

#include "step-propagator/dynamics/vel-verlet/interface.h"
#include "step-propagator/dynamics/vel-verlet/berendsen/parameter-name.h"
#include "propagator/molecular-dynamics/parameter-name.h"

#ifndef _NAME_
#define _NAME_(DT,U)        VelVerletBerendsen_##DT##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _PARAM_
#define _PARAM_(DT,U)       this->_param[_NAME_(DT,U)]
#else
#error "Duplicate _PARAM_"
#endif

#ifndef _Pointer_
#define _Pointer_(DT,U)     Pointer<T>(_PARAM_(DT,U))
#else
#error "Duplicate _Pointer_"
#endif

#ifndef _Value_
#define _Value_(DT,U)       (*_Pointer_(DT,U))
#else
#error "Duplicate _Value_"
#endif

#ifndef _SrcValue_
#define _SrcValue_(U)       _Value_(Src,U)
#else
#error "Duplicate _SrcValue_"
#endif

#ifndef _ValValue_
#define _ValValue_(U)       Value<T>(_PARAM_(Val,U))
#else
#error "Duplicate _ValValue_"
#endif

#ifndef _SrcPointer_
#define _SrcPointer_(RT,U)    Pointer<RT>(_PARAM_(Src,U))
#else
#error "Duplicate _SrcPointer_"
#endif

#ifndef _PPARAM_
#define _PPARAM_(U)           P[PropagatorMD_##U]
#else
#error "Duplicate _PPARAM_"
#endif

#ifndef _PPointer_
#define _PPointer_(RT,U)       Pointer<RT>(_PPARAM_(U))
#else
#error "Duplicate _PPointer_"
#endif

#ifndef _LoadPointer_
#define _LoadPointer_(RT,U)  \
  if(_PPointer_(RT,U)==NULL)  _PPointer_(RT,U)=new RT; \
  _SrcPointer_(RT,U)=_PPointer_(RT,U);
#else
#error "Duplicate _LoadPointer_"
#endif

namespace mysimulator {

  template <typename T, template <typename> class PropagatorWithMass>
  class StepPropagatorVelVerletBerendsen : public PropagatorWithMass<T> {

    public:

      typedef StepPropagatorVelVerletBerendsen<T,PropagatorWithMass> Type;
      typedef PropagatorWithMass<T>   ParentType;

      StepPropagatorVelVerletBerendsen() : ParentType() {}
      virtual ~StepPropagatorVelVerletBerendsen() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=VelVerletBerendsen;
        this->_param.Allocate(VelVerletBerendsen_NumberParameter);
      }
      virtual void Update() {
        this->Update1();
        this->Update5();
        this->Update6();
        this->Update2();
        this->Update7();
      }
      virtual void Update3() {
        assert(this->_param.IsValid());
        _ValValue_(KineticEnergy)=0.5*_ValValue_(DualKineticEnergy);
      }
      virtual void Update4() { this->Update3(); }
      virtual void Update5() {
        assert(this->_param.IsValid());
        unsigned int n=0;
        for(unsigned int i=0;i<this->_X.Size();++i)
          n+=this->_X[i].NumElements();
        _ValValue_(DOF)=n;
      }
      virtual void Update6() {
        assert(this->_param.IsValid());
        T q=0.5*_SrcValue_(TimeStep)/_SrcValue_(RelaxTime);
        _ValValue_(FacBf1)=1-q;
        _ValValue_(FacBf2)=q*_SrcValue_(Temperature)*_ValValue_(DOF);
        q+=1;
        _ValValue_(FacAf1)=1./q;
        _ValValue_(FacAf2)=_ValValue_(FacBf2)/q;
      }
      virtual void Evolute1() {
        assert(this->_param.IsValid());
        assert(this->_V.IsValid());
        T fac=_ValValue_(FacBf1)+
              _ValValue_(FacBf2)/_ValValue_(DualKineticEnergy);
        fac=__SqRoot(fac);
        for(unsigned int i=0;i<this->_V.Size();++i) this->_V[i].BlasScale(fac);
        ParentType::Evolute1();
      }
      virtual void Evolute2() {
        ParentType::Evolute2();
        this->Update2();
        this->Update7();
        T fac=_ValValue_(FacAf1)+
              _ValValue_(FacAf2)/_ValValue_(DualKineticEnergy);
        _ValValue_(DualKineticEnergy)*=fac;
        fac=__SqRoot(fac);
        for(unsigned int i=0;i<this->_V.Size();++i) this->_V[i].BlasScale(fac);
      }

      virtual void Load(Array<Unique64Bit>& P) {
        ParentType::Load(P);
        _LoadPointer_(T,RelaxTime)
        _LoadPointer_(T,Temperature)
      }

    private:

      StepPropagatorVelVerletBerendsen(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename>class PM>
  void Clear(StepPropagatorVelVerletBerendsen<T,PM>& P) {
    typedef typename StepPropagatorVelVerletBerendsen<T,PM>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#ifdef _LoadPointer_
#undef _LoadPointer_
#endif

#ifdef _PPointer_
#undef _PPointer_
#endif

#ifdef _PPARAM_
#undef _PPARAM_
#endif

#ifdef _SrcPointer_
#undef _SrcPointer_
#endif

#ifdef _ValValue_
#undef _ValValue_
#endif

#ifdef _SrcValue_
#undef _SrcValue_
#endif

#ifdef _Value_
#undef _Value_
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

