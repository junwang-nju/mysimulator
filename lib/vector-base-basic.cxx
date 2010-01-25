
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
  void VectorBaseBasic<T>::SetSize(const unsigned int& N) { nData=N; }

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
  void VectorBaseBasic<T>::assign(const VectorBaseBasic<T>& V) {
    long n=(nData<V.nData?nData:V.nData);
    assign(V,n);
  }

  template <typename T>
  void VectorBaseBasic<T>::assign(const T& value) {
    assign(value,nData);
  }

  template <typename T>
  void VectorBaseBasic<T>::assign(
      const VectorBaseBasic<T>& V, long ncopy, int voff, long vstep,
      int off, long step) {
    assert(this->IsAvailable());
    assert(static_cast<unsigned int>(off+step*ncopy)<=nData);
    assert(static_cast<unsigned int>(voff+vstep*ncopy)<=V.nData);
    vector_assign(Data,V.Data,ncopy,voff,vstep,off,step);
  }

  template <typename T>
  void VectorBaseBasic<T>::assign(
      const T& value, long ncopy, int off, long step) {
    assert(this->IsAvailable());
    assert(static_cast<unsigned int>(off+step*ncopy)<=nData);
    vector_assign(Data,&value,ncopy,iZero,lZero,off,step);
  }

  template <typename T>
  void VectorBaseBasic<T>::exchange(VectorBaseBasic<T>& V) {
    long n=(nData<V.nData?nData:nData);
    exchange(V,n);
  }

  template <typename T>
  void VectorBaseBasic<T>::exchange(
      VectorBaseBasic<T>& V, long nex, int voff, long vstep,
                                       int off, long step) {
    assert(this->IsAvailable());
    assert(static_cast<unsigned int>(voff+vstep*nex)<=V.nData);
    assert(static_cast<unsigned int>(off+step*nex)<=nData);
    vector_exchange(Data,V.Data,nex,voff,vstep,off,step);
  }

  template <typename T>
  void VectorBaseBasic<T>::swap(VectorBaseBasic<T>& V) {
    Data=V.Data;
    nData=V.nData;
    SetHeadTail();
    V.SetHeadTail();
  }

  template <typename T>
  istream& operator>>(istream& is, VectorBaseBasic<T>& V) {
    assert(V.IsAvailable());
    unsigned int n=V.size();
    for(unsigned int i=0;i<n;++i)   is>>V[i];
    return is;
  }

  template <typename T>
  ostream& operator<<(ostream& os, const VectorBaseBasic<T>& V) {
    assert(V.IsAvailable());
    unsigned int n=V.size();
    os<<V[0];
    for(unsigned int i=1;i<n;++i)   os<<"\t"<<V[i];
    return os;
  }

}

