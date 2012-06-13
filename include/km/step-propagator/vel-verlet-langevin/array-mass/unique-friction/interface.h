
#ifndef _Step_Propagator_VelVerlet_Langevin_AMass_UFric_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_AMass_UFric_Interface_H_

#include "step-propagator/vel-verlet-langevin/array-mass/interface.h"

#ifndef _PtrArray_
#define _PtrArray_(U) \
  Pointer<Array<Array2DNumeric<T> > >(this->_param[VelVerletLangevin_Ptr##U])
#else
#error "Duplicate _PtrArray_"
#endif

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

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletLangevin_AMassUFric
      : public StepPropagatorVelVerletLangevin_AMass<T> {

    public:

      typedef StepPropagatorVelVerletLangevin_AMassUFric<T>   Type;
      typedef StepPropagatorVelVerletLangevin_AMass<T>  ParentType;

      StepPropagatorVelVerletLangevin_AMassUFric() : ParentType() {}
      ~StepPropagatorVelVerletLangevin_AMassUFric() { Clear(*this); }

      virtual void Init() {
        static_cast<ParentType*>(this)->Init();
        _Src2Ptr_(Friction)
      }
      virtual void Clean() {
        static_cast<ParentType*>(this)->Clean();
      }
      virtual void Update5() {  // RandSize
        assert(this->_param.IsValid());
        for(unsigned int i=0;i<(*_PtrArray_(Mass)).Size();++i) {
          (*_PtrArray_(RandSize))[n].BlasCopy((*_PtrArray_(Mass))[i]);
          (*_PtrArray_(RandSize))[n].Inverse();
          (*_PtrArray_(RandSize))[n].BlasScale(
              _SrcValue_(TimeStep)*_SrcValue_(Temperature)*
              _PtrValue_(Friction));
          (*_PtrArray_(RandSize))[n].SqRoot();
        }
      }
      virtual void Update6() {  // Fac
        assert(this->_param.IsValid());
        for(unsigned int i=0;i<(*_PtrArray_(Mass)).Size();++i) {
          (*_PtrArray_(FacBf))[i].BlasCopy((*_PtrArray_(Mass))[i]);
          (*_PtrArray_(FacBf))[i].Inverse();
          (*_PtrArray_(FacBf))[i].BlasScale(
              -0.5*_SrcValue_(TimeStep)*_PtrValue_(Friction));
          (*_PtrArray_(FacAf))[i].BlasCopy((*_PtrArray_(FacBf))[i]);
          (*_PtrArray_(FacBf))[i].BlasShift(1);
          (*_PtrArray_(FacAf))[i].BlasScale(-1);
          (*_PtrArray_(FacAf))[i].BlasShift(1);
          (*_PtrArray_(FacAf))[i].Inverse();
        }
      }

    private:

      StepPropagatorVelVerletLangevin_AMassUFric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletLangevin_AMassUFric<T>& P) {
    typedef typename StepPropagatorVelVerletLangevin_AMassUFric<T>::ParentType
            PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

