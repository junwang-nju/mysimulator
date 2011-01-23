
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
  void allocate(InteractionUnit<T,DBuff,GType>& F,
      const unsigned int& tag, const unsigned int& dim) {
    F.pTag=new unsigned int;
    F.iTag()=tag;
    Vector<unsigned int> sz;
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
      case FENE:
        F.EFunc=EFuncFENE<T,DBuff,GType>;
        F.GFunc=GFuncFENE<T,DBuff,GType>;
        F.BFunc=BFuncFENE<T,DBuff,GType>;
        break;
      case QuadPlusHarmonic:
        F.EFunc=EFuncQuadHarmonic<T,DBuff,GType>;
        F.GFunc=GFuncQuadHarmonic<T,DBuff,GType>;
        F.BFunc=BFuncQuadHarmonic<T,DBuff,GType>;
        break;
      case AngleHarmonic:
        allocate(sz,4);
        copy(sz,dim);
        allocate(F.tmvec,sz);
        F.EFunc=EFuncAngleHarmonic<T,DBuff,GType>;
        F.GFunc=GFuncAngleHarmonic<T,DBuff,GType>;
        F.BFunc=BFuncAngleHarmonic<T,DBuff,GType>;
        break;
      case DihedralPeriodic:
        allocate(sz,6);
        copy(sz,dim);
        allocate(F.tmvec,sz);
        F.EFunc=EFuncDihPeriodic<T,DBuff,GType>;
        F.GFunc=GFuncDihPeriodic<T,DBuff,GType>;
        F.BFunc=BFuncDihPeriodic<T,DBuff,GType>;
        break;
      case CoreExpandedCoreLJ612:
        F.EFunc=EFuncCECoreLJ612<T,DBuff,GType>;
        F.GFunc=GFuncCECoreLJ612<T,DBuff,GType>;
        F.BFunc=BFuncCECoreLJ612<T,DBuff,GType>;
        break;
      case CoreExpandedLJ612:
        F.EFunc=EFuncCELJ612<T,DBuff,GType>;
        F.GFunc=GFuncCELJ612<T,DBuff,GType>;
        F.BFunc=BFuncCELJ612<T,DBuff,GType>;
        break;
      case CentroidCentroidHarmonic:
        allocate(sz,2);
        copy(sz,dim);
        allocate(F.tmvec,sz);
        F.EFunc=EFuncCentroidCentroidHarmonic<T,DBuff,GType>;
        F.GFunc=GFuncCentroidCentroidHarmonic<T,DBuff,GType>;
        F.BFunc=BFuncCentroidCentroidHarmonic<T,DBuff,GType>;
        break;
      case ParticleCentroidHarmonic:
        allocate(sz,1);
        copy(sz,dim);
        allocate(F.tmvec,sz);
        F.EFunc=EFuncParticleCentroidHarmonic<T,DBuff,GType>;
        F.GFunc=GFuncParticleCentroidHarmonic<T,DBuff,GType>;
        F.BFunc=BFuncParticleCentroidHarmonic<T,DBuff,GType>;
        break;
      case PlaneWallCoreLJ612:
        F.EFunc=EFuncPlaneWallCoreLJ612<T,DBuff,GType>;
        F.GFunc=GFuncPlaneWallCoreLJ612<T,DBuff,GType>;
        F.BFunc=BFuncPlaneWallCoreLJ612<T,DBuff,GType>;
        break;
      case PlaneWallLJ612Cut:
        F.EFunc=EFuncPlaneWallLJ612Cut<T,DBuff,GType>;
        F.GFunc=GFuncPlaneWallLJ612Cut<T,DBuff,GType>;
        F.BFunc=BFuncPlaneWallLJ612Cut<T,DBuff,GType>;
        break;
      case SphericShellCoreLJ612:
        F.EFunc=EFuncSphericShellCoreLJ612<T,DBuff,GType>;
        F.GFunc=GFuncSphericShellCoreLJ612<T,DBuff,GType>;
        F.BFunc=BFuncSphericShellCoreLJ612<T,DBuff,GType>;
        break;
      case SphericShellLJ612Cut:
        F.EFunc=EFuncSphericShellLJ612Cut<T,DBuff,GType>;
        F.GFunc=GFuncSphericShellLJ612Cut<T,DBuff,GType>;
        F.BFunc=BFuncSphericShellLJ612Cut<T,DBuff,GType>;
        break;
      case AncherPointHarmonic:
        F.EFunc=EFuncAncherPointHarmonic<T,DBuff,GType>;
        F.GFunc=GFuncAncherPointHarmonic<T,DBuff,GType>;
        F.BFunc=BFuncAncherPointHarmonic<T,DBuff,GType>;
        break;
      default:
        myError("Unknown interaction type");
    }
  }

}

#endif

