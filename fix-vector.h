
#ifndef _Fixed_Vector_H_
#define _Fixed_Vector_H_

#include "vector-impl.cc"
#include <tr1/tuple>

namespace std {

  template <typename T>
  class varVector;

  template <typename T, uint ND>
  class fixVector {

    public:

      typedef T                  DataType;

      typedef fixVector<T,ND>    Type;

      static const uint nData;

      static const char* TypeTag;

    protected:

      T Data[ND];

      T* head_ptr;

      T* tail_ptr;

    public:

      fixVector() : Data(), head_ptr(Data), tail_ptr(Data+ND) {}

      fixVector(const Type& v) { myError("vector copier is prohibited!"); }

      ~fixVector() {}

      template <typename vType>
      Type& Duplicate(const vType& v) {
        assert(isVector<vType>());
        assign(v);
      }

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
        assert(i<ND);
        return *(Data+i);
      }

      const T& operator[](const uint i) const {
        assert(i<ND);
        return *(Data+i);
      }

      Type& assign(const T* v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*ncopy)<=ND);
        vector_assign(Data,v,ncopy,offset,voffset,step,vstep);
        return *this;
      }

      template <typename vType>
      Type& assign(const vType& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        assert(isVector<vType>());
        assert(static_cast<uint>(voffset+vstep*ncopy)<=v.size());
        return assign(v.data(),ncopy,voffset,vstep,offset,step);
      }

      template <typename vType>
      Type& assign(const vType& v) {
        long n=(ND<v.size()?ND:v.size());
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
        assert(static_cast<uint>(offset+step*nscale)<=ND);
        vector_scale(Data,v,nscale,offset,voffset,step,vstep);
        return *this;
      }

      Type& scale(const T& d, long nscale,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nscale)<=ND);
        vector_scale(Data,d,nscale,offset,iZero,step,lZero);
        return *this;
      }

      Type& scale(const T& d) { return scale(d,nData); }

      template <typename vType>
      Type& scale(const vType& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(isVector<vType>());
        assert(static_cast<uint>(voffset+vstep*nscale)<=v.size());
        return scale(v.data(),nscale,voffset,vstep,offset,step);
      }

      template <typename vType>
      Type& scale(const vType& v) {
        long n=(ND<v.size()?ND:v.size());
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
        assert(static_cast<uint>(offset+step*nshift)<=ND);
        vector_shift(Data,sv,v,nshift,offset,soffset,voffset,step,sstep,vstep);
        return *this;
      }

      template <typename vType>
      Type& shift(const T& value, const vType& v, long nshift,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(isVector<vType>());
        assert(static_cast<uint>(voffset+vstep*nshift)<=v.size());
        return shift(value,v.data(),nshift,
                     iZero,lZero,voffset,vstep,offset,step);
      }

      template <typename vType>
      Type& shift(const T& value, const vType& v) {
        assert(isVector<vType>());
        long n=(ND<v.size()?ND:v.size());
        return shift(value,v,n);
      }

      template <typename vType>
      Type& shift(const pair<const T&,const vType&>& sp) {
        assert(isVector<vType>());
        return shift(sp.first,sp.second);
      }

      template <typename vType>
      Type& shift(const pair<const vType&,const T&>& sp) {
        assert(isVector<vType>());
        return shift(sp.second,sp.first);
      }

      Type& shift(const T& value) {
        return shift(value,&dOne,nData,iZero,lZero,iZero,lZero,iZero,lOne);
      }

      template <typename vType>
      Type& shift(const vType& v) {
        assert(isVector<vType>());
        return shift(dOne,v);
      }

      template <typename vTypeA, typename vTypeB>
      Type& shift(const pair<const vTypeA&,const vTypeB&>& sp) {
        return scaleshift(dOne,dOne,sp.first,sp.second);
      }

      template <typename vTypeA, typename vTypeB>
      Type& shift(const tr1::tuple<const T&,const vTypeA&,const vTypeB&>& st) {
        assert(isVector<vTypeA>()&&isVector<vTypeB>());
        return scaleshift(dOne,tr1::get<0>(st),
                          tr1::get<1>(st),tr1::get<2>(st));
      }

      Type& scaleshift(const T& ScaleF, const T& ShiftF, const T* ShiftFv,
                       const T* v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nscaleshift)<=ND);
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
        assert(static_cast<uint>(sfoffset+sfstep*nscaleshift)<=ShiftFv.size());
        assert(static_cast<uint>(voffset+vstep*nscaleshift)<=v.size());
        return scaleshift(ScaleF,ShiftF,ShiftFv.data(),v.data(),nscaleshift,
                          sfoffset,sfstep,voffset,vstep,offset,step);
      }

      template <typename vTypeA, typename vTypeB>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const vTypeA& ShiftFv, const vTypeB& v) {
        assert(isVector<vTypeA>()&&isVector<vTypeB>());
        long n;
        n=(ND<v.size()?ND:v.size());
        n=(static_cast<uint>(n)<ShiftFv.size()?n:ShiftFv.size());
        return scaleshift(ScaleF,ShiftF,ShiftFv,v,n);
      }

      template <typename vType>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const vType& v, long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        assert(isVector<vType>());
        scale(ScaleF,nscaleshift,offset,step);
        return shift(ShiftF,v,nscaleshift,voffset,vstep,offset,step);
      }

      template <typename vType>
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const vType& v) {
        assert(isVector<vType>());
        long n=(ND<v.size()?ND:v.size());
        return scaleshift(ScaleF,ShiftF,v,n);
      }

      Type& swap_content(T* v, long nswap, int voffset=iZero, int vstep=lOne,
                         int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nswap)<=ND);
        vector_swap(Data,v,nswap,offset,voffset,step,vstep);
        return *this;
      }

      template <typename vType>
      Type& swap_content(vType& v, long nswap,
                         int voffset=iZero, long vstep=lOne,
                         int offset=iZero, long step=lOne) {
        assert(isVector<vType>());
        assert(static_cast<uint>(voffset+vstep*nswap)<=v.size());
        return swap_content(v.data(),nswap,voffset,vstep,offset,step);
      }

      template <typename vType>
      Type& swap_content(vType& v) {
        assert(isVector<vType>());
        long n=(ND<v.size()?ND:v.size());
        return swap_content(v,n);
      }

  };

  template <typename T, uint ND>
  const char* fixVector<T,ND>::TypeTag="fixVector";

  template <typename T, uint ND>
  const uint fixVector<T,ND>::nData=ND;

  template <typename T, uint N>
  istream& operator>>(istream& is, fixVector<T,N>& v) {
    for(uint i=0;i<N;++i) is>>v[i];
    return is;
  }

  template <typename T, uint N>
  ostream& operator<<(ostream& os, const fixVector<T,N>& v) {
    os<<v[0];
    for(uint i=1;i<N;++i) os<<"\t"<<v[i];
    return os;
  }

}

#endif
