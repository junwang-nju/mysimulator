
#ifndef _Interaction_List_H_
#define _Interaction_List_H_

#include "data/interaction/base.h"
#include "data/interaction/unit.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  struct ListInteraction
    : public
      InteractionBase<
      InteractionUnit<T,Vector<Vector<UniqueParameter> >,DistBuffer,GeomType>,
      T,DistBuffer,GeomType> {
    typedef ListInteraction<T,DistBuffer,GeomType>  Type;
    typedef InteractionUnit<T,Vector<Vector<UniqueParameter> >,
                            DistBuffer,GeomType>
            IUType;
    typedef InteractionBase<IUType,T,DistBuffer,GeomType> ParentType;

    ListInteraction() : ParentType() {}
    ListInteraction(const Type& F) {
      myError("Cannot create list interaciton");
    }
    Type& operator=(const Type& F) {
      myError("Cannot copy list interaction");
      return *this;
    }
  };

  template <typename T,template<typename> class DBuffer,typename GType>
  void allocate(ListInteraction<T,DBuffer,GType>& F,
                const unsigned int& tag,
                const unsigned int& dim, const unsigned int& nunit,
                const unsigned int& nlst) {
    typedef typename ListInteraction<T,DBuffer,GType>::IUType
            IUType;
    typedef typename ListInteraction<T,DBuffer,GType>::ParentType
            Parent;
    allocate(static_cast<Parent&>(F),dim,nunit);
    allocateInteractionUnitStatic(static_cast<IUType&>(F),tag);
    allocate(F.prm,nlst);
  }

}

#endif

