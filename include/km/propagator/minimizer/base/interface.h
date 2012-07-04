
#ifndef _Propagator_Minimizer_Base_Interface_H_
#define _Propagator_Minimizer_Base_Interface_H_

#include "propagator/interface.h"
#include "propagator/minimizer/base/parameter-name.h"

#ifndef _NAME_
#define _NAME_(U)   BaseMin_##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _PARAM_
#define _PARAM_(U)  this->_param[_NAME_(U)]
#else
#error "Duplicate _PARAM_"
#endif

#ifndef _Pointer_
#define _Pointer_(RT,U)  Pointer<RT>(_PARAM_(U))
#else
#error "Duplicate _Pointer_"
#endif

#ifndef _ClearPointer_
#define _ClearPointer_(RT,U)  \
  if(_Pointer_(RT,U)!=NULL) { delete _Pointer_(RT,U); _Pointer_(RT,U)=NULL; }
#else
#error "Duplicate _ClearPointer_"
#endif

namespace mysimulator {

  template <typename T,typename GT>
  class PropagatorBaseMinimizer : public Propagator<T,GT> {

    public:

      typedef PropagatorBaseMinimizer<T,GT>   Type;
      typedef Propagator<T,GT>  ParentType;
      template <typename T1,typename GT1>
      friend void Clear(PropagatorBaseMinimizer<T1,GT1>&);

      PropagatorBaseMinimizer() : ParentType(), Proj(0), Move(0), DOF(0) {}
      virtual ~PropagatorBaseMinimizer() { Clear(*this); }

      virtual const T KineticEnergy() const {
        fprintf(stderr,"KineticEnergy Does Not work for Minimizer!\n");
        return 0;
      }
      virtual void UpdateKineticEnergy() {
        fprintf(stderr,"UpdateKineticEnergy Does Not work for Minimizer!\n");
      }

      virtual void IntroduceSystem(System<T,GT>& S) {
        ParentType::IntroduceSystem(S);
        _UpdateDOF();
      }

    protected:

      T Proj;
      T Move;
      unsigned int DOF;

      virtual void _ClearParameter() {
        if(!this->_param.IsValid())  return;
        _ClearPointer_(T,Step)
      }

    private:

      void _UpdateDOF() {
        assert(this->_props.IsValid());
        DOF=0;
        const unsigned int n=this->_props.Size();
        for(unsigned int i=0;i<n;++i) DOF+=this->_props[i]->DegreeFreedom();
      }

      PropagatorBaseMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(PropagatorBaseMinimizer<T,GT>& P) {
    P.Proj=0;
    P.Move=0;
    P.DOF=0;
    typedef typename PropagatorBaseMinimizer<T,GT>::ParentType  PType;
    Clear(static_cast<PType&>(P));
  }

}

#ifdef _ClearPointer_
#undef _ClearPointer_
#endif

#ifdef _Pointer_
#undef _Pointer_
#endif

#ifdef _PARAM_
#undef _PARAM_
#endif

#ifdef _NAME_
#undef _NAME_
#endif

#endif

