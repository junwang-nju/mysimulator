
#ifndef _List_Interaction_H_
#define _List_Interaction_H_

#include "data/interaction/interaction-base.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  struct ListInteraction
    : public InteractionBase<T,DistBuffer,GeomType,
                             Vector<Vector<UniqueParameter> > > {
    typedef ListInteraction<T,DistBuffer,GeomType>    Type;
    typedef InteractionBase<T,DistBuffer,GeomType,
                            Vector<Vector<UniqueParameter> > >
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
                            Vector<Vector<UniqueParameter> > >   IBType;
    return IsAvailable(static_cast<const IBType&>(F));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void release(ListInteraction<T,DistBuffer,GeomType>& F) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            Vector<Vector<UniqueParameter> > >   IBType;
    release(static_cast<IBType&>(F));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void copy(ListInteraction<T,DistBuffer,GeomType>& F,
            const ListInteraction<T,DistBuffer,GeomType>& rF) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            Vector<Vector<UniqueParameter> > >   IBType;
    copy(static_cast<IBType&>(F),static_cast<const IBType&>(rF));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void refer(ListInteraction<T,DistBuffer,GeomType>& F,
             const ListInteraction<T,DistBuffer,GeomType>& rF) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            Vector<Vector<UniqueParameter> > >   IBType;
    refer(static_cast<IBType&>(F),static_cast<const IBType&>(rF));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void allocate(ListInteraction<T,DistBuffer,GeomType>& F,
                const unsigned int iTag,
                const unsigned int dim, const unsigned int nunit,
                const unsigned int nlist) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            Vector<Vector<UniqueParameter> > >   IBType;
    allocate(static_cast<IBType&>(F),iTag,dim,nunit);
    allocate(F.property,4);
    F.Tag()=iTag;
    F.Dimension()=dim;
    F.NumUnit()=nunit;
    F.NumList()=nlist;
    allocate(F.prm,nlist);
    switch(iTag) {
      case Harmonic:
        for(unsigned int i=0;i<nlist;++i)
          allocate(F.prm[i],HarmonicNumberParameter);
        break;
      case LJ612:
        for(unsigned int i=0;i<nlist;++i)
          allocate(F.prm[i],LJ612NumberParameter);
        break;
      case LJ1012:
        for(unsigned int i=0;i<nlist;++i)
          allocate(F.prm[i],LJ1012NumberParameter);
        break;
      case Core12:
        for(unsigned int i=0;i<nlist;++i)
          allocate(F.prm[i],Core12NumberParameter);
        break;
      case CoreLJ612:
        for(unsigned int i=0;i<nlist;++i)
          allocate(F.prm[i],CoreLJ612NumberParameter);
        break;
      case LJ612Cut:
        for(unsigned int i=0;i<nlist;++i)
          allocate(F.prm[i],LJ612CutNumberParameter);
        break;
      case LJ1012Cut:
        for(unsigned int i=0;i<nlist;++i)
          allocate(F.prm[i],LJ1012CutNumberParameter);
        break;
      case Coulomb:
        for(unsigned int i=0;i<nlist;++i)
          allocate(F.prm[i],CoulombNumberParameter);
        break;
      default:
        myError("Unknown interaction type");
    }
  }

}

#endif

