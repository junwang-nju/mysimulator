
#ifndef _Parameter_List_H_
#define _Parameter_List_H_

#include "var-parameter-key.h"
#include "var-parameter-value.h"
#include "fix-vector.h"
#include "ref-vector.h"
#include "btree.h"

namespace std {

  template <template <typename> class VecType>
  class ParameterList {

    public:

      typedef ParameterList<VecType>    Type;
 
      typedef BTree<varParameterKey,varParameterValue>  TreeType;

      typedef fixVector<TreeType,0xFFFFU>* HashTreePtrType;

    protected:

      VecType<varParameterKey>        KeyList;

      VecType<varParameterValue>      ValueList;

      HashTreePtrType    PtrHashTree;

    public:

      ParameterList() : KeyList(), ValueList(), PtrHashTree(NULL) {}

      ParameterList(const unsigned int N)
        : KeyList(), ValueList(), PtrHashTree(NULL) {
        allocate(N);
      }

      ParameterList(const Type& PL) {
        myError("Cannot create from Parameter List");
      }

     ~ParameterList() { clear(); }

      Type& operator=(const Type& PL) {
        KeyList=PL.KeyList;
        ValueList=PL.ValueList;
        updateHashTree();
        return *this;
      }

      template <template <typename> class iVecType>
      Type& operator=(const ParameterList<iVecType>& PL) {
        KeyList=PL.KeyList;
        ValueList=PL.ValueList;
        updateHashTree();
        return *this;
      }

      void clear() {
        KeyList.clear();
        ValueList.clear();
        PtrHashTree=NULL;
      }

      VecType<varParameterKey>& keylist() { return KeyList; }

      const VecType<varParameterKey>& keylist() const { return KeyList; }

      VecType<varParameterValue>& valuelist() { return ValueList; }

      const VecType<varParameterValue>& valuelist() const { return ValueList; }

      HashTreePtrType& ptrhashtree() { return PtrHashTree; }
      
      const HashTreePtrType& ptrhashtree() const { return PtrHashTree; }

      void clearHashTree() {
        if(PtrHashTree==NULL) return;
        unsigned int n=PtrHashTree->size();
        for(unsigned int i=0;i<n;++i) (*PtrHashTree)[i].clear();
      }

      void updateHashTree() {
        assert(KeyList.size()==ValueList.size());
        clearHashTree();
        unsigned int n=KeyList.size();
        for(unsigned int i=0;i<n;++i)
          (*PtrHashTree)[(KeyList[i].hash()[0]&0xFFFF0000)>>16].insert(
              KeyList[i],ValueList[i]);
      }

      const varParameterValue* get(const VectorBase<unsigned int>& idx) const {
        varParameterKey tKey;
        tKey.allocate(idx.size());
        tKey.index()=idx;
        tKey.BuildHash();
        return (*PtrHashTree)[(tKey.hash()[0]&0xFFFF0000)>>16].get(tKey);
      }

      void allocate(const unsigned int N) {
        myError("Not Available");
      }

    protected:

      template <typename T>
      void allocateList(varVector<T>& List,
                        const unsigned int Size, const unsigned int N) {
        List.allocate(N);
        for(unsigned int i=0;i<N;++i) List.allocate(Size);
      }

      template <typename T>
      void allocateList(varVector<T>& List,
                        const VectorBase<unsigned int>& Size,
                        const unsigned int N,
                        const unsigned int off=uZero,
                        const unsigned int step=uOne) {
        assert(off+N*step<=Size.size());
        List.allocate(N);
        for(unsigned int i=0,n=off;i<N;++i,n+=step) List[i].allocate(Size[n]);
      }

    public:

      void allocate(const unsigned int kSize, const unsigned int vSize,
                    const unsigned int N) {
        myError("Not Available");
      }

      void allocate(const unsigned int kSize,
                    const VectorBase<unsigned int>& vSize,
                    const unsigned int N,
                    const unsigned int voff=uZero,
                    const unsigned int vstep=uOne) {
        myError("Not Available");
      }

      void allocate(const VectorBase<unsigned int>& kSize,
                    const unsigned int vSize,
                    const unsigned int N,
                    const unsigned int koff=uZero,
                    const unsigned int kstep=uOne) {
        myError("Not Available");
      }

      void allocate(const VectorBase<unsigned int>& kSize,
                    const VectorBase<unsigned int>& vSize,
                    const unsigned int N,
                    const unsigned int koff=uZero,
                    const unsigned int kstep=uOne,
                    const unsigned int voff=uZero,
                    const unsigned int vstep=uOne) {
        myError("Not Available");
      }

      void allocate(const unsigned int kSize,
                    const VectorBase<unsigned int>& vSize) {
        allocate(kSize,vSize,vSize.size());
      }

      void allocate(const VectorBase<unsigned int>& kSize,
                    const unsigned int vSize) {
        allocate(kSize,vSize,kSize.size());
      }

      void allocate(const VectorBase<unsigned int>& kSize,
                    const VectorBase<unsigned int>& vSize) {
        unsigned int n;
        n=(kSize.size()<vSize.size()?kSize.size():vSize.size());
        allocate(kSize,vSize,n);
      }

      template <template <typename> class iVecType>
      void refer(const ParameterList<iVecType>& PL) {
        myError("Not Available");
      }

      Type& CanonicalForm() { return *this; }

      const Type& CanonicalForm() const { return *this; }

  };

  template <>
  ParameterList<varVector>::~ParameterList() {
    clearHashTree();
    safe_delete(ptrhashtree());
    for(unsigned int i=0;i<keylist().size();++i) {
      keylist()[i].clear();
      valuelist()[i].clear();
    }
  }

  template <>
  void ParameterList<varVector>::clear() {
    clearHashTree();
    safe_delete(ptrhashtree());
    for(unsigned int i=0;i<keylist().size();++i) {
      keylist()[i].clear();
      valuelist()[i].clear();
    }
    KeyList.clear();
    ValueList.clear();
    PtrHashTree=NULL;
  }

  template <>
  void ParameterList<varVector>::allocate(const unsigned int N) {
    keylist().allocate(N);
    valuelist().allocate(N);
    ptrhashtree()=new fixVector<TreeType,0xFFFFU>;
  }

  template <>
  void ParameterList<varVector>::allocate(
      const unsigned int kSize, const unsigned int vSize,
      const unsigned int N) {
    allocateList(keylist(),kSize,N);
    allocateList(valuelist(),vSize,N);
    ptrhashtree()=new fixVector<TreeType,0xFFFFU>;
  }

  template <>
  void ParameterList<varVector>::allocate(
      const unsigned int kSize, const VectorBase<unsigned int>& vSize,
      const unsigned int N, const unsigned int voff, const unsigned int vstep){
    allocateList(keylist(),kSize,N);
    allocateList(valuelist(),vSize,N,voff,vstep);
    ptrhashtree()=new fixVector<TreeType,0xFFFFU>;
  }

  template <>
  void ParameterList<varVector>::allocate(
      const VectorBase<unsigned int>& kSize, const unsigned int vSize,
      const unsigned int N, const unsigned int koff, const unsigned int kstep){
    allocateList(keylist(),kSize,N,koff,kstep);
    allocateList(valuelist(),vSize,N);
    ptrhashtree()=new fixVector<TreeType,0xFFFFU>;
  }

  template <>
  void ParameterList<varVector>::allocate(
      const VectorBase<unsigned int>& kSize,
      const VectorBase<unsigned int>& vSize, const unsigned int N,
      const unsigned int koff, const unsigned int kstep,
      const unsigned int voff, const unsigned int vstep) {
    allocateList(keylist(),kSize,N,koff,kstep);
    allocateList(valuelist(),vSize,N,voff,vstep);
    ptrhashtree()=new fixVector<TreeType,0xFFFFU>;
  }

  template <>
  template <template <typename> class iVecType>
  void ParameterList<refVector>::refer(const ParameterList<iVecType>& PL) {
    keylist().refer(PL.keylist());
    valuelist().refer(PL.valuelist());
    ptrhashtree()=PL.ptrhashtree();
  }

  template <template <typename> class VecType>
  istream& operator>>(istream& is, ParameterList<VecType>& PL) {
    unsigned int n=PL.keylist().size();
    for(unsigned int i=0;i<n;++i) {
      is>>PL.keylist()[i]>>PL.valuelist()[i];
      PL.keylist()[i].BuildHash();
    }
    PL.updateHashTree();
    return is;
  }

}

#endif

