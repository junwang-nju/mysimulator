
#include "vector-base.h"
#include "vector-impl.h"
#include <cassert>

namespace std {

  VectorBase<double>& VectorBase<double>::scale(const VectorBase<double>& V) {
    long n=(nData<V.nData?nData:V.nData);
    return scale(V,n);
  }

  VectorBase<double>& VectorBase<double>::scale(const double value) {
    return scale(value,nData);
  }

  VectorBase<double>& VectorBase<double>::scale(
      const Type& V, long nsc, int voff, long vstep, int off, long step) {
    assert(static_cast<unsigned int>(voff+vstep*nsc)<=V.nData);
    assert(static_cast<unsigned int>(off+step*nsc)<=nData);
    vector_scale(Data,V.Data,nsc,voff,vstep,off,step);
    return *this;
  }

  VectorBase<double>& VectorBase<double>::scale(
      const double& value, long nsc, int off, long step) {
    assert(static_cast<unsigned int>(off+step*nsc)<=nData);
    vector_scale(Data,value,nsc,off,step);
    return *this;
  }

  VectorBase<double>& VectorBase<double>::shift(
      const VectorBase<double>& V) {
    return shift(dOne,V);
  }

  VectorBase<double>& VectorBase<double>::shift(const double value) {
    return shift(value,nData);
  }

  VectorBase<double>& VectorBase<double>::shift(
      const double value, const VectorBase<double>& V) {
    long n=(nData<V.nData?nData:V.nData);
    return shift(value,V,n);
  }

  VectorBase<double>& VectorBase<double>::shift(
      const VectorBase<double>& SfV, const VectorBase<double>& V) {
    return shift(dOne,SfV,V);
  }

  VectorBase<double>& VectorBase<double>::shift(
      const double SfF, const VectorBase<double>& SfV,
      const VectorBase<double>& V) {
    return scaleshift(dOne,SfF,SfV,V);
  }

  VectorBase<double>& VectorBase<double>::shift(
      const double& value, const VectorBase<double>& V, long nsh,
      int voff, long vstep, int off, long step) {
    assert(static_cast<unsigned int>(voff+vstep*nsh)<=V.nData);
    assert(static_cast<unsigned int>(off+step*nsh)<=nData);
    vector_shift(Data,value,V.Data,nsh,voff,vstep,off,step);
    return *this;
  }

  VectorBase<double>& VectorBase<double>::shift(
      const double& value, long nsh, int off, long step) {
    assert(static_cast<unsigned int>(off+step*nsh)<=nData);
    vector_shift(Data,value,&dOne,nsh,iZero,lZero,off,step);
    return *this;
  }

  VectorBase<double>& VectorBase<double>::scaleshift(
      const double ScF, const double SfF, const Type& V) {
    long n=(nData<V.nData?nData:V.nData);
    return scaleshift(ScF,SfF,V,n);
  }

  VectorBase<double>& VectorBase<double>::scaleshift(
      const double ScF,const double SfF,const VectorBase<double>& SfV,
      const VectorBase<double>& V) {
    long n=(nData<SfV.nData?nData:SfV.nData);
    n=(n<V.nData?n:V.nData);
    return scaleshift(ScF,SfF,SfV,V,n);
  }

  VectorBase<double>& VectorBase<double>::scaleshift(
      const double& ScF,const double& SfF,const VectorBase<double>& V,
      long nss, int voff, long vstep, int off, long step) {
    return scale(ScF,nss,off,step).shift(SfF,V,nss,voff,vstep,off,step);
  }

  VectorBase<double>& VectorBase<double>::scaleshift(
      const double& ScF,const double& SfF,const VectorBase<double>& SfV,
      const VectorBase<double>& V, long nss,
      int Sfoff, long Sfstep, int voff, long vstep, int off, long step) {
    assert(static_cast<unsigned int>(Sfoff+Sfstep*nss)<=SfV.nData);
    assert(static_cast<unsigned int>(voff+vstep*nss)<=V.nData);
    assert(static_cast<unsigned int>(off+step*nss)<=nData);
    vector_scaleshift(Data,ScF,SfF,SfV.Data,V.Data,nss,
                      Sfoff,Sfstep,voff,vstep,off,step);
    return *this;
  }

}
