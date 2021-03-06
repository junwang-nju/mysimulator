
#ifndef _Lattice_Chain_Set_H_
#define _Lattice_Chain_Set_H_

#include "data/basic/property-list.h"
#include "data/name/lattice-chain-set-property.h"

namespace std {

  template <unsigned int LatType, unsigned int EmbedDim>
  struct LatticeChainSet : public PropertyList<unsigned short int> {
    typedef LatticeChainSet<LatType,EmbedDim>   Type;
    typedef PropertyList<unsigned short int> ParentType;
    
    Vector<unsigned int> property;
    LatticeChainSet() : ParentType(), property() {}
    LatticeChainSet(const Type& CS) {
      Error("Cannot create lattice chain set");
    }
    Type& operator=(const Type& CS) {
      Error("Cannot copy lattice chain set");
      return *this;
    }
    ~LatticeChainSet() { release(*this); }
    
    unsigned int& Length() { return property[SetChainLength]; }
    const unsigned int& Length() const { return property[SetChainLength]; }
    unsigned int& NumChain() { return property[SetChainNumber]; }
    const unsigned int& NumChain() const { return property[SetChainNumber]; }
    unsigned int& ResidualBonds() { return property[SetBondsInLastByte]; }
    const unsigned int& ResidualBonds() const {
      return property[SetBondsInLastByte];
    }
  };

  template <unsigned int LT, unsigned int ED>
  bool IsAvailable(const LatticeChainSet<LT,ED>& CS) {
    return IsAvailable(static_cast<PropertyList<unsigned short int>&>(CS))&&
           IsAvailable(CS.property);
  }

  template <unsigned int LT, unsigned int ED>
  void release(LatticeChainSet<LT,ED>& CS) {
    release(CS.property);
    release(static_cast<PropertyList<unsigned short int>&>(CS));
  }

  template <unsigned int LT, unsigned int ED>
  void copy(LatticeChainSet<LT,ED>& CS, const LatticeChainSet<LT,ED>& cCS) {
    assert(IsAvailable(CS));
    assert(IsAvailable(cCS));
    copy(static_cast<PropertyList<unsigned short int>&>(CS),
         static_cast<const PropertyList<unsigned short int>&>(cCS));
    copy(CS.property,cCS.property);
  }
  
  template <unsigned int LT, unsigned int ED>
  void refer(LatticeChainSet<LT,ED>& CS, const LatticeChainSet<LT,ED>& rCS) {
    assert(IsAvailable(rCS));
    release(CS);
    refer(static_cast<PropertyList<unsigned short int>&>(CS),
          static_cast<const PropertyList<unsigned short int>&>(rCS));
    refer(CS.property,rCS.property);
  }

}

#include "data/lattice/bond-library.h"

namespace std {

  template <unsigned int LT, unsigned int ED>
  void allocate(LatticeChainSet<LT,ED>& CS,
                const unsigned int n, const unsigned int l) {
    const BondLib<LT,ED>& rBL=RunBondLibrary<LT,ED>();
    assert((n>0)&&(l>0));
    Vector<unsigned int> sz(n);
    copy(sz,(l-2)/rBL.MaxBonds+1);
    allocate(static_cast<PropertyList<unsigned short int>&>(CS),sz);
    allocate(CS.property,LatChainSetPropertyNumberParameter);
    CS.Length()=l;
    CS.NumChain()=n;
    CS.ResidualBonds()=(l-2)%rBL.BondNumber()+1;
  }

}

#endif
