
#ifndef _Fixed_Vector_Double_H_
#define _Fixed_Vector_Double_H_

#include "fix-vector.h"

namespace std {

  template <uint ND>
  class fixVector<double,ND> : public fixVector_base<double,ND> {

    public:

      typedef double                      DataType;

      typedef fixVector<double,ND>        Type;

      typedef fixVector_base<double,ND>   ParentType;

      static const long nData=ND;

      fixVector() : ParentType() {}

      fixVector(const Type& v) {
        myError("vector copier is prohibited!");
      }

      ~fixVector() {}

      template <uint NDC>
      Type& Duplicate(const fixVector<double,NDC>& v) { assign(v); }

      template <typename inputT>
      Type& operator=(const inputT& v) { return assign(v); }

      template <typename inputT>
      Type& operator*=(const inputT& v) { return scale(v); }

      template <typename inputT>
      Type& operator+=(const inputT& v) { return shift(v); }

      Type& assign(const double* v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->assign(v,ncopy,
                                               voffset,lOne,offset,step);
        return *this;
      }

      template <uint NDA>
      Type& assign(const fixVector<double,NDA>& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->assign(
            v,ncopy,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDA>
      Type& assign(const fixVector<double,NDA>& v) {
        static_cast<ParentType*>(this)->assign(v);
        return *this;
      }

      Type& assign(const varVector<double>& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->assign(
            v,ncopy,voffset,vstep,offset,step);
        return *this;
      }

      Type& assign(const varVector<double>& v) {
        static_cast<ParentType*>(this)->assign(v);
        return *this;
      }

      Type& assign(const double& value, long ncopy,
                   int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->assign(value,ncopy,offset,step);
        return *this;
      }

      Type& assign(const double& value) { return assign(value,nData); }

      template <typename inputT>
      Type& scale(const inputT& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scale(
            v,nscale,voffset,vstep,offset,step);
        return *this;
      }

      Type& scale(const double& d, long nscale,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scale(d,nscale,iZero,lOne);
        return *this;
      }

      Type& scale(const double& d) { return scale(d,nData); }

      template <uint NDS>
      Type& scale(const fixVector<double,NDS>& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scale(v,nscale,
                                              voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDS>
      Type& scale(const fixVector<double,NDS>& v) {
        static_cast<ParentType*>(this)->scale(v);
        return *this;
      }

      Type& scale(const varVector<double>& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scale(v,nscale,
                                              voffset,vstep,offset,step);
        return *this;
      }

      Type& scale(const varVector<double>& v) {
        static_cast<ParentType*>(this)->scale(v);
        return *this;
      }

      template <uint NDS>
      Type& scale(const pair<const double&,const fixVector<double,NDS>&>& sp) {
        static_cast<ParentType*>(this)->scale(sp);
        return *this;
      }

      template <uint NDS>
      Type& scale(const pair<const fixVector<double,NDS>&,const double&>& sp) {
        static_cast<ParentType*>(this)->scale(sp);
        return *this;
      }

      Type& scale(const pair<const double&,const varVector<double>&>& sp) {
        static_cast<ParentType*>(this)->scale(sp);
        return *this;
      }

      template <uint NDS>
      Type& scale(const pair<const varVector<double>&,const double&>& sp) {
        static_cast<ParentType*>(this)->scale(sp);
        return *this;
      }

      template <typename ScaleT>
      Type& shift(const ScaleT& sv, const double* v, long nshift,
                  int soffset=iZero, long sstep=lOne,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->shift(
            sv,v,nshift,soffset,sstep,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDV>
      Type& shift(const double& value, const fixVector<double,NDV>& v,
                  long nshift,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->shift(
            value,v,nshift,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDV>
      Type& shift(const double& value, const fixVector<double,NDV>& v) {
        static_cast<ParentType*>(this)->shift(value,v);
        return *this;
      }

      template <uint NDV>
      Type& shift(const pair<const double&,const fixVector<double,NDV>&>& sp) {
        static_cast<ParentType*>(this)->shift(sp);
        return *this;
      }

      template <uint NDV>
      Type& shift(const pair<const fixVector<double,NDV>&,const double&>& sp) {
        static_cast<ParentType*>(this)->shift(sp);
        return *this;
      }

      Type& shift(const double& value, const varVector<double>& v, long nshift,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->shift(
            value,v,nshift,voffset,vstep,offset,step);
        return *this;
      }

      Type& shift(const double& value, const varVector<double>& v) {
        static_cast<ParentType*>(this)->shift(value,v);
        return *this;
      }

      Type& shift(const pair<const double&,const varVector<double>&>& sp) {
        static_cast<ParentType*>(this)->shift(sp);
        return *this;
      }

      Type& shift(const pair<const varVector<double>&,const double&>& sp) {
        static_cast<ParentType*>(this)->shift(sp);
        return *this;
      }

      Type& shift(const double& value) {
        return shift(value,&dOne,nData,iZero,lZero,iZero,lZero,iZero,lOne);
      }

      template <uint NDS>
      Type& shift(const fixVector<double,NDS>& v) { return shift(dOne,v); }

      Type& shift(const varVector<double>& v) { return shift(dOne,v); }

      template <uint NDV1, uint NDV2>
      Type& shift(
          const pair<const fixVector_base<double,NDV1>&,
                     const fixVector_base<double,NDV2>&>& sp) {
        return scaleshift(dOne,dOne,sp.first,sp.second);
      }

      template <uint NDV>
      Type& shift(const pair<const varVector<double>&,
                             const fixVector<double,NDV>&>& sp){
        return scaleshift(dOne,dOne,sp.first,sp.second);
      }

      template <uint NDV>
      Type& shift(const pair<const fixVector<double,NDV>&,
                             const varVector<double>&>& sp){
        return scaleshift(dOne,dOne,sp.first,sp.second);
      }

      Type& shift(const pair<const varVector<double>&,
                             const varVector<double>&>& sp) {
        return scaleshift(dOne,dOne,sp.first,sp.second);
      }

      template <uint NDV1, uint NDV2>
      Type& shift(const tr1::tuple<const double&,
                                   const fixVector<double,NDV1>&,
                                   const fixVector<double,NDV2>&>& st) {
        return scaleshift(dOne,tr1::get<0>(st),
                          tr1::get<1>(st),tr1::get<2>(st));
      }

      template <uint NDV>
      Type& shift(const tr1::tuple<const double&,
                                   const fixVector<double,NDV>&,
                                   const varVector<double>&>& st) {
        return scaleshift(dOne,tr1::get<0>(st),
                          tr1::get<1>(st),tr1::get<2>(st));
      }

      template <uint NDV>
      Type& shift(const tr1::tuple<const double&,
                                   const varVector<double>&,
                                   const fixVector<double,NDV>&>& st) {
        return scaleshift(dOne,tr1::get<0>(st),
                          tr1::get<1>(st),tr1::get<2>(st));
      }

      Type& shift(const tr1::tuple<const double&,
                                   const varVector<double>&,
                                   const varVector<double>&>& st) {
        return scaleshift(dOne,tr1::get<0>(st),
                          tr1::get<1>(st),tr1::get<2>(st));
      }

      Type& scaleshift(const double& ScaleF, const double& ShiftF,
                       const double* ShiftFv, const double* v,
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
      Type& scaleshift(const double& ScaleF, const double& ShiftF,
                       const fixVector<double,NSS>& ShiftFv,
                       const fixVector<double,NSV>& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,ShiftFv,v,nscaleshift,
            sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NSS, uint NSV>
      Type& scaleshift(const double& ScaleF, const double& ShiftF,
                       const fixVector<double,NSS>& ShiftFv,
                       const fixVector<double,NSV>& v) {
        static_cast<ParentType*>(this)->scaleshift(ScaleF,ShiftF,ShiftFv,v);
        return *this;
      }

      template <uint NS>
      Type& scaleshift(const double& ScaleF, const double& ShiftF,
                       const fixVector<double,NS>& ShiftFv,
                       const varVector<double>& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,ShiftFv,v,nscaleshift,
            sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NS>
      Type& scaleshift(const double& ScaleF, const double& ShiftF,
                       const fixVector<double,NS>& ShiftFv,
                       const varVector<double>& v) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,ShiftFv,v);
        return *this;
      }

      template <uint NS>
      Type& scaleshift(const double& ScaleF, const double& ShiftF,
                       const varVector<double>& ShiftFv,
                       const fixVector<double,NS>& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,ShiftFv,v,nscaleshift,
            sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NS>
      Type& scaleshift(const double& ScaleF, const double& ShiftF,
                       const varVector<double>& ShiftFv,
                       const fixVector<double,NS>& v) {
        static_cast<ParentType*>(this)->scaleshift(ScaleF,ShiftF,ShiftFv,v);
        return *this;
      }

      Type& scaleshift(const double& ScaleF, const double& ShiftF,
                       const varVector<double>& ShiftFv,
                       const varVector<double>& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,ShiftFv,v,nscaleshift,
            sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      Type& scaleshift(const double& ScaleF, const double& ShiftF,
                       const varVector<double>& ShiftFv,
                       const varVector<double>& v) {
        static_cast<ParentType*>(this)->scaleshift(ScaleF,ShiftF,ShiftFv,v);
        return *this;
      }

      template <uint NDS>
      Type& scaleshift(const double& ScaleF, const double& ShiftF,
                       const fixVector<double,NDS>& v, long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,v,nscaleshift,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDS>
      Type& scaleshift(const double& ScaleF, const double& ShiftF,
                       const fixVector<double,NDS>& v) {
        static_cast<ParentType*>(this)->scaleshift(ScaleF,ShiftF,v);
        return *this;
      }

      Type& scaleshift(const double& ScaleF, const double& ShiftF,
                       const varVector<double>& v, long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->scaleshift(
            ScaleF,ShiftF,v,nscaleshift,voffset,vstep,offset,step);
        return *this;
      }

      Type& scaleshift(const double& ScaleF, const double& ShiftF,
                       const varVector<double>& v) {
        static_cast<ParentType*>(this)->scaleshift(ScaleF,ShiftF,v);
        return *this;
      }

      Type& swap_content(double* v, long nswap,
                         int voffset=iZero, int vstep=lOne,
                         int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->swap_content(
            v,nswap,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDS>
      Type& swap_content(fixVector<double,NDS>& v, long nswap,
                         int voffset=iZero, long vstep=lOne,
                         int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->swap_content(
            v,nswap,voffset,vstep,offset,step);
        return *this;
      }

      template <uint NDS>
      Type& swap_content(fixVector<double,NDS>& v) {
        static_cast<ParentType*>(this)->swap_content(v);
        return *this;
      }

      Type& swap_content(varVector<double>& v, long nswap,
                         int voffset=iZero, long vstep=lOne,
                         int offset=iZero, long step=lOne) {
        static_cast<ParentType*>(this)->swap_content(
            v,nswap,voffset,vstep,offset,step);
        return *this;
      }

      Type& swap_content(varVector<double>& v) {
        static_cast<ParentType*>(this)->swap_content(v);
        return *this;
      }

  };

}

#endif
