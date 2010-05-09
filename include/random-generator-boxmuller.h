
#ifndef _Random_Generator_BoxMuller_H_
#define _Random_Generator_BoxMuller_H_

#include <cmath>
#include "error-proc.h"
#include "memory.h"
#include "storage-state-name.h"
#include "random-generator-uniform.h"

namespace std {

  template <typename UniformRNG>
  struct BoxMuller {

    typedef BoxMuller<UniformRNG>   Type;

    UniformRNG *urng;
    double *DbFac;
    bool *isSecond;
    double *output;
    unsigned int state;

    BoxMuller()
      : urng(NULL), DbFac(NULL), isSecond(NULL), output(NULL), state(Unused) {}
    BoxMuller(const Type&) { myError("Cannot create from BoxMuller"); }
    Type& operator=(const Type& BM) { assign(*this,BM); return *this; }
    ~BoxMuller() { release(*this); }

    void Init(const unsigned  int seed) { init(*this,seed); }

    const double& DoubleNormal() {
      if(*isSecond) *output=DbFac[1]*DbFac[2];
      else {
        do {
          DbFac[0]=rand<double>(*urng);  DbFac[0]+=DbFac[0]; DbFac[0]-=1.;
          DbFac[1]=rand<double>(*urng);  DbFac[1]+=DbFac[1]; DbFac[1]-=1.;
          DbFac[2]=DbFac[0]*DbFac[0]+DbFac[1]*DbFac[1];
        } while( (DbFac[2]>1.) || (DbFac[2]==0.) );
        DbFac[2]=sqrt(-2.0*log(DbFac[2])/DbFac[2]);
        *output=DbFac[0]*DbFac[2];
      }
      *isSecond=!(*isSecond);
      return *output;
    }

  };

  template <typename UniformRNG>
  bool IsAvailable(const BoxMuller<UniformRNG>& bm) {
    return IsAvailable(bm.urng);
  }
  template <typename UniformRNG>
  bool IsRandomGenerator(const BoxMuller<UniformRNG>&) { return true; }

  template <typename UniformRNG>
  void allocate(BoxMuller<UniformRNG>& BM) {
    BM.urng=new UniformRNG;
    allocate(*BM.urng);
    BM.DbFac=new double[3];
    BM.isSecond=new bool;
    BM.output=new double;
    BM.state=Allocated;
    *BM.isSecond=true;
  }

  template <typename UniformRNG>
  void release(BoxMuller<UniformRNG>& BM) {
    if(BM.state==Allocated) {
      safe_delete(BM.urng);
      safe_delete_array(BM.DbFac);
      safe_delete(BM.isSecond);
      safe_delete(BM.output);
    } else {
      BM.urng=NULL;
      BM.DbFac=NULL;
      BM.isSecond=NULL;
      BM.output=NULL;
    }
    BM.state=Unused;
  }

  template <typename UniformRNG>
  void refer(BoxMuller<UniformRNG>& dest, const BoxMuller<UniformRNG>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.urng=src.urng;
    dest.DbFac=src.DbFac;
    dest.isSecond=src.isSecond;
    dest.output=src.output;
    dest.state=Reference;
  }

  template <typename UniformRNG>
  void assign(BoxMuller<UniformRNG>& dest, const BoxMuller<UniformRNG>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(dest.urng,src.urng);
    assign(dest.DbFac,src.DbFac,3);
    *(dest.isSecond)=*(src.isSecond);
  }

  template <typename UniformRNG>
  void init(BoxMuller<UniformRNG>& bm, const unsigned int seed) {
    init(*bm.urng,seed);
    *bm.isSecond=false;
  }

  template <typename UniformRNG>
  const double& rand(BoxMuller<UniformRNG>& bm) { return bm.DoubleNormal(); }

  template <typename T>
  const T& rand(BoxMuller<MT_Standard>&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<521> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<1279> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<2203> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<4253> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<11213> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<19937> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<44497> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<86243> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<132049> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<216091> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<607> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<1279> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<2281> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<4253> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<11213> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<19937> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<44497> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<86243> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<132049> >&) {
    myError("Default form is prohibited");
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<216091> >&) {
    myError("Default form is prohibited");
  }

  template <>
  const double& rand<double>(BoxMuller<MT_Standard>& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<521> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<1279> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<2203> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<4253> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<11213> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<19937> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<44497> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<86243> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<132049> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<216091> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<607> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<1279> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<2281> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<4253> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<11213> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<19937> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<44497> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<86243> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<132049> >& bm) { return rand(bm); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<216091> >& bm) { return rand(bm); }

  template <typename UniformRNG>
  ostream& operator<<(ostream& os, const BoxMuller<UniformRNG>& bm) {
    os<<*bm.urng<<"\t";
    unsigned long long int *p;
    p=reinterpret_cast<unsigned long long int*>(const_cast<double*>(bm.DbFac));
    for(unsigned int i=0;i<3;++i) os<<p[i]<<"\t";
    os<<*(bm.isSecond);
    return os;
  }

  template <typename UniformRNG>
  istream& operator>>(istream& is, BoxMuller<UniformRNG>& bm) {
    is>>*bm.urng;
    unsigned long long int *p;
    p=reinterpret_cast<unsigned long long int*>(const_cast<double*>(bm.DbFac));
    for(unsigned int i=0;i<3;++i) is>>p[i];
    is>>*(bm.isSecond);
    return is;
  }

}

#endif

