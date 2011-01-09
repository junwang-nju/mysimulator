
#ifndef _Lattice_Chain_Base_H_
#define _Lattice_Chain_Base_H_

#include "data/basic/vector.h"
#include "data/name/lattice-chain-property.h"

namespace std {

  template <unsigned int LatType, unsigned int EmbedDim>
  struct LatticeChain : public Vector<unsigned char> {
    typedef LatticeChain<LatType,EmbedDim>  Type;
    typedef Vector<unsigned char>  ParentType;

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
  };

  template <unsigned int LType, unsigned int EDim>
  bool IsAvailable(const LatticeChain<LType,EDim>& LC) {
    return IsAvailable(static_cast<const Vector<unsigned char>&>(LC))&&
           IsAvailable(LC.property);
  }

  template <unsigned int LType, unsigned int EDim>
  void release(LatticeChain<LType,EDim>& LC) {
    release(LC.property);
    release(static_cast<Vector<unsigned char>&>(LC));
  }

  template <unsigned int LT, unsigned int LD>
  void copy(LatticeChain<LT,LD>& LC, const LatticeChain<LT,LD>& cLC) {
    assert(IsAvailable(LC));
    assert(IsAvailable(cLC));
    copy(static_cast<Vector<unsigned char>&>(LC),
         static_cast<const Vector<unsigned char>&>(cLC));
    copy(LC.property,cLC.property);
  }

  template <unsigned int LT,unsigned int LD>
  void refer(LatticeChain<LT,LD>& LC, const LatticeChain<LT,LD>& rLC) {
    assert(IsAvailable(rLC));
    release(LC);
    refer(static_cast<Vector<unsigned char>&>(LC),
          static_cast<const Vector<unsigned char>&>(rLC));
    refer(LC.property,rLC.property);
  }

}

#include "data/lattice/bond-library.h"

namespace std {

  template <unsigned int LT,unsigned int LD>
  void allocate(LatticeChain<LT,LD>& LC, const unsigned int n) {
    const BondLib<LT,LD>& rBL=RunBondLibrary<LT,LD>();
    assert(n>0);
    allocate(static_cast<Vector<unsigned char>&>(LC),
             ((n-1)/rBL.BondNumber()+1));
    allocate(LC.property,1);
    LC.Length()=n;
  }

}
  
#endif

