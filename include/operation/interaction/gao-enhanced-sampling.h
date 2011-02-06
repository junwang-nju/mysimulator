
#ifndef _Interaction_Gao_Enhanced_Sampling_H_
#define _Interaction_Gao_Enhanced_Sampling_H_

#include "data/basic/unique-parameter.h"

namespace std {
  
  template <typename PType, typename IType, typename T>
  void EFuncGaoES(
      const Vector<T>* X, IType& I, PType& P, 
      const UniqueParameter* MP, T& Energy, Vector<T>* tmvec=NULL) {
    T U=0.;
    CalcInteraction(I,X,P,U);
    Vector<T>& lnd=*reinterpret_cast<Vector<T>*>(MP[LnDensitySet].ptr);
    Vector<T>& b=*reinterpret_cast<Vector<T>*>(MP[BetaSet].ptr);
    Energy=lnd[0]-b[0]*U;
    for(unsigned int i=1;i<b.size;++i)
      Energy+=log1p(exp(lnd[i]-b[i]*U-Energy));
    Energy*=-MP[RunTemperature].value<T>();
  }

  template <typename PType, typename IType, typename T>
  void GFuncGaoES(
      const Vector<T>* X, IType& I, PType& P, 
      const UniqueParameter* MP, Vector<T>* Gradient, Vector<T>* tmvec=NULL) {
    T U=0.;
    CalcInteraction(I,X,P,U,Gradient);
    Vector<T>& lnd=*reinterpret_cast<Vector<T>*>(MP[LnDensitySet].ptr);
    Vector<T>& b=*reinterpret_cast<Vector<T>*>(MP[BetaSet].ptr);
    Vector<T>& lnbd=*reinterpret_cast<Vector<T>*>(MP[LnBetaDensitySet].ptr);
    T FU,FL,tmu;
    FU=lnbd[0]-b[0]*U;
    FL=lnd[0]-b[0]*U;
    for(unsigned int i=1;i<b.size;++i) {
      tmu=b[i]*U;
      FU+=log1p(exp(lnbd[i]-tmu-FU));
      FL+=log1p(exp(lnd[i]-tmu-FL));
    }
    unsigned int n=MP[GaoNumberAllUnits].u;
    tmu=exp(FU-FL)*MP[RunTemperature].value<T>();
    for(unsigned int i=0;i<n;++i)   scale(Gradient[i],tmu);
  }

  template <typename PType, typename IType, typename T>
  void BFuncGaoES(
      const Vector<T>* X, IType& I, PType& P, 
      const UniqueParameter* MP, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    T U=0.;
    CalcInteraction(I,X,P,U,Gradient);
    Vector<T>& lnd=*reinterpret_cast<Vector<T>*>(MP[LnDensitySet].ptr);
    Vector<T>& b=*reinterpret_cast<Vector<T>*>(MP[BetaSet].ptr);
    Vector<T>& lnbd=*reinterpret_cast<Vector<T>*>(MP[LnBetaDensitySet].ptr);
    T FU,FL,tmu;
    FU=lnbd[0]-b[0]*U;
    FL=lnd[0]-b[0]*U;
    for(unsigned int i=1;i<b.size;++i) {
      tmu=b[i]*U;
      FU+=log1p(exp(lnbd[i]-tmu-FU));
      FL+=log1p(exp(lnd[i]-tmu-FL));
    }
    tmu=exp(FL);
    Energy=-tmu*MP[RunTemperature].value<T>();
    unsigned int n=MP[GaoNumberAllUnits].u;
    tmu=exp(FU)/tmu*MP[RunTemperature].value<T>();
    for(unsigned int i=0;i<n;++i)   scale(Gradient[i],tmu);
  }

}

#endif
