
#ifndef _Interaction_H_
#define _Interaction_H_

#include "data/basic/vector.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename InteractionUnitSet, typename T,
            template<typename> class DistBuffer, typename GeomType>
  struct Interaction : public InteractionUnitSet {
    typedef Interaction<InteractionUnitSet> Type;
    typedef InteractionUnitSet  ParentType;

    Vector<unsigned int> property;
    DistBuffer<T> B;
    GeomType  Geo;

    Interaction() : ParentType(), property(), B(), Geo() {}
    Interaction(const Type& F) {
      myError("Cannot create Interaction");
    }
    Type& operator=(const Type& F) {
      myError("Cannot copy Interaction");
      return *this;
    }
    ~Interaction() { release(*this); }

    unsigned int& Dimension() { return property[0]; }
    unsigned int& NumMerUnit() { return property[1]; }
    unsigned int& NumInteractionUnit() { return property[2]; }
    const unsigned int& Dimension() const { return property[0]; }
    const unsigned int& NumMerUnit() const { return property[1]; }
    const unsigned int& NumInteractionUnit() const { return property[2]; }

  };

  template <typename IUSet,typename T,
            template<typename> class DBuff, typename GType>
  bool IsAvailable(const Interaction<IUSet,T,DBuff,GType>& F) {
    return IsAvailable(static_cast<const IUSet&>(F))&&IsAvailable(F.property)&&
           IsAvailable(F.B)&&IsAvailable(F.Geo);
  }

  template <typename IUSet,typename T,
            template<typename> class DBuff, typename GType>
  void release(Interaction<IUSet,T,DBuff,GType>& F) {
    release(F.property);
    release(F.B);
    release(F.Geo);
    release(static_cast<IUSet&>(F));
  }

  template <typename IUSet,typename T,
            template<typename> class DBuff, typename GType>
  void copy(Interaction<IUSet,T,DBuff,GType>& F,
            const Interaction<IUset,T,DBuff,GType>& cF) {
    assert(IsAvailable(F));
    assert(IsAvailable(cF));
    copy(F.property,cF.property);
    copy(F.B,cF.B);
    copy(F.Geo,cF.Geo);
    copy(static_cast<IUSet&>(F),static_cast<const IUSet&>(cF));
  }

  template <typename IUSet,typename T,
            template<typename> class DBuff, typename GType>
  void refer(Interaction<IUSet,T,DBuff,Geo>& F,
             const Interaction<IUSet,T,DBuff,Geo>& rF) {
    assert(IsAvailable(rF));
    release(F);
    refer(F.property,rF.property);
    refer(F.B,rF.B);
    refer(F.Geo,rF.Geo);
    refer(static_cast<IUSet&>(F),static_cast<const IUSet&>(rF));
  }

  template <typename IUSet,typename T,
            template<typename> class DBuff, typename GType>
  void allocate(Interaction<IUSet,T,DBuff,GType>& F,
                const unsigned int dim, const unsigned int nunit) {
    release(F);
    allocate(F.property,3);
    F.Dimension()=dim;
    F.NumMerUnit()=nunit;
    allocate(F.B,dim,nunit);
    allocate(F.Geo,dim);
  }

}

#endif

