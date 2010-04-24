
#ifndef _Parameter_Key_H_
#define _Parameter_Key_H_

#include "hash-func.h"
#include "vector-impl.h"
#include "storage-state-name.h"
#include "error-proc.h"

namespace std {

  struct ParameterKey;
  bool IsAvailable(const ParameterKey&);
  void assign(ParameterKey&, const ParameterKey&);
  void release(ParameterKey&);

  struct ParameterKey {

    unsigned int* index;
    unsigned int  size;
    unsigned int  hsize;
    unsigned int  hash[3];
    unsigned int  state;

    typedef ParameterKey  Type;

    ParameterKey() : index(NULL), size(0), hsize(0), state(Unused) {
      hash[0]=hash[1]=hash[2]=0;
    }
    ParameterKey(const Type&) { myError("Cannot create from Parameter Key"); }
    Type& operator=(const Type& K) { assign(*this,K); return *this; }
    ~ParameterKey() { release(*this); }

  };

  bool IsAvailable(const ParameterKey& K) { return IsAvailable(K.index); }

  void buildhash(ParameterKey& K) {
    K.hash[0]=hash_ap(reinterpret_cast<char*>(K.index),K.hsize);
    K.hash[1]=hash_dek(reinterpret_cast<char*>(K.index),K.hsize);
    K.hash[2]=hash_bp(reinterpret_cast<char*>(K.index),K.hsize);
  }

  void assign(ParameterKey& dest, const ParameterKey& src) {
    assert(IsAvailable(src));
    unsigned int n=(dest.size<src.size?dest.size:src.size);
    assign(dest.index,src.index,n);
    buildhash(dest);
  }

  void release(ParameterKey& K) {
    if(K.state==Allocated) safe_delete_array(K.index);  else K.index=NULL;
    K.size=0; K.hsize=0;
    K.hash[0]=K.hash[1]=K.hash[2]=0;
    K.state=Unused;
  }

  void allocate(ParameterKey& K, const unsigned int nidx) {
    release(K);
    K.index=new unsigned int[nidx];
    K.size=nidx;
    K.hsize=4*nidx;
    K.state=Allocated;
    assign(K.index,uZero,K.size);
  }

  void refer(ParameterKey& dest, const ParameterKey& src) {
    release(dest);
    dest.index=src.index;
    dest.state=Reference;
    dest.size=src.size;
    dest.hsize=src.hsize;
    assign(dest.hash,src.hash,3);
  }

  istream& operator>>(istream& is, ParameterKey& K) {
    assert(IsAvailable(K));
    for(unsigned int i=0;i<K.size;++i) is>>K.index[i];
    buildhash(K);
    return is;
  }

  int compare(const ParameterKey& k1, const ParameterKey& k2) {
    for(unsigned int i=0;i<3;++i)
      if(k1.hash[i]!=k2.hash[i]) return (k1.hash[i]>k2.hash[i]?1:-1);
    return 0;
  }

}

#endif

