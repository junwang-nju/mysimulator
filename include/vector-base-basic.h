
#ifndef _Vector_Base_Basic_H_
#define _Vector_Base_Basic_H_

#include "error-proc.h"
#include "constant.h"
#include "vector-impl.h"
#include <cassert>

namespace std {

  template <typename T>
  class VectorBaseBasic {

    protected:

      T* Data;

      unsigned int nData;

      T* headPtr;

      T* tailPtr;

    public:

      typedef T   DataType;

      typedef VectorBaseBasic<T>  Type;

      static const bool IsVector;

      VectorBaseBasic()
        : Data(NULL), nData(0), headPtr(NULL), tailPtr(NULL) {}

      VectorBaseBasic(const Type& V) {
        myError("Cannot create from VectorBaseBasic");
      }

      virtual ~VectorBaseBasic() { clear(); }

      Type& operator=(const Type& V) { assign(V); return *this; }

      Type& operator=(const T& V) { assign(V); return *this; }

      T*& data() { return Data; }

      const T* data() const { return Data; }

      const T* begin() const { return headPtr; }

      const T* end() const { return tailPtr; }

      const unsigned int& size() const { return nData; }

      T& operator[](const unsigned int& I) {
        assert(I<nData);
        return *(Data+I);
      }

      const T& operator[](const unsigned int& I) const {
        assert(I<nData);
        return *(Data+I);
      }

      void clear() { Data=NULL;  nData=uZero;  headPtr=NULL; tailPtr=NULL; }

      void SetSize(const unsigned int N) { nData=N; }

      void SetHeadTail() { headPtr=Data; tailPtr=Data+nData; }

      const bool IsAvailable() const { return Data!=NULL; }

      void assign(const Type& V) {
        long n=(nData<V.nData?nData:V.nData);
        assign(V,n);
      }

      void assign(const T& value) { assign(value,nData); }

      void assign(const Type& V, long ncopy, int voff=iZero, long vstep=lOne,
                                             int off=iZero, long step=lOne) {
        assert(this->IsAvailable());
        assert(static_cast<unsigned int>(off+step*ncopy)<=nData);
        assert(static_cast<unsigned int>(voff+vstep*ncopy)<=V.nData);
        vector_assign(Data,V.Data,ncopy,voff,vstep,off,step);
      }

      void assign(const T& value, long ncopy, int off=iZero, long step=lOne) {
        assert(this->IsAvailable());
        assert(static_cast<unsigned int>(off+step*ncopy)<=nData);
        vector_assign(Data,&value,ncopy,iZero,lZero,off,step);
      }

      void exchange(Type& V) {
        long n=(nData<V.nData?nData:nData);
        exchange(V,n);
      }

      void exchange(Type& V, long nex, int voff=iZero, long vstep=lOne,
                                       int off=iZero, long step=lOne) {
        assert(this->IsAvailable());
        assert(static_cast<unsigned int>(voff+vstep*nex)<=V.nData);
        assert(static_cast<unsigned int>(off+step*nex)<=nData);
        vector_exchange(Data,V.Data,nex,voff,vstep,off,step);
      }

      virtual const char* type() const = 0;

  };

  template <typename T>
  const bool VectorBaseBasic<T>::IsVector=true;

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

#endif

