
#ifndef _Interaction_Simple_H_
#define _Interaction_Simple_H_

#include "data/interaction/base.h"
#include "data/interaction/unit.h"

namespace std {

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  struct SimpleInteraction
    : public 
      InteractionBase<InteractionUnit<T,DistBuffer,GeomType>,
                      T,DistBuffer,GeomType> {
    typedef SimpleInteraction<T,DistBuffer,GeomType>  Type;
    typedef InteractionUnit<T,DistBuffer,GeomType>  IUType;
    typedef InteractionBase<IUType,T,DistBuffer,GeomType> ParentType;

    SimpleInteraction() : ParentType() {}
    SimpleInteraction(const Type& F) {
      Error("Cannot create simple interaction");
    }
    Type& operator=(const Type& F) {
      Error("Cannot copy simple interaction");
      return *this;
    }
  };

  template <typename T,template<typename> class DBuffer,typename GType>
  void allocate(SimpleInteraction<T,DBuffer,GType>& F,
                const unsigned int& tag,
                const unsigned int& dim, const unsigned int& nunit) {
    typedef InteractionUnit<T,DBuffer,GType>   IUType;
    typedef typename SimpleInteraction<T,DBuffer,GType>::ParentType
            Parent;
    allocate(static_cast<Parent&>(F),dim,nunit);
    allocate(static_cast<IUType&>(F),tag,dim);
  }

}

#endif

