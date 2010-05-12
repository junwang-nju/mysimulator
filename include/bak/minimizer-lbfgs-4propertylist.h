
#ifndef _Minimizer_LBFGS_For_PropertyList_H_
#define _Minimizer_LBFGS_For_PropertyList_H_

#include "minimizer-lbfgs-base.h"
#include "property-list.h"
#include "interaction-method.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            unsigned int CondType,
            template <template <template <typename> class> class,
                      template <template <typename> class> class, unsigned int>
            class LineMinMethod,
            unsigned int MaxCorr=6>
  class LBFGSbMinimizer4PropertyList
    : public LBFGSbMinimizerBase<
                LineMinMethod<DistEvalMethod,GeomType,CondType>,MaxCorr> {

    public:

      typedef LBFGSbMinimizer4PropertyList<DistEvalMethod,GeomType,CondType,
                                           LineMinMethod,MaxCorr>
              Type;
      typedef LineMinMethod<DistEvalMethod,GeomType,CondType>  LineMinType;
      typedef LBFGSbMinimizerBase<LineMinType,MaxCorr>  ParentType;
      typedef typename ParentType::ParamType  ParamType;

      LBFGSbMinimizer4PropertyList() : ParentType() {}

      LBFGSbMinimizer4PropertyList(const Type& LM) {
        myError("Cannot create from LBFGSb-type Minimizer");
      }

      Type& operator=(const Type& LM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(LM));
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
        this->Dirc.allocate(Sz);
        for(unsigned int i=0;i<MaxCorr;++i) {
          this->dX[i].allocate(Sz);
          this->dG[i].allocate(Sz);
        }
        this->lastX.allocate(Sz);
        this->lastG.allocate(Sz);
      }

  };
}

#endif

