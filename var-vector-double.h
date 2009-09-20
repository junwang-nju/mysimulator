
#ifndef _Variable_Vector_Double_H_
#define _Variable_Vector_Double_H_

#include "var-vector.h"

namespace std {

  typedef varVector<double> varDVector;
  
  template <>
  varDVector& varDVector::shift(const varDVector& v) {
    return shift(dOne,v);
  }
  
  template <>
  template <uint ND>
  varDVector& varDVector::shift(const fixVector<double,ND>& v) {
    return shift(dOne,v);
  }
  
  template <>
  varDVector& varDVector::shift(const double& value) {
    return shift(value,&dOne,nData,iZero,lZero,iZero,lZero,iZero,lOne);
  }
  
  template <>
  varDVector& varDVector::shift(const pair<const Type&,const Type&>& sp) {
    return scaleshift(dOne,dOne,sp.first,sp.second);
  }
  
  template <>
  template <uint ND>
  varDVector& varDVector::shift(
      const pair<const Type&,const fixVector<double,ND>&>& sp) {
    return scaleshift(dOne,dOne,sp.first,sp.second);
  }
  
  template <>
  template <uint ND>
  varDVector& varDVector::shift(
      const pair<const fixVector<double,ND>&,const Type&>& sp) {
    return scaleshift(dOne,dOne,sp.first,sp.second);
  }
  
  template <>
  template <uint ND1, uint ND2>
  varDVector& varDVector::shift(
      const pair<const fixVector<double,ND1>&,const fixVector<double,ND2>&>&
            sp) {
    return scaleshift(dOne,dOne,sp.first,sp.second);
  }
  
  template <>
  varDVector& varDVector::shift(
      const tr1::tuple<const double&,const Type&,const Type&>& st) {
    return scaleshift(dOne,tr1::get<0>(st),tr1::get<1>(st),tr1::get<2>(st));
  }
  
  template <>
  template <uint ND>
  varDVector& varDVector::shift(
      const tr1::tuple<const double&,const fixVector<double,ND>&,const Type&>&
            st) {
    return scaleshift(dOne,tr1::get<0>(st),tr1::get<1>(st),tr1::get<2>(st));
  }
  
  template <>
  template <uint ND>
  varDVector& varDVector::shift(
      const tr1::tuple<const double&,const Type&,const fixVector<double,ND>&>&
            st) {
    return scaleshift(dOne,tr1::get<0>(st),tr1::get<1>(st),tr1::get<2>(st));
  }
  
  template <>
  template <uint ND1, uint ND2>
  varDVector& varDVector::shift(
      const tr1::tuple<const double&,
                       const fixVector<double,ND1>&,
                       const fixVector<double,ND2>&>&
            st) {
    return scaleshift(dOne,tr1::get<0>(st),tr1::get<1>(st),tr1::get<2>(st));
  }
  
}

#endif
