
#ifndef _Vector_Base_H_
#define _Vector_Base_H_

#include "vector-impl.cc"
#include <tr1/tuple>

namespace std {

  template <typename T>
  class VectorBase {

    protected:

      T* Data;

      uint nData;

      T* head_ptr;

      T* tail_ptr;

    public:

      typedef T               DataType;

      typedef VectorBase<T>   Type;

      static const uint IsVector;

      VectorBase() : Data(NULL), nData(0), head_ptr(NULL), tail_ptr(NULL) {}

      VectorBase(const Type&) { myError("vector copier is prohibited!"); }

      ~VectorBase() { clear(); }

      void clear() { Data=NULL; nData=0; head_ptr=NULL; tail_ptr=NULL; }

      void set_HeadTail() { head_ptr=Data; tail_ptr=Data+nData; }

      Type& operator=(const Type& vb) { assign(vb); }

      template <typename inputT>
      Type& operator*=(const inputT& v) { return scale(v); }

      template <typename inputT>
      Type& operator+=(const inputT& v) { return shift(v); }

      Type& assign(const T* v, long ncopy, int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*ncopy)<=nData);
        vector_assign(Data,v,ncopy,offset,voffset,step,vstep);
        return *this;
      }

      Type& assign(const Type& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*ncopy)<=v.nData);
        return assign(v.data(),ncopy,voffset,vstep,offset,step);
      }

      Type& assign(const Type& v) {
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

      Type& scale(const Type& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*nscale)<=v.nData);
        return scale(v.data(),nscale,voffset,vstep,offset,step);
      }

      Type& scale(const Type& v) {
        long n=(nData<v.nData?nData:v.nData);
        return scale(v,n);
      }

      template <typename vType>
      Type& scale(const pair<const T&,const vType&>& sp) {
        assert(vType::IsVector);
        return scale(sp.first).scale(sp.second);
      }

      template <typename vType>
      Type& scale(const pair<const Type&,const T&>& sp) {
        assert(vType::IsVector);
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

      Type& shift(const T& value, const Type& v, long nshift,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*nshift)<=v.nData);
        return shift(value,v.Data,nshift,
                     iZero,lZero,voffset,vstep,offset,step);
      }
      
      Type& shift(const T& value, const Type& v) {
        long n=(nData<v.nData?nData:v.nData);
        return shift(value,v,n);
      }
      
      template <typename vType>
      Type& shift(const pair<const T&,const vType&>& sp) {
        assert(vType::IsVector);
        return shift(sp.first,sp.second);
      }

      template <typename vType>
      Type& shift(const pair<const vType&,const T&>& sp) {
        assert(vType::IsVector);
        return shift(sp.second,sp.first);
      }

      Type& shift(const T& value) {
        return shift(value,&dOne,nData,iZero,lZero,iZero,lZero,iZero,lOne);
      }

      Type& shift(const Type& v) { return shift(dOne,v); }

      Type& shift(const Type& ShiftFv, const Type& v) {
        return scaleshift(dOne,dOne,ShiftFv,v);
      }

      template <typename vTypeA, typename vTypeB>
      Type& shift(const pair<const vTypeA&,const vTypeB&>& sp) {
        assert(vTypeA::IsVector);
        assert(vTypeB::IsVector);
        return shift(sp.first,sp.second);
      }

      Type& shift(const T& ShiftF, const Type& ShiftFv, const Type& v) {
        return scaleshift(dOne,ShiftF,ShiftFv,v);
      }

      template <typename vTypeA, typename vTypeB>
      Type& shift(const tr1::tuple<const T&,const vTypeA&,const vTypeB&>& st) {
        assert(vTypeA::IsVector);
        assert(vTypeB::IsVector);
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

      Type& scaleshift(const T& ScaleF, const T& ShiftF, const Type& ShiftFv,
                       const Type& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(sfoffset+sfstep*nscaleshift)<=ShiftFv.nData);
        assert(static_cast<uint>(voffset+vstep*nscaleshift)<=v.nData);
        return scaleshift(ScaleF,ShiftF,ShiftFv.Data,v.Data,nscaleshift,
                          sfoffset,sfstep,voffset,vstep,offset,step);
      }
      
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const Type& ShiftFv,
                       const Type& v) {
        long n;
        n=(nData<ShiftFv.nData?nData:ShiftFv.nData);
        n=(static_cast<uint>(n)<v.nData?n:v.nData);
        return scaleshift(ScaleF,ShiftF,ShiftFv,v,n);
      }

      Type& scaleshift(const T& ScaleF, const T& ShiftF, const Type& v,
                       long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        scale(ScaleF,nscaleshift,offset,step);
        return shift(ShiftF,v,nscaleshift,voffset,vstep,offset,step);
      }
      
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const Type& v) {
        long n=(nData<v.nData?nData:v.nData);
        return scaleshift(ScaleF,ShiftF,v,n);
      }

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

      Type& exchange(T* v, long nswap, int voffset=iZero, long vstep=lOne,
                     int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nswap)<=nData);
        vector_swap(Data,v,nswap,offset,voffset,step,vstep);
        return *this;
      }

      Type& exchange(Type& v, long nswap,
                     int voffset=iZero, long vstep=lOne,
                     int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*nswap)<=v.nData);
        return exchange(v.Data,nswap,voffset,vstep,offset,step);
      }

      Type& exchange(Type& v) {
        long n=(nData<v.nData?nData:v.nData);
        return exchange(v,n);
      }

      bool isAvailable() const { return Data!=NULL; }

      virtual const char* type() = 0;

  };

  template <typename T>
  void exchange(VectorBase<T>& va, VectorBase<T>& vb) {
    va.exchange(vb);
  }

  template <typename T>
  const uint VectorBase<T>::IsVector=1;

  template <typename T>
  ostream& operator<<(ostream& os, const VectorBase<T>& v) {
    uint n=v.size();
    assert(n>0);
    os<<v[0];
    for(uint i=1;i<n;++i) os<<"\t"<<v[i];
    return os;
  }

}

#endif

