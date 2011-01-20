
#ifndef _Lattice_Chain_H_
#define _Lattice_Chain_H_

#include "data/basic/vector.h"
#include "data/name/lattice-chain-property.h"

namespace std {

  template <unsigned int LatType, unsigned int EmbedDim>
  struct LatticeChain : public Vector<unsigned short int> {
    typedef LatticeChain<LatType,EmbedDim>  Type;
    typedef Vector<unsigned short int>  ParentType;

    Vector<unsigned int> property;

    LatticeChain() : ParentType(), property() {}
    LatticeChain(const Type& LC) { myError("Cannot create lattice chain"); }
    Type& operator=(const Type& LC) {
      myError("Cannot copy lattice chain");
      return *this;
    }
    ~LatticeChain() { release(*this); }

    unsigned int& Length() { return property[LatChainLength]; }
    const unsigned int& Length() const { return property[LatChainLength]; }
    unsigned int& ResidualBonds() { return property[BondsInLastUnit]; }
    const unsigned int& ResidualBonds() const {
      return property[BondsInLastUnit];
    }
  };

  template <unsigned int LType, unsigned int EDim>
  bool IsAvailable(const LatticeChain<LType,EDim>& LC) {
    return IsAvailable(static_cast<const Vector<unsigned short int>&>(LC))&&
           IsAvailable(LC.property);
  }

  template <unsigned int LType, unsigned int EDim>
  void release(LatticeChain<LType,EDim>& LC) {
    release(LC.property);
    release(static_cast<Vector<unsigned short int>&>(LC));
  }

  template <unsigned int LT, unsigned int LD>
  void copy(LatticeChain<LT,LD>& LC, const LatticeChain<LT,LD>& cLC) {
    assert(IsAvailable(LC));
    assert(IsAvailable(cLC));
    copy(static_cast<Vector<unsigned short int>&>(LC),
         static_cast<const Vector<unsigned short int>&>(cLC));
    copy(LC.property,cLC.property);
  }

  template <unsigned int LT,unsigned int LD>
  void refer(LatticeChain<LT,LD>& LC, const LatticeChain<LT,LD>& rLC) {
    assert(IsAvailable(rLC));
    release(LC);
    refer(static_cast<Vector<unsigned short int>&>(LC),
          static_cast<const Vector<unsigned short int>&>(rLC));
    refer(LC.property,rLC.property);
  }

}

#include "data/lattice/bond-library.h"

namespace std {

  template <unsigned int LT,unsigned int LD>
  void allocate(LatticeChain<LT,LD>& LC, const unsigned int n) {
    const BondLib<LT,LD>& rBL=RunBondLibrary<LT,LD>();
    assert(n>0);
    allocate(static_cast<Vector<unsigned short int>&>(LC),
             ((n-2)/rBL.MaxBonds+1));
    allocate(LC.property,LatChainPropertyNumberParameter);
    LC.Length()=n;
    LC.ResidualBonds()=(n-2)%rBL.MaxBonds+1;
  }

}
  
#endif
