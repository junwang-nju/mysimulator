
#ifndef _Propagator_Minimizer_Interface_H_
#define _Propagator_Minimizer_Interface_H_

#include "propagator/interface.h"

#define _NAME_(U)   PropagatorMin_##U
#define _PARAM_(U)  this->_param[_NAME_(U)]
#define _Pointer_(RT,U)  Pointer<RT>(_PARAM_(U))
#define _ClearPointer_(RT,U)  \
  if(_Pointer_(RT,U)!=NULL) { delete _Pointer_(RT,U); _Pointer_(RT,U)=NULL; }

namespace mysimulator {

  template <typename T,typename GT>
  class PropagatorMinimizer : public Propagator<T,GT> {

    public:

      typedef PropagatorMinimizer<T,GT>   Type;
      typedef Propagator<T,GT>  ParentType;
      template <typename T1,typename GT1>
      friend void Clear(PropagatorMinimizer<T1,GT1>&);

      PropagatorMinimizer() : ParentType(), Proj(0), Move(0), DOF(0) {}
      virtual ~PropagatorMinimizer() { Clear(*this); }

      virtual const T KineticEnergy() const {
        fprintf(stderr,"KineticEnergy Does Not work for Minimizer!\n");
        return 0;
      }
      virtual void UpdateKineticEnergy() {
        fprintf(stderr,"UpdateKineticEnergy Does Not work for Minimizer!\n");
      }

    protected:

      T Proj;
      T Move;
      unsigned int DOF;

      virtual void _ClearParameter() {
        if(!this->_param.IsValid())  return;
        _ClearPointer_(T,Step)
      }
      void _UpdateDOF() {
        assert(this->_props.IsValid());
        DOF=0;
        const unsigned int n=this->_props.Size();
        for(unsigned int i=0;i<n;++i) DOF+=this->_props[i]->DegreeFreedom();
      }

    private:

      PropagatorMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(PropagatorMinimizer<T,GT>& P) {
    P.Proj=0;
    P.Move=0;
    P.DOF=0;
    typedef typename PropagatorMinimizer<T,GT>::ParentType  PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

