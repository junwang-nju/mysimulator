
#ifndef _List_Interaction_H_
#define _List_Interaction_H_

#include "data/interaction/interaction-base.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  struct ListInteraction
    : public InteractionBase<T,DistBuffer,GeomType,
                             PropertyList<UniqueParameter> > {
    typedef ListInteraction<T,DistBuffer,GeomType>    Type;
    typedef InteractionBase<T,DistBuffer,GeomType,
                            PropertyList<UniqueParameter> >
            ParentType;

    ListInteraction() : ParentType() {}
    ListInteraction(const Type& F) {
      myError("Cannot create List Interaction");
    }
    Type& operator=(const Type& F) {
      myError("Cannot copy List Interaction");
      return *this;
    }
    ~ListInteraction() { release(*this); }

    unsigned int& NumList() { return this->property[3]; }
    const unsigned int& NumList() const { return this->property[3]; }

  };

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  bool IsAvailable(const ListInteraction<T,DistBuffer,GeomType>& F) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            PropertyList<UniqueParameter> >   IBType;
    return IsAvailable(static_cast<const IBType&>(F));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void release(ListInteraction<T,DistBuffer,GeomType>& F) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            PropertyList<UniqueParameter> >   IBType;
    release(static_cast<IBType&>(F));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void copy(ListInteraction<T,DistBuffer,GeomType>& F,
            const ListInteraction<T,DistBuffer,GeomType>& rF) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            PropertyList<UniqueParameter> >   IBType;
    copy(static_cast<IBType&>(F),static_cast<const IBType&>(rF));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void refer(ListInteraction<T,DistBuffer,GeomType>& F,
             const ListInteraction<T,DistBuffer,GeomType>& rF) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            PropertyList<UniqueParameter> >   IBType;
    refer(static_cast<IBType&>(F),static_cast<const IBType&>(rF));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void allocate(ListInteraction<T,DistBuffer,GeomType>& F,
                const unsigned int iTag,
                const unsigned int dim, const unsigned int nunit,
                const unsigned int nlist) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            PropertyList<UniqueParameter> >   IBType;
    allocate(static_cast<IBType&>(F),iTag,dim,nunit);
    allocate(F.property,4);
    F.Tag()=iTag;
    F.Dimension()=dim;
    F.NumUnit()=nunit;
    F.NumList()=nlist;
    Vector<unsigned int> sz;
    allocate(sz,nlist);
    switch(iTag) {
      case Harmonic:
        copy(sz,HarmonicNumberParameter);
        allocate(F.prm,sz);
        break;
      case LJ612:
        copy(sz,LJ612NumberParameter);
        allocate(F.prm,sz);
        break;
      case LJ1012:
        copy(sz,LJ1012NumberParameter);
        allocate(F.prm,sz);
        break;
      case Core12:
        copy(sz,Core12NumberParameter);
        allocate(F.prm,sz);
        break;
      case CoreLJ612:
        copy(sz,CoreLJ612NumberParameter);
        allocate(F.prm,sz);
        break;
      case LJ612Cut:
        copy(sz,LJ612CutNumberParameter);
        allocate(F.prm,sz);
        break;
      case LJ1012Cut:
        copy(sz,LJ1012CutNumberParameter);
        allocate(F.prm,sz);
        break;
      case Coulomb:
        copy(sz,CoulombNumberParameter);
        allocate(F.prm,sz);
        break;
      default:
        myError("Unknown interaction type");
    }
  }

}

#endif

