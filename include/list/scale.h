
#ifndef _List_Scale_H_
#define _List_Scale_H_

#include "list/interface.h"
#include "vector/scale.h"

namespace mysimulator {

  template <typename T, typename sT>
  void scale(List<T>& L, const sT& d) { scale(static_cast<Vector<T>&>(L),d); }

  template <typename T, typename sT>
  void scale(List<T>& L, const Vector<sT>& sV) {
    for(unsigned int i=0;i<L.ListSize();++i)  scale<T,sT>(L[i],sV);
  }

  template <typename T, typename sT>
  void scale(List<T>& L, const List<sT>& sL) {
    unsigned int n=(L.ListSize()<sL.ListSize()?L.ListSize():sL.ListSize());
    for(unsigned int i=0;i<n;++i) scale<T,sT>(L[i],sL[i]);
  }

  template <typename T, typename sT, typename dT>
  void scale(List<T>& L, const sT& d, const Vector<dT>& v) {
    scale(L,d);
    scale(L,v);
  }

  template <typename T, typename sT, typename dT>
  void scale(List<T>& L, const sT& d, const List<dT>& dL) {
    scale(L,d);
    scale(L,dL);
  }

  template <typename T, typename sT, typename dT>
  void scale(List<T>& L, const Vector<sT>& sV, const dT& d) { scale(L,d,sV); }

  template <typename T, typename sT, typename dT>
  void scale(List<T>& L, const Vector<sT>& sV, const Vector<dT>& dV) {
    scale(L,sV);
    scale(L,dV);
  }

  template <typename T, typename sT, typename dT>
  void scale(List<T>& L, const Vector<sT>& sV, const List<dT>& dL) {
    scale(L,sV);
    scale(L,dL);
  }

  template <typename T, typename sT, typename dT>
  void scale(List<T>& L, const List<sT>& sL, const dT& d) { scale(L,d,sL); }

  template <typename T, typename sT, typename dT>
  void scale(List<T>& L, const List<sT>& sL, const Vector<dT>& dV) {
    scale(L,dV,sL);
  }

  template <typename T, typename sT, typename dT>
  void scale(List<T>& L, const List<sT>& sL, const List<dT>& dL) {
    scale(L,sL);
    scale(L,dL);
  }

}

#endif

