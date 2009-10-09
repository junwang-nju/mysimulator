
#ifndef _Variable_Vector_H_
#define _Variable_Vector_H_

#include "vector-impl.cc"
#include "memory.h"
#include <tr1/tuple>
#include <cstring>

namespace std {

  template <typename T, uint NT>
  class fixVector;

  template <typename T>
  class varVector {

    public:

      typedef T               DataType;

      typedef varVector<T>    Type;

      static const char*      TypeTag;

    private:

      T* Data;

      uint nData;

      T* head_ptr;

      T* tail_ptr;

    public:

      varVector() : Data(NULL), nData(0), head_ptr(NULL), tail_ptr(NULL) {}

      varVector(const uint& n) : nData(n) {
        assert(nData>0);
        Data=new T[nData];
        head_ptr=Data;
        tail_ptr=Data+nData;
      }

      varVector(const Type& v) { myError("vector copier is prohibited!"); }

      ~varVector() {  clear();  }

      void clear() {
        safe_delete(Data);
        nData=0;
        head_ptr=NULL;
        tail_ptr=NULL;
      }

      Type& allocate(const uint& n) {
        if(nData==n)  return *this;
        if(Data!=NULL) clear();
        nData=n;
        Data=new T[nData];
        head_ptr=Data;
        tail_ptr=head_ptr+nData;
        return *this;
      }

      Type& allocate(const int& n) { return allocate(static_cast<uint>(n)); }

      template <typename vType>
      Type& allocate(const vType& v) {
        assert(isVector<vType>());
        return allocate(v.nData);
      }

      template <typename vType>
      Type& Duplicate(const vType& v) { return allocate(v).assign(v); }

      Type& operator=(const Type& v) { return assign(v); }

      template <typename inputT>
      Type& operator=(const inputT& v) { return assign(v); }

      template <typename inputT>
      Type& operator*=(const inputT& v) { return scale(v); }
      
      template <typename inputT>
      Type& operator+=(const inputT& v) { return shift(v); }

      T* data() { return Data; }

      const T* data() const { return Data; }

      const T* begin() const { return head_ptr; }

      const T* end() const { return tail_ptr; }

      const uint& size() const { return nData; }

      T& operator[](const uint i) {
        assert(i<nData);
        return *(Data+i);
      }

      const T& operator[](const uint i) const {
        assert(i<nData);
        return *(Data+i);
      }

      Type& assign(const T* v, long ncopy, int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*ncopy)<=nData);
        vector_assign(Data,v,ncopy,offset,voffset,step,vstep);
        return *this;
      }

      template <typename vType>
      Type& assign(const vType& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        assert(isVector<vType>());
        assert(static_cast<uint>(voffset+vstep*ncopy)<=v.nData);
        assign(v.data(),ncopy,voffset,vstep,offset,step);
        return *this;
      }

      template <typename vType>
      Type& assign(const vType& v) {
        assert(isVector<vType>());
        long n=(nData<v.nData?nData:v.nData);
        return assign(v,n);
      }

      Type& assign(const T& value, long ncopy,
                   int offset=iZero, long step=lOne) {
        return assign(&value,ncopy,iZero,lZero,offset,step);
      }
      
      Type& assign(const T& value) { return assign(value,nData); }

      Type& scale(const T* v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nscale)<=nData);
        vector_scale(Data,v,nscale,offset,voffset,step,vstep);
        return *this;
      }

      Type& scale(const T& d, long nscale,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nscale)<=nData);
        vector_scale(Data,d,nscale,offset,iZero,step,lZero);
        return *this;
      }

      Type& scale(const T& d) { return scale(d,nData); }

      template <typename vType>
      Type& scale(const vType& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(isVector<vType>());
        assert(static_cast<uint>(voffset+vstep*nscale)<=v.nData);
        return scale(v.data(),nscale,voffset,vstep,offset,step);
      }

      template <typename vType>
      Type& scale(const vType& v) {
        assert(isVector<vType>());
        long n=(nData<v.nData?nData:v.nData);
        return scale(v,n);
      }

      template <typename vType>
      Type& scale(const pair<const T&,const vType&>& sp) {
        assert(isVector<vType>());
        return scale(sp.first).scale(sp.second);
      }

      template <typename vType>
      Type& scale(const pair<const vType&,const T&>& sp) {
        assert(isVector<vType>());
        return scale(sp.first).scale(sp.second);
      }

      template <typename ScaleT>
      Type& shift(const ScaleT& sv, const T* v, long nshift,
                  int soffset=iZero, long sstep=lOne,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nshift)<=nData);
        vector_shift(Data,sv,v,nshift,offset,soffset,voffset,step,sstep,vstep);
        return *this;
      }

      template <typename vType>
      Type& shift(const T& value, const vType& v, long nshift,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(isVector<vType>());
        assert(static_cast<uint>(voffset+vstep*nshift)<=v.nData);
        return shift(value,v.data(),nshift,
                     iZero,lZero,voffset,vstep,offset,step);
      }
      
      template <typename vType>
      Type& shift(const T& value, const vType& v) {
        assert(isVector<vType>());
        long n=(nData<v.nData?nData:v.nData);
        return shift(value,v,n);
      }
      
      template <typename vType>
      Type& shift(const pair<const T&,const vType&>& sp) {
        assert(isVector<vType>());
        return shift(sp.first,sp.second);
      }

      template <typename vType>
      Type& shift(const pair<const Type&,const T&>& sp) {
        assert(isVector<vType>());
        return shift(sp.second,sp.first);
      }

      Type& shift(const T& value) {
        return (value,&dOne,nData,iZero,lZero,iZero,lZero,iZero,lOne);
      }

      template <typename vType>
      Type& shift(const vType& v) {
        assert(isVector<vType>());
        return shift(dOne,v);
      }

      template <typename vTypeA, typename vTypeB>
      Type& shift(const vTypeA& ShiftFv, const vTypeB& v) {
        assert(isVector<vTypeA>()&&isVector<vTypeB>());
        return scaleshift(dOne,dOne,ShiftFv,v);
      }

      template <typename vTypeA, typename vTypeB>
      Type& shift(const pair<const vTypeA&,const vTypeB&>& sp) {
        return shift(sp.first,sp.second);
      }

      template <typename vTypeA, typename vTypeB>
      Type& shift(const T& ShiftF, const vTypeA& ShiftFv, const vTypeB& v) {
        assert(isVector<vTypeA>()&&isVector<vTypeB>());
        return scaleshift(dOne,ShiftF,ShiftFv,v);
      }

      template <typename vTypeA, typename vTypeB>
      Type& shift(const tr1::tuple<const T&,const vTypeA&,const vTypeB&>& st) {
        return shift(tr1::get<0>(st),tr1::get<1>(st),tr1::get<2>(st));
      }

      Type& scaleshift(const T& ScaleF, const T& ShiftF, const T* ShiftFv,
                       const T* v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nscaleshift)<=nData);
        vector_scaleshift(Data,ScaleF,ShiftF,ShiftFv,v,nscaleshift,
                          offset,sfoffset,voffset,step,sfstep,vstep);
        return *this;
      }

      template <typename vTypeA, typename vTypeB>
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const vTypeA& ShiftFv,
                       const vTypeB& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        assert(isVector<vTypeA>()&&isVector<vTypeB>());
        assert(static_cast<uint>(sfoffset+sfstep*nscaleshift)<=ShiftFv.nData);
        assert(static_cast<uint>(voffset+vstep*nscaleshift)<=v.nData);
        return scaleshift(ScaleF,ShiftF,ShiftFv.data(),v.data(),nscaleshift,
                          sfoffset,sfstep,voffset,vstep,offset,step);
      }
      
      template <typename vTypeA, typename vTypeB>
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const vTypeA& ShiftFv,
                       const vTypeB& v) {
        assert(isVector<vTypeA>()&&isVector<vTypeB>());
        long n;
        n=(nData<ShiftFv.nData?nData:ShiftFv.nData);
        n=(static_cast<uint>(n)<v.nData?n:v.nData);
        return scaleshift(ScaleF,ShiftF,ShiftFv,v,n);
      }

      template <typename vType>
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const vType& v,
                       long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        assert(isVector<vType>());
        scale(ScaleF,nscaleshift,offset,step);
        return shift(ShiftF,v,nscaleshift,voffset,vstep,offset,step);
      }
      
      template <typename vType>
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const vType& v) {
        long n=(nData<v.nData?nData:v.nData);
        return scaleshift(ScaleF,ShiftF,v,n);
      }

      Type& swap(Type& v) {
        T* tptr;
        uint tmn;
        tptr=Data;        Data=v.Data;          v.Data=tptr;
        tmn=nData;        nData=v.nData;        v.nData=tmn;
        tptr=head_ptr;    head_ptr=v.head_ptr;  v.head_ptr=tptr;
        tptr=tail_ptr;    tail_ptr=v.tail_ptr;  v.tail_ptr=tptr;
        return *this;
      }

      Type& swap_content(T* v, long nswap, int voffset=iZero, long vstep=lOne,
                         int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nswap)<=nData);
        vector_swap(Data,v,nswap,offset,voffset,step,vstep);
        return *this;
      }

      template <typename vType>
      Type& swap_content(vType& v, long nswap,
                         int voffset=iZero, long vstep=lOne,
                         int offset=iZero, long step=lOne) {
        assert(isVector<vType>());
        assert(static_cast<uint>(voffset+vstep*nswap)<=v.nData);
        return swap_content(v.data(),nswap,voffset,vstep,offset,step);
      }

      template <typename vType>
      Type& swap_content(vType& v) {
        assert(isVector<vType>());
        long n=(nData<v.nData?nData:v.nData);
        return swap_content(v,n);
      }

  };

  template <typename T>
  const char* varVector<T>::TypeTag="varVector";

  template <typename T>
  istream& operator>>(istream& is, varVector<T>& v) {
    uint n;
    is>>n;
    v.allocate(n);
    for(uint i=0;i<n;++i) is>>v[i];
    return is;
  }

  template <typename T>
  ostream& operator<<(ostream& os, const varVector<T>& v) {
    uint n=v.size();
    assert(n>0);
    os<<v[0];
    for(uint i=1;i<n;++i) os<<"\t"<<v[i];
    return os;
  }

}

#endif
