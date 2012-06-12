
#ifndef _Step_Propagator_VelVerlet_Langevin_UMass_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_UMass_Interface_H_

#include "step-propagator/vel-verlet-langevin/interface.h"

#ifndef _Src2Ptr_
#define _Src2Ptr_(U) \
  Pointer<T>(this->_param[VelVerletLangevin_Ptr##U])=\
    Pointer<T>(this->_param[VelVerletLangevin_Src##U]);
#else
#error "Duplicate _Src2Ptr_"
#endif

#ifndef _PtrValue_
#define _PtrValue_(U) \
  (*Pointer<T>(this->_param[VelVerletLangevin_Ptr##U]))
#else
#error "Duplicate _PtrValue_"
#endif

#ifndef _SrcValue_
#define _SrcValue_(U) \
  (*Pointer<T>(this->_param[VelVerletLangevin_Src##U]))
#else
#error "Duplicate _SrcValue_"
#endif

#ifndef _ValValue_
#define _ValValue_(U) \
  (*Pointer<T>(this->_param[VelVerletLangevin_Val##U]))
#else
#error "Duplicate _ValValue_"
#endif

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletLangevin_UMass
      : public StepPropagatorVelVerletLangevin<T> {

    public:

      typedef StepPropagatorVelVerletLangevin_UMass<T>  Type;
      typedef StepPropagatorVelVerletLangevin<T>  ParentType;

      StepPropagatorVelVerletLangevin_UMass() : ParentType() {}
      ~StepPropagatorVelVerletLangevin_UMass() { Clear(*this); }

      virtual void Init() {
        static_cast<ParentType*>(this)->Init();
        _Src2Ptr_(Mass)
        _Src2Ptr_(NegHTIM)
        _Src2Ptr_(VelocitySQ)
      }
      virtual void Clean() {
        static_cast<ParentType*>(this)->Clean();
      }
      virtual void Update1() {  // HTIM
        assert(this->_param.IsValid());
        _PtrValue_(NegHTIM)=-0.5*_SrcValue_(TimeStep)/_PtrValue_(Mass);
      }
      virtual void Update2() {  // VelocitySQ
        assert(this->_param.IsValid());
        assert(this->_V.IsValid());
        _PtrValue_(VelocitySQ)=0;
        for(unsigned int i=0;i<this->_V.Size();++i)
          _PtrValue_(VelocitySQ)+=this->_V[i].BlasNormSQ();
      }
      virtual void Update3() {  // KineticEnergy_Simple
        assert(this->_param.IsValid());
        _ValValue_(KineticEnergy)=0.5*_PtrValue_(Mass)*_PtrValue_(VelocitySQ);
      }

    private:

      StepPropagatorVelVerletLangevin_UMass(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletLangevin_UMass<T>& P) {
    typedef typename StepPropagatorVelVerletLangevin_UMass<T>::ParentType
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

