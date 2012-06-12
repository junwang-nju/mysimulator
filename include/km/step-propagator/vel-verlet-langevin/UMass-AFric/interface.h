
#ifndef _Step_Propagator_VelVerlet_Langevin_UMassAFric_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_UMassAFric_Interface_H_

#include "step-propagator/vel-verlet-langevin/interface.h"

#ifndef _Src2Ptr_
#define _Src2Ptr_(U) \
  Pointer<T>(this->_param[VelVerletLangevin_Ptr##U])=\
    Pointer<T>(this->_param[VelVerletLangevin_Src##U]);
#else
#error "Duplicate _Src2Ptr_"
#endif

#ifndef _PtrArray_
#define _PtrArray_(U) \
  Pointer<Array<Array2DNumeric<T> > >(this->_param[VelVerletLangevin_Ptr##U])
#else
#error "Duplicate _PtrArray_"
#endif

#ifndef _SrcArray_
#define _SrcArray_(U) \
  Pointer<Array<Array2DNumeric<T> > >(this->_param[VelVerletLangevin_Src##U])
#else
#error "Duplicate _SrcArray_"
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
  class StepPropagatorVelVerletLangevin_UMassAFric
      : public StepPropagatorVelVerletLangevin<T> {

    public:

      typedef StepPropagatorVelVerletLangevin_UMassAFric<T> Type;
      typedef StepPropagatorVelVerletLangevin<T>  ParentType;
      typedef Array<Array2DNumeric<T> > AType;

      StepPropagatorVelVerletLangevin_UMassAFric() : ParentType() {}
      ~StepPropagatorVelVerletLangevin() { Clear(*this); }

      virtual void Init() {
        _Src2Ptr_(Mass)
        _Src2Ptr_(NegHTIM)
        _Src2Ptr_(VelocitySQ)
        assert(_SrcArray_(Friction)!=NULL);
        _PtrArray_(Friction)=new AType;
        this->_Introduce(*_PtrArray_(Friction),*_SrcArray_(Friction));
        assert(_SrcArray_(RandVector)!=NULL);
        _PtrArray_(RandVector)=new AType;
        this->_Introduce(*_PtrArray_(RandVector),*_SrcArray_(RandVector));
        assert(_SrcArray_(RandSize)!=NULL);
        _PtrArray_(RandSize)=new AType;
        this->_Introduce(*_PtrArray_(RandSize),*_SrcArray_(RandSize));
        assert(_SrcArray_(FacBf)!=NULL);
        _PtrArray_(FacBf)=new AType;
        this->_Introduce(*_PtrArray_(FacBf),*_SrcArray_(FacBf));
        assert(_SrcArray_(FacAf)!=NULL);
        _PtrArray_(FacAf)=new AType;
        this->_Introduce(*_PtrArray_(FacAf),*_SrcArray_(FacAf));
      }
      virtual void Clean() {
        if(_PtrArray_(Friction)!=NULL) {
          Clear(*_PtrArray_(Friction));
          delete _PtrArray_(Friction);
          _PtrArray_(Friction)=NULL;
        }
        if(_PtrArray_(RandVector)!=NULL) {
          Clear(*_PtrArray_(RandVector));
          delete _PtrArray_(RandVector);
          _PtrArray_(RandVector)=NULL;
        }
        if(_PtrArray_(RandSize)!=NULL) {
          Clear(*_PtrArray_(RandSize));
          delete _PtrArray_(RandSize);
          _PtrArray_(RandSize)=NULL;
        }
        if(_PtrArray_(FacBf)!=NULL) {
          Clear(*_PtrArray_(FacBf));
          delete _PtrArray_(FacBf);
          _PtrArray_(FacBf)=NULL;
        }
        if(_PtrArray_(FacAf)!=NULL) {
          Clear(*_PtrArray_(FacAf));
          delete _PtrArray_(FacAf);
          _PtrArray_(FacAf)=NULL;
        }
      }

    private:

      StepPropagatorVelVerletLangevin_UMassAFric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletLangevin_UMassAFric<T>& P) {
    typedef typename StepPropagatorVelVerletLangevin_UMassAFric<T>::ParentType
            PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

