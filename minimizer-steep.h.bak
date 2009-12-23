
#ifndef _Minimizer_Steepest_Descent_H_
#define _Minimizer_Steepest_Descent_H_

#include "minimizer-base.h"

namespace std {

  template <typename DistEvalObj, typename GeomType,
            template <typename,typename> class MinKern=CoarseMinimizerKern>
  class SteepestDescentMin : public MinKern<DistEvalObj,GeomType> {

    public:

      typedef SteepestDescentMin<DistEvalObj,GeomType,MinKern>  Type;

      typedef MinKern<DistEvalObj,GeomType>                     ParentType;

      static const uint DefaultMaxIter;

    private:

      varVector<double>   Dirc;

    public:

      void Import(const PropertyList& vProp, const DistEvalObj& DEval,
                  const ParamList& PList,
                  const varVector<IDList<DistEvalObj,GeomType> >& IDLS,
                  const GeomType& Geo, const double& E) {
        static_cast<ParentType*>(this)->Import(vProp,DEval,PList,IDLS,Geo,E);
        Dirc.allocate(vProp.gDProperty[gCoordinate].size());
      }

      int Go(const uint& MaxIter=DefaultMaxIter) {
        this->MinGCount=0;
        uint mStatus;
        double tmd;
        Dirc=this->MinSys.gDProperty[gGradient];
        Dirc*=-1.;
        tmd=normSQ(Dirc);
        if(tmd<=0)    return 1;
        this->MinPrj=-tmd;
        this->Step=this->MinScale/sqrt(tmd);
        mStatus=0;
        for(uint nEval=0;nEval<MaxIter;++nEval) {
          if(this->Step<=0)
            this->Step=this->MinScale/sqrt(tmd);
          if(this->Step<MinimalStep4(this->MinSys.gDProperty[gCoordinate],
                                     Dirc,this->MinSys.gIProperty[gMask]))
            return 1;
          mStatus=this->MinimizeAlongLine(Dirc);
          if(mStatus==2)    return  1;
          Dirc=this->MinSys.gDProperty[gGradient];
          Dirc*=-1.;
          tmd=normSQ(Dirc);
          this->MinPrj=-tmd;
        }
        return 0;
      }

  };

  template <typename DistEvalObj, typename GeomType,
            template <typename,typename> class MinKern>
  const uint SteepestDescentMin<DistEvalObj,GeomType,MinKern>::DefaultMaxIter
      =10000;

}

#endif

