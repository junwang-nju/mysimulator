
#ifndef _Monomer_Propagator_H_
#define _Monomer_Propagator_H_

#include "unique-parameter.h"
#include "vector.h"

namespace std {

  struct MonomerPropagator;

  void assign(MonomerPropagator&, const MonomerPropagator&);
  void release(MonomerPropagator&);

  struct MonomerPropagator {

    typedef MonomerPropagator Type;
    typedef void (*MoveFuncType)(double*,double*,const double*,const double*,
                                 const unsigned int,
                                 const UniqueParameter*,UniqueParameter*);
    typedef void (*SetFuncType)(UniqueParameter*,const void*);
    typedef void (*SyncFuncType)(const Vector<double>&,
                                 const UniqueParameter*,UniqueParameter*);

    Vector<MoveFuncType>    Move;
    Vector<SetFuncType>     MSet;
    SyncFuncType     MSync;
    Vector<UniqueParameter> MParam;
    unsigned int    *UnitKind;
    unsigned int    *MoveMode;
    unsigned int     state;

    MonomerPropagator()
      : Move(), MSet(), MSync(NULL), MParam(), UnitKind(NULL),
        MoveMode(NULL), state(Unused) {}
    MonomerPropagator(const Type&) {
      myError("Cannot create from Monomer Propagator");
    }
    Type& operator=(const Type& MP) { assign(*this,MP); return *this; }
    ~MonomerPropagator() { release(*this); }

  };

  bool IsAvailable(const MonomerPropagator& MP) {
    return IsAvailable(MP.UnitKind);
  }

  void release(MonomerPropagator& MP) {
    if(MP.state==Allocated) {
      safe_delete(MP.UnitKind);
      safe_delete(MP.MoveMode);
    }
    else {
      MP.UnitKind=NULL;
      MP.MoveMode=NULL;
    }
    release(MP.Move);
    release(MP.MSet);
    release(MP.MParam);
    MP.MSync=NULL;
    MP.state=Unused;
  }

  void allocate(MonomerPropagator& MP) {
    release(MP);
    MP.UnitKind=new unsigned int;
    MP.MoveMode=new unsigned int;
    MP.state=Allocated;
  }

  void assign(MonomerPropagator& dest, const MonomerPropagator& src) {
    assert(IsAvailable(src));
    assert(IsAvailable(dest));
    if((*(dest.UnitKind)!=*(src.UnitKind))||
       (*(dest.MoveMode)!=*(src.MoveMode))) {
      allocate(dest);
      if(IsAvailable(src.Move))   allocate(dest.Move,src.Move.size);
      if(IsAvailable(src.MSet))   allocate(dest.MSet,src.MSet.size);
      if(IsAvailable(src.MParam)) allocate(dest.MParam,src.MParam.size);
    }
    if(IsAvailable(src.Move)) assign(dest.Move,src.Move);
    if(IsAvailable(src.MSet)) assign(dest.MSet,src.MSet);
    dest.MSync=src.MSync;
    if(IsAvailable(src.MParam)) assign(dest.MParam,src.MParam);
    *(dest.UnitKind)=*(src.UnitKind);
    *(dest.MoveMode)=*(src.MoveMode);
  }

  void refer(MonomerPropagator& dest, const MonomerPropagator& src) {
    assert(IsAvailable(src));
    release(dest);
    if(IsAvailable(src.Move))   refer(dest.Move,src.Move);
    if(IsAvailable(src.MSet))   refer(dest.MSet,src.MSet);
    dest.MSync=src.MSync;
    if(IsAvailable(src.MParam)) refer(dest.MParam,src.MParam);
    dest.UnitKind=src.UnitKind;
    dest.MoveMode=src.MoveMode;
    dest.state=Reference;
  }

  void synchronize(MonomerPropagator& MP, const Vector<double>& ivMass,
                   const UniqueParameter* GlbParam) {
    assert(MP.MSync!=NULL);
    MP.MSync(ivMass,GlbParam,MP.MParam());
  }

  template <typename T>
  void setparameter(MonomerPropagator& MP,
                    const unsigned int ComponentID, const T& value) {
    assert(IsAvailable(MP.MSet));
    MP.MSet[ComponentID](MP.MParam(),reinterpret_cast<const void*>(&value));
  }

}

#endif

