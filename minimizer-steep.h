
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

      varVector<varVector<double> >   Dirc;

    public:

      void Import(const varVector<Property>& vProp, const DistEvalObj& DEval,
                  const ParamList& PList,
                  const varVector<IDList<DistEvalObj,GeomType> >& IDLS,
                  const GeomType& Geo, const double& E) {
        static_cast<ParentType*>(this)->Import(vProp,DEval,PList,IDLS,Geo,E);
        uint n=vProp.size();
        Dirc.allocate(n);
        for(uint i=0;i<n;++i) Dirc[i].allocate(vProp[i].Coordinate.size());
      }

      int Go(const uint& MaxIter=DefaultMaxIter) {
        this->MinGCount=0;
        uint mStatus;
        double tmd;
        tmd=0;
        uint n=Dirc.size();
        for(uint i=0;i<n;++i) {
          Dirc[i]=this->MinSys[i].Gradient;
          Dirc[i].scale(-1.);
          tmd+=normSQ(Dirc[i]);
        }
        tmd=sqrt(tmd);
        if(tmd<=0)    return 1;
        this->MinPrj=-tmd*tmd;
        this->Step=this->MinScale/tmd;
        mStatus=0;
        for(uint nEval=0;nEval<MaxIter;++nEval) {
          if(this->Step<=0) {
            tmd=0.;
            for(uint i=0;i<n;++i)   tmd+=normSQ(Dirc[i]);
            this->Step=this->MinScale/sqrt(tmd);
          }
          if(this->Step<MinimalStep4(this->MinSys,Dirc))  return 1;
          mStatus=this->MinimizeAlongLine(Dirc);
          if(mStatus==2)    return  1;
          tmd=0.;
          for(uint i=0;i<n;++i) {
            Dirc[i]=this->MinSys[i].Gradient;
            Dirc[i].scale(-1.);
            tmd+=normSQ(Dirc[i]);
          }
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

