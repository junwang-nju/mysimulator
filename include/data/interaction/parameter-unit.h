
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
#include "operation/parameter/build-param-dihedral-periodic.h"
#include <cstdarg>

namespace std {

  void allocate(InteractionParameterUnit& P, const unsigned int& itag, ...) {
    assert((!IsAvailable(P.tag))||(P.iTag()==itag));
    if(!IsAvailable(P.tag)) {
      allocate(P.tag,1);
      P.iTag()=itag;
    }
    va_list vl;
    va_start(vl,itag);
    if(!IsAvailable(InteractionIdxSize))  InitInteractionIndexSize();
    if(itag==CentroidCentroidHarmonic) {
      unsigned int nunit=va_arg(vl,unsigned int);
      allocate(P.idx,4+nunit);
    } else if(itag==ParticleCentroidHarmonic) {
      unsigned int nunit=va_arg(vl,unsigned int);
      allocate(P.idx,2+nunit);
    } else if(itag<NumberInteractions)
      allocate(P.idx,InteractionIdxSize[itag]);
    else  myError("Unknown Type of Interaction Parameter Unit");
    if(!IsAvailable(InteractionPrmSize))  InitInteractionParameterSize();
    if(itag==DihedralPeriodic) {
      unsigned int nperiod=va_arg(vl,unsigned int);
      allocateDihPeriodicParameter(P.prm,nperiod);
    } else if(itag<NumberInteractions)
      allocate(P.prm,InteractionPrmSize[itag]);
    else  myError("Unknown Type of Interaction Parameter Unit");
    va_end(vl);
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

}

#include "data/derived/dual-vector.h"

namespace std {

  void imprint(Vector<Vector<InteractionParameterUnit> >& P,
               const Vector<Vector<InteractionParameterUnit> >& cP) {
    allocate<Vector<InteractionParameterUnit> >(P,cP.size);
    for(unsigned int i=0;i<P.size;++i)
      if(cP[i].size>0)  allocate(P[i],cP[i].size);
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

