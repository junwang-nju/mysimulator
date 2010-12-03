
#ifndef _Interaction_H_
#define _Interaction_H_

#include "data/interaction/interaction-base.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  struct Interaction
    : public InteractionBase<T,DistBuffer,GeomType,Vector<UniqueParameter> > {
    typedef Interaction<T,DistBuffer,GeomType>    Type;
    typedef InteractionBase<T,DistBuffer,GeomType,Vector<UniqueParameter> >
            ParentType;

    Interaction() : ParentType() {}
    Interaction(const Type& F) { myError("Cannot create Interaction"); }
    Type& operator=(const Type& F) {
      myError("Cannot copy Interaction");
      return *this;
    }
    ~Interaction() { release(*this); }

  };

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  bool IsAvailable(const Interaction<T,DistBuffer,GeomType>& F) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            Vector<UniqueParameter> >   IBType;
    return IsAvailable(static_cast<const IBType&>(F));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void release(Interaction<T,DistBuffer,GeomType>& F) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            Vector<UniqueParameter> >   IBType;
    release(static_cast<IBType&>(F));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void copy(Interaction<T,DistBuffer,GeomType>& F,
            const Interaction<T,DistBuffer,GeomType>& rF) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            Vector<UniqueParameter> >   IBType;
    copy(static_cast<IBType&>(F),static_cast<const IBType&>(rF));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void refer(Interaction<T,DistBuffer,GeomType>& F,
             const Interaction<T,DistBuffer,GeomType>& rF) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            Vector<UniqueParameter> >   IBType;
    refer(static_cast<IBType&>(F),static_cast<const IBType&>(rF));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void allocate(Interaction<T,DistBuffer,GeomType>& F,
                const unsigned int iTag,
                const unsigned int dim, const unsigned int nunit) {
    typedef InteractionBase<T,DistBuffer,GeomType,
                            Vector<UniqueParameter> >   IBType;
    allocate(static_cast<IBType&>(F),iTag,dim,nunit);
    switch(iTag) {
      case Harmonic:
        allocate(F.prm,HarmonicNumberParameter);
        break;
      case LJ612:
        allocate(F.prm,LJ612NumberParameter);
        break;
      case LJ1012:
        allocate(F.prm,LJ1012NumberParameter);
        break;
      case Core12:
        allocate(F.prm,Core12NumberParameter);
        break;
      case CoreLJ612:
        allocate(F.prm,CoreLJ612NumberParameter);
        break;
      case LJ612Cut:
        allocate(F.prm,LJ612CutNumberParameter);
        break;
      case LJ1012Cut:
        allocate(F.prm,LJ1012CutNumberParameter);
        break;
      case Coulomb:
        allocate(F.prm,CoulombNumberParameter);
        break;
      default:
        myError("Unknown interaction type");
    }
  }

}

#endif

