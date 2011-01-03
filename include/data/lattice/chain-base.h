
#ifndef _Lattice_Chain_Base_H_
#define _Lattice_Chain_Base_H_

#include "data/lattice/bond-library.h"

namespace std {

  template <unsigned int LatType, unsigned int EmbedDim,
            unsigned int NbNumber, unsigned int BdNumber>
  struct LatticeChainBase : public Vector<char> {
    typedef LatticeChainBase<LatType,EmbedDim,NbNumber,BdNumber>  Type;
    typedef Vector<char>  ParentType;

    BondLib<LatType,EmbedDim,NbNumber,BdNumber> runLib;
    LatticeChainBase() : ParentType(), runLib() {}
    LatticeChainBase(const Type& LC) {
      myError("Cannot create lattice chain base");
    }
    Type& operator=(const Type& LC) {
      myError("Cannot copy lattice chain base");
      return *this;
    }
    ~LatticeChainBase() { release(*this); }
  };

  template <unsigned int LType, unsigned int EDim, unsigned int NNum,
            unsigned int BNum>
  bool IsAvailable(const LatticeChainBase<LType,EDim,NNum,BNum>& LC) {
    return IsAvailable(static_cast<const Vector<char>&>(LC))&&
           IsAvailable(LC.runLib);
  }

  template <unsigned int LType, unsigned int EDim, unsigned int NNum,
            unsigned int BNum>
  void release(LatticeChainBase<LType,EDim,NNum,BNum>& LC) {
    release(static_cast<Vector<char>&>(LC));
    release(LC.runLib);
  }

  template <unsigned int LT,unsigned int LD,unsigned int NN,unsigned int BN>
  void allocate(LatticeChainBase<LT,LD,NN,BN>& LC, const unsigned int n) {
    assert(n>0);
    allocate(static_cast<Vector<char>&>(LC),((n-1)/BN+1));
    load(LC.runLib);
  }
  
  template <unsigned int LT, unsigned int LD, unsigned int NN, unsigned int BN>
  void copy(LatticeChainBase<LT,LD,NN,BN>& LC,
            const LatticeChainBase<LT,LD,NN,BN>& cLC) {
    assert(IsAvailable(LC));
    assert(IsAvailable(cLC));
    copy(static_cast<Vector<char>&>(LC),static_cast<const Vector<char>&>(cLC));
  }

  template <unsigned int LT,unsigned int LD,unsigned int NN,unsigned int BN>
  void refer(LatticeChainBase<LT,LD,NN,BN>& LC,
             const LatticeChainBase<LT,LD,NN,BN>& rLC) {
    assert(IsAvailable(rLC));
    release(LC);
    refer(static_cast<Vector<char>&>(LC),static_cast<const Vector<char>&>(rLC));
    refer(LC.runLib,rLC.runLib);
  }

  template <unsigned int LatticeType, unsigned int LatticeDim>
  struct LatticeChain {
    typedef LatticeChain<LatticeType,LatticeDim>  Type;
    LatticeChain() { myError("The Chain is not available"); }
    LatticeChain(const Type& LC) { myError("The Chain is not available"); }
    Type& operator=(const Type& LC) {
      myError("The Chain is not available");
      return *this;
    }
  };
  
}

#endif

