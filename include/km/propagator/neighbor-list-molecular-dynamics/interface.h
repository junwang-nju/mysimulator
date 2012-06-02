
#ifndef _Propagator_NeighborList_MD_Interface_H_
#define _Propagator_NeighborList_MD_Interface_H_

#include "propagator/molecular-dynamics/interface.h"
#include "propagator/neighbor-list-molecular-dynamics/parameter-name.h"
#include "neighbor-list/interface.h"

#ifndef _NAME_
#define _NAME_(U)         PropagatorMDWithNL_##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _PARAM_
#define _PARAM_(U)        this->_param[_NAME_(U)]
#else
#error "Duplicate _PARAM_"
#endif

#ifndef _Pointer_
#define _Pointer_(RT,U)   Pointer<RT>(_PARAM_(U))
#else
#error "Duplicate _Pointer_"
#endif

#ifndef _LIST_
#define _LIST_            (*_Pointer_(NLArrayType,ListArray))
#else
#error "Duplicate _LIST_"
#endif

namespace mysimulator {

  template <typename T,typename GT>
  class PropagatorMDWithNL : public PropagatorMD<T,GT> {

    public:

      typedef PropagatorMDWithNL<T,GT>    Type;
      typedef PropagatorMD<T,GT>    ParentType;
      typedef Array<NeighborList<T,GT> >  NLArrayType;

      PropagatorMDWithNL() : ParentType() {}
      virtual ~PropagatorMDWithNL() { Clear(*this); }

      virtual bool IsValid() const { return ParentType::IsValid(); }

      virtual void AllocateParameter() {
        this->_param.Allocate(PropagatorMDWithNL_NumberParameter);
      }

      virtual void StepEvolute(System<T,GT>& S) {
        for(unsigned int i=0;i<_LIST_.Size();++i) _LIST_[i].Update(S.Location());
        ParentType::StepEvolute(S);
      }
      virtual void IntroduceSystem(System<T,GT>& S) {
        ParentType::IntroduceSystem(S);
        assert(_Pointer_(NLArrayType,ListArray)!=NULL);
        for(unsigned int i=0;i<_LIST_.Size();++i)
          _LIST_[i].ImprintX(S.Location());
      }

    private:

      PropagatorMDWithNL(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(PropagatorMDWithNL<T,GT>& P) {
    typedef typename PropagatorMDWithNL<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#ifdef _LIST_
#undef _LIST_
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

