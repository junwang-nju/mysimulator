
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

      varVector<varVector<double> > Dirc;

      varVector<varVector<double> > OldMinG;

    public:

      void Import(const varVector<Property>& vProp, const DistEvalObj& DEval,
                  const ParamList& PList,
                  const varVector<IDList<DistEvalObj,GeomType> >& IDLS,
                  const GeomType& Geo, const double& E) {
        static_cast<ParentType*>(this)->Import(vProp,DEval,PList,IDLS,Geo,E);
        uint n=vProp.size();
        Dirc.allocate(n);
        OldMinG.allocate(n);
        for(uint i=0;i<n;++i) {
          Dirc[i].allocate(vProp[i].Coordinate.size());
          OldMinG[i].allocate(vProp[i].Coordinate.size());
        }
      }

      int Go(const uint& MaxIter=DefaultMaxIter) {
        this->MinGCount=0;
        uint n=Dirc.size();
        for(uint i=0;i<n;++i) Dirc[i]=0.;
        bool isSteep=true;
        double beta=0.;
        double fnorm2,tmd;
        fnorm2=0;
        for(uint i=0;i<n;++i) fnorm2+=normSQ(this->MinSys[i].Gradient);
        if(fnorm2<=0.)  return 1;
        double oldfnorm2;
        this->Step=this->MinScale/sqrt(fnorm2);
        uint mStatus=0;
        for(uint nEval=0;nEval<MaxIter;++nEval) {
          for(uint i=0;i<n;++i)
            Dirc[i].scaleshift(beta,-1.,this->MinSys[i].Gradient);
          if(this->MinPrj>0) {
            isSteep=true;
            beta=0.;
            --nEval;
            continue;
          }
          if(this->Step<=0) {
            tmd=0;
            for(uint i=0;i<n;++i) tmd+=normSQ(Dirc[i]);
            this->Step=this->MinScale/sqrt(tmd);
          }
          if(this->Step<MinimalStep4(this->MinSys,Dirc))  return 1;
          for(uint i=0;i<n;++i) OldMinG[i]=this->MinSys[i].Gradient;
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
          fnorm2=0.;
          tmd=0;
          for(uint i=0;i<n;++i) {
            fnorm2+=normSQ(this->MinSys[i].Gradient);
            tmd+=dot(this->MinSys[i].Gradient,OldMinG[i]);
          }
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

