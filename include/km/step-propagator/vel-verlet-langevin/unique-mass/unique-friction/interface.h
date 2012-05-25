
#ifndef _Step_Propagator_VelVerlet_Langevin_UMass_UFric_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_UMass_UFric_Interface_H_

#include "step-propagator/vel-verlet-langevin/unique-mass/interface.h"

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

#ifndef _PtrArray_
#define _PtrArray_(U) \
  Pointer<Array<Array2DNumeric<T> > >(this->_param[VelVerletLangevin_Ptr##U])
#else
#error "Duplicate _PtrArray_"
#endif

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletLangevin_UMassUFric
      : public StepPropagatorVelVerletLangevin_UMass<T> {

    public:

      typedef StepPropagatorVelVerletLangevin_UMassUFric<T> Type;
      typedef StepPropagatorVelVerletLangevin_UMass<T>  ParentType;

      StepPropagatorVelVerletLangevin_UMassUFric() : ParentType() {}
      ~StepPropagatorVelVerletLangevin_UMassUFric() { Clear(*this); }

      virtual void Init() {
        static_cast<ParentType*>(this)->Init();
        _Src2Ptr_(Friction)
        _Src2Ptr_(RandSize)
        _Src2Ptr_(FacBf)
        _Src2Ptr_(FacAf)
      }
      virtual void Clean() {
        static_cast<ParentType*>(this)->Clean();
      }
      virtual void Update5() {  // RandSize
        assert(this->_param.IsValid());
        _PtrValue_(RandSize)=
          __SqRoot(_SrcValue_(TimeStep)*_SrcValue_(Temperature)*
                   _PtrValue_(Friction)/_PtrValue_(Mass));
      }
      virtual void Update6() {  // Fac
        assert(this->_param.IsValid());
        // must be used after Update1
        T d=-_PtrValue_(NegHTIM)*_PtrValue_(Friction);
        _PtrValue_(FacBf)=1-d;
        _PtrValue_(FacAf)=1./(1.+d);
      }

      virtual void Evolute1() {
        assert(this->_param.IsValid());
        assert(this->_X.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_X.Size()==this->_G.Size());
        assert(this->_X.Size()==this->_V.Size());
        for(unsigned int i=0;i<this->_X.Size();++i) {
          this->_V[i].BlasScale(_PtrValue_(FacBf));
          this->_V[i].BlasShift(_PtrValue_(NegHTIM),this->_G[i]);
          this->_V[i].BlasShift(_PtrValue_(RandSize),
                                (*_PtrArray_(RandVector))[i]);
          this->_X[i].BlasShift(_SrcValue_(TimeStep),this->_V[i]);
        }
      }
      virtual void Evolute2() {
        assert(this->_param.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_V.Size()==this->_G.Size());
        for(unsigned int i=0;i<this->_V.Size();++i) {
          this->_V[i].BlasShift(_PtrValue_(RandSize),
                                (*_PtrArray_(RandVector))[i]);
          this->_V[i].BlasShift(_PtrValue_(NegHTIM),this->_G[i]);
          this->_V[i].BlasScale(_PtrValue_(FacAf));
        }
      }

    private:

      StepPropagatorVelVerletLangevin_UMassUFric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletLangevin_UMassUFric<T>& P) {
    typedef typename StepPropagatorVelVerletLangevin_UMassUFric<T>::ParentType
            PType;
    Clear(static_cast<PType&>(P));
  }

}

#ifdef _PtrArray_
#undef _PtrArray_
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

