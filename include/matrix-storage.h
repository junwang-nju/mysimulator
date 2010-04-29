
#ifndef _Matrix_Storage_H_
#define _Matrix_Storage_H_

#include "matrix-storage-item.h"
#include "matrix.h"

namespace std {

  template <typename T>
  struct MatrixStorage {

    typedef MatrixStorage<T>    Type;

    unsigned int *gstatus;
    Matrix<MatrixStorageItem<T> > data;
    unsigned int state;

    MatrixStorage() : gstatus(NULL), data() {}
    MatrixStorage(const Type&){ myError("Cannot create from Matrix Storage"); }
    Type& operator=(const Type& MS) { assign(*this,MS); return *this; }
    ~MatrixStorage() { release(*this); }

    const MatrixStorageItem<T>&
    operator()(const unsigned int I, const unsigned int J) const {
      return data(I,J);
    }
    unsigned int& operator()() { return *gstatus; }
    const unsigned int& operator()() const { return *gstatus; }

  };

  template <typename T>
  bool IsAvailable(const MatrixStorage<T>& MS) {
    return IsAvailable(MS.gstatus);
  }

  template <typename T>
  void release(MatrixStorage<T>& MS) {
    if(IsAvailable(MS)) {
      if(MS.state==Allocated) safe_delete(MS.gstatus);
      else MS.gstatus=NULL;
      unsigned int n=MS.data.property[MatrixNumberElement];
      for(unsigned int i=0;i<n;++i) release(*(MS.data.data+i));
      release(*(MS.data.PtrOtherElement));
      release(MS.data);
      MS.state=Unused;
    }
  }

  template <typename T>
  void assign(MatrixStorage<T>& dest, const MatrixStorage<T>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    *(dest.gstatus)=*(src.gstatus);
    assign(dest.data,src.data);
  }

  template <typename T>
  void allocate(MatrixStorage<T>& MS, const unsigned int nunit) {
    release(MS);
    MS.gstatus=new unsigned int;
    allocate(MS.data,TriangleMatrix,nunit,COrder,NoTranspose,UpperTriangle,
             true,false);
    unsigned int n=MS.data.property[MatrixNumberElement];
    for(unsigned int i=0;i<n;++i) allocate(*(MS.data.data+i));
    allocate(*(MS.data.PtrOtherElement));
    MS.state=Allocated;
    MS()=1;
  }

  template <typename T>
  void refer(MatrixStorage<T>& dest, const MatrixStorage<T>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.gstatus=src.gstatus;
    refer(dest.data,src.data);
    dest.state=Reference;
  }

  template <typename T>
  void refresh(MatrixStorage<T>& MS) { ++MS(); }

  template <typename T>
  void refresh(MatrixStorage<T>& MS, const unsigned int idx) {
    unsigned int n=MS.data.property[MatrixDimension];
    for(unsigned int i=0;i<n;++i) {
      if(i==idx)  continue;
      *(MS(i,idx).status)=MS()-1;
    }
  }

  template <typename T>
  void refresh(MatrixStorage<T>& MS,
               const unsigned int I, const unsigned int J) {
    *(MS(I,J).status)=MS()-1;
  }

  template <typename T>
  bool IsUpToDate(MatrixStorage<T>& MS,
                  const unsigned int I, const unsigned int J) {
    return *(MS(I,J).status)==MS();
  }

  template <typename T>
  void update(MatrixStorage<T>& MS,
              const unsigned int I, const unsigned int J, const T& content) {
    MatrixStorageItem<T> &runItem=MS.data(I,J);
    runItem()=content;
    *(runItem.status)=MS();
  }

}

#endif

