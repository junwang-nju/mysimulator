
#ifndef _Lattice_MotifChain_Interface_H_
#define _Lattice_MotifChain_Interface_H_

#include "lattice/motif-library/interface.h"

#define _GetElement(num,element) \
  assert(num<Len); \
  unsigned int u=LatticeMotifLibrary<LSN,Dim>::MaxBondOfMotif; \
  unsigned int I=num/u; \
  unsigned int R=num%u; \
  unsigned int NB=(I==NumMotifs-1?NumBondsLastMotif:u); \
  assert(IsValid(LatticeMotifLibrary<LSN,Dim>::map)); \
  return LatticeMotifLibrary<LSN,Dim>::map[NB-1][SegMotif[I]].element[R]

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int Len>
  struct LatticeMotifChain {

    public:

      typedef LatticeMotifChain<LSN,Dim,Len>  Type;

      static const unsigned int NumMotifs;
      static const unsigned int NumBondsLastMotif;

      Array1D<unsigned short> SegMotif;

      LatticeMotifChain() : SegMotif() {}
      ~LatticeMotifChain() { clearData(); }

      void clearData() { release(SegMotif); }
      bool isvalid() const { return IsValid(SegMotif); }

      unsigned char& bondID(const unsigned int& n) { _GetElement(n,bond); }
      const unsigned char&
      bondID(const unsigned int& n) const { _GetElement(n,bond); }

      typename LatticeCoordinate<LSN,Dim>::Type&
      nodePosition(const unsigned int& n) { _GetElement((n-1),coordinate); }

      const typename LatticeCoordinate<LSN,Dim>::Type&
      nodePosition(const unsigned int& n) const{ _GetElement((n-1),coordinate); }

    private:

      LatticeMotifChain(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int Len>
  const unsigned int LatticeMotifChain<LSN,Dim,Len>::NumMotifs=
    (Len==1?0:(Len-2)/LatticeMotifLibrary<LSN,Dim>::MaxBondOfMotif+1);

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int Len>
  const unsigned int LatticeMotifChain<LSN,Dim,Len>::NumBondsLastMotif=
    (Len==1?0:(Len-2)%LatticeMotifLibrary<LSN,Dim>::MaxBondOfMotif+1);

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int L>
  bool IsValid(const LatticeMotifChain<LSN,Dim,L>& C) { return C.isvalid(); }

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int L>
  void release(LatticeMotifChain<LSN,Dim,L>& C) { C.clearData(); }

}

#undef _GetElement

#endif

