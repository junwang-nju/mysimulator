
#ifndef _Minimizer_Parameter_Flat_for_PropertyList_H_
#define _Minimizer_Parameter_Flat_for_PropertyList_H_

#include "interaction-method.h"
#include "property-list.h"
#include "minimizer-parameter-name-4propertylist.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  struct MinimizerParameter4PropertyListFlat {

    typedef MinimizerParameter4PropertyListFlat<DistEvalMethod,GeomType>  Type;

    static const unsigned int Mode;

    PropertyList<unsigned int> iMask;
    PropertyList<double>  dMask;
    DistEvalMethod  DEval;
    GeomType  Geo;
    Vector<Vector<UniqueParameter> > ParamLst;
    Vector<InteractionMethod<DistEvalMethod,GeomType> > IMLst;
    PropertyList<unsigned int> IdxLst;
    const unsigned int nunit;
    const unsigned int nlst;
    static const unsigned int state;

    MinimizerParameter4PropertyListFlat()
      : iMask(), dMask(), DEval(), Geo(), ParamLst(), IMLst(),
        IdxLst(), nunit(0), nlst(0) {}
    MinimizerParameter4PropertyListFlat(const Type&) {
      myError("Cannot create from Minimizer Parameter Flat for Property List");
    }
    Type& operator=(const Type& MP) { assign(*this,MP); return *this; }
    ~MinimizerParameter4PropertyListFlat() { release(*this); }

  };

  template <typename DistEvalMethod, typename GeomType>
  const unsigned int
  MinimizerParameter4PropertyListFlat<DistEvalMethod,GeomType>::Mode
    =FlatParameter4PropertyList;

  template <typename DistEvalMethod, typename GeomType>
  const unsigned int
  MinimizerParameter4PropertyListFlat<DistEvalMethod,GeomType>::state
    =HybridStorage;

  template <typename DistEvalMethod, typename GeomType>
  bool IsAvailable(
      const MinimizerParameter4PropertyListFlat<DistEvalMethod,GeomType>& MP) {
    return IsAvailable(MP.iMask)&&IsAvailable(MP.dMask)&&IsAvailable(MP.DEval)
         &&IsAvailable(MP.Geo)&&IsAvailable(MP.ParamLst)
         &&IsAvailable(MP.IMLst)&&IsAvailable(MP.IdxLst);
  }

  template <typename DistEvalMethod, typename GeomType>
  void release(
      MinimizerParameter4PropertyListFlat<DistEvalMethod,GeomType>& MP) {
    release(MP.iMask);
    release(MP.dMask);
    release(MP.DEval);
    release(MP.Geo);
    release(MP.ParamLst);
    release(MP.IMLst);
    release(MP.IdxLst);
    MP.nunit=0;
    MP.nlst=0;
  }

  template <typename DistEvalMethod, typename GeomType>
  void assign(
      MinimizerParameter4PropertyListFlat<DistEvalMethod,GeomType>& dest,
      const MinimizerParameter4PropertyListFlat<DistEvalMethod,GeomType>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(dest.iMask,src.iMask);
    assign(dest.dMask,src.dMask);
    assign(dest.DEval,src.DEval);
    assign(dest.Geo,src.Geo);
    assign(dest.ParamLst,src.ParamLst);
    assign(dest.IMLst,src.IMLst);
    assign(dest.IdxLst,src.IdxLst);
    dest.nunit=src.nunit;
    dest.nlst=src.nlst;
  }

  template <typename DistEvalMethod, typename GeomType>
  void refer(
      MinimizerParameter4PropertyListFlat<DistEvalMethod,GeomType>& dest,
      const MinimizerParameter4PropertyListFlat<DistEvalMethod,GeomType>& src) {
    assert(IsAvailable(src));
    release(dest);
    refer(dest.iMask,src.iMask);
    refer(dest.dMask,src.dMask);
    refer(dest.DEval,src.DEval);
    refer(dest.Geo,src.Geo);
    refer(dest.ParamLst,src.ParamLst);
    refer(dest.IMLst,src.IMLst);
    refer(dest.IdxLst,src.IdxLst);
    dest.nunit=src.nunit;
    dest.nlst=src.nlst;
  }

  template <typename DistEvalMethod, typename GeomType>
  bool Consistency(
      const MinimizerParameter4PropertyListFlat<DistEvalMethod,GeomType>& MP) {
    assert(IsAvailable(MP));
    bool out;
    out=(MP.iMask.nunit==MP.dMask.nunit);
    out=out&&(MP.ParamLst.size==MP.IMLst.size);
    out=out&&(MP.ParamLst.size==MP.IdxLst.nunit);
    out=out&&(MP.ParamLst.size==MP.DEval.nunit);
    return out;
  }

  template <typename DistEvalMethod, typename GeomType>
  void Update(MinimizerParameter4PropertyListFlat<DistEvalMethod,GeomType>& MP){
    assert(Consistency(MP));
    MP.nunit=MP.iMask.nunit;
    MP.nlst=MP.IMLst.size;
  }

}

#endif

