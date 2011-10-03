
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
      Array1D<unsigned char> numMax,numMin;

      LatticeOutput()
        : Max(), Min(), RangeMax(), RangeMin(),
          posMax(), posMin(), numMax(), numMin() {}
      ~LatticeOutput() { clearData(); }

      void clearData() {
        release(Max); release(Min); release(RangeMax);  release(RangeMin);
        release(posMax); release(posMin); release(numMax);  release(numMin);
      }
      bool isvalid() const {
        return IsValid(Max)&&IsValid(Min)&&
               IsValid(RangeMax)&&IsValid(RangeMin)&&
               IsValid(posMax)&&IsValid(posMin)&&
               IsValid(numMax)&&IsValid(numMin);
      }

      void operator()(
          const Array1DContent<int>& Branch,
          const LatticeMesh<SquareLattice,Dim>& M,
          const Array1DContent<CoorType>& Pos) {
        fill(posMax,cMin);
        fill(posMin,cMax);
        fill(numMax,ucZero);
        fill(numMin,ucZero);
        char c;
        for(unsigned int i=0;i<Pos.size;++i)
        for(unsigned int k=0;k<Dim;++k) {
          c=Pos[i].c[k];
          if(posMax[k]<c) { posMax[k]=c; numMax[k]=1; }
          else if(posMax[k]==c)   numMax[k]++;
          if(posMin[k]>c) { posMin[k]=c; numMin[k]=1; }
          else if(posMin[k]==c)   numMin[k]++;
        }
        for(unsigned int i=0;i<Dim;++i) {
          RangeMax[i]=Max[i]-1-posMax[i];
          RangeMin[i]=Min[i]+1-posMin[i];
        }
        COut<<Branch<<"\t"<<RangeMax<<"\t"<<RangeMin<<Endl;
      }

    private:

      LatticeOutput(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

