
#ifndef _Lattice_Chain_Interface_H_
#define _Lattice_Chain_Interface_H_

#include "vector/interface.h"
#include "lattice/chain/property-name.h"
#include "lattice/type-name.h"

namespace mysimulator {

  template <LatticeTypeName LatType, unsigned int Dim>
  struct LatticeChain : public Vector<unsigned short> {

    typedef LatticeChain<LatType,Dim>   Type;
    typedef Vector<unsigned short>      ParentType;

    Vector<unsigned int> property;

    LatticeChain() : ParentType(), property() {}
    LatticeChain(const Type&) { Error("Copier of LatticeChain Disabled!"); }
    Type& operator=(const Type& C) {
      Error("Operator= for LatticeChain Disabled!");
      return *this;
    }
    ~LatticeChain() { clearData(); }

    void clearData() {
      static_cast<ParentType*>(this)->clearData();
      release(property);
    }
    unsigned int& Length() { return property[LatticeChainLength]; }
    const unsigned int& Length() const { return property[LatticeChainLength]; }
    unsigned int& NumMotifs() { return property[LatticeNumberMotifs]; }
    const unsigned int& NumMotifs() const {
      return property[LatticeNumberMotifs];
    }

  };

  template <LatticeTypeName LT, unsigned int Dim>
  bool IsValid(const LatticeChain<LT,Dim>& C) {
    return IsValid(static_cast<const Vector<unsigned short>&>(C))&&
           Isvalid(C.property);
  }

  template <LatticeTypeName LT, unsigned int Dim>
  void release(LatticeChain<LT,Dim>& C) { C.clearData(); }

}

#endif

