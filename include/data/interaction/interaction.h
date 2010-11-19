
#ifndef _Interaction_H_
#define _Interaction_H_

#include "data/basic/vector.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  struct Interaction : public Vector<UniqueParameter> {
    unsigned int* tag;
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

    typedef Interaction<T,DistBuffer,GeomType>    Type;
    typedef Vector<UniqueParameter>   ParentType;

    Interaction()
      : ParentType(),tag(NULL),EFunc(NULL),GFunc(NULL),BFunc(NULL),tmvec() {}
    Interaction(const Type& F) { myError("Cannot create Interaction"); }
    Type& operator=(const Type& F) {
      myError("Cannot copy Interaction");
      return *this;
    }
    ~Interaction() { release(*this); }
  };

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  bool IsAvailable(const Interaction<T,DistBuffer,GeomType>& F) {
    return IsAvailable(static_cast<const Vector<UniqueParameter>&>(F));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void release(Interaction<T,DistBuffer,GeomType>& F) {
    if(F.state==Allocated)    safe_delete(F.tag);
    else  F.tag=NULL;
    F.EFunc=NULL;
    F.GFunc=NULL;
    F.BFunc=NULL;
    release(F.tmvec);
    release(static_cast<Vector<UniqueParameter>&>(F));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void copy(Interaction<T,DistBuffer,GeomType>& F,
            const Interaction<T,DistBuffer,GeomType>& rF) {
    assert(IsAvailable(F));
    assert(IsAvailable(rF));
    assert(F.size==rF.size);
    assert(IsStructureSame(F.tmvec,rF.tmvec));
    *(F.tag)=*(rF.tag);
    F.EFunc=rF.EFunc;
    F.GFunc=rF.GFunc;
    F.BFunc=rF.BFunc;
    copy(static_cast<Vector<UniqueParameter>&>(F),
         static_cast<const Vector<UniqueParameter>&>(rF));
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void refer(Interaction<T,DistBuffer,GeomType>& F,
             const Interaction<T,DistBuffer,GeomType>& rF) {
    assert(IsAvailable(rF));
    release(F);
    F.tag=rF.tag;
    F.EFunc=rF.EFunc;
    F.GFunc=rF.GFunc;
    F.BFunc=rF.BFunc;
    refer(F.tmvec,rF.tmvec);
    refer(static_cast<Vector<UniqueParameter>&>(F),
          static_cast<const Vector<UniqueParameter>&>(rF));
  }

}

#include "data/name/interaction.h"
#include "operation/interaction/all.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void allocate(Interaction<T,DistBuffer,GeomType>& F,
                const unsigned int iTag, const unsigned int Dim=0) {
    release(F);
    F.tag=new unsigned int;
    F.tag=iTag;
    Vector<unsigned int> sz;
    switch(iTag) {
      case Harmonic:
        F.EFunc=EFuncHarmonic<T,DistBuffer,GeomType>;
        F.GFunc=GFuncHarmonic<T,DistBuffer,GeomType>;
        F.BFunc=BFuncHarmonic<T,DistBuffer,GeomType>;
        allocate(static_cast<Vector<UniqueParameter>&>(F),
                 HarmonicNumberParameter);
        break;
      case LJ612:
        F.EFunc=EFuncLJ612<T,DistBuffer,GeomType>;
        F.GFunc=GFuncLJ612<T,DistBuffer,GeomType>;
        F.BFunc=BFuncLJ612<T,DistBuffer,GeomType>;
        allocate(static_cast<Vector<UniqueParameter>&>(F),
                 LJ612NumberParameter);
        break;
      case LJ1012:
        F.EFunc=EFuncLJ1012<T,DistBuffer,GeomType>;
        F.GFunc=GFuncLJ1012<T,DistBuffer,GeomType>;
        F.BFunc=BFuncLJ1012<T,DistBuffer,GeomType>;
        allocate(static_cast<Vector<UniqueParameter>&>(F),
                 LJ1012NumberParameter);
        break;
      case Core12:
        F.EFunc=EFuncCore12<T,DistBuffer,GeomType>;
        F.GFunc=GFuncCore12<T,DistBuffer,GeomType>;
        F.BFunc=BFuncCore12<T,DistBuffer,GeomType>;
        allocate(static_cast<Vector<UniqueParameter>&>(F),
                 Core12NumberParameter);
        break;
      case CoreLJ612:
        F.EFunc=EFuncCoreLJ612<T,DistBuffer,GeomType>;
        F.GFunc=GFuncCoreLJ612<T,DistBuffer,GeomType>;
        F.BFunc=BFuncCoreLJ612<T,DistBuffer,GeomType>;
        allocate(static_cast<Vector<UniqueParameter>&>(F),
                 CoreLJ612NumberParameter);
        break;
      case LJ612Cut:
        F.EFunc=EFuncLJ612Cut<T,DistBuffer,GeomType>;
        F.GFunc=GFuncLJ612Cut<T,DistBuffer,GeomType>;
        F.BFunc=BFuncLJ612Cut<T,DistBuffer,GeomType>;
        allocate(static_cast<Vector<UniqueParameter>&>(F),
                 LJ612CutNumberParameter);
        break;
      case LJ1012Cut:
        F.EFunc=EFuncLJ1012Cut<T,DistBuffer,GeomType>;
        F.GFunc=GFuncLJ1012Cut<T,DistBuffer,GeomType>;
        F.BFunc=BFuncLJ1012Cut<T,DistBuffer,GeomType>;
        allocate(static_cast<Vector<UniqueParameter>&>(F),
                 LJ1012CutNumberParameter);
      case Coulomb:
        F.EFunc=EFuncCoulomb<T,DistBuffer,GeomType>;
        F.GFunc=GFuncCoulomb<T,DistBuffer,GeomType>;
        F.BFunc=BFuncCoulomb<T,DistBuffer,GeomType>;
        allocate(static_cast<Vector<UniqueParameter>&>(F),
                 CoulombNumberParameter);
    }
    release(sz);
  }

}

#endif

