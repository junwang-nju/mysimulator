
#ifndef _Minimizer_SteepestDescent_For_PropertyList_H_
#define _Minimizer_SteepestDescent_For_PropertyList_H_

#include "minimizer-steep-base.h"

namespace std {

  template <template <typename> class ListType,
            typename DistEvalObj, typename GeomType, uint bMode,
            uint CondType,
            template <template <typename> class,typename,typename,uint,uint>
            class LineMinMethod>
  class SteepestDescentMinimizer4PropertyList
    : public SteepestDescentMinimizerBase<
                LineMinMethod<ListType,DistEvalObj,GeomType,bMode,CondType> > {
    public:
      typedef SteepestDescentMinimizer4PropertyList<
                  ListType,DistEvalObj,GeomType,bMode,CondType,
                  LineMinMethod>
              Type;
      typedef SteepestDescentMinimizerBase<
                  LineMinMethod<ListType,DistEvalObj,GeomType,bMode,CondType> >
              ParentType;
      typedef typename ParentType::ParamType  ParamType;
      SteepestDescentMinimizer4PropertyList() : ParentType() {}
      SteepestDescentMinimizer4PropertyList(const Type& SDM) {
        myError("copier for minimizer with steep method is disabled!");
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
        this->Dirc.allocate(n);
        this->Dirc.BuildStructure(offset,size);
      }
  };

}

#endif
