
#ifndef _Interaction_Unit_H_
#define _Interaction_Unit_H_

#include "data/basic/property-list.h"

namespace std {

  template <typename T,
            template<typename> class DistBuffer,typename GeomType>
  struct InteractionUnit {
    unsigned int *pTag;
    PropertyList<T> tmvec;
    void (*EFunc)(const Vector<T>*,const unsigned int*,const UniqueParameter*,
                  DistBuffer<T>&,const GeomType&,T&,
                  Vector<T>*,const unsigned int);
    void (*GFunc)(const Vector<T>*,const unsigned int*,const UniqueParameter*,
                  DistBuffer<T>&,const GeomType&,Vector<T>*,
                  Vector<T>*,const unsigned int);
    void (*BFunc)(const Vector<T>*,const unsigned int*,const UniqueParameter*,
                  DistBuffer<T>&,const GeomType&,T&,Vector<T>*,
                  Vector<T>*,const unsigned int);

    typedef InteractionUnit<T,DistBuffer,GeomType>  Type;

    InteractionUnit()
      : pTag(NULL), tmvec(), EFunc(NULL), GFunc(NULL), BFunc() {}
    InteractionUnit(const Type& U) {
      myError("Cannot create Interaction Unit");
    }
    Type& operator=(const Type& U) {
      myError("Cannot copy Interaction Unit");
      return *this;
    }
    ~InteractionUnit() { release(*this); }

    unsigned int& iTag() { assert(pTag); return *pTag; }
    const unsigned int& iTag() const { assert(pTag!=NULL); return *pTag; }
  };

  template <typename T,template<typename> class DBuff,typename GType>
  bool IsAvailable(const InteractionUnit<T,DBuff,GType>& U) {
    return IsAvailable(U.EFunc)&&IsAvailable(U.GFunc)&&
           IsAvailable(U.BFunc)&&IsAvailable(U.pTag);
  }

  template <typename T,template<typename> class DBuff,typename GType>
  void release(InteractionUnit<T,DBuff,GType>& U) {
    safe_delete(U.pTag);
    release(U.tmvec);
    U.EFunc=NULL;
    U.GFunc=NULL;
    U.BFunc=NULL;
  }

  template <typename T,template<typename> class DBuff,typename GType>
  void copy(InteractionUnit<T,DBuff,GType>& U,
            const InteractionUnit<T,DBuff,GType>& cU) {
    assert(IsAvailable(U));
    assert(IsAvailable(cU));
    assert(U.iTag()==cU.iTag());
  }

  template <typename T,template<typename> class DBuff,typename GType>
  void refer(InteractionUnit<T,DBuff,GType>& U,
             const InteractionUnit<T,DBuff,GType>& rU) {
    assert(IsAvailable(rU));
    release(U);
    U.pTag=rU.pTag;
    if(IsAvailable(rU.tmvec)) refer(U.tmvec,rU.tmvec);
  }

}

#include "data/name/all-interaction.h"
#include "operation/interaction/all.h"

namespace std {

  template <typename T, template<typename> class DBuff,typename GType>
  void allocate(InteractionUnit<T,DBuff,GType>& F, const unsigned int& tag) {
    F.pTag=new unsigned int;
    F.iTag()=tag;
    switch(tag) {
      case Harmonic:
        F.EFunc=EFuncHarmonic<T,DBuff,GType>;
        F.GFunc=GFuncHarmonic<T,DBuff,GType>;
        F.BFunc=BFuncHarmonic<T,DBuff,GType>;
        break;
      case LJ612:
        F.EFunc=EFuncLJ612<T,DBuff,GType>;
        F.GFunc=GFuncLJ612<T,DBuff,GType>;
        F.BFunc=BFuncLJ612<T,DBuff,GType>;
        break;
      case LJ612Cut:
        F.EFunc=EFuncLJ612Cut<T,DBuff,GType>;
        F.GFunc=GFuncLJ612Cut<T,DBuff,GType>;
        F.BFunc=BFuncLJ612Cut<T,DBuff,GType>;
        break;
      case LJ1012:
        F.EFunc=EFuncLJ1012<T,DBuff,GType>;
        F.GFunc=GFuncLJ1012<T,DBuff,GType>;
        F.BFunc=BFuncLJ1012<T,DBuff,GType>;
        break;
      case LJ1012Cut:
        F.EFunc=EFuncLJ1012Cut<T,DBuff,GType>;
        F.GFunc=GFuncLJ1012Cut<T,DBuff,GType>;
        F.BFunc=BFuncLJ1012Cut<T,DBuff,GType>;
        break;
      case Core12:
        F.EFunc=EFuncCore12<T,DBuff,GType>;
        F.GFunc=GFuncCore12<T,DBuff,GType>;
        F.BFunc=BFuncCore12<T,DBuff,GType>;
        break;
      case CoreLJ612:
        F.EFunc=EFuncCoreLJ612<T,DBuff,GType>;
        F.GFunc=GFuncCoreLJ612<T,DBuff,GType>;
        F.BFunc=BFuncCoreLJ612<T,DBuff,GType>;
        break;
      case Coulomb:
        F.EFunc=EFuncCoulomb<T,DBuff,GType>;
        F.GFunc=GFuncCoulomb<T,DBuff,GType>;
        F.BFunc=BFuncCoulomb<T,DBuff,GType>;
        break;
      default:
        myError("Unknown interaction type");
    }
  }

}

#endif
