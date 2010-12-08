
#ifndef _Interaction_List_H_
#define _Interaction_List_H_

#include "data/interaction/base.h"
#include "data/interaction/unit.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  struct ListInteraction
    : public
      InteractionBase<Vector<InteractionUnit<T,DistBuffer,GeomType> >,
                      T,DistBuffer,GeomType> {
    typedef ListInteraction<T,DistBuffer,GeomType>  Type;
    typedef InteractionUnit<T,DistBuffer,GeomType>  IUType;
    typedef InteractionBase<Vector<IUType>,T,DistBuffer,GeomType> ParentType;

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
  void copy(ListInteraction<T,DBuffer,GType>& F,
            const ListInteraction<T,DBuffer,GType>& cF) {
    typedef typename ListInteraction<T,DBuffer,GType>::ParentType
            Parent;
    copy(static_cast<Parent&>(F),static_cast<const Parent&>(cF));
  }

  template <typename T,template<typename> class DBuffer,typename GType>
  void allocate(ListInteraction<T,DBuffer,GType>& F,
                const Vector<unsigned int>& tags,
                const unsigned int& dim, const unsigned int& nunit) {
    typedef typename ListInteraction<T,DBuffer,GType>::IUType
            IUType;
    typedef typename ListInteraction<T,DBuffer,GType>::ParentType
            Parent;
    allocate(static_cast<Parent&>(F),dim,nunit);
    allocate(static_cast<Vector<IUType>&>(F),tags.size);
    for(unsigned int i=0;i<tags.size;++i) allocate(F[i],tags[i]);
  }

}

#endif

