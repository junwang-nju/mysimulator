
#ifndef _Matrix_Storage_Interface_H_
#define _Matrix_Storage_Interface_H_

#include "matrix/storage/item/interface.h"
#include "matrix/interface.h"
#include "matrix/triangle/property-name.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename T>
  struct MatrixStorage {

    typedef MatrixStorage<T>    Type;

    Matrix<MatrixStorageItem<T> > data;
    unsigned int gstatus;

    MatrixStorage() : data(), gstatus(1) {}
    MatrixStorage(const Type&) { Error("Copier for MatrixStorage Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for MatrixStorage Disabled!");
      return *this;
    }
    ~MatrixStorage() { clearData(); }

    void clearData() { data.clearData(); gstatus=1; }
    void unlock() { ++gstatus; }
    void unlock(const unsigned int I) {
      unsigned int n=data.property[MatrixDimension];
      for(unsigned int i=0;i<n;++i) {
        if(i==I)  continue;
        data(i,I).status=gstatus-1;
      }
    }
    void unlock(const unsigned int I, const unsigned int J) {
      data(I,J).status=gstatus-1;
    }
    void renew(const unsigned int I, const unsigned int J, const T& C) {
      MatrixStorageItem<T>& U=data(I,J);
      copy(U.content,C);
      U.status=gstatus;
    }
    unsigned int& status(const unsigned int I, const unsigned int J) {
      return data(I,J).status;
    }
    const unsigned int& status(const unsigned int I, const unsigned int J)
      const { return data(I,J).status; }
    unsigned int& status() { return gstatus; }
    const unsigned int& status() const { return gstatus; }
    T& value(const unsigned int I, const unsigned int J) {
      return data(I,J).content;
    }
    const T& value(const unsigned int I, const unsigned int J) const {
      return data(I,J).content;
    }

  };

  template <typename T>
  bool IsValid(const MatrixStorage<T>& S) { return IsValid(S.data); }

  template <typename T>
  void release(MatrixStorage<T>& S) { S.clearData(); }

  template <typename T>
  bool IsNewest(const MatrixStorage<T>& S, const unsigned int I,
                const unsigned int J) { return S.status(I,J)==S.status(); }

}

#endif

