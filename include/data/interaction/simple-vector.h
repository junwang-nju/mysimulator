
#ifndef _Interaction_Simple_Vector_H_
#define _Interaction_Simple_Vector_H_

#include "data/interaction/base.h"
#include "data/interaction/unit.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  struct SimpleVectorInteraction
    : public
      InteractionBase<
        Vector<InteractionUnit<T,Vector<UniqueParameter>,DistBuffer,GeomType> >,
        T,DistBuffer,GeomType> {
    typedef SimpleVectorInteraction<T,DistBuffer,GeomType>  Type;
    typedef InteractionUnit<T,Vector<UniqueParameter>,DistBuffer,GeomType>
            IUType;
    typedef InteractionBase<Vector<IUType>,T,DistBuffer,GeomType>
            ParentType;

    SimpleVectorInteraction() : ParentType() {}
    SimpleVectorInteraction(const Type& F) {
      myError("Cannot create simple vector interaction");
    }
    Type& operator=(const Type& F) {
      myError("Cannot copy simple vector interaction");
      return *this;
    }
  };

  template <typename T,template<typename> class DBuffer,typename GType>
  void allocate(SimpleVectorInteraction<T,DBuffer,GType>& F,
                const Vector<unsigned int>& tags,
                const unsigned int& dim, const unsigned int& nunit) {
    typedef typename SimpleVectorInteraction<T,DBuffer,GType>::IUType
            IUType;
    typedef typename SimpleVectorInteraction<T,DBuffer,GType>::ParentType
            Parent;
    allocate(static_cast<Parent&>(F),dim,nunit);
    allocate(static_cast<Vector<IUType>&>(F),tags.size);
    for(unsigned int i=0;i<tags.size;++i)
      allocateInteractionUnitStatic(F[i],tags[i]);
  }

}

#endif

