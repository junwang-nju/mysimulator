
#ifndef _Step_Propagator_VelVerlet_Langevin_AMass_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_AMass_Interface_H_

#include "step-propagator/vel-verlet-langevin/interface.h"

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
  class StepPropagatorVelVerletLangevin_AMass
      : public StepPropagatorVelVerletLangevin<T> {

    public:

      typedef StepPropagatorVelVerletLangevin_AMass<T>    Type;
      typedef StepPropagatorVelVerletLangevin<T>  ParentType;
      typedef Array<Array2DNumeric<T> >   AType;

      StepPropagatorVelVerletLangevin_AMass() : ParentType() {}
      ~StepPropagatorVelVerletLangevin_AMass() { Clear(*this); }

      virtual void Init() {
        static_cast<ParentType*>(this)->Init();
        assert(_SrcArray_(Mass)!=NULL);
        _PtrArray_(Mass)=new AType;
        this->_Introduce(*_PtrArray_(Mass),*_SrcArray_(Mass));
        assert(_SrcArray_(NegHTIM)!=NULL);
        _PtrArray_(NegHTIM)=new AType;
        this->_Introduce(*_PtrArray_(NegHTIM),*_SrcArray_(NegHTIM));
        assert(_SrcArray_(VelocitySQ)!=NULL);
        _PtrArray_(VelocitySQ)=new AType;
        this->_Introduce(*_PtrArray_(VelocitySQ),*_SrcArray_(VelocitySQ));
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
          delete _PtrArray_(VelocitySQ);
          _PtrArray_(VelocitySQ)=NULL;
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

      virtual void Evolute1() {
        assert(this->_param.IsValid());
        assert(this->_X.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_X.Size()==this->_G.Size());
        assert(this->_X.Size()==this->_V.Size());
        for(unsigned int i=0;i<this->_X.Size();++i) {
          this->_V[i].BlasScale((*_PtrArray_(FacBf))[i]);
          this->_V[i].BlasShift((*_PtrArray_(NegHTIM))[i],this->_G[i]);
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
          this->_V[i].BlasShift((*_PtrArray_(NegHTIM))[i],this->_G[i]);
          this->_V[i].BlasScale((*_PtrArray_(FacAf))[i]);
        }
      }

    private:

      StepPropagatorVelVerletLangevin_AMass(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletLangevin_AMass<T>& P) {
    typedef typename StepPropagatorVelVerletLangevin_AMass<T>::ParentType
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

