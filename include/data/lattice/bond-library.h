
#ifndef _Bond_Library_H_
#define _Bond_Library_H_

#include "data/name/lattice-type.h"
#include "data/basic/property-list.h"
#include <fstream>

namespace std {

  template <unsigned int LatticeType, unsigned int LatticeDim>
  struct BondLib {
    static const unsigned int NeighborNumber;
    static const unsigned int BondNumber;
    static const unsigned int MotifNumber;
    PropertyList<unsigned int> BondMapper;
    PropertyList<int> BondDirectionMapper;

    typedef BondLib<LatticeType,LatticeDim> Type;

    BondLib() { myError("This Library is not available"); }
    BondLib(const Type& BL) { myError("This Library is not available"); }
    Type& operator=(const Type& BL) {
      myError("This Library is not available");
      return *this;
    }
    ~BondLib() { release(*this); }
  };
  
  template <unsigned int LT, unsigned int LD>
  const unsigned int BondLib<LT,LD>::NeighborNumber=0;
  template <unsigned int LT, unsigned int LD>
  const unsigned int BondLib<LT,LD>::BondNumber=0;
  template <unsigned int LT, unsigned int LD>
  const unsigned int BondLib<LT,LD>::MotifNumber=0;

  template <unsigned int LT, unsigned int LD>
  bool IsAvailable(const BondLib<LT,LD>& BL) {
    return IsAvailable(BL.BondMapper)&&IsAvailable(BL.BondDirectionMapper);
  }
  template <unsigned int LT, unsigned int LD>
  void release(BondLib<LT,LD>& BL) {
    release(BL.BondMapper);
    release(BL.BondDirectionMapper);
  }
  template <unsigned int LT, unsigned int LD>
  void allocate(BondLib<LT,LD>& BL) {
    Vector<unsigned int> sz(BondLib<LT,LD>::MotifNumber);
    copy(sz,BondLib<LT,LD>::BondNumber);
    allocate(BL.BondMapper,sz);
    copy(sz,LD*BondLib<LT,LD>::BondNumber);
    allocate(BL.BondDirectionMapper,sz);
  }
  template <unsigned int LT, unsigned int LD>
  void copy(BondLib<LT,LD>& BL, const BondLib<LT,LD>& cBL) {
    assert(IsAvailable(BL));
    assert(IsAvailable(cBL));
    copy(BL.BondMapper,cBL.BondMapper);
    copy(BL.BondDirectionMapper,cBL.BondDirectionMapper);
  }
  template <unsigned int LT, unsigned int LD>
  void refer(BondLib<LT,LD>& BL, const BondLib<LT,LD>& rBL) {
    assert(IsAvailable(rBL));
    release(BL);
    refer(BL.BondMapper,rBL.BondMapper);
    refer(BL.BondDirectionMapper,rBL.BondDirectionMapper);
  }

  template<>
  BondLib<SquareLattice,2>::BondLib() : BondMapper(), BondDirectionMapper() {}
  template<>
  BondLib<SquareLattice,2>::BondLib(const Type& BL) {
    myError("Cannot create Bond Library");
  }
  template <>
  BondLib<SquareLattice,2>&
  BondLib<SquareLattice,2>::operator=(const BondLib<SquareLattice,2>& B) {
    myError("Cannot copt Bond Library");
    return *this;
  }
  template <>
  const unsigned int BondLib<SquareLattice,2>::NeighborNumber=4;
  template <>
  const unsigned int BondLib<SquareLattice,2>::BondNumber=4;
  template <>
  const unsigned int BondLib<SquareLattice,2>::MotifNumber=100;

  BondLib<SquareLattice,2> BondLibSquare2D;
  
}

#endif

