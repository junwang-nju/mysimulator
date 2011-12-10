
#ifndef _Lattice_Output_Square_Box_Specification_H_
#define _Lattice_Output_Square_Box_Specification_H_

#include "lattice/output/interface.h"
#include "intrinsic-type/constant.h"
#include "array/1d/fill.h"

namespace mysimulator {

  template <unsigned int Dim>
  struct LatticeOutput<SquareLattice,Dim,BoxOutput> {

    public:

      typedef LatticeOutput<SquareLattice,Dim,BoxOutput>  Type;
      typedef typename LatticeNodeCoordinate<SquareLattice,Dim>::Type
              CoorType;

      Array1D<int>  Max,Min;
      Array1D<int>  RangeMax,RangeMin;
      Array1D<char> posMax,posMin;

      LatticeOutput()
        : Max(), Min(), RangeMax(), RangeMin(), posMax(), posMin() {}
      ~LatticeOutput() { clearData(); }

      void clearData() {
        release(Max); release(Min); release(RangeMax);  release(RangeMin);
        release(posMax); release(posMin);
      }
      bool isvalid() const {
        return IsValid(Max)&&IsValid(Min)&&
               IsValid(RangeMax)&&IsValid(RangeMin)&&
               IsValid(posMax)&&IsValid(posMin);
      }

      void operator()(
          const Array1DContent<int>& Branch,
          const LatticeMesh<SquareLattice,Dim>& M,
          const Array1DContent<CoorType>& Pos) {
        fill(posMax,cMin);
        fill(posMin,cMax);
        char c;
        for(unsigned int i=0;i<Pos.size;++i)
        for(unsigned int k=0;k<Dim;++k) {
          c=Pos[i].c[k];
          if(posMax[k]<c)   posMax[k]=c;
          if(posMin[k]>c)   posMin[k]=c;
        }
        for(unsigned int i=0;i<Dim;++i) {
          RangeMax[i]=Max[i]-1-posMax[i];
          RangeMin[i]=Min[i]+1-posMin[i];
        }
      }

    private:

      LatticeOutput(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

