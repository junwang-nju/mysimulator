
#ifndef _Interaction_Method_H_
#define _Interaction_Method_H_

#include "property-list.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  struct InteractionMethod {

    typedef InteractionMethod<DistEvalMethod,GeomType>  Type;

    unsigned int *iTag;
    void (*EFunc)(const Vector<double>*, const unsigned int*, const double*,
                  Vector<double>*, DistEvalMethod&, const GeomType&, double&);
    void (*GFunc)(const Vector<double>*, const unsigned int*, const double*,
                  Vector<double>*, DistEvalMethod&, const GeomType&,
                  Vector<double>*);
    void (*BFunc)(const Vector<double>*, const unsigned int*, const double*,
                  Vector<double>*, DistEvalMethod&, const GeomType&, double&,
                  Vector<double>*);
    PropertyList<double> *tmpvec;
    unsigned int state;

    InteractionMethod()
      : iTag(NULL), EFunc(NULL), GFunc(NULL), BFunc(NULL), tmpvec(NULL),
        state(Unused) {}
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
    *(IM.iTag)=iTag;
    unsigned int *sz=NULL;
    switch(iTag) {
      default:
        myError("Unknown Interaction Type");
    }
    safe_delete_array(sz);
  }

}

#endif

