
#ifndef _Interaction_Meta_Parameter_H_
#define _Interaction_Meta_Parameter_H_

#include "data/basic/unique-parameter.h"
#include "data/basic/property-list.h"

namespace std {

  template <typename IPType, typename IType, typename T>
  struct InteractionMetaParameter {

    IPType inprm;
    Vector<UniqueParameter> prm;
    Vector<unsigned int> tag;
    PropertyList<T> tmvec;
    void (*EFunc)(const Vector<T>*,IType&,IPType&,const UniqueParameter*,
                  T&,Vector<T>*);
    void (*GFunc)(const Vector<T>*,IType&,IPType&,const UniqueParameter*,
                  Vector<T>*,Vector<T>*);
    void (*BFunc)(const Vector<T>*,IType&,IPType&,const UniqueParameter*,
                  T&,Vector<T>*,Vector<T>*);

    typedef InteractionMetaParameter<IPType,IType,T> Type;

    InteractionMetaParameter()
      : inprm(),prm(),tag(),tmvec(),EFunc(NULL),GFunc(NULL),BFunc(NULL) {}
    InteractionMetaParameter(const Type&) {
      Error("Cannot create Interaction Meta Parameter");
    }
    Type& operator=(const Type& P) {
      Error("Cannot copy Interaction Meta Parameter");
      return *this;
    }
    ~InteractionMetaParameter() { release(*this); }
    
    unsigned int& iTag() { return tag[0]; }
    const unsigned int& iTag() const { return tag[0]; }

  };

  template <typename IPType, typename IType, typename T>
  bool IsAvailable(const InteractionMetaParameter<IPType,IType,T>& P) {
    return IsAvailable(P.inprm)&&IsAvailable(P.prm)&&IsAvailable(P.tag)&&
           IsAvailable(P.EFunc)&&IsAvailable(P.GFunc)&&IsAvailable(P.BFunc);
  }

  template <typename IPType, typename IType, typename T>
  void release(InteractionMetaParameter<IPType,IType,T>& P) {
    release(P.inprm);
    release(P.prm);
    release(P.tag);
    release(P.tmvec);
    P.EFunc=NULL;
    P.GFunc=NULL;
    P.BFunc=NULL;
  }

  template <typename IPType, typename IType, typename T>
  void copy(InteractionMetaParameter<IPType,IType,T>& P,
            const InteractionMetaParameter<IPType,IType,T>& cP) {
    assert(IsAvailable(P));
    assert(IsAvailable(cP));
    assert(P.iTag()==cP.iTag());
    copy(P.inprm,cP.inprm);
    copy(P.prm,cP.prm);
  }

  template <typename IPType, typename IType, typename T>
  void refer(InteractionMetaParameter<IPType,IType,T>& P,
             const InteractionMetaParameter<IPType,IType,T>& rP) {
    assert(IsAvailable(rP));
    release(P);
    refer(P.inprm,rP.inprm);
    refer(P.prm,rP.prm);
    refer(P.tag,rP.tag);
    P.EFunc=rP.EFunc;
    P.GFunc=rP.GFunc;
    P.BFunc=rP.BFunc;
    if(IsAvailable(rP.tmvec)) refer(P.tmvec,rP.tmvec);
  }

}

#include "data/name/all-interaction.h"
#include "operation/interaction/all.h"

namespace std {

  template <typename IPType, typename IType, typename T>
  void allocate(InteractionMetaParameter<IPType,IType,T>& P,
                const unsigned int& mitag) {
    allocate(P.tag,1);
    P.iTag()=mitag;
    if(!IsAvailable(InteractionMetaPrmSize))
      InitInteractionMetaParameterSize();
    allocate(P.prm,InteractionMetaPrmSize[mitag]);
    Vector<unsigned int> sz;
    switch(mitag) {
      case GaoEnhancedSampling:
        P.EFunc=EFuncGaoES<IPType,IType>;
        P.GFunc=GFuncGaoES<IPType,IType>;
        P.BFunc=BFuncGaoES<IPType,IType>;
        break;
      default:
        Error("Unknown Meta Interaction Type");
    }
  }

  template <typename IPType, typename IType, typename T>
  void imprint(InteractionMetaParameter<IPType,IType,T>& P,
               const InteractionMetaParameter<IPType,IType,T>& cP) {
    imprint(P.inprm,cP.inprm);
    imprint(P.prm,cP.prm);
    allocate(P.tag,1);
    P.iTag()=cP.iTag();
    P.EFunc=cP.EFunc;
    P.GFunc=cP.GFunc;
    P.BFunc=cP.BFunc;
    if(IsAvailable(cP.tmvec)) imprint(P.tmvec,cP.tmvec);
  }

}

#endif

