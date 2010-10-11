
/**
 * @file matrix-storage-item.h
 * @brief The item object related to matrix-like storage
 *
 * This file contains the declaration of the object describing the
 * items which are used in storage with the shape of matrix.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Matrix_Storage_Item_H_
#define _Matrix_Storage_Item_H_

#include "memory.h"
#include "storage-state-name.h"
#include "error-proc.h"
#include "util.h"
#include <cassert>

namespace std {

  template <typename T>
  struct MatrixStorageItem {

    typedef MatrixStorageItem<T>    Type;

    T *content;
    unsigned int *status;
    unsigned int state;

    MatrixStorageItem() : content(NULL), status(NULL), state(Unused) {}
    MatrixStorageItem(const Type&) {
      myError("Cannot create from Item of Matrix Storage");
    }
    Type& operator=(const Type& MSI) { assign(*this,MSI); return *this; }
    ~MatrixStorageItem() { release(*this); }

    T& operator()() { return *content; }
    const T& operator()() const { return *content; }

  };

  template <typename T>
  bool IsAvailable(const MatrixStorageItem<T>& MSI) {
    return IsAvailable(MSI.content);
  }

  template <typename T>
  void release(MatrixStorageItem<T>& MSI) {
    if(MSI.state==Allocated) {
      safe_delete(MSI.content);
      safe_delete(MSI.status);
    } else {
      MSI.content=NULL;
      MSI.status=NULL;
    }
    MSI.state=Unused;
  }

  template <typename T>
  void assign(MatrixStorageItem<T>& dest, const MatrixStorageItem<T>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    *(dest.content)=*(src.content);
    *(dest.status)=*(src.status);
  }

  template <typename T>
  void allocate(MatrixStorageItem<T>& MSI) {
    release(MSI);
    MSI.content=new T;
    MSI.status=new unsigned int;
    MSI.state=Allocated;
  }

  template <typename T>
  void refer(MatrixStorageItem<T>& dest, const MatrixStorageItem<T>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.content=src.content;
    dest.status=src.status;
    dest.state=Reference;
  }

  template <typename T>
  ostream& operator<<(ostream& os, const MatrixStorageItem<T>& MSI) {
    os<<"["<<MSI()<<"\t("<<*(MSI.status)<<")]";
    return os;
  }

}

#endif

