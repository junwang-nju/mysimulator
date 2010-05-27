
#ifndef _Interaction_Method_H_
#define _Interaction_Method_H_

#include "property-list.h"
#include "unique-parameter.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  struct InteractionMethod {

    typedef InteractionMethod<DistEvalMethod,GeomType>  Type;

    unsigned int *iTag;
    void (*EFunc)(const Vector<double>*, const unsigned int*,
                  const UniqueParameter*, const unsigned int,
                  Vector<double>*, const unsigned int,
                  DistEvalMethod&, const GeomType&, double&);
    void (*GFunc)(const Vector<double>*, const unsigned int*,
                  const UniqueParameter*, const unsigned int,
                  Vector<double>*, const unsigned int,
                  DistEvalMethod&, const GeomType&, Vector<double>*);
    void (*BFunc)(const Vector<double>*, const unsigned int*,
                  const UniqueParameter*, const unsigned int,
                  Vector<double>*, const unsigned int,
                  DistEvalMethod&, const GeomType&, double&, Vector<double>*);
    PropertyList<double> *tmpvec;
    unsigned int state;

    InteractionMethod()
      : iTag(NULL), EFunc(NULL), GFunc(NULL), BFunc(NULL),
        tmpvec(NULL), state(Unused) {}
    InteractionMethod(const Type&) {
      myError("Cannot create from Interaction Method");
    }
    Type& operator=(const Type& IM) { assign(*this,IM); return *this; }
    ~InteractionMethod() { release(*this); }

  };

  template <typename DistEvalMethod, typename GeomType>
  bool IsAvailable(const InteractionMethod<DistEvalMethod,GeomType>& IM) {
    return IsAvailable(IM.iTag);
  }

  template <typename DistEvalMethod, typename GeomType>
  void release(InteractionMethod<DistEvalMethod,GeomType>& IM) {
    if(IM.state==Allocated) {
      safe_delete(IM.iTag);
      safe_delete(IM.tmpvec);
    } else {
      IM.iTag=NULL;
      IM.tmpvec=NULL;
    }
    IM.EFunc=NULL;
    IM.GFunc=NULL;
    IM.BFunc=NULL;
    IM.state=Unused;
  }

  template <typename DistEvalMethod, typename GeomType>
  void assign(InteractionMethod<DistEvalMethod,GeomType>& dest,
              const InteractionMethod<DistEvalMethod,GeomType>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    *dest.iTag=*src.iTag;
    dest.EFunc=src.EFunc;
    dest.GFunc=src.GFunc;
    dest.BFunc=src.BFunc;
  }

  template <typename DistEvalMethod, typename GeomType>
  void allocate(InteractionMethod<DistEvalMethod,GeomType>& IM) {
    release(IM);
    IM.iTag=new unsigned int;
    IM.tmpvec=new PropertyList<double>;
    IM.state=Allocated;
  }

  template <typename DistEvalMethod, typename GeomType>
  void refer(InteractionMethod<DistEvalMethod,GeomType>& dest,
             const InteractionMethod<DistEvalMethod,GeomType>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.iTag=src.iTag;
    dest.EFunc=src.EFunc;
    dest.GFunc=src.GFunc;
    dest.BFunc=src.BFunc;
    dest.tmpvec=src.tmpvec;
    dest.state=Reference;
  }

}

#include "interaction-type.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void Set(InteractionMethod<DistEvalMethod,GeomType>& IM,
           const unsigned int iTag, const unsigned int Dim=0) {
    assert(IsAvailable(IM));
    *(IM.iTag)=iTag;
    unsigned int *sz=NULL;
    switch(iTag) {
      case PairwiseHarmonic:
        IM.EFunc=EFuncPairwiseHarmonic<DistEvalMethod,GeomType>;
        IM.GFunc=GFuncPairwiseHarmonic<DistEvalMethod,GeomType>;
        IM.BFunc=BFuncPairwiseHarmonic<DistEvalMethod,GeomType>;
        break;
      case PairwiseLJ612:
        IM.EFunc=EFuncPairwiseLJ612<DistEvalMethod,GeomType>;
        IM.GFunc=GFuncPairwiseLJ612<DistEvalMethod,GeomType>;
        IM.BFunc=BFuncPairwiseLJ612<DistEvalMethod,GeomType>;
        break;
      case PairwiseLJ1012:
        IM.EFunc=EFuncPairwiseLJ1012<DistEvalMethod,GeomType>;
        IM.GFunc=GFuncPairwiseLJ1012<DistEvalMethod,GeomType>;
        IM.BFunc=BFuncPairwiseLJ1012<DistEvalMethod,GeomType>;
        break;
      case PairwiseCore12:
        IM.EFunc=EFuncPairwiseCore12<DistEvalMethod,GeomType>;
        IM.GFunc=GFuncPairwiseCore12<DistEvalMethod,GeomType>;
        IM.BFunc=BFuncPairwiseCore12<DistEvalMethod,GeomType>;
        break;
      case PairwiseLJ612Cut:
        IM.EFunc=EFuncPairwiseLJ612Cut<DistEvalMethod,GeomType>;
        IM.GFunc=GFuncPairwiseLJ612Cut<DistEvalMethod,GeomType>;
        IM.BFunc=BFuncPairwiseLJ612Cut<DistEvalMethod,GeomType>;
        break;
      case PairwiseLJ1012Cut:
        IM.EFunc=EFuncPairwiseLJ1012Cut<DistEvalMethod,GeomType>;
        IM.GFunc=GFuncPairwiseLJ1012Cut<DistEvalMethod,GeomType>;
        IM.BFunc=BFuncPairwiseLJ1012Cut<DistEvalMethod,GeomType>;
        break;
      case PairwiseCoreLJ612:
        IM.EFunc=EFuncPairwiseCoreLJ612<DistEvalMethod,GeomType>;
        IM.GFunc=GFuncPairwiseCoreLJ612<DistEvalMethod,GeomType>;
        IM.BFunc=BFuncPairwiseCoreLJ612<DistEvalMethod,GeomType>;
        break;
      case PairwiseCoulomb:
        IM.EFunc=EFuncPairwiseCoulomb<DistEvalMethod,GeomType>;
        IM.GFunc=GFuncPairwiseCoulomb<DistEvalMethod,GeomType>;
        IM.BFunc=BFuncPairwiseCoulomb<DistEvalMethod,GeomType>;
        break;
      case PairwiseQuadHarm:
        IM.EFunc=EFuncPairwiseQuadHarm<DistEvalMethod,GeomType>;
        IM.GFunc=GFuncPairwiseQuadHarm<DistEvalMethod,GeomType>;
        IM.BFunc=BFuncPairwiseQuadHarm<DistEvalMethod,GeomType>;
        break;
      case PairwiseCoreExpandLJ612:
        IM.EFunc=EFuncCoreExpandLJ612<DistEvalMethod,GeomType>;
        IM.GFunc=GFuncCoreExpandLJ612<DistEvalMethod,GeomType>;
        IM.BFunc=BFuncCoreExpandLJ612<DistEvalMethod,GeomType>;
        break;
      case PairwiseCoreExpandCoreLJ612:
        IM.EFunc=EFuncCoreExpandCoreLJ612<DistEvalMethod,GeomType>;
        IM.GFunc=GFuncCoreExpandCoreLJ612<DistEvalMethod,GeomType>;
        IM.BFunc=BFuncCoreExpandCoreLJ612<DistEvalMethod,GeomType>;
        break;
      case CentroidHarmonic:
        IM.EFunc=EFuncCentroidHarmonic<DistEvalMethod,GeomType>;
        IM.GFunc=GFuncCentroidHarmonic<DistEvalMethod,GeomType>;
        IM.BFunc=BFuncCentroidHarmonic<DistEvalMethod,GeomType>;
        sz=new unsigned int[2];
        assign(sz,Dim,2);
        allocate(*(IM.tmpvec),sz,2);
        break;
      default:
        myError("Unknown Interaction Type");
    }
    safe_delete_array(sz);
  }

}

#endif

