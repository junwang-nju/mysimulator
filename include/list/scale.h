
#ifndef _List_Scale_H_
#define _List_Scale_H_

#include "list/compare.h"
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

  template <typename T>
  void escale(List<T>& L, const List<T>& sL) {
    assert(IsSameStructure(L,sL));
    scale<T,T>(static_cast<Vector<T>&>(L),static_cast<const Vector<T>&>(sL));
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

  template <typename T>
  void escale(List<T>& L, const T& d, const List<T>& sL) {
    scale(L,d);
    escale(L,sL);
  }

  template <typename T, typename dT>
  void escale(List<T>& L, const List<T>& sL, const dT& d) { escale(L,d,sL); }

  template <typename T>
  void escale(List<T>& L, const List<T>& sL, const List<T>& dL) {
    escale(L,sL);
    escale(L,dL);
  }
}

#endif

