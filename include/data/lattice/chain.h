
#ifndef _Lattice_Chain_Base_H_
#define _Lattice_Chain_Base_H_

#include "data/lattice/bond-library.h"

namespace std {

  template <unsigned int LatType, unsigned int EmbedDim>
  struct LatticeChain : public Vector<char> {
    typedef LatticeChain<LatType,EmbedDim>  Type;
    typedef Vector<char>  ParentType;

    LatticeChain() : ParentType() {}
    LatticeChain(const Type& LC) { myError("Cannot create lattice chain"); }
    Type& operator=(const Type& LC) {
      myError("Cannot copy lattice chain");
      return *this;
    }
    ~LatticeChain() { release(*this); }
  };

  template <unsigned int LType, unsigned int EDim>
  bool IsAvailable(const LatticeChain<LType,EDim>& LC) {
    return IsAvailable(static_cast<const Vector<char>&>(LC));
  }

  template <unsigned int LType, unsigned int EDim>
  void release(LatticeChain<LType,EDim>& LC) {
    release(static_cast<Vector<char>&>(LC));
  }

  template <unsigned int LT,unsigned int LD>
  void allocate(LatticeChain<LT,LD>& LC, const unsigned int n) {
    assert(n>0);
    allocate(static_cast<Vector<char>&>(LC),
             ((n-1)/BondLib<LT,LD>::BondNumber+1));
  }
  
  template <unsigned int LT, unsigned int LD>
  void copy(LatticeChain<LT,LD>& LC, const LatticeChain<LT,LD>& cLC) {
    assert(IsAvailable(LC));
    assert(IsAvailable(cLC));
    copy(static_cast<Vector<char>&>(LC),static_cast<const Vector<char>&>(cLC));
  }

  template <unsigned int LT,unsigned int LD>
  void refer(LatticeChain<LT,LD>& LC, const LatticeChain<LT,LD>& rLC) {
    assert(IsAvailable(rLC));
    release(LC);
    refer(static_cast<Vector<char>&>(LC),static_cast<const Vector<char>&>(rLC));
  }

}

#endif

