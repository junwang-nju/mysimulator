
#ifndef _Minimizer_Conjugate_Gradient_For_PropertyList_H_
#define _Minimizer_Conjugate_Gradient_For_PropertyList_H_

#include "minimizer-conjg-base.h"
#include "property-list.h"
#include "interaction-method.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            unsigned int CondType,
            template <template <template <typename> class> class,
                      template <template <typename> class> class, unsigned int>
            class LineMinMethod>
  class ConjugateGradientMinimizer4PropertyList
    : public ConjugateGradientMinimizerBase<
                LineMinMethod<DistEvalMethod,GeomType,CondType> > {

    public:

      typedef ConjugateGradientMinimizer4PropertyList<DistEvalMethod,GeomType,
                                                      CondType,LineMinMethod>
              Type;

      typedef LineMinMethod<DistEvalMethod,GeomType,CondType>
              LineMinType;

      typedef ConjugateGradientMinimizerBase<LineMinType>   ParentType;

      typedef typename ParentType::ParamType    ParamType;

      ConjugateGradientMinimizer4PropertyList() : ParentType() {}

      ConjugateGradientMinimizer4PropertyList(const Type& CGM) {
        myError("Cannot create from conjugate-gradient minimizer");
      }

      Type& operator=(const Type& CGM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(CGM));
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
        this->OldMinGrad.allocate(Sz);
      }

  };

}

#endif

