
#ifndef _Fixed_Vector_H_
#define _Fixed_Vector_H_

#include "fix-vector-base.h"

namespace std {

  template <typename T, uint ND>
  class fixVector : public fixVector_base<T,ND> {

    public:

      typedef T                     DataType;

      typedef fixVector<T,ND>       Type;

      typedef fixVector_base<T,ND>  ParentType;

      static const long nData=ND;

      fixVector() : ParentType() {}

      fixVector(const Type& v) {
        myError("vector copier is prohibited!");
      }

      ~fixVector() {}

      template <typename inputT>
      Type& operator=(const inputT& v) { return assign(v); }

      template <typename inputT>
      Type& operator*=(const inputT& v) { return scale(v); }

      template <typename inputT>
      Type& operator+=(const inputT& v) { return shift(v); }

      Type& assign(const T* v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->assign(v,ncopy,
                                               voffset,lOne,offset,step);
        return *this;
      }

      template <uint NDA>
      Type& assign(const fixVector<T,NDA>& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->assign(
            v,ncopy,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDA>
      Type& assign(const fixVector<T,NDA>& v) {
        static_cast<ParentType*>(this)->assign(v);
        return *this;
      }

      Type& assign(const varVector<T>& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->assign(
            v,ncopy,voffset,vstep,offset,step);
        return *this;
      }

      Type& assign(const varVector<T>& v) {
        static_cast<ParentType*>(this)->assign(v);
        return *this;
      }

      Type& assign(const T& value, long ncopy,
                   int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->assign(value,ncopy,offset,step);
        return *this;
      }

      Type& assign(const T& value) { return assign(value,nData); }

      template <typename inputT>
      Type& scale(const inputT& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scale(
            v,nscale,voffset,vstep,offset,step);
        return *this;
      }

      Type& scale(const T& d, long nscale,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scale(d,nscale,iZero,lOne);
        return *this;
      }

      Type& scale(const T& d) { return scale(d,nData); }

      template <uint NDS>
      Type& scale(const fixVector<T,NDS>& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scale(v,nscale,
                                              voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDS>
      Type& scale(const fixVector<T,NDS>& v) {
        static_cast<ParentType*>(this)->scale(v);
        return *this;
      }

      Type& scale(const varVector<T>& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scale(v,nscale,
                                              voffset,vstep,offset,step);
        return *this;
      }

      Type& scale(const varVector<T>& v) {
        static_cast<ParentType*>(this)->scale(v);
        return *this;
      }

      template <uint NDS>
      Type& scale(const pair<const T&,const fixVector<T,NDS>&>& sp) {
        static_cast<ParentType*>(this)->scale(sp);
        return *this;
      }

      template <uint NDS>
      Type& scale(const pair<const fixVector<T,NDS>&,const T&>& sp) {
        static_cast<ParentType*>(this)->scale(sp);
        return *this;
      }

      Type& scale(const pair<const T&,const varVector<T>&>& sp) {
        static_cast<ParentType*>(this)->scale(sp);
        return *this;
      }

      template <uint NDS>
      Type& scale(const pair<const varVector<T>&,const T&>& sp) {
        static_cast<ParentType*>(this)->scale(sp);
        return *this;
      }

      template <typename ScaleT>
      Type& shift(const ScaleT& sv, const T* v, long nshift,
                  int soffset=iZero, long sstep=lOne,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->shift(
            sv,v,nshift,soffset,sstep,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDV>
      Type& shift(const T& value, const fixVector<T,NDV>& v,
                  long nshift,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->shift(
            value,v,nshift,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDV>
      Type& shift(const T& value, const fixVector<T,NDV>& v) {
        static_cast<ParentType*>(this)->shift(value,v);
        return *this;
      }

      template <uint NDV>
      Type& shift(const pair<const T&,const fixVector<T,NDV>&>& sp) {
        static_cast<ParentType*>(this)->shift(sp);
        return *this;
      }

      template <uint NDV>
      Type& shift(const pair<const fixVector<T,NDV>&,const T&>& sp) {
        static_cast<ParentType*>(this)->shift(sp);
        return *this;
      }

      Type& shift(const T& value, const varVector<T>& v, long nshift,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->shift(
            value,v,nshift,voffset,vstep,offset,step);
        return *this;
      }

      Type& shift(const T& value, const varVector<T>& v) {
        static_cast<ParentType*>(this)->shift(value,v);
        return *this;
      }

      Type& shift(const pair<const T&,const varVector<T>&>& sp) {
        static_cast<ParentType*>(this)->shift(sp);
        return *this;
      }

      Type& shift(const pair<const varVector<T>&,const T&>& sp) {
        static_cast<ParentType*>(this)->shift(sp);
        return *this;
      }

      Type& shift(const T& value) {
        static_cast<ParentType*>(this)->shift(value);
        return *this;
      }

      template <uint NDS>
      Type& shift(const fixVector<T,NDS>& v) {
        static_cast<ParentType*>(this)->shift(v);
        return *this;
      }

      Type& shift(const varVector<T>& v) {
        static_cast<ParentType*>(this)->shift(v);
        return *this;
      }

      template <uint NDV1, uint NDV2>
      Type& shift(
          const pair<const fixVector_base<T,NDV1>&,
                     const fixVector_base<T,NDV2>&>& sp) {
        static_cast<ParentType*>(this)->shift(sp);
        return *this;
      }

      template <uint NDV>
      Type& shift(const pair<const varVector<T>&,
                             const fixVector<T,NDV>&>& sp){
        static_cast<ParentType*>(this)->shift(sp);
        return *this;
      }

      template <uint NDV>
      Type& shift(const pair<const fixVector<T,NDV>&,
                             const varVector<T>&>& sp){
        static_cast<ParentType*>(this)->shift(sp);
        return *this;
      }

      Type& shift(const pair<const varVector<T>&,
                             const varVector<T>&>& sp) {
        static_cast<ParentType*>(this)->shift(sp);
        return *this;
      }

      template <uint NDV1, uint NDV2>
      Type& shift(const tr1::tuple<const T&,
                                   const fixVector<T,NDV1>&,
                                   const fixVector<T,NDV2>&>& st) {
        static_cast<ParentType*>(this)->shift(st);
        return *this;
      }

      template <uint NDV>
      Type& shift(const tr1::tuple<const T&,
                                   const fixVector<T,NDV>&,
                                   const varVector<T>&>& st) {
        static_cast<ParentType*>(this)->shift(st);
        return *this;
      }

      template <uint NDV>
      Type& shift(const tr1::tuple<const T&,
                                   const varVector<T>&,
                                   const fixVector<T,NDV>&>& st) {
        static_cast<ParentType*>(this)->shift(st);
        return *this;
      }

      Type& shift(const tr1::tuple<const T&,
                                   const varVector<T>&,
                                   const varVector<T>&>& st) {
        static_cast<ParentType*>(this)->shift(st);
        return *this;
      }

      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const T* ShiftFv, const T* v,
                       long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,ShiftFv,v,nscaleshift,
            sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NSS, uint NSV>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,NSS>& ShiftFv,
                       const fixVector<T,NSV>& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,ShiftFv,v,nscaleshift,
            sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NSS, uint NSV>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,NSS>& ShiftFv,
                       const fixVector<T,NSV>& v) {
        static_cast<ParentType*>(this)->scaleshift(ScaleF,ShiftF,ShiftFv,v);
        return *this;
      }

      template <uint NS>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,NS>& ShiftFv,
                       const varVector<T>& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,ShiftFv,v,nscaleshift,
            sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NS>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,NS>& ShiftFv,
                       const varVector<T>& v) {
        static_cast<ParentType*>(this)->scaleshift(ScaleF,ShiftF,ShiftFv,v);
        return *this;
      }

      template <uint NS>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const varVector<T>& ShiftFv,
                       const fixVector<T,NS>& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,ShiftFv,v,nscaleshift,
            sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NS>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const varVector<T>& ShiftFv,
                       const fixVector<T,NS>& v) {
        static_cast<ParentType*>(this)->scaleshift(ScaleF,ShiftF,ShiftFv,v);
        return *this;
      }

      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const varVector<T>& ShiftFv,
                       const varVector<T>& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,ShiftFv,v,nscaleshift,
            sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const varVector<T>& ShiftFv,
                       const varVector<T>& v) {
        static_cast<ParentType*>(this)->scaleshift(ScaleF,ShiftF,ShiftFv,v);
        return *this;
      }

      template <uint NDS>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,NDS>& v, long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,v,nscaleshift,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDS>
      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const fixVector<T,NDS>& v) {
        static_cast<ParentType*>(this)->scaleshift(ScaleF,ShiftF,v);
        return *this;
      }

      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const varVector<T>& v, long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,v,nscaleshift,voffset,vstep,offset,step);
        return *this;
      }

      Type& scaleshift(const T& ScaleF, const T& ShiftF,
                       const varVector<T>& v) {
        static_cast<ParentType*>(this)->scaleshift(ScaleF,ShiftF,v);
        return *this;
      }

      Type& swap_content(T* v, long nswap,
                         int voffset=iZero, int vstep=lOne,
                         int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->swap_content(
            v,nswap,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDS>
      Type& swap_content(fixVector<T,NDS>& v, long nswap,
                         int voffset=iZero, long vstep=lOne,
                         int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->swap_content(
            v,nswap,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDS>
      Type& swap_content(fixVector<T,NDS>& v) {
        static_cast<ParentType*>(this)->swap_content(v);
        return *this;
      }

      Type& swap_content(varVector<T>& v, long nswap,
                         int voffset=iZero, long vstep=lOne,
                         int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->swap_content(
            v,nswap,voffset,vstep,offset,step);
        return *this;
      }

      Type& swap_content(varVector<T>& v) {
        static_cast<ParentType*>(this)->swap_content(v);
        return *this;
      }

  };

}

#endif
