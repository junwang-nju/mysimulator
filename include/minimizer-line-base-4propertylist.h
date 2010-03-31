
#ifndef _Minimizer_Line_For_PropertyList_H_
#define _Minimizer_Line_For_PropertyList_H_

#include "minimizer-line-base.h"
#include "minimizer-func-4propertylist.h"
#include "property-list.h"
#include "vector-op.h"
#include <cmath>

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  class LineMinmizerBase4PropertyList
    : public LineMinmizerBase<
                PropertyList<double,varVector>,
                MinimizerParameter4PropertyList<DistEvalMethod,GeomType> > {

    public:

      typedef LineMinmizerBase4PropertyList<DistEvalMethod,GeomType>
              Type;

      typedef MinimizerParameter4PropertyList<DistEvalMethod,GeomType>
              ParamType;

      typedef LineMinmizerBase<PropertyList<double,varVector>,ParamType>
              ParentType;

      typedef PropertyList<double,varVector>  RunSpaceVecType;

      LineMinmizerBase4PropertyList() : ParentType() {
        this->MinEFunc=EFunc_4PropertyList<DistEvalMethod,GeomType,varVector>;
        this->MinGFunc=GFunc_4PropertyList<DistEvalMethod,GeomType,varVector>;
        this->MinBFunc=BFunc_4PropertyList<DistEvalMethod,GeomType,varVector>;
      }

      LineMinmizerBase4PropertyList(const Type& LMB) {
        myError("Cannot create from Line Minimization Base for Property List");
      }

      ~LineMinmizerBase4PropertyList() {}

      Type& operator=(const Type& LMB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(LMB));
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
        varVector<unsigned int> Sz(Coor.size());
        for(unsigned int i=0;i<Coor.size();++i)   Sz[i]=Coor[i].size();
        this->MinCoorSeq.allocate(Sz);
        this->MinGradSeq.allocate(Sz);
        this->MinCoorSeq=Coor;
        this->MinParam.iMaskSeq.refer(Mask);
        this->MinParam.dMaskSeq.refer(dMask);
        this->MinParam.DEval.refer(DEval);
        this->MinParam.Geo.refer(Geo);
        this->MinParam.ParamLst.refer(ParamLst);
        this->MinParam.IMethodLst.refer(IMLst);
        this->MinParam.IdxLst.refer(IdxLst);
        this->MinParam.update();
        this->MinE=0.;
        this->MinGradSeq=0.;
        this->MinBFunc(this->MinCoorSeq,this->MinE,this->MinGradSeq,
                       this->MinParam);
      }

      double MinStep(const RunSpaceVecType& Orig,
                     const RunSpaceVecType& Dirc) {
        assert(Orig.size()==Dirc.size());
        assert(Orig.size()==this->MinParam.iMaskSeq.size());
        double minStep=0.,tmd;
        for(unsigned int i=0;i<Orig.size();++i)
        for(unsigned int j=0;j<Orig[i].size();++j) {
          if(this->MinParam.iMaskSeq[i][j]==0)  continue;
          tmd=fabs(Orig[i][j]);
          tmd=(tmd<1.?Dirc[i][j]:Dirc[i][j]/tmd);
          minStep+=tmd*tmd;
        }
        minStep=sumABS(this->MinParam.dMaskSeq)/minStep;
        return DRelDelta*sqrt(minStep);
      }

  };

}

#endif

