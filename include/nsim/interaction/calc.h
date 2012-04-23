
#ifndef _Interaction_Calc_H_
#define _Interaction_Calc_H_

#include "interaction/func/interface.h"

namespace mysimulator {

  template <typename GT,typename T>
  void Calc(const InteractionFunc<GT,T>& F,const Array1D<Array1D<T> >& X,
            const Array1D<unsigned int>& ID,const Array1D<Unique64Bit>& P,
            InteractionBuffer<T>& Buf,const GT& Geo,T& E) {
    F.Energy(X,ID,P,Buf,Geo,E);
  }
  template <typename GT,typename T>
  void Calc(const InteractionFunc<GT,T>& F,const Array1D<Array1D<T> >& X,
            const Array1D<unsigned int>& ID,const Array1D<Unique64Bit>& P,
            InteractionBuffer<T>& Buf,const GT& Geo,Array1D<Array1D<T> >& G) {
    F.Gradient(X,ID,P,Buf,Geo,G);
  }
  template <typename GT,typename T>
  void Calc(const InteractionFunc<GT,T>& F,const Array1D<Array1D<T> >& X,
            const Array1D<unsigned int>& ID,const Array1D<Unique64Bit>& P,
            InteractionBuffer<T>& Buf,const GT& Geo,T& E,
            Array1D<Array1D<T> >& G) {
    F.Both(X,ID,P,Buf,Geo,E,G);
  }

  template <typename GT,typename T>
  void Calc(const InteractionFunc<GT,T>& F,const Array1D<Array1D<T> >& X,
            const Array1D<Array1D<unsigned int> >& ID,
            const Array1D<Unique64Bit>& P,Array1D<InteractionBuffer<T> >& Buf,
            const GT& Geo,T& E) {
    assert(ID.Size()==Buf.Size());
    for(unsigned int i=0;i<ID.Size();++i) Calc(F,X,ID[i],P,Buf[i],Geo,E);
  }
  template <typename GT,typename T>
  void Calc(const InteractionFunc<GT,T>& F,const Array1D<Array1D<T> >& X,
            const Array1D<Array1D<unsigned int> >& ID,
            const Array1D<Unique64Bit>& P,Array1D<InteractionBuffer<T> >& Buf,
            const GT& Geo,Array1D<Array1D<T> >& G) {
    assert(ID.Size()==Buf.Size());
    for(unsigned int i=0;i<ID.Size();++i) Calc(F,X,ID[i],P,Buf[i],Geo,G);
  }
  template <typename GT,typename T>
  void Calc(const InteractionFunc<GT,T>& F,const Array1D<Array1D<T> >& X,
            const Array1D<Array1D<unsigned int> >& ID,
            const Array1D<Unique64Bit>& P,Array1D<InteractionBuffer<T> >& Buf,
            const GT& Geo,T& E,Array1D<Array1D<T> >& G) {
    assert(ID.Size()==Buf.Size());
    for(unsigned int i=0;i<ID.Size();++i) Calc(F,X,ID[i],P,Buf[i],Geo,E,G);
  }

  template <typename GT,typename T>
  void Calc(const InteractionFunc<GT,T>& F,const Array1D<Array1D<T> >& X,
            const Array1D<Array1D<unsigned int> >& ID,
            const Array1D<Array1D<Unique64Bit> >& P,
            Array1D<InteractionBuffer<T> >& Buf,const GT& Geo,T& E) {
    assert((ID.Size()==Buf.Size())&&(ID.Size()==P.Size()));
    for(unsigned int i=0;i<ID.Size();++i) Calc(F,X,ID[i],P[i],Buf[i],Geo,E);
  }
  template <typename GT,typename T>
  void Calc(const InteractionFunc<GT,T>& F,const Array1D<Array1D<T> >& X,
            const Array1D<Array1D<unsigned int> >& ID,
            const Array1D<Array1D<Unique64Bit> >& P,
            Array1D<InteractionBuffer<T> >& Buf,const GT& Geo,
            Array1D<Array1D<T> >& G) {
    assert((ID.Size()==Buf.Size())&&(ID.Size()==P.Size()));
    for(unsigned int i=0;i<ID.Size();++i) Calc(F,X,ID[i],P[i],Buf[i],Geo,G);
  }
  template <typename GT,typename T>
  void Calc(const InteractionFunc<GT,T>& F,const Array1D<Array1D<T> >& X,
            const Array1D<Array1D<unsigned int> >& ID,
            const Array1D<Array1D<Unique64Bit> >& P,
            Array1D<InteractionBuffer<T> >& Buf,const GT& Geo, T& E,
            Array1D<Array1D<T> >& G) {
    assert((ID.Size()==Buf.Size())&&(ID.Size()==P.Size()));
    for(unsigned int i=0;i<ID.Size();++i) Calc(F,X,ID[i],P[i],Buf[i],Geo,E,G);
  }

  template <typename T,typename IDT,typename PT,typename GT,typename BT>
  void Calc(const Array1D<InteractionFunc<GT,T> >& F,
            const Array1D<Array1D<T> >& X,const IDT& ID,const PT& P,BT& Buf,
            const GT& Geo, T& E) {
    assert((F.Size()==ID.Size())&&(F.Size()==P.Size())&&(F.Size()==Buf.Size()));
    for(unsigned int i=0;i<F.Size();++i) Calc(F[i],X,ID[i],P[i],Buf[i],Geo,E);
  }
  template <typename T,typename IDT,typename PT,typename GT,typename BT>
  void Calc(const Array1D<InteractionFunc<GT,T> >& F,
            const Array1D<Array1D<T> >& X,const IDT& ID,const PT& P,BT& Buf,
            const GT& Geo, Array1D<Array1D<T> >& G) {
    assert((F.Size()==ID.Size())&&(F.Size()==P.Size())&&(F.Size()==Buf.Size()));
    for(unsigned int i=0;i<F.Size();++i) Calc(F[i],X,ID[i],P[i],Buf[i],Geo,G);
  }
  template <typename T,typename IDT,typename PT,typename GT,typename BT>
  void Calc(const Array1D<InteractionFunc<GT,T> >& F,
            const Array1D<Array1D<T> >& X,const IDT& ID,const PT& P,BT& Buf,
            const GT& Geo, T& E, Array1D<Array1D<T> >& G) {
    assert((F.Size()==ID.Size())&&(F.Size()==P.Size())&&(F.Size()==Buf.Size()));
    for(unsigned int i=0;i<F.Size();++i) Calc(F[i],X,ID[i],P[i],Buf[i],Geo,E,G);
  }

}

#endif

