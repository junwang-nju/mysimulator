
#ifndef _Interaction_Calc_H_
#define _Interaction_Calc_H_

#include "interaction/func/generic/interface.h"
#include "interaction/geometry/interface.h"
#include "interaction/parameter/unit/interface.h"
#include "interaction/func/interface.h"
#include <iostream>

namespace mysimulator {

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(InteractionFuncGeneric<DBuffer,GeomType,T>& FG,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const InteractionParameterUnit& P, T& Energy) {
    FG.EFunc(X,P.idx.pdata,P.prm.pdata,IG.DB,IG.Geo,Energy,
             FG.tmvec.infra.pdata);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(InteractionFuncGeneric<DBuffer,GeomType,T>& FG,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const InteractionParameterUnit& P, Vector<T>* Gradient) {
    FG.GFunc(X,P.idx.pdata,P.prm.pdata,IG.DB,IG.Geo,Gradient,
             FG.tmvec.infra.pdata);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(InteractionFuncGeneric<DBuffer,GeomType,T>& FG,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const InteractionParameterUnit& P, T& Energy,Vector<T>* Gradient) {
    FG.BFunc(X,P.idx.pdata,P.prm.pdata,IG.DB,IG.Geo,Energy,Gradient,
             FG.tmvec.infra.pdata);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(InteractionFuncGeneric<DBuffer,GeomType,T>& FG,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const Vector<InteractionParameterUnit>& PS, T& Energy) {
    for(unsigned int i=0;i<PS.size;++i) Calc(FG,IG,X,PS[i],Energy);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(InteractionFuncGeneric<DBuffer,GeomType,T>& FG,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const Vector<InteractionParameterUnit>& PS, Vector<T>* Gradient) {
    for(unsigned int i=0;i<PS.size;++i) Calc(FG,IG,X,PS[i],Gradient);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(InteractionFuncGeneric<DBuffer,GeomType,T>& FG,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const Vector<InteractionParameterUnit>& PS,
            T& Energy, Vector<T>* Gradient) {
    for(unsigned int i=0;i<PS.size;++i) Calc(FG,IG,X,PS[i],Energy,Gradient);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(Vector<InteractionFuncGeneric<DBuffer,GeomType,T> >& FGS,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const Vector<InteractionParameterUnit>& PS, T& Energy) {
    unsigned int n=(FGS.size<PS.size?FGS.size:PS.size);
    for(unsigned int i=0;i<n;++i) Calc(FGS[i],IG,X,PS[i],Energy);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(Vector<InteractionFuncGeneric<DBuffer,GeomType,T> >& FGS,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const Vector<InteractionParameterUnit>& PS, Vector<T>* Gradient) {
    unsigned int n=(FGS.size<PS.size?FGS.size:PS.size);
    for(unsigned int i=0;i<n;++i) Calc(FGS[i],IG,X,PS[i],Gradient);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(Vector<InteractionFuncGeneric<DBuffer,GeomType,T> >& FGS,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const Vector<InteractionParameterUnit>& PS,
            T& Energy, Vector<T>* Gradient) {
    unsigned int n=(FGS.size<PS.size?FGS.size:PS.size);
    for(unsigned int i=0;i<n;++i) Calc(FGS[i],IG,X,PS[i],Energy,Gradient);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(Vector<InteractionFuncGeneric<DBuffer,GeomType,T> >& FGS,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const List<InteractionParameterUnit>& PL, T& Energy) {
    unsigned int n=(FGS.size<PL.ListSize()?FGS.size:PL.ListSize());
    for(unsigned int i=0;i<n;++i) Calc(FGS[i],IG,X,PL[i],Energy);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(Vector<InteractionFuncGeneric<DBuffer,GeomType,T> >& FGS,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const List<InteractionParameterUnit>& PL, Vector<T>* Gradient) {
    unsigned int n=(FGS.size<PL.ListSize()?FGS.size:PL.ListSize());
    for(unsigned int i=0;i<n;++i) Calc(FGS[i],IG,X,PL[i],Gradient);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(Vector<InteractionFuncGeneric<DBuffer,GeomType,T> >& FGS,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const List<InteractionParameterUnit>& PL,
            T& Energy, Vector<T>* Gradient) {
    unsigned int n=(FGS.size<PL.ListSize()?FGS.size:PL.ListSize());
    for(unsigned int i=0;i<n;++i) Calc(FGS[i],IG,X,PL[i],Energy,Gradient);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(Vector<InteractionFuncGeneric<DBuffer,GeomType,T> >& FGS,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const Vector<Vector<InteractionParameterUnit> >& PL, T& Energy) {
    unsigned int n=(FGS.size<PL.size?FGS.size:PL.size);
    for(unsigned int i=0;i<n;++i) Calc(FGS[i],IG,X,PL[i],Energy);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(Vector<InteractionFuncGeneric<DBuffer,GeomType,T> >& FGS,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const Vector<Vector<InteractionParameterUnit> >& PL,
            Vector<T>* Gradient) {
    unsigned int n=(FGS.size<PL.size?FGS.size:PL.size);
    for(unsigned int i=0;i<n;++i) Calc(FGS[i],IG,X,PL[i],Gradient);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(Vector<InteractionFuncGeneric<DBuffer,GeomType,T> >& FGS,
            InteractionGeometry<DBuffer,GeomType,T>& IG, const Vector<T>* X,
            const Vector<Vector<InteractionParameterUnit> >& PL,
            T& Energy, Vector<T>* Gradient) {
    unsigned int n=(FGS.size<PL.size?FGS.size:PL.size);
    for(unsigned int i=0;i<n;++i) Calc(FGS[i],IG,X,PL[i],Energy,Gradient);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType,
            typename IFType, typename IPType>
  void Calc(IFType& FG, InteractionGeometry<DBuffer,GeomType,T>& IG,
            const List<T>& X, const IPType& P, T& Energy) {
    Calc(FG,IG,X.infra.pdata,P,Energy);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType,
            typename IFType, typename IPType>
  void Calc(IFType& FG, InteractionGeometry<DBuffer,GeomType,T>& IG,
            const Vector<Vector<T> >& X, const IPType& P, T& Energy) {
    Calc(FG,IG,X.pdata,P,Energy);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType,
            typename IFType, typename IPType>
  void Calc(IFType& FG, InteractionGeometry<DBuffer,GeomType,T>& IG,
            const List<T>& X, const IPType& P, List<T>& Gradient) {
    Calc(FG,IG,X.infra.pdata,P,Gradient.infra.pdata);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType,
            typename IFType, typename IPType>
  void Calc(IFType& FG, InteractionGeometry<DBuffer,GeomType,T>& IG,
            const Vector<Vector<T> >& X, const IPType& P, List<T>& Gradient) {
    Calc(FG,IG,X.pdata,P,Gradient.infra.pdata);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType,
            typename IFType, typename IPType>
  void Calc(IFType& FG, InteractionGeometry<DBuffer,GeomType,T>& IG,
            const List<T>& X, const IPType& P, Vector<Vector<T> >& Gradient) {
    Calc(FG,IG,X.infra.pdata,P,Gradient.pdata);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType,
            typename IFType, typename IPType>
  void Calc(IFType& FG, InteractionGeometry<DBuffer,GeomType,T>& IG,
            const Vector<Vector<T> >& X, const IPType& P,
            Vector<Vector<T> >& Gradient) {
    Calc(FG,IG,X.pdata,P,Gradient.pdata);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType,
            typename IFType, typename IPType>
  void Calc(IFType& FG, InteractionGeometry<DBuffer,GeomType,T>& IG,
            const List<T>& X, const IPType& P, T& Energy, List<T>& Gradient) {
    Calc(FG,IG,X.infra.pdata,P,Energy,Gradient.infra.pdata);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType,
            typename IFType, typename IPType>
  void Calc(IFType& FG, InteractionGeometry<DBuffer,GeomType,T>& IG,
            const Vector<Vector<T> >& X, const IPType& P, T& Energy,
            List<T>& Gradient) {
    Calc(FG,IG,X.pdata,P,Energy,Gradient.infra.pdata);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType,
            typename IFType, typename IPType>
  void Calc(IFType& FG, InteractionGeometry<DBuffer,GeomType,T>& IG,
            const List<T>& X, const IPType& P, T& Energy,
            Vector<Vector<T> >& Gradient) {
    Calc(FG,IG,X.infra.pdata,P,Energy,Gradient.pdata);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType,
            typename IFType, typename IPType>
  void Calc(IFType& FG, InteractionGeometry<DBuffer,GeomType,T>& IG,
            const Vector<Vector<T> >& X, const IPType& P, T& Energy,
            Vector<Vector<T> >& Gradient) {
    Calc(FG,IG,X.pdata,P,Energy,Gradient.pdata);
  }

}

#endif

