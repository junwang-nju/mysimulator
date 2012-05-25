
#ifndef _Step_Propagator_VelVerlet_ConstE_UMass_Interface_H_
#define _Step_Propagator_VelVerlet_ConstE_UMass_Interface_H_

#include "step-propagator/vel-verlet-const-e/interface.h"

#ifndef _Src2Ptr_
#define _Src2Ptr_(U) \
  Pointer<T>(this->_param[VelVerletConstE_Ptr##U])=\
    Pointer<T>(this->_param[VelVerletConstE_Src##U]);
#else
#error "Duplicate _Src2Ptr_"
#endif

#ifndef _PtrValue_
#define _PtrValue_(U) \
  (*Pointer<T>(this->_param[VelVerletConstE_Ptr##U]))
#else
#error "Duplicate _PtrValue_"
#endif

#ifndef _SrcValue_
#define _SrcValue_(U) \
  (*Pointer<T>(this->_param[VelVerletConstE_Src##U]))
#else
#error "Duplicate _SrcValue_"
#endif

#ifndef _ValValue_
#define _ValValue_(U) \
  Value<T>(this->_param[VelVerletConstE_Val##U])
#else
#error "Duplicate _ValValue_"
#endif

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletConstE_UMass
      : public StepPropagatorVelVerletConstE<T> {

    public:

      typedef StepPropagatorVelVerletConstE_UMass<T>  Type;
      typedef StepPropagatorVelVerletConstE<T>  ParentType;

      StepPropagatorVelVerletConstE_UMass() : ParentType() {}
      ~StepPropagatorVelVerletConstE_UMass() { Clear(*this); }

      virtual void Init() {
        _Src2Ptr_(Mass)
        _Src2Ptr_(NegHTIM)
        _Src2Ptr_(VelocitySQ)
      }
      virtual void Clean() {}
      virtual void Update1() {  // HTIM
        assert(this->_param.IsValid());
        _PtrValue_(NegHTIM)=-0.5*_SrcValue_(TimeStep)/_PtrValue_(Mass);
      }
      virtual void Update2() {  // VelocitySQ
        assert(this->_V.IsValid());
        assert(this->_param.IsValid());
        _PtrValue_(VelocitySQ)=0;
        for(unsigned int i=0;i<this->_V.Size();++i)
          _PtrValue_(VelocitySQ)+=this->_V[i].BlasNormSQ();
      }
      virtual void Update3() {  // KineticEnergy_Simple
        assert(this->_param.IsValid());
        _ValValue_(KineticEnergy)=0.5*_PtrValue_(Mass)*_PtrValue_(VelocitySQ);
      }
      virtual void Evolute1() { // BeforeG
        assert(this->_param.IsValid());
        assert(this->_X.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_X.Size()==this->_G.Size());
        assert(this->_X.Size()==this->_V.Size());
        for(unsigned int i=0;i<this->_X.Size();++i) {
          this->_V[i].BlasShift(this->_G[i],_PtrValue_(NegHTIM));
          this->_X[i].BlasShift(this->_V[i],_SrcValue_(TimeStep));
        }
      }
      virtual void Evolute2() { // AfterG
        assert(this->_param.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_G.Size()==this->_V.Size());
        for(unsigned int i=0;i<this->V.Size();++i)
          this->_V[i].BlasShift(this->_G[i],_PtrValue_(NegHTIM));
      }

    private:

      StepPropagatorVelVerletConstE_UMass(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletConstE_UMass<T>& P) {
    typedef typename StepPropagatorVelVerletConstE_UMass<T>::ParentType
            PType;
    Clear(static_cast<PType&>(P));
  }

}

#ifdef _ValValue_
#undef _ValValue_
#endif

#ifdef _SrcValue_
#undef _SrcValue_
#endif

#ifdef _PtrValue_
#undef _PtrValue_
#endif

#ifdef _Src2Ptr_
#undef _Src2Ptr_
#endif

#endif

