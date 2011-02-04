
#ifndef _Interaction_Meta_Parameter_H_
#define _Interaction_Meta_Parameter_H_

#include "data/name/all-interaction.h"

namespace std {

  template <typename IPType>
  struct InteractionMetaParameter {

    IPType inprm;
    Vector<UniqueParameter> prm;
    Vector<unsigned int> tag;

    typedef InteractionMetaParameter<IPType> Type;

    InteractionMetaParameter() : inprm(), prm(), tag() {}
    InteractionMetaParameter(const Type&) {
      myError("Cannot create Interaction Parameter Meta-Unit");
    }
    Type& operator=(const Type& P) {
      myError("Cannot copy Interaction Parameter Meta-Unit");
      return *this;
    }
    ~InteractionMetaParameter() { release(*this); }
    
    unsigned int& iTag() { return tag[0]; }
    const unsigned int& iTag() const { return tag[0]; }

  };

  template <typename IPType>
  bool IsAvailable(const InteractionMetaParameter<IPType>& P) {
    return IsAvailable(P.inprm)&&IsAvailable(P.prm)&&IsAvailable(P.tag);
  }

  template <typename IPType>
  void release(InteractionMetaParameter<IPType>& P) {
    release(P.inprm);
    release(P.prm);
    release(P.tag);
  }

  template <typename IPType>
  void copy(InteractionMetaParameter<IPType>& P,
            const InteractionMetaParameter<IPType>& cP) {
    assert(IsAvailable(P));
    assert(IsAvailable(cP));
    assert(P.iTag()==cP.iTag());
    copy(P.inprm,cP.inprm);
    copy(P.prm,cP.prm);
  }

  template <typename IPType>
  void refer(InteractionMetaParameter<IPType>& P,
             const InteractionMetaParameter<IPType>& rP) {
    assert(IsAvailable(rP));
    release(P);
    refer(P.inprm,rP.inprm);
    refer(P.prm,rP.prm);
    refer(P.tag,rP.tag);
  }

  void allocate(InteractionMetaParameter<IPType>& P,
                const unsigned int& mitag) {
    if(!IsAvailable(P.tag)) {
      allocate(P.tag,1);
      P.iTag()=mitag;
    }
    If(!IsAvailable(InteractionMetaPrmSize))
      InitInteractionMetaParameterSize();
    allocate(P.prm,InteractionMetaPrmSize[mitag]);
  }

  void imprint(InteractionMetaParameter<IPType>& P,
               const InteractionMetaParameter<IPType>& cP) {
    imprint(P.inprm,cP.inprm);
    imprint(P.prm,cP.prm);
    allocate(P.tag,1);
    P.iTag()=cP.iTag();
  }

}

#endif

