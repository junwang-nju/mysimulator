
#ifndef _List_Shift_H_
#define _List_Shift_H_

#include "list/compare.h"
#include "vector/shift.h"

namespace mysimulator {

  template <typename T, typename fT, typename sT>
  void shift(List<T>& L, const fT& d, const List<sT>& sL) {
    assert(IsValid(L)&&IsValid(sL));
    unsigned int n=(L.ListSize()<sL.ListSize()?L.ListSize():sL.ListSize());
    for(unsigned int i=0;i<n;++i)   shift(L[i],d,sL[i]);
  }

  template <typename T, typename fT, typename sT>
  void shift(List<T>& L, const List<fT>& fL, const sT& d) { shift(L,d,fL); }

  template <typename T>
  void eshift(List<T>& L, const T& d, const List<T>& sL) {
    assert(IsSameStructure(L,sL));
    assert(IsValid(L)&&IsValid(sL));
    scale(static_cast<Vector<T>&>(L),d,static_cast<const Vector<T>&>(sL));
  }

  template <typename T, typename fT, typename sT>
  void shift(List<T>& L, const fT& d, const Vector<sT>& sV) {
    assert(IsValid(L)&&IsValid(sV));
    for(unsigned int i=0;i<L.ListSize();++i)  shift(L[i],d,sV);
  }

  template <typename T, typename fT, typename sT>
  void shift(List<T>& L, const Vector<fT>& fV, const sT& d) { shift(L,d,fV); }

  template <typename T, typename sT>
  void shift(List<T>& L, const sT& d) { shift(static_cast<Vector<T>&>(L),d); }

  template <typename T, typename sT>
  void shift(List<T>& L, const Vector<sT>& sV) { shift(L,iOne,sV); }

  template <typename T, typename sT>
  void shift(List<T>& L, const List<sT>& sV) { shift(L,iOne,sV); }

  template <typename T, typename sT>
  void eshift(List<T>& L, const List<sT>& sV) { eshift(L,iOne,sV); }

  template <typename T,typename dT,typename cT,typename fT,typename sT>
  void scaleshift(List<T>& L, const dT& d, const cT& cd,
                  const Vector<fT>& fV, const Vector<sT>& sV) {
    assert(IsValid(L)&&IsValid(fV)&&IsValid(sV));
    for(unsigned int i=0;i<L.ListSize();++i)  scaleshift(L[i],d,cd,fV,sV);
  }

  template <typename T,typename dT,typename cT,typename fT,typename sT>
  void scaleshift(List<T>& L, const dT& d, const cT& cd,
                  const List<fT>& fL, const Vector<sT>& sV) {
    assert(IsValid(L)&&IsValid(fL)&&IsValid(sV));
    unsigned int n=(L.ListSize()<fL.ListSize()?L.ListSize():fL.ListSize());
    for(unsigned int i=0;i<n;++i) scaleshift(L[i],d,cd,fL[i],sV);
  }

  template <typename T,typename dT,typename cT,typename fT,typename sT>
  void scaleshift(List<T>& L, const dT& d, const cT& cd,
                  const Vector<fT>& fV, const List<sT>& sL) {
    assert(IsValid(L)&&IsValid(fV)&&IsValid(sL));
    unsigned int n=(L.ListSize()<sL.ListSize()?L.ListSize():sL.ListSize());
    for(unsigned int i=0;i<n;++i) scaleshift(L[i],d,cd,fV,sL[i]);
  }

  template <typename T,typename dT,typename cT,typename fT,typename sT>
  void scaleshift(List<T>& L, const dT& d, const cT& cd,
                  const List<fT>& fL, const List<sT>& sL) {
    assert(IsValid(L)&&IsValid(fL)&&IsValid(sL));
    unsigned int n=(L.ListSize()<fL.ListSize()?L.ListSize():fL.ListSize());
    n=(n<sL.ListSize()?n:sL.ListSize());
    for(unsigned int i=0;i<n;++i) scaleshift(L[i],d,cd,fL[i],sL[i]);
  }

  template <typename T, typename dT, typename cT>
  void escalshift(List<T>& L, const dT& d, const cT& cd,
                  const List<T>& fL, const List<T>& sL) {
    assert(IsValid(L)&&IsValid(fL)&&IsValid(sL));
    assert(IsSameStructure(L,fL)&&IsSameStructure(L,sL));
    scaleshift(static_cast<Vector<T>&>(L),d,cd,
               static_cast<const Vector<T>&>(fL),
               static_cast<const Vector<T>&>(sL));
  }

  template <typename T, typename dT, typename fT, typename sT,
            template<typename> class VAType,template<typename> class VBType>
  void scaleshift(List<T>& L, const dT& d, const VAType<fT>& fv,
                  const VBType<sT>& sv) {
    scaleshift(L,d,cOne,fv,sv);
  }

  template <typename T, typename dT>
  void escaleshift(List<T>& L,const dT& d,const List<T>& fL,const List<T>& sL){
    assert(IsValid(L)&&IsValid(fL)&&IsValid(sL));
    assert(IsSameStructure(L,fL)&&IsSameStructure(L,sL));
    scaleshift(static_cast<Vector<T>&>(L),d,static_cast<const Vector<T>&>(fL),
               static_cast<const Vector<T>&>(sL));
  }

  template <typename T, typename dT, typename cT, typename sT,
            template<typename> class VType>
  void scaleshift(List<T>& L, const dT& d, const cT& cd,const VType<sT>& sv) {
    scale(L,d);
    shift(L,cd,sv);
  }

  template <typename T, typename dT, typename cT>
  void escaleshift(List<T>& L, const dT& d, const cT& cd, const List<T>& sL) {
    assert(IsValid(L)&&IsValid(sL));
    assert(IsSameStructure(L,sL));
    scaleshift(static_cast<Vector<T>&>(L),d,cd,
               static_cast<const Vector<T>&>(sL));
  }

  template <typename T,typename cT,typename fT,typename sT,
            template<typename> class VAType,template<typename> class VBType>
  void shift(List<T>& v, const cT& cd, const VAType<fT>& fv,
             const VBType<sT>& sv) {
    scaleshift(v,cOne,cd,fv,sv);
  }

  template <typename T,typename cT>
  void eshift(List<T>& L,const cT& cd, const List<T>& fL, const List<T>& sL) {
    assert(IsValid(L)&&IsValid(fL)&&IsValid(sL));
    assert(IsSameStructure(L,fL)&&IsSameStructure(L,sL));
    shift(static_cast<Vector<T>&>(L),cd,static_cast<const Vector<T>&>(fL),
          static_cast<const Vector<T>&>(sL));
  }

}

#endif

