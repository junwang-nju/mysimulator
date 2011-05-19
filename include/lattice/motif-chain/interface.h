
#ifndef _Lattice_Motif_Chain_Interface_H_
#define _Lattice_Motif_Chain_Interface_H_

#include "vector/interface.h"
#include "lattice/motif-chain/property-name.h"
#include "lattice/library/interface.h"

namespace mysimulator {

  template <LatticeShapeName LShape, unsigned int Dimension>
  struct LatticeMotifChain {

    typedef LatticeMotifChain<LShape,Dimension> Type;

    Vector<unsigned short>  motifID;
    Vector<unsigned int> property;

    LatticeMotifChain() : motifID(), property() {}
    LatticeMotifChain(const Type&) {
      Error("Copier of LatticeMotifChain Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for LatticeMotifChain Disabled!");
      return *this;
    }
    ~LatticeMotifChain() { clearData(); }

    void clearData() { release(motifID); release(property); }

    unsigned int& Length() { return property[LatMotifChainLength]; }
    const unsigned int& Length() const { return property[LatMotifChainLength]; }
    unsigned int& NumBondsInLastMotif() {
      return property[LatMotifChainNumResidualBonds];
    }
    const unsigned int& NumBondsInLastMotif() const {
      return property[LatMotifChainNumResidualBonds];
    }

    unsigned int bondID(const unsigned int n) {
      unsigned int u=LatticeLibrary<LShape,Dimension>::MaxBondOfMotif;
      unsigned int I=n/u,J=n%u;
      unsigned int NB=(I==Length()-1?C.NumBondsInLastMotif():u);
      assert(IsValid(LatticeLibrary<LShape,Dimension>::map));
      return LatticeLibrary<LShape,Dimension>::map[NB][motifID[I]].bond[J];
    }
    const Vector<int>& bond(const unsigned int n) {
      unsigned int u=LatticeLibrary<LShape,Dimension>::MaxBondOfMotif;
      unsigned int I=n/u,J=n%u;
      unsigned int NB=(I==Length()-1?C.NumBondsInLastMotif():u);
      assert(IsValid(LatticeLibrary<LShape,Dimension>::map));
      return
        LatticeLibrary<LShape,Dimension>::map[NB][motifID[I]].coordinate[J];
    }

    void _import(const Vector<unsigned int>& bond) {
      clearData();
      unsigned n=bond.size+1;
      unsigned int u=(n-2)/LatticeLibrary<LS,Dim>::MaxBondOfMotif+1;
      allocate(motifID,u);
      allocate(property,LatMotifChainNumberProperty);
      Length()=n;
      NumBondsInLastMotif()=(n-2)%LatticeLibrary<LS,Dim>::MaxBondOfMotif+1;
      bool flag;
      unsigned int nmotif;
      nmotif=LatticeLibrary<LShape,Dimension>::shiftLoc[u-1].size;
      nmotif=LatticeLibrary<LShape,Dimension>::shiftLoc[u-1][nmotif-1];
      for(unsigned int i=0,bid=0;i<u-1;++i,bid+=u) {
        for(unsigned int j=0;j<nmotif;++j) {
          flag=true;
          for(unsigned int k=0;k<u;++k)
            if(bond[bid+k]!=
               LatticeLibrary<LShape,Dimension>::map[u-1][j].bond[k]) {
              flag=false;
              break;
            }
          if(flag) {
            motifID[i]=static_cast<unsigned short>(j);
            break;
          }
        }
      }
      u=
      nmotif=LatticeLibrary<LShape,Dimension>::shiftLoc[u-1].size;
      nmotif=LatticeLibrary<LShape,Dimension>::shiftLoc[u-1][nmotif-1];
      for(unsigned int j=0,bid=bond.size-NumBondsInLastMotif();j<nmotif;++j) {
    }

  };

  template <LatticeShapeName LS, unsigned int Dim>
  bool IsValid(const LatticeMotifChain<LS,Dim>& C) {
    return IsValid(C.motifID)&&IsValid(C.property);
  }

  template <LatticeShapeName LS, unsigned int Dim>
  void release(LatticeMotifChain<LS,Dim>& C) { C. clearData(); }

}

#endif

