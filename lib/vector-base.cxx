
#include "vector-base.h"
#include "vector-impl.h"
#include <cassert>

namespace std {

  void VectorBase<double>::scale(const VectorBase<double>& V) {
    long n=(nData<V.nData?nData:V.nData);
    scale(V,n);
  }

  void VectorBase<double>::scale(const double value) {
    scale(value,nData);
  }

  void VectorBase<double>::scale(
      const Type& V, long nsc, int voff, long vstep, int off, long step) {
    assert(static_cast<unsigned int>(voff+vstep*nsc)<=V.nData);
    assert(static_cast<unsigned int>(off+step*nsc)<=nData);
    vector_scale(Data,V.Data,nsc,voff,vstep,off,step);
  }

  void VectorBase<double>::scale(
      const double& value, long nsc, int off, long step) {
    assert(static_cast<unsigned int>(off+step*nsc)<=nData);
    vector_scale(Data,value,nsc,off,step);
  }

  void VectorBase<double>::shift(const VectorBase<double>& V){ shift(dOne,V); }

  void VectorBase<double>::shift(const double value) { shift(value,nData); }

  void VectorBase<double>::shift(
      const double value, const VectorBase<double>& V) {
    long n=(nData<V.nData?nData:V.nData);
    shift(value,V,n);
  }

  void VectorBase<double>::shift(
      const VectorBase<double>& V, const double value) {
    return shift(value,V);
  }

  void VectorBase<double>::shift(
      const VectorBase<double>& SfV, const VectorBase<double>& V) {
    shift(dOne,SfV,V);
  }

  void VectorBase<double>::shift(
      const double SfF, const VectorBase<double>& SfV,
      const VectorBase<double>& V) {
    scaleshift(dOne,SfF,SfV,V);
  }

  void VectorBase<double>::shift(
      const double& value, const VectorBase<double>& V, long nsh,
      int voff, long vstep, int off, long step) {
    assert(static_cast<unsigned int>(voff+vstep*nsh)<=V.nData);
    assert(static_cast<unsigned int>(off+step*nsh)<=nData);
    vector_shift(Data,value,V.Data,nsh,voff,vstep,off,step);
  }

  void VectorBase<double>::shift(
      const double& value, long nsh, int off, long step) {
    assert(static_cast<unsigned int>(off+step*nsh)<=nData);
    vector_shift(Data,value,&dOne,nsh,iZero,lZero,off,step);
  }

  void VectorBase<double>::scaleshift(
      const double ScF, const double SfF, const Type& V) {
    long n=(nData<V.nData?nData:V.nData);
    scaleshift(ScF,SfF,V,n);
  }

  void VectorBase<double>::scaleshift(
      const double ScF,const double SfF,const VectorBase<double>& SfV,
      const VectorBase<double>& V) {
    long n=(nData<SfV.nData?nData:SfV.nData);
    n=(n<V.nData?n:V.nData);
    scaleshift(ScF,SfF,SfV,V,n);
  }

  void VectorBase<double>::scaleshift(
      const double& ScF,const double& SfF,const VectorBase<double>& V,
      long nss, int voff, long vstep, int off, long step) {
    scale(ScF,nss,off,step);
    shift(SfF,V,nss,voff,vstep,off,step);
  }

  void VectorBase<double>::scaleshift(
      const double& ScF,const double& SfF,const VectorBase<double>& SfV,
      const VectorBase<double>& V, long nss,
      int Sfoff, long Sfstep, int voff, long vstep, int off, long step) {
    assert(static_cast<unsigned int>(Sfoff+Sfstep*nss)<=SfV.nData);
    assert(static_cast<unsigned int>(voff+vstep*nss)<=V.nData);
    assert(static_cast<unsigned int>(off+step*nss)<=nData);
    vector_scaleshift(Data,ScF,SfF,SfV.Data,V.Data,nss,
                      Sfoff,Sfstep,voff,vstep,off,step);
  }

}
