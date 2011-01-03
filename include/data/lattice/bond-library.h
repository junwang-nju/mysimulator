
#ifndef _Bond_Library_H_
#define _Bond_Library_H_

#include "data/name/lattice-type.h"
#include "data/basic/property-list.h"
#include <fstream>

namespace std {

  struct BondLibBase;
  void release(BondLibBase&);

  struct BondLibBase {
    PropertyList<unsigned int> BondMapper;
    PropertyList<int> BondDirectionMapper;

    BondLibBase() : BondMapper(), BondDirectionMapper() {}
    BondLibBase(const BondLibBase& BL) {
      myError("Cannot create Bond Library Base");
    }
    BondLibBase& operator=(const BondLibBase& BL) {
      myError("Cannot copy Bond Library Base");
      return *this;
    }
    ~BondLibBase() { release(*this); }
  };

  bool IsAvailable(const BondLibBase& BL) {
    return IsAvailable(BL.BondMapper)&&IsAvailable(BL.BondDirectionMapper);
  }
  
  void release(BondLibBase& BL) {
    release(BL.BondMapper);
    release(BL.BondDirectionMapper);
  }

  template <unsigned int LatticeType, unsigned int LatticeDim,
            unsigned int NeighborNumber, unsigned int BondNumber>
  struct BondLib : public BondLibBase {
    static const unsigned int MotifNumber;
    typedef BondLib<LatticeType,LatticeDim,NeighborNumber,BondNumber> Type;
    BondLib() { myError("This Library is not available"); }
    typedef BondLibBase ParentType;
    BondLib(const Type& BL) { myError("This Library is not available"); }
    Type& operator=(const Type& BL) {
      myError("This Library is not available");
      return *this;
    }
    ~BondLib() { release(*this); }
  };

  template <unsigned int LT, unsigned int LD, unsigned int NN, unsigned int BN>
  void release(BondLib<LT,LD,NN,BN>& BL) {
    release(static_cast<BondLibBase&>(BL));
  }
  template <unsigned int LT, unsigned int LD, unsigned int NN, unsigned int BN>
  void allocate(BondLib<LT,LD,NN,BN>& BL) {
    Vector<unsigned int> sz(BondLib<LT,LD,NN,BN>::MotifNumber);
    copy(sz,BN);
    allocate(BL.BondMapper,sz);
    copy(sz,LD*BN);
    allocate(BL.BondDirectionMapper,sz);
  }
  template <unsigned int LT, unsigned int LD, unsigned int NN, unsigned int BN>
  void copy(BondLib<LT,LD,NN,BN>& BL, const BondLib<LT,LD,NN,BN>& cBL) {
    assert(IsAvailable(BL));
    assert(IsAvailable(cBL));
    copy(BL.BondMapper,cBL.BondMapper);
    copy(BL.BondDirectionMapper,cBL.BondDirectionMapper);
  }
  template <unsigned int LT, unsigned int LD, unsigned int NN, unsigned int BN>
  void refer(BondLib<LT,LD,NN,BN>& BL, const BondLib<LT,LD,NN,BN>& rBL) {
    assert(IsAvailable(rBL));
    release(BL);
    refer(BL.BondMapper,rBL.BondMapper);
    refer(BL.BondDirectionMapper,rBL.BondDirectionMapper);
  }

  template<>
  BondLib<SquareLattice,2,4,4>::BondLib() : BondLibBase() {}
  template<>
  BondLib<SquareLattice,2,4,4>::BondLib(const Type& BL) {
    myError("Cannot create Bond Library");
  }
  template <>
  BondLib<SquareLattice,2,4,4>&
  BondLib<SquareLattice,2,4,4>::operator=(
      const BondLib<SquareLattice,2,4,4>& B) {
    myError("Cannot copt Bond Library");
    return (*this);
  }
  template <>
  const unsigned int BondLib<SquareLattice,2,4,4>::MotifNumber=100;

  BondLib<SquareLattice,2,4,4> BondLibSquare2D;
  
}

#endif

