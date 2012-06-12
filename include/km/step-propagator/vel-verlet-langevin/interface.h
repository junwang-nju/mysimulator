
#ifndef _Step_Propagator_VelVerlet_Langevin_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_Interface_H_

#include "step-propagator/interface.h"
#include "step-propagator/vel-verlet-langevin/parameter-name.h"

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

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletLangevin : public StepPropagator<T> {

    public:

      typedef StepPropagatorVelVerletLangevin<T>    Type;
      typedef StepPropagator<T>   ParentType;

      StepPropagatorVelVerletLangevin() : ParentType() {}
      ~StepPropagatorVelVerletLangevin() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=VelVerletLangevin;
        this->_param.Allocate(VelVerletLangevin_NumberParameter);
      }
      virtual void Init() {
        assert(this->_param.IsValid());
        assert(_SrcArray_(RandVector)!=NULL);
        _PtrArray_(RandVector)=new AType;
        this->_Introduce(*_PtrArray_(RandVector),*_SrcArray_(RandVector));
      }
      virtual void Clean() {
        if(_PtrArray_(RandVector)!=NULL) {
          Clear(*_PtrArray_(RandVector));
          delete _PtrArray_(RandVector);
          _PtrArray_(RandVector)=NULL;
        }
      }
      virtual void Update4() {
        this->Update2();
        this->Update3();
      }
      virtual void Evolute3() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Evolute4() { fprintf(stderr,"Not Implemented!\n"); }

    private:

      StepPropagatorVelVerletLangevin(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletLangevin<T>& P) {
    typedef typename StepPropagatorVelVerletLangevin<T>::ParentType PType;
    Clear(static_cast<PType&>(*this));
  }

}

#ifdef _SrcArray_
#undef _SrcArray_
#endif

#ifdef _PtrArray_
#undef _PtrArray_
#endif

#endif

