
#ifndef _Array_2D_Content_Interface_H_
#define _Array_2D_Content_Interface_H_

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  struct Array2DContent {

    public:

      typedef Array2DContent<T>   Type;
      typedef Array1DContent<T>   SubType;

      Array1DContent<T> base;
      Array1DContent<SubType> infra;

      Array2DContent() : base(), infra() {}
      ~Array2DContent() { clearData(); }

      void clearData() { release(base); release(infra); }
      bool isvalid() const { return base.isvalid()&&infra.isvalid(); }

      SubType& operator[](const int& I) { return infra[I]; }
      const SubType& operator[](const int& I) const { return infra[I]; }
      const unsigned int& NumLines() const { return infra.size; }
      const unsigned int& NumElements() const { return base.size; }

    private:

      Array2DContent(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  bool IsValid(const Array2DContent<T>& A) { return A.isvalid(); }

  template <typename T>
  void release(Array2DContent<T>& A) { A.clearData(); }

  template <typename T>
  bool IsValid(const Array2DContent<T>& A,
               const int& lb, const unsigned int& ld, const unsigned int& nl,
               const int& rb, const unsigned int& rd, const unsigned int& nr) {
    if(!IsValid(A.infra,lb,ld,nl))    return false;
    for(int i=lb;i<lb+static_cast<int>(nl);i+=ld)
      if(!IsValid(A[i],rb,rd,nr))     return false;
    return true;
  }

  template <typename T>
  bool IsValid(const Array2DContent<T>& A,
               const int& lb, const unsigned int& nl,
               const int& rb, const unsigned int& nr) {
    if(!IsValid(A.infra,lb,nl))    return false;
    for(int i=lb;i<lb+static_cast<int>(nl);++i)
      if(!IsValid(A[i],rb,nr))     return false;
    return true;
  }

  template <typename T>
  bool IsValid(const Array2DContent<T>& A, const unsigned int& nl,
               const unsigned int& nr) {
    if(!IsValid(A.infra,nl))    return false;
    for(int i=A.infra.first;i<=A.infra.last;++i)
      if(!IsValid(A[i],nr))     return false;
    return true;
  }

}

#endif

