
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

      typedef T                 DataType;

      typedef fixVector<T,ND>   Type;

      static const long nData=ND;

    private:

      T Data[ND];

      T* head_ptr;

      T* tail_ptr;

    public:

      fixVector() : Data(), head_ptr(Data), tail_ptr(Data+ND) {}

      fixVector(const Type& v) { myError("vector copier is prohibited!"); }

      ~fixVector() {}

      template <uint NDC>
      Type& Duplicate(const fixVector<T,NDC>& v) { assign(v); }

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

      Type& assign(const T* v, long ncopy, int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*ncopy)<=ND);
        vector_assign(Data,v,ncopy,offset,voffset,step,vstep);
        return *this;
      }

      template <uint NDA>
      Type& assign(const fixVector<T,NDA>& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*ncopy)<=NDA);
        return assign(v.data(),ncopy,voffset,vstep,offset,step);
      }

      template <uint NDA>
      Type& assign(const fixVector<T,NDA>& v) {
        long n=(ND<NDA?ND:NDA);
        return assign(v,n);
      }

      Type& assign(const varVector<T>& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*ncopy)<=v.size());
        return assign(v.data(),ncopy,voffset,vstep,offset,step);
      }

      Type& assign(const varVector<T>& v) {
        long n=(ND<v.size()?ND:v.size());
        return assign(v,n);
      }

      Type& assign(const T& value, long ncopy,
                   int offset=iZero, long step=lOne) {
        return assign(&value,ncopy,iZero,lZero,offset,step);
      }

      Type& assign(const T& value) { return assign(value,nData); }

      template <typename inputT>
      Type& scale(const inputT& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nscale)<=ND);
        vector_scale(Data,v,nscale,offset,voffset,step,vstep);
        return *this;
      }

      Type& scale(const T& d, long nscale,
                  int offset=iZero, long step=lOne) {
        return scale(d,nscale,iZero,lZero,offset,step);
      }

      Type& scale(const T& d) { return scale(d,nData); }

      template <uint NDS>
      Type& scale(const fixVector<T,NDS>& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*nscale)<=NDS);
        return scale(v.data(),nscale,voffset,vstep,offset,step);
      }

      template <uint NDS>
      Type& scale(const fixVector<T,NDS>& v) {
        long n=(ND<NDS?ND:NDS);
        return scale(v,n);
      }

      Type& scale(const varVector<T>& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*nscale)<=v.size());
        return scale(v.data(),nscale,voffset,vstep,offset,step);
      }

      Type& scale(const varVector<T>& v) {
        long n=(ND<v.size()?ND:v.size());
        return scale(v,n);
      }

      template <uint NDS>
      Type& scale(const pair<const T&,const fixVector<T,NDS>&>& sp) {
        return scale(sp.first).scale(sp.second);
      }

      template <uint NDS>
      Type& scale(const pair<const fixVector<T,NDS>&,const T&>& sp) {
        return scale(sp.first).scale(sp.second);
      }

      Type& scale(const pair<const T&,const varVector<T>&>& sp) {
        return scale(sp.first).scale(sp.second);
      }

      template <uint NDS>
      Type& scale(const pair<const varVector<T>&,const T&>& sp) {
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

      template <uint NDV>
      Type& shift(const T& value, const fixVector<T,NDV>& v, long nshift,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*nshift)<=NDV);
        return shift(value,v.data(),nshift,
                     iZero,lZero,voffset,vstep,offset,step);
      }

      template <uint NDV>
      Type& shift(const T& value, const fixVector<T,NDV>& v) {
        long n=(ND<NDV?ND:NDV);
        return shift(value,v,n);
      }

      template <uint NDV>
      Type& shift(const pair<const T&,const fixVector<T,NDV>&>& sp) {
        return shift(sp.first,sp.second);
      }

      template <uint NDV>
      Type& shift(const pair<const fixVector<T,NDV>&,const T&>& sp) {
        return shift(sp.second,sp.first);
      }

      Type& shift(const T& value, const varVector<T>& v, long nshift,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*nshift)<=v.data());
        return shift(value,v.data(),nshift,
                     iZero,lZero,voffset,vstep,offset,step);
      }

      Type& shift(const T& value, const varVector<T>& v) {
        long n=(ND<v.data()?ND:v.data());
        return shift(value,v,n);
      }

      Type& shift(const pair<const T&,const varVector<T>&>& sp) {
        return shift(sp.first,sp.second);
      }

      Type& shift(const pair<const varVector<T>&,const T&>& sp) {
        return shift(sp.second,sp.first);
      }

      Type& shift(const T& value) {
        myError("shift with a value for generic type is not available!");
        return *this;
      }

      template <uint NDV>
      Type& shift(const fixVector<T,NDV>& v) {
        myError("Shift with a fix-vector for generic type is not available!");
        return *this;
      }

      Type& shift(const varVector<T>& v) {
        myError("Shift with a var-vector for generic type is not available!");
        return *this;
      }

      template <uint NDV1, uint NDV2>
      Type& shift(
          const pair<const fixVector<T,NDV1>&,const fixVector<T,NDV2>&>& sp) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }

      template <uint NDV>
      Type& shift(const pair<const varVector<T>&,const fixVector<T,NDV>&>& sp){
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }

      template <uint NDV>
      Type& shift(const pair<const fixVector<T,NDV>&,const varVector<T>&>& sp){
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }

      Type& shift(const pair<const varVector<T>&,const varVector<T>&>& sp) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }

      template <uint NDV1, uint NDV2>
      Type& shift(const tr1::tuple<const T&,const fixVector<T,NDV1>&,
                                   const fixVector<T,NDV2>&>& st) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }

      template <uint NDV>
      Type& shift(const tr1::tuple<const T&,const fixVector<T,NDV>&,
                                   const varVector<T>&>& st) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }

      template <uint NDV>
      Type& shift(const tr1::tuple<const T&,const varVector<T>&,
                                   const fixVector<T,NDV>&>& st) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }

      Type& shift(const tr1::tuple<const T&,const varVector<T>&,
                                   const varVector<T>&>& st) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
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

      template <uint NSS, uint NSV>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,NSS>& ShiftFv,
                       const fixVector<T,NSV>& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(sfoffset+sfstep*nscaleshift)<=NSS);
        assert(static_cast<uint>(voffset+vstep*nscaleshift)<NSV);
        return scaleshift(ScaleF,ShiftF,ShiftFv.data(),v.data(),nscaleshift,
                          sfoffset,sfstep,voffset,vstep,offset,step);
      }

      template <uint NSS, uint NSV>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,NSS>& ShiftFv,
                       const fixVector<T,NSV>& v) {
        long n;
        n=(ND<NSS?ND:NSS);
        n=(n<NSV?n:NSV);
        return scaleshift(ScaleF,ShiftF,ShiftFv,v,n);
      }

      template <uint NS>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,NS>& ShiftFv,
                       const varVector<T>& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(sfoffset+sfstep*nscaleshift)<=NS);
        assert(static_cast<uint>(voffset+vstep*nscaleshift)<v.size());
        return scaleshift(ScaleF,ShiftF,ShiftFv.data(),v.data(),nscaleshift,
                          sfoffset,sfstep,voffset,vstep,offset,step);
      }

      template <uint NS>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,NS>& ShiftFv, const varVector<T>& v) {
        long n;
        n=(ND<ND?ND:NS);
        n=(n<v.size()?n:v.size());
        return scaleshift(ScaleF,ShiftF,ShiftFv,v,n);
      }

  };

}

#endif
