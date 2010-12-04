
#ifndef _Interaction_Simple_H_
#define _Interaction_Simple_H_

#include "data/interaction/base.h"
#include "data/interaction/unit.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  struct SimpleInteraction
    : public 
      InteractionBase<
        InteractionUnit<T,Vector<UniqueParameter>,DistBuffer,GeomType>,
        T,DistBuffer,GeomType> {
    typedef SimpleInteraction<T,DistBuffer,GeomType>  Type;
    typedef InteractionUnit<T,Vector<UniqueParameter>,DistBuffer,GeomType>
            IUType;
    typedef InteractionBase<IUType,T,DistBuffer,GeomType> ParentType;

    SimpleInteraction() : ParentType() {}
    SimpleInteraction(const Type& F) {
      myError("Cannot create simple interaction");
    }
    Type& operator=(const Type& F) {
      myError("Cannot copy simple interaction");
      return *this;
    }
  };

  template <typename T,template<typename> class DBuffer,typename GType>
  void allocate(SimpleInteraction<T,DBuffer,GType>& F,
                const unsigned int& tag,
                const unsigned int& dim, const unsigned int& nunit) {
    typedef typename SimpleInteraction<T,DBuffer,GType>::IUType
            IUType;
    typedef typename SimpleInteraction<T,DBuffer,GType>::ParentType
            Parent;
    allocate(static_cast<Parent&>(F),dim,nunit);
    allocateInteractionUnitStatic(static_cast<IUType&>(F),tag);
  }

}

#endif

