
#ifndef _Interaction_Calc_H_
#define _Interaction_Calc_H_

#include "interaction/func/generic/interface.h"
#include "interaction/geometry/interface.h"
#include "interaction/parameter/unit/interface.h"
#include "interaction/func/interface.h"

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

}

#endif

