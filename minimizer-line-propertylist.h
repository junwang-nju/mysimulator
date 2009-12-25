
#ifndef _Minimizer_Line_PropertyList_H_
#define _Minimizer_Line_PropertyList_H_

#include "minimizer-line-base.h"
#include "minimizer-propertylist-base.h"

namespace std {

  template <typename DistEvalObj, typename GeomType, uint bMode,
            template <typename> class ListType>
  class LineMinimizerBase4PropertyList
    : public LineMinimizerBase<
                PropertyList<ListType>,
                Parameter4MinimizerPropertyList<DistEvalObj,GeomType,bMode> >{
    public:
      typedef LineMinimizerBase4PropertyList<DistEvalObj,GeomType,bMode,
                                             ListType>
              Type;
      typedef Parameter4MinimizerPropertyList<DistEvalObj,GeomType,bMode>
              ParamType;
      typedef LineMinimizerBase<PropertyList<ListType>,ParamType>
              ParentType;

      LineMinimizerBase4PropertyList() : ParentType() {
        this->ImportFunc(E_MinPropertyList,
                         G_MinPropertyList,
                         EG_MinPropertyList);
      }
      LineMinimizerBase4PropertyList(const Type& BP) {
        myError("copier for line minimizer is prohibited!");
      }
      virtual void ImportState(const PropertyList<ListType>& PCoor,
                               const ParamType& Prm) {
        uint n=PCoor.size();
        varVector<uint> offset(n),size(n);
        offset[0]=0;
        for(uint i=0;i<n-1;++i) {
          size[i]=PCoor[i].size();
          offset[i+1]=offset[i]+size[i];
        }
        this->MinCoor.allocate(n);
        this->MinCoor.BuildStructure(offset,size);
        this->MinGrad.allocate(n);
        this->MinGrad.BuildStructure(offset,size);
        this->MinCoor=PCoor;
        this->pRunParam=const_cast<ParamType*>(&Prm);
        this->MinY=0.;
        this->MinGrad=0.;
        this->BFunc(this->MinCoor,*(this->pRunParam),this->MinY,this->MinGrad);
      }
  };

  template <typename DistEvalObj, typename GeomType, uint bMode,
            template <typename> class ListType>
  class Backtracking4PropertyList
    : public LineMinimizerBase4PropertyList<DistEvalObj,GeomType,bMode,
                                            ListType> {
    public:
      typedef Backtracking4PropertyList<DistEvalObj,GeomType,bMode,ListType>
              Type;
      typedef LineMinimizerBase4PropertyList<DistEvalObj,GeomType,bMode,
                                             ListType>
              ParentType;

  };

}

#endif

