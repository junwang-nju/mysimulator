
#ifndef _Meta_Interaction_Calculation_H_
#define _Meta_Interaction_Calculation_H_

#include "data/interaction/meta-parameter.h"
#include "operation/interaction/calc.h"

namespace std {

  template <typename T,template<typename> class DBuff, typename GeomType,
            template <typename,template<typename> class,typename> class IType,
            typename PType>
  void CalcInteraction(
      IType<T,DBuff,GeomType>& F, const Vector<T>*X,
      InteractionMetaParameter<PType,IType<T,DBuff,GeomType>,T>& P, T& Energy) {
    P.EFunc(X,F,P.inprm,P.prm.data,Energy,P.tmvec.structure);
  }

  template <typename T,template<typename> class DBuff, typename GeomType,
            template <typename,template<typename> class,typename> class IType,
            typename PType>
  void CalcInteraction(
      IType<T,DBuff,GeomType>& F, const Vector<T>*X,
      InteractionMetaParameter<PType,IType<T,DBuff,GeomType>,T>& P,
      Vector<T>* Gradient) {
    P.GFunc(X,F,P.inprm,P.prm.data,Gradient,P.tmvec.structure);
  }

  template <typename T,template<typename> class DBuff, typename GeomType,
            template <typename,template<typename> class,typename> class IType,
            typename PType>
  void CalcInteraction(
      IType<T,DBuff,GeomType>& F, const Vector<T>*X,
      InteractionMetaParameter<PType,IType<T,DBuff,GeomType>,T>& P,
      T& Energy, Vector<T>* Gradient) {
    P.BFunc(X,F,P.inprm,P.prm.data,Energy,Gradient,P.tmvec.structure);
  }

  template <typename T,template<typename> class DBuff, typename GeomType,
            template <typename,template<typename> class,typename> class IType,
            typename PType>
  void CalcInteraction(
      IType<T,DBuff,GeomType>& F, const PropertyList<T>& X,
      InteractionMetaParameter<PType,IType<T,DBuff,GeomType>,T>& P, T& Energy){
    CalcInteraction(F,X.structure,P,Energy);
  }

  template <typename T,template<typename> class DBuff, typename GeomType,
            template <typename,template<typename> class,typename> class IType,
            typename PType>
  void CalcInteraction(
      IType<T,DBuff,GeomType>& F, const PropertyList<T>& X,
      InteractionMetaParameter<PType,IType<T,DBuff,GeomType>,T>& P,
      PropertyList<T>& Gradient){
    CalcInteraction(F,X.structure,P,Gradient.structure);
  }

  template <typename T,template<typename> class DBuff, typename GeomType,
            template <typename,template<typename> class,typename> class IType,
            typename PType>
  void CalcInteraction(
      IType<T,DBuff,GeomType>& F, const PropertyList<T>& X,
      InteractionMetaParameter<PType,IType<T,DBuff,GeomType>,T>& P,
      T& Energy,PropertyList<T>& Gradient){
    CalcInteraction(F,X.structure,P,Energy,Gradient.structure);
  }

}

#endif

