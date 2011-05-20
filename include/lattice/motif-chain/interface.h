
#ifndef _Lattice_Motif_Chain_Interface_H_
#define _Lattice_Motif_Chain_Interface_H_

#include "vector/interface.h"
#include "lattice/library/interface.h"

namespace mysimulator {

  template <LatticeShapeName LShape, unsigned int Dimen, unsigned int Length>
  struct LatticeMotifChain {

    typedef LatticeMotifChain<LShape,Dimen,Length>    Type;

    static const unsigned int NumMotifs;
    static const unsigned int NumBondsLastMotif;
    Vector<unsigned short> motifValue;

    LatticeMotifChain() : motifValue() {}
    LatticeMotifChain(const Type&) {
      Error("Copier of LatticeMotifChain Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for LatticeMotifChain Disabled!");
      return *this;
    }
    ~LatticeMotifChain() { clearData(); }

    void clearData() { release(motifValue); }

    unsigned int bondValue(const unsigned int n) {
      unsigned int u=LatticeLibrary<LShape,Dimen>::MaxBondOfMotif;
      unsigned int I=n/u;
      unsigned int J=n%u;
      unsigned int NB=(I==Length-1?NumBondsLastMotif:u);
      assert(IsValid(LatticeLibrary<LShape,Dimen>::map));
      return LatticeLibrary<LShape,Dimen>::map[NB][motifValue[I]].bond[J];
    }
    unsigned int bondVec(const unsigned int n) {
      unsigned int u=LatticeLibrary<LShape,Dimen>::MaxBondOfMotif;
      unsigned int I=n/u;
      unsigned int J=n%u;
      unsigned int NB=(I==Length-1?NumBondsLastMotif:u);
      assert(IsValid(LatticeLibrary<LShape,Dimen>::map));
      return LatticeLibrary<LShape,Dimen>::map[NB][motifValue[I]].coordinate[J];
    }

  };

  template <LatticeShapeName LS, unsigned int Dim, unsigned int L>
  const unsigned int LatticeMotifChain<LS,Dim,L>::NumMotifs=
      (L-2)/LatticeLibrary<L,Dim>::MaxBondOfMotif+1;

  template <LatticeShapeName LS, unsigned int Dim, unsigned int L>
  const unsigned int LatticeMotifChain<LS,Dim,L>::NumBondsLastMotif=
      (L-2)%LatticeLibrary<LS,Dim>::MaxBondOfMotif+1;

  template <LatticeShapeName LS, unsigned int Dim, unsigned int L>
  bool IsValid(const LatticeMotifChain<LS,Dim,L>& C) {
    return IsValid(C.motifValue);
  }

  template <LatticeShapeName LS, unsigned int Dim, unsigned int L>
  void release(LatticeMotifChain<LS,Dim,L>& C) { C.clearData(); }

}

#endif

