
#ifndef _Variable_Vector_H_
#define _Variable_Vector_H_

#include <tr1/tuple>
#include "vector-impl.cc"
#include "memory.h"

namespace std {

  template <typename T, uint NT>
  class fixVector;

  template <typename T>
  class varVector {

    public:

      typedef T               DataType;

      typedef varVector<T>    Type;

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

      ~varVector() { safe_delete(Data); }

      Type& allocate(const uint& n) {
        nData=n;
        Data=new T[nData];
        head_ptr=Data;
        tail_ptr=head_ptr+nData;
        return *this;
      }

      Type& allocate(const Type& v) {
        nData=v.nData;
        Data=new T[nData];
        head_ptr=Data;
        tail_ptr=head_ptr+nData;
        return *this;
      }

      Type& Duplicate(const Type& v) { return allocate(v).assign(v); }

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

      T& operator[](const uint i) const {
        assert(i<nData);
        return *(Data+i);
      }

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
        assign(v.data(),ncopy,voffset,vstep,offset,step);
        return *this;
      }

      Type& assign(const Type& v) {
        long n=(nData<v.nData?nData:v.nData);
        return assign(v,n);
      }

      template <uint ND>
      Type& assign(const fixVector<T,ND>& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*ncopy)<=ND);
        assign(v.data(),ncopy,voffset,vstep,offset,step);
        return *this;
      }

      template <uint ND>
      Type& assign(const fixVector<T,ND>& v) {
        long n=(nData<ND?nData:ND);
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
        assert(static_cast<uint>(offset+step*nscale)<=nData);
        vector_scale(Data,v,nscale,offset,voffset,step,vstep);
        return *this;
      }

      Type& scale(const T& d, long nscale,
                  int offset=iZero, long step=lOne) {
        return scale(d,nscale,iZero,lZero,offset,step);
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

      template <uint ND>
      Type& scale(const fixVector<T,ND>& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*nscale)<=ND);
        return scale(v.data(),nscale,voffset,vstep,offset,step);
      }

      template <uint ND>
      Type& scale(const fixVector<T,ND>& v) {
        long n=(nData<ND?nData:ND);
        return scale(v,n);
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
        return shift(value,v.data(),nshift,
                     iZero,lZero,voffset,vstep,offset,step);
      }
      
      Type& shift(const T& value, const Type& v) {
        long n=(nData<v.nData?nData:v.nData);
        return shift(value,v,n);
      }
      
      Type& shift(const pair<const T&,const Type&>& sp) {
        return shift(sp.first,sp.second);
      }

      Type& shift(const pair<const Type&,const T&>& sp) {
        return shift(sp.second,sp.first);
      }

      template <uint ND>
      Type& shift(const T& value, const fixVector<T,ND>& v, long nshift,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*nshift)<=ND);
        return shift(value,v.data(),nshift,
                     iZero,lZero,voffset,vstep,offset,step);
      }

      template <uint ND>
      Type& shift(const T& value, const fixVector<T,ND>& v) {
        long n=(nData<ND?nData:ND);
        return shift(value,v,n);
      }

      template <uint ND>
      Type& shift(const pair<const T&,const fixVector<T,ND>&>& sp) {
        return shift(sp.first,sp.second);
      }

      template <uint ND>
      Type& shift(const pair<const fixVector<T,ND>&,const T&>& sp) {
        return shift(sp.second,sp.first);
      }

      Type& shift(const T& value) {
        myError("Shift with a value for generic type is not available!");
        return *this;
      }

      Type& shift(const Type& v) {
        myError("Shift with a var-vector for generic type is not available!");
        return *this;
      }

      template <uint ND>
      Type& shift(const fixVector<T,ND>& v) {
        myError("Shift with a fix-vector for generic type is not available!");
        return *this;
      }

      Type& shift(const pair<const Type&,const Type&>& sp) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }

      template <uint ND>
      Type& shift(const pair<const fixVector<T,ND>&,const Type&>& sp) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }

      template <uint ND>
      Type& shift(const pair<const Type&,const fixVector<T,ND>&>& sp) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }

      template <uint ND1, uint ND2>
      Type& shift(const pair<const fixVector<T,ND1>&,const fixVector<T,ND2>&>&
                        sp) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }
      
      Type& shift(const tr1::tuple<const T&,const Type&,const Type&>& st) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }

      template <uint ND>
      Type& shift(
          const tr1::tuple<const T&,const fixVector<T,ND>&,const Type&>& st) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }

      template <uint ND>
      Type& shift(
          const tr1::tuple<const T&,const Type&,const fixVector<T,ND>&>& st) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
      }

      template <uint ND1, uint ND2>
      Type& shift(
          const tr1::tuple<const T&,
                           const fixVector<T,ND1>&,const fixVector<T,ND2>&>&
                st) {
        myError("Shift with vector-factors for generic type is not available!");
        return *this;
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
        return scaleshift(ScaleF,ShiftF,ShiftFv.data(),v.data(),nscaleshift,
                          sfoffset,sfstep,voffset,vstep,offset,step);
      }
      
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const Type& ShiftFv,
                       const Type& v) {
        long n;
        n=(nData<ShiftFv.nData?nData:ShiftFv.nData);
        n=(static_cast<uint>(n)<v.nData?n:v.nData);
        return scaleshift(ScaleF,ShiftF,ShiftFv,v,n);
      }

      template <uint ND>
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const Type& ShiftFv,
                       const fixVector<T,ND>& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(sfoffset+sfstep*nscaleshift)<=ShiftFv.nData);
        assert(static_cast<uint>(voffset+vstep*nscaleshift)<=ND);
        return scaleshift(ScaleF,ShiftF,ShiftFv.data(),v.data(),nscaleshift,
                          sfoffset,sfstep,voffset,vstep,offset,step);
      }

      template <uint ND>
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const Type& ShiftFv,
                       const fixVector<T,ND>& v) {
        long n;
        n=(nData<ShiftFv.nData?nData:ShiftFv.nData);
        n=(n<ND?n:ND);
        return scaleshift(ScaleF,ShiftF,ShiftFv,v,n);
      }

      template <uint ND>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,ND>& ShiftFv,
                       const Type& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(sfoffset+sfstep*nscaleshift)<=ND);
        assert(static_cast<uint>(voffset+vstep*nscaleshift)<=v.nData);
        return scaleshift(ScaleF,ShiftF,ShiftFv.data(),v.data(),nscaleshift,
                          sfoffset,sfstep,voffset,vstep,offset,step);
      }

      template <uint ND>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,ND>& ShiftFv, const Type& v) {
        long n;
        n=(nData<ND?nData:ND);
        n=(n<v.nData?n:v.nData);
        return scaleshift(ScaleF,ShiftF,ShiftFv,v,n);
      }

      template <uint ND1, uint ND2>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,ND1>& ShiftFv,
                       const fixVector<T,ND2>& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(sfoffset+sfstep*nscaleshift)<=ND1);
        assert(static_cast<uint>(voffset+vstep*nscaleshift)<=ND2);
        return scaleshift(ScaleF,ShiftF,ShiftFv.data(),v.data(),nscaleshift,
                          sfoffset,sfstep,voffset,vstep,offset,step);
      }

      template <uint ND1, uint ND2>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,ND1>& ShiftFv,
                       const fixVector<T,ND2>& v) {
        long n;
        n=(nData<ND1?nData:ND1);
        n=(n<ND2?n:ND2);
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

      template <uint ND>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,ND>& v, long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        scale(ScaleF,nscaleshift,offset,step);
        return shift(ShiftF,v,nscaleshift,voffset,vstep,offset,step);
      }
      
      template <uint ND>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,ND>& v) {
        long n=(nData<ND?nData:ND);
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

  };

}

#endif
