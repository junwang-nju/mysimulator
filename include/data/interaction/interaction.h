
#ifndef _Interaction_H_
#define _Interaction_H_

#include "data/basic/property-list.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  struct Interaction {
    Vector<UniqueParameter> prm;
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

    typedef Interaction<T,DistBuffer,GeomType>    Type;

    Interaction() : prm(),property(),EFunc(NULL),GFunc(NULL),BFunc(NULL),
                    tmvec(),dbuff(),geo() {}
    Interaction(const Type& F) { myError("Cannot create Interaction"); }
    Type& operator=(const Type& F) {
      myError("Cannot copy Interaction");
      return *this;
    }
    ~Interaction() { release(*this); }

    unsigned int& Tag() { return property[0]; }
    const unsigned int& tag() const { return property[0]; }
    unsigned int& Dimension() { return property[1]; }
    const unsigned int& dimension() const { return property[1]; }
    unsigned int& NumUnit() { return property[2]; }
    const unsigned int& NumUnit() const { return property[2]; }
  };

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  bool IsAvailable(const Interaction<T,DistBuffer,GeomType>& F) {
    return IsAvailable(F.prm)&&IsAvailable(F.property)&&
           IsAvailable(F.dbuff)&&IsAvailable(F.geo);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void release(Interaction<T,DistBuffer,GeomType>& F) {
    release(F.prm);
    release(F.property);
    F.EFunc=NULL;
    F.GFunc=NULL;
    F.BFunc=NULL;
    release(F.tmvec);
    release(F.dbuff);
    release(F.geo);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void copy(Interaction<T,DistBuffer,GeomType>& F,
            const Interaction<T,DistBuffer,GeomType>& rF) {
    assert(IsAvailable(F));
    assert(IsAvailable(rF));
    assert(F.prm.size==rF.prm.size);
    assert(F.tmvec.size==rF.tmvec.size);
    assert(IsStructureSame(F.tmvec,rF.tmvec));
    copy(F.prm,rF.prm);
    copy(F.property,rF.property);
    F.EFunc=rF.EFunc;
    F.GFunc=rF.GFunc;
    F.BFunc=rF.BFunc;
    copy(F.dbuff,rF.dbuff);
    copy(F.geo,rF.geo);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void refer(Interaction<T,DistBuffer,GeomType>& F,
             const Interaction<T,DistBuffer,GeomType>& rF) {
    assert(IsAvailable(rF));
    release(F);
    refer(F.prm,rF.prm);
    refer(F.property,rF.property);
    F.EFunc=rF.EFunc;
    F.GFunc=rF.GFunc;
    F.BFunc=rF.BFunc;
    refer(F.tmvec,rF.tmvec);
    refer(F.dbuff,rF.dbuff);
    refer(F.geo,rF.geo);
  }

}

#include "data/name/interaction.h"
#include "operation/interaction/all.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void allocateStatic(Interaction<T,DistBuffer,GeomType>& F,
                      const unsigned int iTag, const unsigned int dim=0) {
    Vector<unsigned int> sz;
    switch(iTag) {
      case Harmonic:
        F.EFunc=EFuncHarmonic<T,DistBuffer,GeomType>;
        F.GFunc=GFuncHarmonic<T,DistBuffer,GeomType>;
        F.BFunc=BFuncHarmonic<T,DistBuffer,GeomType>;
        break;
      case LJ612:
        F.EFunc=EFuncLJ612<T,DistBuffer,GeomType>;
        F.GFunc=GFuncLJ612<T,DistBuffer,GeomType>;
        F.BFunc=BFuncLJ612<T,DistBuffer,GeomType>;
        break;
      case LJ1012:
        F.EFunc=EFuncLJ1012<T,DistBuffer,GeomType>;
        F.GFunc=GFuncLJ1012<T,DistBuffer,GeomType>;
        F.BFunc=BFuncLJ1012<T,DistBuffer,GeomType>;
        break;
      case Core12:
        F.EFunc=EFuncCore12<T,DistBuffer,GeomType>;
        F.GFunc=GFuncCore12<T,DistBuffer,GeomType>;
        F.BFunc=BFuncCore12<T,DistBuffer,GeomType>;
        break;
      case CoreLJ612:
        F.EFunc=EFuncCoreLJ612<T,DistBuffer,GeomType>;
        F.GFunc=GFuncCoreLJ612<T,DistBuffer,GeomType>;
        F.BFunc=BFuncCoreLJ612<T,DistBuffer,GeomType>;
        break;
      case LJ612Cut:
        F.EFunc=EFuncLJ612Cut<T,DistBuffer,GeomType>;
        F.GFunc=GFuncLJ612Cut<T,DistBuffer,GeomType>;
        F.BFunc=BFuncLJ612Cut<T,DistBuffer,GeomType>;
        break;
      case LJ1012Cut:
        F.EFunc=EFuncLJ1012Cut<T,DistBuffer,GeomType>;
        F.GFunc=GFuncLJ1012Cut<T,DistBuffer,GeomType>;
        F.BFunc=BFuncLJ1012Cut<T,DistBuffer,GeomType>;
        break;
      case Coulomb:
        F.EFunc=EFuncCoulomb<T,DistBuffer,GeomType>;
        F.GFunc=GFuncCoulomb<T,DistBuffer,GeomType>;
        F.BFunc=BFuncCoulomb<T,DistBuffer,GeomType>;
        break;
      default:
        myError("Unknown interaction type");
    }
    release(sz);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void allocate(Interaction<T,DistBuffer,GeomType>& F,
                const unsigned int iTag,
                const unsigned int dim, const unsigned int nunit) {
    release(F);
    allocate(F.property,3);
    F.Tag()=iTag;
    F.Dimension()=dim;
    F.NumUnit()=nunit;
    allocate(F.dbuff,dim,nunit);
    allocate(F.geo,dim);
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
    allocateStatic(F,iTag,dim);
  }

}

#endif

