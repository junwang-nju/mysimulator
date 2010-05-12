
#ifndef _Minimizer_Line_Tracking_For_PropertyList_H_
#define _Minimizer_Line_Tracking_For_PropertyList_H_

#include "minimizer-line-base-4propertylist.h"
#include "minimizer-line-tracking.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            unsigned int CondType>
  class TrackingLineMinimizer4PropertyList
    : public TrackingLineMinimizer<
                LineMinmizerBase4PropertyList<DistEvalMethod,GeomType>,
                CondType> {

    public:

      typedef TrackingLineMinimizer4PropertyList<DistEvalMethod,GeomType,
                                                 CondType>
              Type;

      typedef TrackingLineMinimizer<
                LineMinmizerBase4PropertyList<DistEvalMethod,GeomType>,
                CondType>
              ParentType;

      typedef typename ParentType::ParamType  ParamType;

      TrackingLineMinimizer4PropertyList() : ParentType() {}

      TrackingLineMinimizer4PropertyList(const Type& TLM4P) {
        myError("Cannot create from tracking line minimizer of property list");
      }

      Type& operator=(const Type& TLM4P) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(TLM4P));
        return *this;
      }

      template <template <typename> class VecTypeC,
                template <typename> class VecTypeM,
                template <typename> class VecTypeMD,
                template <typename> class VecTypeD,
                template <typename> class VecTypeG,
                template <typename> class VecTypeP,
                template <typename> class VecTypeF,
                template <typename> class VecTypeI>
      void ImportState(
          const PropertyList<double,VecTypeC>& Coor,
          const PropertyList<unsigned int,VecTypeM>& Mask,
          const PropertyList<double,VecTypeMD>& dMask,
          const DistEvalMethod<VecTypeD>& DEval,
          const GeomType<VecTypeG>& Geo,
          const VecTypeP<refVector<double> >& ParamLst,
          VecTypeF<InteractionMethod<DistEvalMethod,GeomType> >& IMLst,
          const PropertyList<unsigned int,VecTypeI>& IdxLst) {
        static_cast<ParentType*>(this)->ImportState(Coor,Mask,dMask,DEval,Geo,
                                                    ParamLst,IMLst,IdxLst);
        varVector<unsigned int> Sz(Coor.size());
        for(unsigned int i=0;i<Coor.size();++i)   Sz[i]=Coor[i].size();
        this->RunCoor.allocate(Sz);
        this->RunGrad.allocate(Sz);
      }


  };

}

#endif

