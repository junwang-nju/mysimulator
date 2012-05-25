
#ifndef _Step_Propagator_VelVerlet_Langevin_UMass_AFric_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_UMass_AFric_Interface_H_

#include "step-propagator/vel-verlet-langevin/unique-mass/interface.h"

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
  class StepPropagatorVelVerletLangevin_UMassAFric
      : public StepPropagatorVelVerletLangevin_UMass<T> {

    public:

      typedef StepPropagatorVelVerletLangevin_UMassAFric<T> Type;
      typedef StepPropagatorVelVerletLangevin_UMass<T>  ParentType;
      typedef Array<Array2DNumeric<T> >   AType;

      StepPropagatorVelVerletLangevin_UMassAFric() : ParentType() {}
      ~StepPropagatorVelVerletLangevin_UMassAFric() { Clear(*this); }

      virtual void Init() {
        static_cast<ParentType*>(this)->Init();
        assert(_SrcArray_(Friction)!=NULL);
        _PtrArray_(Friction)=new AType;
        this->_Introduce(*_PtrArray_(Friction),*_SrcArray_(Friction));
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
        static_cast<ParentType*>(this)->Clean();
        if(_PtrArray_(Friction)!=NULL) {
          Clear(*_PtrArray_(Friction));
          delete _PtrArray_(Friction);
          _PtrArray_(Friction)=NULL;
        }
        if(_PtrArray_(RandSize)!=NULL) {
          Clear(*_PtrArray_(RandSize));
          delete _PtrArray_(RandSize);
          _PtrArray_(RandSize)=NULL;
        }
        if(_PtrArray_(FacBf)!=NULL) {
          Clear(*_PtrArray_(FacBf));
          delete _PtrArray_(FacBf);
          _PtrArray_(FacBf);
        }
        if(_PtrArray_(FacAf)!=NULL) {
          Clear(*_PtrArray_(FacAf));
          delete _PtrArray_(FacAf);
          _PtrArray_(FacAf)=NULL;
        }
      }

      virtual void Update5() {  // RandSize
        assert(this->_param.IsValid());
        for(unsigned int i=0;i<(*_PtrArray_(Friction)).Size();++i) {
          (*_PtrArray_(RandSize))[i].BlasCopy((*_PtrArray_(Friction))[i]);
          (*_PtrArray_(RandSize))[i].BlasScale(
              _SrcValue_(TimeStep)*_SrcValue_(Temperature)*_PtrValue_(Mass));
          (*_PtrArray_(RandSize))[i].SqRoot();
        }
      }
      virtual void Update6() {  // Fac
        assert(this->_param.IsValid());
        for(unsigned int i=0;i<(*_PtrArray_(Friction)).Size();++i) {
          (*_PtrArray_(FacBf))[i].BlasCopy((*_PtrArray_(Friction))[i]);
          // must be used after Update1
          (*_PtrArray_(FacBf))[i].BlasScale(_PtrValue_(NegHTIM));
          (*_PtrArray_(FacAf))[i].BlasCopy((*_PtrArray_(FacBf))[i]);
          (*_PtrArray_(FacBf))[i].BlasShift(1);
          (*_PtrArray_(FacAf))[i].BlasScale(-1);
          (*_PtrArray_(FacAf))[i].BlasShift(1);
          (*_PtrArray_(FacAf))[i].Inverse();
        }
      }

      virtual void Evolute1() {
        assert(this->_param.IsValid());
        assert(this->_X.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_X.Size()==this->_G.Size());
        assert(this->_X.Size()==this->_V.Size());
        for(unsigned int i=0;i<this->_X.Size();++i) {
          this->_V[i].BlasScale((*_PtrArray_(FacBf))[i]);
          this->_V[i].BlasShift(_PtrValue_(NegHTIM),this->_G[i]);
          this->_V[i].BlasShift((*_PtrArray_(RandSize))[i],
                                (*_PtrArray_(RandVector))[i]);
          this->_X[i].BlasShift(_SrcValue_(TimeStep),this->_V[i]);
        }
      }
      virtual void Evolute2() {
        assert(this->_param.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_G.Size()==this->_V.Size());
        for(unsigned int i=0;i<this->_V.Size();++i) {
          this->_V[i].BlasShift((*_PtrArray_(RandSize))[i],
                                (*_PtrArray_(RandVector))[i]);
          this->_V[i].BlasShift(_PtrValue_(NegHTIM),this->_G[i]);
          this->_V[i].BlasScale((*_PtrArray_(FacAf))[i]);
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

#ifdef _SrcArray_
#undef _SrcArray_
#endif

#ifdef _PtrArray_
#undef _PtrArray_
#endif

#endif

