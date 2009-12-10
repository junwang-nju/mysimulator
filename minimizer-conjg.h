
#ifndef _Minimizer_Conjugate_Gradient_H_
#define _Minimizer_Conjugate_Gradient_H_

#include "minimizer-base.h"

namespace std {

  template <typename DistEvalObj, typename GeomType,
            template <typename,typename> class MinKern=CoarseMinimizerKern>
  class ConjGradientMin : public MinKern<DistEvalObj,GeomType> {

    public:

      typedef   ConjGradientMin<DistEvalObj,GeomType,MinKern>   Type;

      typedef   MinKern<DistEvalObj,GeomType>                   ParentType;

      static const uint DefaultMaxIter;

    private:

      varVector<double> Dirc;

      varVector<double> OldMinG;

    public:

      void Import(const PropertyList& vProp, const DistEvalObj& DEval,
                  const ParamList& PList,
                  const varVector<IDList<DistEvalObj,GeomType> >& IDLS,
                  const GeomType& Geo, const double& E) {
        static_cast<ParentType*>(this)->Import(vProp,DEval,PList,IDLS,Geo,E);
        uint n=vProp.gDProperty[gCoordinate].size();
        Dirc.allocate(n);
        OldMinG.allocate(n);
      }

      int Go(const uint& MaxIter=DefaultMaxIter) {
        this->MinGCount=0;
        Dirc=0.;
        bool isSteep=true;
        double beta=0.;
        double fnorm2,tmd;
        fnorm2=normSQ(this->MinSys.gDProperty[gGradient]);
        if(fnorm2<=0.)  return 1;
        double oldfnorm2;
        this->Step=this->MinScale/sqrt(fnorm2);
        uint mStatus=0;
        for(uint nEval=0;nEval<MaxIter;++nEval) {
          Dirc.scaleshift(beta,-1.,this->MinSys.gDProperty[gGradient]);
          if(this->MinPrj>0) {
            isSteep=true;
            beta=0.;
            --nEval;
            continue;
          }
          if(this->Step<=0) {
            tmd=normSQ(Dirc);
            this->Step=this->MinScale/sqrt(tmd);
          }
          if(this->Step<MinimalStep4(this->MinSys.gDProperty[gCoordinate],
                                     Dirc,this->MinSys.gIProperty[gMask]))
            return 1;
          OldMinG=this->MinSys.gDProperty[gGradient];
          mStatus=this->MinimizeAlongLine(Dirc);
          if(mStatus==2) {
            if(isSteep)   return 1;
            else {
              isSteep=true;
              beta=0.;
              continue;
            }
          }
          oldfnorm2=fnorm2;
          fnorm2=normSQ(this->MinSys.gDProperty[gGradient]);
          tmd=dot(this->MinSys.gDProperty[gGradient],OldMinG);
          beta=(fnorm2-tmd)/oldfnorm2;
          isSteep=false;
          if(fabs(beta)>5.0) {
            beta=0.;
            isSteep=true;
          }
        }
        return 0;
      }

  };

  template <typename DistEvalObj, typename GeomType,
            template <typename,typename> class MinKern>
  const uint ConjGradientMin<DistEvalObj,GeomType,MinKern>::DefaultMaxIter
      =1000;

}

#endif

