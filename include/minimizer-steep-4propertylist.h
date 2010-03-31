
#ifndef _Minimizer_SteepestDescent_For_PropertyList_H_
#define _Minimizer_SteepestDescent_For_PropertyList_H_

#include "minimizer-steep-base.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            unsigned int CondType,
            template <template <template <typename> class> class,
                      template <template <typename> class> class, unsigned int>
            class LineMinMethod>
  class SteepestDescentMinimizer4PropertyList
    : public SteepestDescentMinimizerBase<
                LineMinMethod<DistEvalMethod,GeomType,CondType> > {

    public:

      typedef SteepestDescentMinimizer4PropertyList<DistEvalMethod,GeomType,
                                                    CondType,LineMinMethod>
              Type;
      typedef LineMinMethod<DistEvalMethod,GeomType,CondType>
              LineMinType;
      typedef SteepestDescentMinimizerBase<LineMinType> ParentType;
      typedef typename ParentType::ParamType  ParamType;

      SteepestDescentMinimizer4PropertyList() : ParentType() {}

      SteepestDescentMinimizer4PropertyList(const Type& SDM4P) {
        myError("Cannot create from steep-descent minimizer of property list");
      }

      Type& operator=(const Type& SDM4P) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(SDM4P));
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
          const VecTypeF<InteractionMethod<DistEvalMethod,GeomType> >& IMLst,
          const PropertyList<unsigned int,VecTypeI>& IdxLst) {
        static_cast<ParentType*>(this)->ImportState(Coor,Mask,dMask,DEval,Geo,
                                                    ParamLst,IMLst,IdxLst);
        varVector<unsigned int> Sz(Coor.size());
        for(unsigned int i=0;i<Coor.size();++i)   Sz[i]=Coor[i].size();
        this->Dirc.allocate(Sz);
      }

  };

}

#endif

