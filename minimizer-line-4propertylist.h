
#ifndef _Minimizer_Line_For_PropertyList_H_
#define _Minimizer_Line_For_PropertyList_H_

#include "minimizer-line-base.h"
#include "minimizer-base-4propertylist.h"
#include <cmath>

namespace std {

  template <template <typename> class ListType,
            typename DistEvalObj, typename GeomType, uint bMode>
  class LineMinimizerBase4PropertyList
    : public LineMinimizerBase<
                PropertyList<ListType>,
                MinimizerParameter4PropertyList<DistEvalObj,GeomType,bMode> >{
    public:
      typedef LineMinimizerBase4PropertyList<ListType,
                                             DistEvalObj,GeomType,bMode>
              Type;
      typedef MinimizerParameter4PropertyList<DistEvalObj,GeomType,bMode>
              ParamType;
      typedef LineMinimizerBase<PropertyList<ListType>,ParamType>
              ParentType;
      typedef typename ParentType::SpaceType  SpaceType;

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
      virtual 
      double MinStep(const SpaceType& Origin, const SpaceType& Dirc) {
        uint n=Origin.PropertyData.size();
        assert(n==Dirc.PropertyData.size());
        assert(n==this->pRunParam->Mask.PropertyData.size());
        double minStep=0.,tmd;
        for(uint i=0;i<n;++i) {
          if(this->pRunParam->Mask[i]==0)   continue;
          tmd=fabs(Origin[i]);
          tmd=(tmd<1.?Dirc[i]:Dirc[i]/tmd);
          minStep+=tmd*tmd;
        }
        minStep=sumABS(this->pRunParam->DMask.PropertyData)/minStep;
        return DRelDelta*sqrt(minStep);
      }
  };

}

#endif

