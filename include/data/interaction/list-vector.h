
#ifndef _Interaction_List_Vector_H_
#define _Interaction_List_Vector_H_

#include "data/interaction/base.h"
#include "data/interaction/unit.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  struct ListVectorInteraction
    : public
      InteractionBase<
        Vector<InteractionUnit<T,Vector<Vector<UniqueParameter> >,
                               DistBuffer,GeomType> >,
        T,DistBuffer,GeomType> {
    typedef ListVectorInteraction<T,DistBuffer,GeomType>  Type;
    typedef InteractionUnit<T,Vector<Vector<UniqueParameter> >,
                            DistBuffer,GeomType>
            IUType;
    typedef InteractionBase<Vector<IUType>,T,DistBuffer,GeomType> ParentType;

    ListVectorInteraction() : ParentType() {}
    ListVectorInteraction(const Type& F) {
      myError("Cannot create list vector interaction");
    }
    Type& operator=(const Type& F) {
      myError("Cannot copy list vector interaction");
      return *this;
    }
  };

  template <typename T,template<typename> class DBuffer,typename GType>
  void allocate(ListVectorInteraction<T,DBuffer,GType>& F,
                const Vector<unsigned int>& tags,
                const unsigned int& dim, const unsigned int& nunit,
                const Vector<unsigned int>& nlsts) {
    typedef typename ListVectorInteraction<T,DBuffer,GType>::IUType
            IUType;
    typedef typename ListVectorInteraction<T,DBuffer,GType>::ParentType
            Parent;
    allocate(static_cast<Parent&>(F),dim,nunit);
    unsigned int n=(tags.size>nlsts.size?nlsts.size:tags.size);
    allocate(static_cast<Vector<IUType>&>(F),n);
    for(unsigned int i=0;i<n;++i) {
      allocateInteractionUnitStatic(F[i],tags[i]);
      allocate(F[i].prm,nlsts[i]);
    }
  }

}

#endif

