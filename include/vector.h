
#ifndef _Vector_H_
#define _Vector_H_

#include "vector-base.h"
#include "blas.h"
#include "memory.h"
#include "util.h"
#include <cassert>

namespace std {

  template <typename T>
  struct Vector : public VectorBase {

    typedef Vector<T>   Type;
    typedef VectorBase  ParentType;

    T* data;

    Vector() : ParentType(), data(NULL) {}
    Vector(const Type& v) : ParentType(v) {}
    Vector(const unsigned int n) : ParentType(), data(NULL) {
      allocate(*this,n);
    }
    Type& operator=(const Type& V) { myError("Copy Prohibited"); return *this; }
    ~Vector() { safe_release(data,state); }
    T*& operator()() { return data; }
    const T* operator()() const { return data; }
    T& operator[](const int I) { return *(data+I); }
    const T& operator[](const int I) const { return *(data+I); }

  };

  template <typename T>
  bool IsAvailable(const Vector<T>& V) { return IsAvailable(V()); }

  template <typename T>
  void allocate(Vector<T>& V, const unsigned int n) {
    assert(n>0);
    release(V);
    V.data=new T[n];
    V.size=n;
    V.state=Allocated;
  }

  template <typename T>
  void release(Vector<T>& V) {
    safe_release(V.data,V.state);
    V.size=uZero;
    V.state=Unused;
  }

  template <typename T>
  void refer(Vector<T>& V, const Vector<T>& rV) {
    assert(IsAvailable(rV));
    release(V);
    V.data=rV.data;
    V.size=rV.size;
    V.state=Reference;
  }

  template <typename T>
  void refer(Vector<T>& V, const T* ptr, const unsigned int sz) {
    assert(IsAvailable(ptr));
    release(V);
    V.data=const_cast<T*>(ptr);
    V.size=sz;
    V.state=Reference;
  }

  template <typename T, typename cT>
  void copy(Vector<T>& V, const Vector<cT>& cV) {
    assert(IsAvailable(V));
    assert(IsAvailable(cV));
    unsigned int n=(V.size<cV.size?V.size:cV.size);
    T* p=V.data;
    T* cp=const_cast<T*>(cV.data);
    for(unsigned int i=0;i<n;++i,++p,++cp) copy(*p,*cp);
  }

  template <typename T, typename cT>
  void copy(Vector<T>& V, const cT& d) {
    assert(IsAvailable(V));
    T* p=V.data;
    for(unsigned int i=0;i<V.size;++i,++p) copy(*p,d);
  }

  void copy(Vector<double>& V, const Vector<double>& cV) {
    assert(IsAvailable(V));
    assert(IsAvailable(cV));
    long n=(V.size<cV.size?V.size:cV.size);
    dcopy_(&n,const_cast<double*>(cV.data),const_cast<long*>(&lOne),
           V.data,const_cast<long*>(&lOne));
  }

  void copy(Vector<double>& V, const double& d) {
    assert(IsAvailable(V));
    dcopy_(reinterpret_cast<long*>(&(V.size)),
           const_cast<double*>(&d),const_cast<long*>(&lZero),
           V.data,const_cast<long*>(&lOne));
  }

  template <typename T>
  void copy(Vector<double>& V, const T& d) {
    double dd;
    copy(dd,d);
    copy(V,dd);
  }

  void copy(Vector<float>& V, const Vector<float>& cV) {
    assert(IsAvailable(V));
    assert(IsAvailable(cV));
    long n=(V.size<cV.size?V.size:cV.size);
    scopy_(&n,const_cast<float*>(cV.data),const_cast<long*>(&lOne),
           V.data,const_cast<long*>(&lOne));
  }

  void copy(Vector<float>& V, const float& d) {
    assert(IsAvailable(V));
    scopy_(reinterpret_cast<long*>(&(V.size)),
           const_cast<float*>(&d),const_cast<long*>(&lZero),
           V.data,const_cast<long*>(&lOne));
  }

  template <typename T>
  void copy(Vector<float>& V, const T& d) {
    float fd;
    copy(fd,d);
    copy(V,fd);
  }

  void copy(Vector<int>& V, const Vector<int>& cV) {
    assert(IsAvailable(V));
    assert(IsAvailable(cV));
    long n=(V.size<cV.size?V.size:cV.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<int*>(cV.data)),
           const_cast<long*>(&lOne),
           reinterpret_cast<float*>(V.data),const_cast<long*>(&lOne));
  }

  void copy(Vector<int>& V, const Vector<unsigned int>& cV) {
    assert(IsAvailable(V));
    assert(IsAvailable(cV));
    long n=(V.size<cV.size?V.size:cV.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<unsigned int*>(cV.data)),
           const_cast<long*>(&lOne),
           reinterpret_cast<float*>(V.data),const_cast<long*>(&lOne));
  }

  void copy(Vector<int>& V, const int& d) {
    assert(IsAvailable(V));
    scopy_(reinterpret_cast<long*>(&V.size),
           reinterpret_cast<float*>(const_cast<int*>(&d)),
           const_cast<long*>(&lZero),
           reinterpret_cast<float*>(V.data),const_cast<long*>(&lOne));
  }

  void copy(Vector<unsigned int>& V, const unsigned int& d) {
    assert(IsAvailable(V));
    scopy_(reinterpret_cast<long*>(&V.size),
           reinterpret_cast<float*>(const_cast<unsigned int*>(&d)),
           const_cast<long*>(&lZero),
           reinterpret_cast<float*>(V.data),const_cast<long*>(&lOne));
  }

  void copy(Vector<int>& V, const unsigned int& d) {
    copy(V,static_cast<int>(d));
  }

  void copy(Vector<unsigned int>& V, const int& d) {
    copy(V,static_cast<unsigned int>(d));
  }

  void scale(Vector<double>& V, const double& d) {
    assert(IsAvailable(V));
    dscal_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(V.size))),
           const_cast<double*>(&d),V.data,const_cast<long*>(&lOne));
  }

  void scale(Vector<float>& V, const float& d) {
    assert(IsAvailable(V));
    sscal_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(V.size))),
           const_cast<float*>(&d),V.data,const_cast<long*>(&lOne));
  }

  template <typename T, typename sT>
  void scale(Vector<T>& V, const sT& d) {
    assert(IsAvailable(V));
    T* p=V.data;
    for(unsigned int i=0;i<V.size;++i,++p)  scale((*p),d);
  }

  template <typename sT>
  void scale(Vector<double>& V, const sT& d) {
    double dd;
    copy(dd,d);
    scale(V,dd);
  }

  template <typename sT>
  void scale(Vector<float>& V, const sT& d) {
    float fd;
    copy(fd,d);
    scale(V,fd);
  }

  void scale(Vector<double>& V, const Vector<double>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(sV));
    long n=(V.size<sV.size?V.size:sV.size);
    static char flag[]="LNN";
    dtbmv_(flag,flag+1,flag+2,&n,const_cast<long*>(&lZero),
           const_cast<double*>(sV.data),const_cast<long*>(&lOne),V.data,
           const_cast<long*>(&lOne));
  }

  void scale(Vector<float>& V, const Vector<float>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(sV));
    long n=(V.size<sV.size?V.size:sV.size);
    static char flag[]="LNN";
    stbmv_(flag,flag+1,flag+2,&n,const_cast<long*>(&lZero),
           const_cast<float*>(sV.data),const_cast<long*>(&lOne),V.data,
           const_cast<long*>(&lOne));
  }

  template <typename T, typename sT>
  void scale(Vector<T>& V, const Vector<sT>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(sV));
    unsigned int n=(V.size<sV.size?V.size:sV.size);
    T* p=V.data;
    sT* sp=const_cast<int*>(sV.data);
    for(unsigned int i=0;i<n;++i,++p,++sp)  scale((*p),(*sp));
  }

  template <typename T, typename sT, typename fT>
  void scale(Vector<T>& V, const Vector<sT>& sV, const fT& d) {
    scale(V,sV);
    scale(V,d);
  }

  template <typename T, typename sT, typename fT>
  void scale(Vector<T>& V, const fT& d, const Vector<sT>& sV) {
    scale(V,sV);
    scale(V,d);
  }

  void shift(Vector<double>& V, const double& d, const Vector<double>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(sV));
    long n=(V.size<sV.size?V.size:sV.size);
    daxpy_(&n,const_cast<double*>(&d),const_cast<double*>(sV.data),
           const_cast<long*>(&lOne),V.data,const_cast<long*>(&lOne));
  }

  void shift(Vector<float>& V, const float& d, const Vector<float>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(sV));
    long n=(V.size<sV.size?V.size:sV.size);
    saxpy_(&n,const_cast<float*>(&d),const_cast<float*>(sV.data),
           const_cast<long*>(&lOne),V.data,const_cast<long*>(&lOne));
  }

  template <typename T, typename sT, typename fT>
  void shift(Vector<T>& V, const fT& d, const Vector<sT>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(sV));
    unsigned int n=(V.size<sV.size?V.size:sV.size);
    T* p=V.data;
    sT* sp=const_cast<sT*>(sV.data);
    for(unsigned int i=0;i<n;++i,++p,++sp) shift(*p,d,*sp);
  }

  template <typename T, typename sT, typename fT>
  void shift(Vector<T>& V, const Vector<sT>& sV, const fT& d) {
    shift(V,d,sV);
  }

  template <typename T>
  void shift(Vector<double>& V, const T& d, const Vector<double>& sV) {
    double dd;
    copy(dd,d);
    shift(V,dd,sV);
  }

  template <typename T>
  void shift(Vector<float>& V, const T& d, const Vector<float>& sV) {
    float dd;
    copy(dd,d);
    shift(V,dd,sV);
  }

  void shift(Vector<double>& V, const double& d) {
    assert(IsAvailable(V));
    daxpy_(reinterpret_cast<long*>(&(V.size)),
           const_cast<double*>(&d),const_cast<double*>(&dOne),
           const_cast<long*>(&lZero),V.data,const_cast<long*>(&lOne));
  }

  void shift(Vector<float>& V, const float& d) {
    assert(IsAvailable(V));
    saxpy_(reinterpret_cast<long*>(&(V.size)),
           const_cast<float*>(&d),const_cast<float*>(&fOne),
           const_cast<long*>(&lZero),V.data,const_cast<long*>(&lOne));
  }

  template <typename T, typename fT>
  void shift(Vector<T>& V, const fT& d) {
    assert(IsAvailable(V));
    T* p=V.data;
    for(unsigned int i=0;i<V.size;++i,++p)  shift(*p,d,iOne);
  }
  
  template <typename T>
  void shift(Vector<double>& V, const T& d) {
    double dd;
    copy(dd,d);
    shift(V,dd);
  }

  template <typename T>
  void shift(Vector<float>& V, const T& d) {
    float dd;
    copy(dd,d);
    shift(V,dd);
  }

  template <typename T, typename cT>
  void shift(Vector<T>& V, const Vector<cT>& sV) { shift(V,iOne,sV); }

  template <typename T>
  void shift(Vector<double>& V, const Vector<T>& sV) { shift(V,dOne,sV); }

  template <typename T>
  void shift(Vector<float>& V, const Vector<T>& sV) { shift(V,fOne,sV); }

  void scaleshift(Vector<double>& V, const double& d, const double& sd,
                  const Vector<double>& fV, const Vector<double>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(fV));
    assert(IsAvailable(sV));
    long n=(V.size<fV.size?V.size:fV.size);
    n=(static_cast<unsigned int>(n)<sV.size?n:sV.size);
    static char flag[]="L";
    dsbmv_(flag,&n,const_cast<long*>(&lZero),const_cast<double*>(&sd),
           const_cast<double*>(fV.data),const_cast<long*>(&lOne),
           const_cast<double*>(sV.data),const_cast<long*>(&lOne),
           const_cast<double*>(&d),V.data,const_cast<long*>(&lOne));
  }

  void scaleshift(Vector<float>& V, const float& d, const float& sd,
                  const Vector<float>& fV, const Vector<float>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(fV));
    assert(IsAvailable(sV));
    long n=(V.size<fV.size?V.size:fV.size);
    n=(static_cast<unsigned int>(n)<sV.size?n:sV.size);
    static char flag[]="L";
    ssbmv_(flag,&n,const_cast<long*>(&lZero),const_cast<float*>(&sd),
           const_cast<float*>(fV.data),const_cast<long*>(&lOne),
           const_cast<float*>(sV.data),const_cast<long*>(&lOne),
           const_cast<float*>(&d),V.data,const_cast<long*>(&lOne));
  }

  template <typename T, typename dT, typename sT, typename fT, typename svT>
  void scaleshift(Vector<T>& V, const dT& d, const sT& sd,
                  const Vector<fT>& fV, const Vector<svT>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(fV));
    assert(IsAvailable(sV));
    unsigned int n=(V.size<fV.size?V.size:fV.size);
    n=(n<sV.size?n:sV.size);
    T* p=V.data;
    fT* fp=const_cast<fT*>(fV.data);
    svT* svp=const_cast<svT*>(sV.data);
    for(unsigned int i=0;i<n;++i,++p,++fp,++svp) {
      scale(*p,d);
      shift(*p,sd*(*fp),*svp);
    }
  }

  template <typename dT, typename sT>
  void scaleshift(Vector<double>& V, const dT& d, const sT& sd,
                  const Vector<double>& fV, const Vector<double>& sV) {
    double dd,dsd;
    copy(dd,d);
    copy(dsd,sd);
    scaleshift(V,dd,dsd,fV,sV);
  }

  template <typename dT, typename sT>
  void scaleshift(Vector<float>& V, const dT& d, const sT& sd,
                  const Vector<float>& fV, const Vector<float>& sV) {
    float dd,dsd;
    copy(dd,d);
    copy(dsd,sd);
    scaleshift(V,dd,dsd,fV,sV);
  }

  template <typename T,typename dT,typename fT,typename svT>
  void scaleshift(Vector<T>& V, const dT& d, const Vector<fT>& fV,
                  const Vector<svT>& sV) {
    scaleshift(V,d,iOne,fV,sV);
  }

  template <typename T, typename sT, typename fT, typename svT>
  void shift(Vector<T>& V, const sT& sd, const Vector<fT>& fV,
             const Vector<svT>& sV) {
    scaleshift(V,iOne,sd,fV,sV);
  }

  template <typename T, typename fT, typename svT>
  void shift(Vector<T>& V, const Vector<fT>& fV, const Vector<svT>& sV) {
    scaleshift(V,iOne,iOne,fV,sV);
  }

  template <typename T, typename dT, typename sT, typename svT>
  void scaleshift(Vector<T>& V, const dT& d, const sT& sd,
                  const Vector<svT>& sV) {
    scale(V,d);
    shift(V,sd,sV);
  }

  void exchange(Vector<double>& Va, Vector<double>& Vb) {
    assert(IsAvailable(Va));
    assert(IsAvailable(Vb));
    long n=(Va.size<Vb.size?Va.size:Vb.size);
    dswap_(&n,Va.data,const_cast<long*>(&lOne),
              Vb.data,const_cast<long*>(&lOne));
  }

  void exchange(Vector<float>& Va, Vector<float>& Vb) {
    assert(IsAvailable(Va));
    assert(IsAvailable(Vb));
    long n=(Va.size<Vb.size?Va.size:Vb.size);
    sswap_(&n,Va.data,const_cast<long*>(&lOne),
              Vb.data,const_cast<long*>(&lOne));
  }

  void exchange(Vector<int>& Va, Vector<int>& Vb) {
    assert(IsAvailable(Va));
    assert(IsAvailable(Vb));
    long n=(Va.size<Vb.size?Va.size:Vb.size);
    sswap_(&n,reinterpret_cast<float*>(Va.data),const_cast<long*>(&lOne),
              reinterpret_cast<float*>(Vb.data),const_cast<long*>(&lOne));
  }

  void exchange(Vector<unsigned int>& Va, Vector<unsigned int>& Vb) {
    assert(IsAvailable(Va));
    assert(IsAvailable(Vb));
    long n=(Va.size<Vb.size?Va.size:Vb.size);
    sswap_(&n,reinterpret_cast<float*>(Va.data),const_cast<long*>(&lOne),
              reinterpret_cast<float*>(Vb.data),const_cast<long*>(&lOne));
  }

  template <typename TA, typename TB>
  void exchange(Vector<TA>& Va, Vector<TB>& Vb) {
    assert(IsAvailable(Va));
    assert(IsAvailable(Vb));
    unsigned int n=(Va.size<Vb.size?Va.size:Vb.size);
    TA* pa=Va.data;
    TB* pb=Vb.data;
    for(unsigned int i=0;i<n;++i,++pa,++pb) exchange(*pa,*pb);
  }

  template <typename T>
  void swap(Vector<T>& Va, Vector<T>& Vb) {
    swap(Va.data,Vb.data);
    swap(Va.size,Vb.size);
    swap(Va.state,Vb.state);
  }

  double dot(const Vector<double>& Va, const Vector<double>& Vb) {
    assert(IsAvailable(Va));
    assert(IsAvailable(Vb));
    long n=(Va.size<Vb.size?Va.size:Vb.size);
    return ddot_(&n,const_cast<double*>(Va.data),const_cast<long*>(&lOne),
                    const_cast<double*>(Vb.data),const_cast<long*>(&lOne));
  }

  float dot(const Vector<float>& Va, const Vector<float>& Vb) {
    assert(IsAvailable(Va));
    assert(IsAvailable(Vb));
    long n=(Va.size<Vb.size?Va.size:Vb.size);
    return sdot_(&n,const_cast<float*>(Va.data),const_cast<long*>(&lOne),
                    const_cast<float*>(Vb.data),const_cast<long*>(&lOne));
  }

  template <typename T, typename TA, typename TB>
  T dotrun(const Vector<TA>& Va, const Vector<TB>& Vb) {
    assert(IsAvailable(Va));
    assert(IsAvailable(Vb));
    unsigned int n=(Va.size<Vb.size?Va.size:Vb.size);
    T sum=0.;
    TA* ap=Va.data;
    TB* bp=Vb.data;
    for(unsigned int i=0;i<n;++i,++ap,++bp)  shift(sum,*ap,*bp);
    return sum;
  }
  
  template <typename T>
  double dot(const Vector<double>& Va, const Vector<T>& Vb) {
    return dotrun<double>(Va,Vb);
  }
  template <typename T>
  double dot(const Vector<T>& Va, const Vector<double>& Vb) {
    return dotrun<double>(Va,Vb);
  }

  float dot(const Vector<float>& Va, const Vector<int>& Vb) {
    return dotrun<float>(Va,Vb);
  }
  float dot(const Vector<int>& Va, const Vector<float>& Vb) {
    return dotrun<float>(Va,Vb);
  }

  float dot(const Vector<float>& Va, const Vector<unsigned int>& Vb) {
    return dotrun<float>(Va,Vb);
  }
  float dot(const Vector<unsigned int>& Va, const Vector<float>& Vb) {
    return dotrun<float>(Va,Vb);
  }

  int dot(const Vector<int>& Va, const Vector<int>& Vb) {
    return dotrun<int>(Va,Vb);
  }
  int dot(const Vector<int>& Va, const Vector<unsigned int>& Vb) {
    return dotrun<int>(Va,Vb);
  }
  int dot(const Vector<unsigned int>& Va, const Vector<int>& Vb) {
    return dotrun<int>(Va,Vb);
  }
  unsigned int dot(const Vector<unsigned int>& Va,
                   const Vector<unsigned int>& Vb) {
    return dotrun<unsigned int>(Va,Vb);
  }

  template <typename T>
  T normSQ(const Vector<T>& V) { return dot(V,V); }

  double norm(const Vector<double>& V) {
    assert(IsAvailable(V));
    return dnrm2_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(V.size))),
                  const_cast<double*>(V.data),const_cast<long*>(&lOne));
  }

  float norm(const Vector<float>& V) {
    assert(IsAvailable(V));
    return snrm2_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(V.size))),
                  const_cast<float*>(V.data),const_cast<long*>(&lOne));
  }

  double asum(const Vector<double>& V) {
    assert(IsAvailable(V));
    return dasum_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(V.size))),
                  const_cast<double*>(V.data),const_cast<long*>(&lOne));
  }

  float asum(const Vector<float>& V) {
    assert(IsAvailable(V));
    return sasum_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(V.size))),
                  const_cast<float*>(V.data),const_cast<long*>(&lOne));
  }

  template <typename T>
  T asum(const Vector<T>& V) {
    assert(IsAvailable(V));
    T* p=V.data;
    T sum;
    for(unsigned int i=0;i<V.size;++i,++p)  shift(sum,iOne,absval(*p));
    return sum;
  }

  template <typename T>
  ostream& operator<<(ostream& os, const Vector<T>& v) {
    assert(IsAvailable(v));
    os<<v[0];
    for(unsigned int i=1;i<v.size;++i)  os<<"\t"<<v[i];
    return os;
  }

  template <typename T>
  istream& operator>>(istream& is, Vector<T>& v) {
    assert(IsAvailable(v));
    for(unsigned int i=0;i<v.size;++i)  is>>v[i];
    return is;
  }

  void crossProd(Vector<double>& V,
                 const Vector<double>& Va, const Vector<double>& Vb,
                 const unsigned int off=uZero, const unsigned int step=uOne,
                 const unsigned int aoff=uZero, const unsigned int astep=uOne,
                 const unsigned int boff=uZero, const unsigned int bstep=uOne){
    assert(off+step+step<=V.size);
    assert(aoff+astep+astep<=Va.size);
    assert(boff+bstep+bstep<=Vb.size);
    double *p=V.data+off;
    double *pa=const_cast<double*>(Va.data)+aoff;
    double *pb=const_cast<double*>(Vb.data)+boff;
    unsigned int dastep=astep+astep, dbstep=bstep+bstep, dstep=step+step;
    p[0]    = pa[astep] *pb[dbstep] -pa[dastep] *pb[bstep];
    p[step] = pa[dastep]*pb[0]      -pa[0]      *pb[dbstep];
    p[dstep]= pa[0]     *pb[bstep]  -pa[astep]  *pb[0];
  }

  void crossProd(Vector<float>& V,
                 const Vector<float>& Va, const Vector<float>& Vb,
                 const unsigned int off=uZero, const unsigned int step=uOne,
                 const unsigned int aoff=uZero, const unsigned int astep=uOne,
                 const unsigned int boff=uZero, const unsigned int bstep=uOne){
    assert(off+step+step<=V.size);
    assert(aoff+astep+astep<=Va.size);
    assert(boff+bstep+bstep<=Vb.size);
    float *p=V.data+off;
    float *pa=const_cast<float*>(Va.data)+aoff;
    float *pb=const_cast<float*>(Vb.data)+boff;
    unsigned int dastep=astep+astep, dbstep=bstep+bstep, dstep=step+step;
    p[0]    = pa[astep] *pb[dbstep] -pa[dastep] *pb[bstep];
    p[step] = pa[dastep]*pb[0]      -pa[0]      *pb[dbstep];
    p[dstep]= pa[0]     *pb[bstep]  -pa[astep]  *pb[0];
  }

}

#endif
