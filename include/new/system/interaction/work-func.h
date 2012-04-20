
#ifndef _System_Interaction_Work_Function_H_
#define _System_Interaction_Work_Function_H_

#include "array/1d/interface.h"
#include "interaction/func/interface.h"
#include "interaction/calc.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT, typename BT,
            template<typename> class VT>
  void _EWorkSingle(
      const Array1DContent<InteractionFunc<GT,T> >& F, const VT<T>& X,
      const IDT& id, const PT& Prm, BT& Buf, const GT& Geo, T& E) {
    Calc(F[0],X,id,Prm,Geo,E);
  }

  template <typename T,typename IDT,typename PT,typename GT, typename BT,
            template<typename> class VT>
  void _EWorkArray(
      const Array1DContent<InteractionFunc<GT,T> >& F, const VT<T>& X,
      const IDT& id, const PT& Prm, BT& Buf, const GT& Geo, T& E) {
    Calc(F,X,id,Prm,Geo,E);
  }

  template <typename T,typename IDT,typename PT,typename GT, typename BT,
            template<typename> class VT>
  void _GWorkSingle(
      const Array1DContent<InteractionFunc<GT,T> >& F, const VT<T>& X,
      const IDT& id, const PT& Prm, BT& Buf, const GT& Geo, VT<T>& G) {
    Calc(F[0],X,id,Prm,Geo,G);
  }

  template <typename T,typename IDT,typename PT,typename GT, typename BT,
            template<typename> class VT>
  void _GWorkArray(
      const Array1DContent<InteractionFunc<GT,T> >& F, const VT<T>& X,
      const IDT& id, const PT& Prm, BT& Buf, const GT& Geo, VT<T>& G) {
    Calc(F,X,id,Prm,Geo,G);
  }

  template <typename T,typename IDT,typename PT,typename GT, typename BT,
            template<typename> class VT>
  void _BWorkSingle(
      const Array1DContent<InteractionFunc<GT,T> >& F,const VT<T>& X,
      const IDT& id, const PT& Prm, BT& Buf, const GT& Geo, T& E, VT<T>& G) {
    Calc(F[0],X,id,Prm,Geo,E,G);
  }

  template <typename T,typename IDT,typename PT,typename GT, typename BT,
            template<typename> class VT>
  void _BWorkArray(
      const Array1DContent<InteractionFunc<GT,T> >& F, const VT<T>& X,
      const IDT& id, const PT& Prm, BT& Buf, const GT& Geo, T& E, VT<T>& G) {
    Calc(F,X,id,Prm,Geo,E,G);
  }

}

#endif

