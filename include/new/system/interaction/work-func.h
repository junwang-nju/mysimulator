
#ifndef _System_Interaction_Work_Function_H_
#define _System_Interaction_Work_Function_H_

#include "array/1d/interface.h"
#include "interaction/func/interface.h"
#include "interaction/calc.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _EWorkSingle(
      Array1D<InteractionFunc<GT,T> >& F, const VT<T>& X, const IDT& id,
      const PT& Prm, const GT& Geo, T& E) {
    Calc(F[0],X,id,Prm,Geo,E);
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _EWorkArray(
      Array1D<InteractionFunc<GT,T> >& F, const VT<T>& X, const IDT& id,
      const PT& Prm, const GT& Geo, T& E) {
    Calc(F,X,id,Prm,Geo,E);
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _GWorkSingle(
      Array1D<InteractionFunc<GT,T> >& F, const VT<T>& X, const IDT& id,
      const PT& Prm, const GT& Geo, VT<T>& G) {
    Calc(F[0],X,id,Prm,Geo,G);
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _GWorkArray(
      Array1D<InteractionFunc<GT,T> >& F, const VT<T>& X, const IDT& id,
      const PT& Prm, const GT& Geo, VT<T>& G) {
    Calc(F,X,id,Prm,Geo,G);
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _BWorkSingle(
      Array1D<InteractionFunc<GT,T> >& F,const VT<T>& X, const IDT& id,
      const PT& Prm, const GT& Geo, T& E, VT<T>& G) {
    Calc(F[0],X,id,Prm,Geo,E,G);
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _BWorkArray(
      Array1D<InteractionFunc<GT,T> >& F, const VT<T>& X, const IDT& id,
      const PT& Prm, const GT& Geo, T& E, VT<T>& G) {
    Calc(F,X,id,Prm,Geo,E,G);
  }

}

#endif

