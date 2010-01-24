
#include "vector-base-basic.h"
#include "vector-impl.h"
#include <cassert>

namespace std {

  template <typename T>
  T* VectorBaseBasic<T>::data() { return Data; }

  template <typename T>
  const T* VectorBaseBasic<T>::data() const { return Data; }

  template <typename T>
  const T* VectorBaseBasic<T>::begin() const { return headPtr; }

  template <typename T>
  const T* VectorBaseBasic<T>::end() const { return tailPtr; }

  template <typename T>
  const unsigned int& VectorBaseBasic<T>::size() const{ return nData; }

  template <typename T>
  T& VectorBaseBasic<T>::operator[](const unsigned int& I) {
    assert(I<nData);
    return *(Data+I);
  }

  template <typename T>
  const T& VectorBaseBasic<T>::operator[](const unsigned int& I) const{
    assert(I<nData);
    return *(Data+I);
  }

  template <typename T>
  void VectorBaseBasic<T>::clear() {
    Data=NULL;  nData=uZero;  headPtr=NULL; tailPtr=NULL;
  }

  template <typename T>
  void VectorBaseBasic<T>::SetHeadTail() {
    headPtr=Data;
    tailPtr=Data+nData;
  }

  template <typename T>
  const bool VectorBaseBasic<T>::IsAvailable() const {
    return Data!=NULL;
  }

  template <typename T>
  VectorBaseBasic<T>& VectorBaseBasic<T>::assign(
      const VectorBaseBasic<T>& V) {
    long n=(nData<V.nData?nData:V.nData);
    return assign(V,n);
  }

  template <typename T>
  VectorBaseBasic<T>& VectorBaseBasic<T>::assign(const T& value) {
    return assign(value,nData);
  }

  template <typename T>
  VectorBaseBasic<T>& VectorBaseBasic<T>::assign(
      const VectorBaseBasic<T>& V, long ncopy, int voff, long vstep,
      int off, long step) {
    assert(static_cast<unsigned int>(off+step*ncopy)<=nData);
    assert(static_cast<unsigned int>(voff+vstep*ncopy)<=V.nData);
    vector_assign(Data,v.Data,ncopy,voff,vstep,off,step);
    return *this;
  }

  template <typename T>
  VectorBaseBasic<T>& VectorBaseBasic<T>::assign(
      const T& value, long ncopy, int off, long step) {
    assert(static_cast<unsigned int>(off+step*ncopy)<nData);
    vector_assign(Data,&value,ncopy,iZero,lZero,off,step);
  }

  template <typename T>
  VectorBaseBasic<T>& VectorBaseBasic<T>::exchange(
      VectorBaseBasic<T>& V) {
    long n=(nData<V.nData?nData:nData);
    return exchange(V,n);
  }

  template <typename T>
  VectorBaseBasic<T>& VectorBaseBasic<T>::exchange(
      VectorBaseBasic<T>& V, long nex, int voff, long vstep,
                                       int off, long step) {
    assert(static_cast<unsigned int>(voff+vstep*nex)<V.nData);
    assert(static_cast<unsigned int>(off+step*nex)<nData);
    vector_exchange(Data,v.Data,nex,voff,vstep,off,step);
    return *this;
  }

}

