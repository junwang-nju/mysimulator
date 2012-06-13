
#ifndef _Step_Propagator_VelVerlet_Langevin_AMass_AFric_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_AMass_AFric_Interface_H_

#include "step-propagator/vel-verlet-langevin/array-mass/interface.h"

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletLangevin_AMassAFric
      : public StepPropagatorVelVerletLangevin_AMass<T> {

    public:

      typedef StepPropagatorVelVerletLangevin_AMassAFric<T> Type;
      typedef StepPropagatorVelVerletLangevin_AMass<T>  ParentType;

      StepPropagatorVelVerletLangevin_AMassAFric() : ParentType() {}
      ~StepPropagatorVelVerletLangevin_AMassAFric() { Clear(*this); }

      virtual void Init() {
        static_cast<ParentType*>(this)->Init();
        assert(_SrcArray_(Friction)!=NULL);
        _PtrArray_(Friction)=new AType;
        this->_Introduce(*_PtrArray_(Friction),*_SrcArray_(Friction));
      }
      virtual void Clean() {
        static_cast<ParentType*>(this)->Clean();
        if(_PtrArray_(Friction)!=NULL) {
          Clear(*_PtrArray_(Friction));
          delete _PtrArray_(Friction);
          _PtrArray_(Friction)=NULL;
        }
      }

      virtual void Update5() {
        assert(this->_param.IsValid());
        for(unsigned int i=0;i<(*_PtrArray_(Mass)).Size();++i) {
          (*_PtrArray_(RandSize))[i].BlasCopy((*_PtrArray_(Mass))[i]);
          (*_PtrArray_(RandSize))[i].Inverse();
          (*_PtrArray_(RandSize))[i].BlasScale(_SrcValue_(TimeStep)*
                                               _SrcValue_(Temperature));
          (*_PtrArray_(RandSize))[i].BlasScale((*_PtrArray_(Friction))[i]);
          (*_PtrArray_(RandSize))[i].SqRoot();
        }
      }
      virtual void Update6() {
        assert(this->_param.IsValid());
        for(unsigned int i=0;i<(*_PtrArray_(Mass)).Size();++i) {
          (*_PtrArray_(FacBf))[i].BlasCopy((*_PtrArray_(Mass))[i]);
          (*_PtrArray_(FacBf))[i].Inverse();
          (*_PtrArray_(FacBf))[i].BlasScale(-0.5*_SrcValue_(TimeStep));
          (*_PtrArray_(FacBf))[i].BlasScale((*_PtrArray_(Friction))[i]);
          (*_PtrArray_(FacAf))[i].BlasCopy((*_PtrArray_(FacBf))[i]);
          (*_PtrArray_(FacBf))[i].BlasShift(1);
          (*_PtrArray_(FacAf))[i].BlasScale(-1);
          (*_PtrArray_(FacAf))[i].BlasShift(1);
          (*_PtrArray_(FacAf))[i].Inverse();
        }
      }

    private:

      StepPropagatorVelVerletLangevin_AMassAFric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletLangevin_AMassAFric<T>& P) {
    typedef typename StepPropagatorVelVerletLangevin_AMassAFric<T>::ParentType
            PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

