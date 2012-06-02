
#ifndef _Propagator_NeighborList_MD_Interface_H_
#define _Propagator_NeighborList_MD_Interface_H_

#include "propagator/molecular-dynamics/interface.h"
#include "propagator/neighbor-list-molecular-dynamics/parameter-name.h"
#include "neighbor-list/interface.h"

#define _NAME_(U)         PropagatorMDWithNL_##U
#define _PARAM_(U)        this->_param[_NAME_(U)]
#define _Pointer_(RT,U)   Pointer<RT>(_PARAM_(U))
#define _LIST_            (*_Pointer_(Array<NeighborList<T,GT> >,ListArray))

namespace mysimulator {

  template <typename T,typename GT>
  class PropagatorMDWithNL : public PropagatorMD<T,GT> {

    public:

      typedef PropagatorMDWithNL<T,GT>    Type;
      typedef PropagatorMD<T,GT>    ParentType;

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
        assert(_Pointer_(Array<NeighborList<T,GT> >,ListArray)!=NULL);
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

#endif

