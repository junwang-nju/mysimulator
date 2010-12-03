
#ifndef _Interaction_Base_H_
#define _Interaction_Base_H_

#include "data/basic/property-list.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType,
            typename ParameterType>
  struct InteractionBase {
    ParameterType prm;
    Vector<unsigned int> property;
    void (*EFunc)(const Vector<T>*,const unsigned int*,const UniqueParameter*,
                  DistBuffer<T>&,const GeomType&,T&,
                  Vector<T>*,const unsigned int);
    void (*GFunc)(const Vector<T>*,const unsigned int*,const UniqueParameter*,
                  DistBuffer<T>&,const GeomType&,Vector<T>*,
                  Vector<T>*,const unsigned int);
    void (*BFunc)(const Vector<T>*,const unsigned int*,const UniqueParameter*,
                  DistBuffer<T>&,const GeomType&,T&,Vector<T>*,
                  Vector<T>*,const unsigned int);
    PropertyList<T> tmvec;
    DistBuffer<T> dbuff;
    GeomType geo;

    typedef InteractionBase<T,DistBuffer,GeomType,ParameterType>    Type;

    InteractionBase() : prm(),property(),EFunc(NULL),GFunc(NULL),BFunc(NULL),
                        tmvec(),dbuff(),geo() {}
    InteractionBase(const Type& F) {
      myError("Cannot create Interaction Base");
    }
    Type& operator=(const Type& F) {
      myError("Cannot copy Interaction Base");
      return *this;
    }
    ~InteractionBase() { release(*this); }

    unsigned int& Tag() { return property[0]; }
    const unsigned int& tag() const { return property[0]; }
    unsigned int& Dimension() { return property[1]; }
    const unsigned int& dimension() const { return property[1]; }
    unsigned int& NumUnit() { return property[2]; }
    const unsigned int& NumUnit() const { return property[2]; }
  };

  template <typename T,template <typename> class DBuffer,typename GType,
            typename PType>
  bool IsAvailable(const InteractionBase<T,DBuffer,GType,PType>& F) {
    return IsAvailable(F.prm)&&IsAvailable(F.property)&&
           IsAvailable(F.dbuff)&&IsAvailable(F.geo);
  }

  template <typename T,template <typename> class DBuffer,typename GType,
            typename PType>
  void release(InteractionBase<T,DBuffer,GType,PType>& F) {
    release(F.prm);
    release(F.property);
    F.EFunc=NULL;
    F.GFunc=NULL;
    F.BFunc=NULL;
    release(F.tmvec);
    release(F.dbuff);
    release(F.geo);
  }

  template <typename T,template <typename> class DBuffer,typename GType,
            typename PType>
  void copy(InteractionBase<T,DBuffer,GType,PType>& F,
            const InteractionBase<T,DBuffer,GType,PType>& rF) {
    assert(IsAvailable(F));
    assert(IsAvailable(rF));
    assert(F.tag()==rF.tag());
    assert(F.prm.size==rF.prm.size);
    assert(F.tmvec.size==rF.tmvec.size);
    assert((!IsAvailable(F.tmvec))||(IsStructureSame(F.tmvec,rF.tmvec)));
    copy(F.prm,rF.prm);
    copy(F.property,rF.property);
    copy(F.dbuff,rF.dbuff);
    copy(F.geo,rF.geo);
  }

  template <typename T,template <typename> class DBuffer,typename GType,
            typename PType>
  void refer(InteractionBase<T,DBuffer,GType,PType>& F,
             const InteractionBase<T,DBuffer,GType,PType>& rF) {
    assert(IsAvailable(rF));
    release(F);
    refer(F.prm,rF.prm);
    refer(F.property,rF.property);
    F.EFunc=rF.EFunc;
    F.GFunc=rF.GFunc;
    F.BFunc=rF.BFunc;
    if(IsAvailable(rF.tmvec)) refer(F.tmvec,rF.tmvec);
    refer(F.dbuff,rF.dbuff);
    refer(F.geo,rF.geo);
  }

}

#include "data/name/interaction.h"
#include "operation/interaction/all.h"

namespace std {

  template <typename T,template <typename> class DBuffer,typename GType,
            typename PType>
  void allocateStatic(InteractionBase<T,DBuffer,GType,PType>& F,
                      const unsigned int iTag, const unsigned int dim=0) {
    Vector<unsigned int> sz;
    switch(iTag) {
      case Harmonic:
        F.EFunc=EFuncHarmonic<T,DBuffer,GType>;
        F.GFunc=GFuncHarmonic<T,DBuffer,GType>;
        F.BFunc=BFuncHarmonic<T,DBuffer,GType>;
        break;
      case LJ612:
        F.EFunc=EFuncLJ612<T,DBuffer,GType>;
        F.GFunc=GFuncLJ612<T,DBuffer,GType>;
        F.BFunc=BFuncLJ612<T,DBuffer,GType>;
        break;
      case LJ1012:
        F.EFunc=EFuncLJ1012<T,DBuffer,GType>;
        F.GFunc=GFuncLJ1012<T,DBuffer,GType>;
        F.BFunc=BFuncLJ1012<T,DBuffer,GType>;
        break;
      case Core12:
        F.EFunc=EFuncCore12<T,DBuffer,GType>;
        F.GFunc=GFuncCore12<T,DBuffer,GType>;
        F.BFunc=BFuncCore12<T,DBuffer,GType>;
        break;
      case CoreLJ612:
        F.EFunc=EFuncCoreLJ612<T,DBuffer,GType>;
        F.GFunc=GFuncCoreLJ612<T,DBuffer,GType>;
        F.BFunc=BFuncCoreLJ612<T,DBuffer,GType>;
        break;
      case LJ612Cut:
        F.EFunc=EFuncLJ612Cut<T,DBuffer,GType>;
        F.GFunc=GFuncLJ612Cut<T,DBuffer,GType>;
        F.BFunc=BFuncLJ612Cut<T,DBuffer,GType>;
        break;
      case LJ1012Cut:
        F.EFunc=EFuncLJ1012Cut<T,DBuffer,GType>;
        F.GFunc=GFuncLJ1012Cut<T,DBuffer,GType>;
        F.BFunc=BFuncLJ1012Cut<T,DBuffer,GType>;
        break;
      case Coulomb:
        F.EFunc=EFuncCoulomb<T,DBuffer,GType>;
        F.GFunc=GFuncCoulomb<T,DBuffer,GType>;
        F.BFunc=BFuncCoulomb<T,DBuffer,GType>;
        break;
      default:
        myError("Unknown interaction type");
    }
    release(sz);
  }

  template <typename T,template <typename> class DBuffer,typename GType,
            typename PType>
  void allocate(InteractionBase<T,DBuffer,GType,PType>& F,
                const unsigned int iTag,
                const unsigned int dim, const unsigned int nunit) {
    release(F);
    allocate(F.property,3);
    F.Tag()=iTag;
    F.Dimension()=dim;
    F.NumUnit()=nunit;
    allocate(F.dbuff,dim,nunit);
    allocate(F.geo,dim);
    allocateStatic(F,iTag,dim);
  }

}

#endif

