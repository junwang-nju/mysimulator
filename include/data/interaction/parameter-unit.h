
#ifndef _Interaction_Parameter_Unit_H_
#define _Interaction_Parameter_Unit_H_

#include "data/basic/unique-parameter.h"

namespace std {

  struct InteractionParameterUnit;
  void release(InteractionParameterUnit&);

  struct InteractionParameterUnit {
    typedef InteractionParameterUnit  Type;
    Vector<UniqueParameter> prm;
    Vector<unsigned int> idx;
    Vector<unsigned int> tag;

    InteractionParameterUnit() : prm(), idx(), tag() {}
    InteractionParameterUnit(const Type&) {
      myError("Cannot create Interaction Parameter Unit");
    }
    Type& operator=(const Type& P) {
      myError("Cannot copy Interaction Parameter Unit");
      return *this;
    }
    ~InteractionParameterUnit() { release(*this); }

    unsigned int& iTag() { return tag[0]; }
    const unsigned int& iTag() const { return tag[0]; }
  };

  bool IsAvailable(const InteractionParameterUnit& P) {
    return IsAvailable(P.prm)&&IsAvailable(P.idx)&&IsAvailable(P.tag);
  }

  void release(InteractionParameterUnit& P) {
    release(P.prm);
    release(P.idx);
    release(P.tag);
  }

  void copy(InteractionParameterUnit& P, const InteractionParameterUnit& cP) {
    assert(IsAvailable(P));
    assert(IsAvailable(cP));
    assert(P.iTag()==cP.iTag());
    copy(P.prm,cP.prm);
    copy(P.idx,cP.idx);
  }

  void refer(InteractionParameterUnit& P, const InteractionParameterUnit& rP) {
    assert(IsAvailable(rP));
    release(P);
    refer(P.prm,rP.prm);
    refer(P.idx,rP.idx);
    refer(P.tag,rP.tag);
  }

}

#include "data/name/all-interaction.h"

namespace std {

  void allocateIndex(InteractionParameterUnit& P,
                     const unsigned int& itag, const unsigned int nunit=0) {
    assert((!IsAvailable(P.tag))||(P.iTag()==itag));
    if(!IsAvailable(P.tag)) {
      allocate(P.tag,1);
      P.iTag()=itag;
    }
    switch(itag) {
      case Harmonic:
      case LJ612:
      case LJ612Cut:
      case LJ1012:
      case LJ1012Cut:
      case Coulomb:
      case Core12:
      case CoreLJ612:
        allocate(P.idx,2);    break;
      default:
        myError("Unknown Type of Interaction Parameter Unit");
    }
  }

  void allocateParameter(InteractionParameterUnit& P,
                         const unsigned int& itag){
    assert((!IsAvailable(P.tag))||(P.iTag()==itag));
    if(!IsAvailable(P.tag)) {
      allocate(P.tag,1);
      P.iTag()=itag;
    }
    switch(itag) {
      case Harmonic:
        allocate(P.prm,HarmonicNumberParameter);  break;
      case LJ612:
        allocate(P.prm,LJ612NumberParameter); break;
      case LJ612Cut:
        allocate(P.prm,LJ612CutNumberParameter);  break;
      case LJ1012:
        allocate(P.prm,LJ1012NumberParameter);  break;
      case LJ1012Cut:
        allocate(P.prm,LJ1012CutNumberParameter); break;
      case Coulomb:
        allocate(P.prm,CoulombNumberParameter); break;
      case Core12:
        allocate(P.prm,Core12NumberParameter);  break;
      case CoreLJ612:
        allocate(P.prm,CoreLJ612NumberParameter); break;
      default:
        myError("Unknown Type of Interaction Parameter Unit");
    }
  }

  void allocate(InteractionParameterUnit& P,
                const unsigned int& itag, const unsigned int nunit=0) {
    allocateIndex(P,itag,nunit);
    allocateParameter(P,itag);
  }

  void imprint(InteractionParameterUnit& P,
               const InteractionParameterUnit& cP) {
    imprint(P.prm,cP.prm);
    imprint(P.idx,cP.idx);
    allocate(P.tag,1);
    P.iTag()=cP.iTag();
  }

  void imprint(Vector<InteractionParameterUnit>& P,
               const Vector<InteractionParameterUnit>& cP) {
    allocate(P,cP.size);
    for(unsigned int i=0;i<P.size;++i)  imprint(P[i],cP[i]);
  }

  void imprint(Vector<Vector<InteractionParameterUnit> >& P,
               const Vector<Vector<InteractionParameterUnit> >& cP) {
    allocate(P,cP.size);
    for(unsigned int i=0;i<P.size;++i)  allocate(P[i],cP[i].size);
    for(unsigned int i=0;i<P.size;++i)
    for(unsigned int j=0;j<P[i].size;++j)
      imprint(P[i][j],cP[i][j]);
  }

}

#include "data/basic/property-list.h"

namespace std {

  void imprint(PropertyList<InteractionParameterUnit>& P,
               const PropertyList<InteractionParameterUnit>& cP) {
    Vector<unsigned int> sz(cP.size);
    for(unsigned int i=0;i<cP.size;++i) sz[i]=cP[i].size;
    allocate(P,sz);
    for(unsigned int i=0;i<P.size;++i)
      for(unsigned int j=0;j<P[i].size;++j)
        imprint(P[i][j],cP[i][j]);
  }

}

#endif

