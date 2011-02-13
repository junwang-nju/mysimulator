
#ifndef _Parameter_List_H_
#define _Parameter_List_H_

#include "data/derived/parameter-key.h"
#include "data/basic/unique-parameter.h"
#include "data/basic/btree.h"

namespace std {

  typedef Vector<UniqueParameter> ParameterValue;
  typedef BTree<ParameterKey,ParameterValue>  ParameterTreeType;

  struct ParameterList : public Vector<ParameterTreeType> {
    typedef ParameterList   Type;
    typedef Vector<ParameterTreeType> ParentType;

    unsigned int size;
    ParameterKey* key;
    ParameterValue* value;

    ParameterList() : ParentType(), size(0), key(NULL), value(NULL) {}
    ParameterList(const Type& L) { Error("Cannot create Parameter List"); }
    Type& operator=(const Type& L) {
      Error("Cannot copy Parameter List");
      return *this;
    }
    ~ParameterList() { release(*this); }

    void update() {
      IsAvailable(static_cast<ParentType&>(*this));
      for(unsigned int i=0;i<0xFFFFU;++i) release(this->operator[](i));
      for(unsigned int i=0;i<size;++i)
        insert(this->operator[]((key[i].hash[0]&0xFFFF0000U)>>16),
               key[i],value[i]);
    }    

  };

  bool IsAvailable(const ParameterList& L) {
    return IsAvailable(static_cast<const Vector<ParameterTreeType>&>(L));
  }

  void release(ParameterList& L) {
    L.size=0;
    if(L.state==Allocated) {
      safe_delete_array(L.key);
      safe_delete_array(L.value);
    } else { L.key=NULL; L.value=NULL; }
    release(static_cast<Vector<ParameterTreeType>&>(L));
  }

  void copy(ParameterList& L, const ParameterList& cL) {
    assert(IsAvailable(L));
    assert(IsAvailable(cL));
    int n=(L.size<cL.size?L.size:cL.size);
    for(int i=0;i<n;++i) {
      copy(L.key[i],cL.key[i]);
      copy(L.value[i],cL.value[i]);
    }
    L.update();
  }

  void refer(ParameterList& L, const ParameterList& rL) {
    assert(IsAvailable(rL));
    release(L);
    L.size=rL.size;
    L.key=rL.key;
    L.value=rL.value;
    refer(static_cast<Vector<ParameterTreeType>&>(L),
          static_cast<const Vector<ParameterTreeType>&>(rL));
  }

  template <typename T>
  void allocateKeyValue(T*& item,
                        const unsigned int size, const unsigned int nitem) {
    item=new T[nitem];
    for(unsigned int i=0;i<nitem;++i) allocate(item[i],size);
  }

  template <typename T>
  void allocateKeyValue(T*& item,
                        const unsigned int* size, const unsigned int nitem,
                        const int off=iZero, const int step=iOne) {
    item=new T[nitem];
    unsigned int *ps=const_cast<unsigned int*>(size)+off;
    for(unsigned int i=0;i<nitem;++i,ps+=step) allocate(item[i],*ps);
  }

  template <typename T>
  void allocateKeyValue(T*& item, const Vector<unsigned int>& size) {
    allocateKeyValue(item,size.data,size.size);
  }

  void allocate(ParameterList& L,
                const unsigned int ksize, const unsigned int vsize,
                const unsigned int nitem) {
    allocate(static_cast<Vector<ParameterTreeType>&>(L),0xFFFFU);
    L.size=nitem;
    allocateKeyValue(L.key,ksize,nitem);
    allocateKeyValue(L.value,vsize,nitem);
  }

  void allocate(ParameterList& L,
                const unsigned int* ksize, const unsigned int vsize,
                const unsigned int nitem,
                const int koff=iZero, const int kstep=iOne) {
    allocate(static_cast<Vector<ParameterTreeType>&>(L),0xFFFFU);
    L.size=nitem;
    allocateKeyValue(L.key,ksize,nitem,koff,kstep);
    allocateKeyValue(L.value,vsize,nitem);
  }

  void allocate(ParameterList& L,
                const unsigned int ksize, const unsigned int* vsize,
                const unsigned int nitem,
                const int voff=iZero, const int vstep=iOne) {
    allocate(static_cast<Vector<ParameterTreeType>&>(L),0xFFFFU);
    L.size=nitem;
    allocateKeyValue(L.key,ksize,nitem);
    allocateKeyValue(L.value,vsize,nitem,voff,vstep);
  }

  void allocate(ParameterList& L,
                const unsigned int* ksize, const unsigned int* vsize,
                const unsigned int nitem,
                const int koff=iZero, const int kstep=iOne,
                const int voff=iZero, const int vstep=iOne) {
    allocate(static_cast<Vector<ParameterTreeType>&>(L),0xFFFFU);
    L.size=nitem;
    allocateKeyValue(L.key,ksize,nitem,koff,kstep);
    allocateKeyValue(L.value,vsize,nitem,voff,vstep);
  }

  void allocate(ParameterList& L,
                const unsigned int ksize, const Vector<unsigned int>& vsize) {
    allocate(L,ksize,vsize.data,vsize.size);
  }

  void allocate(ParameterList& L,
                const Vector<unsigned int>& ksize, const unsigned int vsize) {
    allocate(L,ksize.data,vsize,ksize.size);
  }

  void allocate(ParameterList& L,
                const unsigned int* ksize, const Vector<unsigned int>& vsize,
                const unsigned int nitem,
                const int koff=iZero, const int kstep=iOne) {
    assert(nitem==vsize.size);
    allocate(L,ksize,vsize.data,nitem,koff,kstep);
  }

  void allocate(ParameterList& L,
                const Vector<unsigned int>& ksize, const unsigned int* vsize,
                const unsigned int nitem,
                const int voff=iZero, const int vstep=iOne) {
    assert(nitem==ksize.size);
    allocate(L,ksize.data,vsize,nitem,voff,vstep);
  }

  void allocate(ParameterList& L,
                const Vector<unsigned int>& ksize,
                const Vector<unsigned int>& vsize) {
    assert(ksize.size==vsize.size);
    allocate(L,ksize.data,vsize.data,ksize.size);
  }

  const ParameterValue* get(const ParameterList& L,
                            const unsigned int* idx, const unsigned int nidx,
                            const int off=iZero, const long step=iOne) {
    static ParameterKey K;
    allocate(K,nidx);
    scopy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&nidx)),
           reinterpret_cast<float*>(const_cast<unsigned int*>(idx)+off),
           const_cast<long*>(&step),reinterpret_cast<float*>(K.data),
           const_cast<long*>(&lOne));
    K.update();
    return get(L[(K.hash[0]&0xFFFF0000U)>>16],K);
  }

  const ParameterValue* get(const ParameterList& L,
                            const Vector<unsigned int>& idx) {
    return get(L,idx.data,idx.size);
  }

}

#endif
