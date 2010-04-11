
#ifndef _Minimizer_Line_Tracking_For_PropertyList_H_
#define _Minimizer_Line_Tracking_For_PropertyList_H_

#include "minimizer-line-4propertylist.h"
#include "minimizer-line-tracking.h"

namespace std {
  template <template <typename> class ListType,
            typename DistEvalObj, typename GeomType, uint bMode,
            uint CondType>
  class TrackingLineMinimizer4PropertyList
    : public TrackingLineMinimizer<
                LineMinimizerBase4PropertyList<ListType,
                                               DistEvalObj,GeomType,bMode>,
                CondType> {
    public:
      typedef TrackingLineMinimizer4PropertyList<ListType,DistEvalObj,
                                                 GeomType,bMode,CondType>
              Type;
      typedef TrackingLineMinimizer<
                 LineMinimizerBase4PropertyList<ListType,
                                                DistEvalObj,GeomType,bMode>,
                 CondType>
              ParentType;
      typedef typename ParentType::ParentType::ParamType    ParamType;
      TrackingLineMinimizer4PropertyList() : ParentType() {}
      TrackingLineMinimizer4PropertyList(const Type& BLM) {
        myError("copier for tracking is disabled!");
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
        this->RunCoor.allocate(n);
        this->RunCoor.BuildStructure(offset,size);
        this->RunGrad.allocate(n);
        this->RunGrad.BuildStructure(offset,size);
      }
  };

}

#endif

