
#ifndef _Lattice_MotifChain_Interface_H_
#define _Lattice_MotifChain_Interface_H_

#include "lattice/motif-library/interface.h"

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

      unsigned char bondID(const unsigned int& n) {
        assert(n<Len);
        unsigned int u=LatticeMotifLibrary<LSN,Dim>::MaxBondOfMotif;
        unsigned int I=n/u;
        unsigned int R=n%u;
        unsigned int NB=(I==NumMotifs-1?NumBondsLastMotif:u);
        assert(IsValid(LatticeMotifLibrary<LSN,Dim>::map));
        return LatticeMotifLibrary<LSN,Dim>::map[NB-1][SegMotif[I]].bond[R];
      }

      typename LatticeCoordinate<LSN,Dim>::Type&
      nodePosition(const unsigned int& n) {
        assert((n>0)&&(n<=Len));
        unsigned int u=LatticeMotifLibrary<LSN,Dim>::MaxBondOfMotif;
        unsigned int I=(n-1)/u;
        unsigned int R=(n-1)%u;
        unsigned int NB=(I==NumMotifs-1?NumBondsLastMotif:u);
        assert(IsValid(LatticeMotifLibrary<LSN,Dim>::map));
        return
        LatticeMotifLibrary<LSN,Dim>::map[NB-1][SegMotif[I]].coordinate[R];
      }

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

#endif

