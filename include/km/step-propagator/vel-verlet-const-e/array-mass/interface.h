
#ifndef _Step_Propagator_VelVerlet_ConstE_ArrayMass_Interface_H_
#define _Step_Propagator_VelVerlet_ConstE_ArrayMass_Interface_H_

#include "step-propagator/vel-verlet-const-e/interface.h"

#ifndef _PtrArray_
#define _PtrArray_(U) \
  Pointer<Array2DNumeric<T> >(this->_param[VelVerletConstE_Ptr##U])
#else
#error "Duplicate _PtrArray_"
#endif

#ifndef _SrcArray_
#define _SrcArray_(U) \
  Pointer<Array2DNumeric<T> >(this->_param[VelVerletConstE_Src##U])
#else
#error "Duplicate _SrcArray_"
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
  class StepPropagatorVelVerletConstE_AMass
      : public StepPropagatorVelVerletConstE<T> {

    public:

      typedef StepPropagatorVelVerletConstE_AMass<T>    Type;
      typedef StepPropagatorVelVerletConstE<T>    ParentType;
      typedef Array<Array2DNumeric<T> >   AType;

      StepPropagatorVelVerletConstE_AMass() : ParentType() {}
      ~StepPropagatorVelVerletConstE_AMass() { Clear(*this); }

      virtual void Init() {
        AType* v;
        v=new AType;
        this->_Introduce(*v,*_SrcArray_(Mass));
        _PtrArray_(Mass)=v;
        v=new AType;
        this->_Introduce(*v,*_SrcArray_(NegHTIM));
        _PtrArray_(NegHTIM)=v;
        if(_SrcArray_(VelocitySQ)!=NULL) {
          v=new AType;
          this->_Introduce(*v,*_SrcArray_(VelocitySQ));
          _PtrArray_(VelocitySQ)=v;
        }
      }
      virtual void Clean() {
        if(_PtrArray_(Mass)!=NULL) {
          Clear(*_PtrArray_(Mass));
          delete _PtrArray_(Mass);
          _PtrArray_(Mass)=NULL;
        }
        if(_PtrArray_(NegHTIM)!=NULL) {
          Clear(*_PtrArray_(NegHTIM));
          delete _PtrArray_(NegHTIM);
          _PtrArray_(NegHTIM)=NULL;
        }
        if(_PtrArray_(VelocitySQ)!=NULL) {
          Clear(*_PtrArray_(VelocitySQ));
          delete *_PtrArray_(VelocitySQ);
          _PtrArray_(VelocitySQ);
        }
      }
      virtual void Update1() {  // HTIM
        assert(this->_param.IsValid());
        T hdt=-0.5*_SrcValue_(TimeStep);
        unsigned int n=_PtrArray_(Mass)->Size();
        for(unsigned int i=0;i<n;++i) {
          (*_PtrArray_(NegHTIM))[i].BlasCopy((*_PtrArray_(Mass))[i]);
          (*_PtrArray_(NegHTIM))[i].Inverse();
          (*_PtrArray_(NegHTIM))[i].BlasScale(hdt);
        }
      }
      virtual void Update2() {  // VelocitySQ
        assert(this->_param.IsValid());
        assert(this->_V.IsValid());
        for(unsigned int i=0;i<this->_V.Size();++i) {
          (*_PtrArray_(VelocitySQ))[i].BlasCopy(this->_V[i]);
          (*_PtrArray_(VelocitySQ))[i].BlasScale(this->_V[i]);
        }
      }
      virtual void Update3() {  // KineticEnergy_Simple
        assert(this->_param.IsValid());
        _ValValue_(KineticEnergy)=0;
        unsigned int n=_PtrArray_(VelocitySQ)->Size();
        for(unsigned int i=0;i<n;++i)
          _ValValue_(KineticEnergy)+=
            BlasDot((*_PtrArray_(Mass))[i],(*_PtrArray_(VelocitySQ))[i]);
        _ValValue_(KineticEnergy)*=0.5;
      }
      virtual void Evolute1() { // BeforeG
        assert(this->_param.IsValid());
        assert(this->_X.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_X.Size()==this->_G.Size());
        assert(this->_X.Size()==this->_V.Size());
        T dt=_SrcValue_(TimeStep);
        for(unsigned int i=0;i<this->_X.Size();++i) {
          this->_V[i].BlasShift(this->_G[i],(*_PtrArray_(NegHTIM))[i]);
          this->_X[i].BlasShift(this->_V[i],dt);
        }
      }
      virtual void Evolute2() { // AfterG
        assert(this->_param.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_G.Size()==this->_V.Size());
        for(unsigned int i=0;i<this->_V.Size();++i)
          this->_V[i].BlasShift(this->_G[i],(*_PtrArray_(NegHTIM))[i]);
      }

    private:

      StepPropagatorVelVerletConstE_AMass(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletConstE_AMass<T>& P) {
    typedef typename StepPropagatorVelVerletConstE_AMass<T>::ParentType
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

#ifdef _SrcArray_
#undef _SrcArray_
#endif

#ifdef _PtrArray_
#undef _PtrArray_
#endif

#endif

