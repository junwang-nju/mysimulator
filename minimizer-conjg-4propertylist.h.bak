
#ifndef _Minimizer_Conjugate_Gradient_For_PropertyList_H_
#define _Minimizer_Conjugate_Gradient_For_PropertyList_H_

#include "minimizer-conjg-base.h"

namespace std {
  
  template <template <typename> class ListType,
            typename DistEvalObj, typename GeomType, uint bMode,
            uint CondType,
            template <template <typename> class,typename,typename,uint,uint>
            class LineMinMethod>
  class ConjugateGradientMinimizer4PropertyList
    : public ConjugateGradientMinimizerBase<
                LineMinMethod<ListType,DistEvalObj,GeomType,bMode,CondType> >{
    public:
      typedef ConjugateGradientMinimizer4PropertyList<
                  ListType,DistEvalObj,GeomType,bMode,CondType,
                  LineMinMethod>
              Type;
      typedef ConjugateGradientMinimizerBase<
                  LineMinMethod<ListType,DistEvalObj,GeomType,bMode,CondType> >
              ParentType;
      typedef typename ParentType::ParamType    ParamType;
      
      ConjugateGradientMinimizer4PropertyList() : ParentType() {}
      ConjugateGradientMinimizer4PropertyList(const Type& CGM) {
        myError("copier for minimizer with conjugate gradient is disabled!");
      }
      virtual void ImportState(const PropertyList<ListType>& PCoor,
                               const ParamType& Prm) {
        ParentType::ParentType::ImportState(PCoor,Prm);
        uint n=PCoor.size();
        varVector<uint> offset(n),size(n);
        offset[0]=0;
        for(uint i=0;i<n-1;++i) {
          size[i]=PCoor[i].size();
          offset[i+1]=offset[i]+size[i];
        }
        size[n-1]=PCoor[n-1].size();
        this->Dirc.allocate(n);
        this->Dirc.BuildStructure(offset,size);
        this->OldMinGrad.allocate(n);
        this->OldMinGrad.BuildStructure(offset,size);
      }
  };
}

#endif
