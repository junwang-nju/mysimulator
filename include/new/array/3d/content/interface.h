
#ifndef _Array_3D_Content_Interface_H_
#define _Array_3D_Content_Interface_H_

#include "array/2d/content/interface.h"

namespace mysimulator {

  template <typename T>
  struct Array3DContent {

    public:

      typedef Array3DContent<T>   Type;
      typedef Array2DContent<T>   SubType;
      typedef Array1DContent<T>   SubSubType;

      Array1DContent<T>           base;
      Array1DContent<SubSubType>  base2;
      Array1DContent<SubType>     infra;

      Array3DContent() : base(), base2(), infra() {}
      ~Array3DContent() { clearData(); }

      void clearData() { release(base); release(base2); release(infra); }
      bool isvalid() const { return base.isvalid()&&infra.invalid(); }

      SubType& operator[](const int& I) { return infra[I]; }
      const SubType& operator[](const int& I) const { return infra[I]; }
      const unsigned int& NumElements() const { return base.size; }
      const unsigned int& NumPlanes() const { return infra.size; }

    private:

      Array3DContent(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  bool IsValid(const Array3DContent<T>& A) { return A.isvalid(); }

  template <typename T>
  void release(Array3DContent<T>& A) { A.clearData(); }

  template <typename T>
  bool IsValid(const Array3DContent<T>& A,
               const int& pb, const unsigned int& pd, const unsigned int& np,
               const int& lb, const unsigned int& ld, const unsigned int& nl,
               const int& rb, const unsigned int& rd, const unsigned int& nr) {
    if(!IsValid(A.infra,pb,pd,np))    return false;
    for(int i=pb;i<pb+static_cast<int>(np);i+=pd)
      if(!IsValid(A[i],lb,ld,nl,rb,rd,nr))  return false;
    return true;
  }

  template <typename T>
  bool IsValid(const Array3DContent<T>& A,
               const int& pb, const unsigned int& np, const int& lb,
               const unsigned int& nl, const int& rb, const unsigned int& nr) {
    if(!IsValid(A.infra,pb,np))   return false;
    for(int i=pb;i<pb+static_cast<int>(np);i++)
      if(!IsValid(A[i],lb,nl,rb,nr))    return false;
    return true;
  }

  template <typename T>
  bool IsValid(const Array3DContent<T>& A, const unsigned int& np,
               const unsigned int& nl, const unsigned int& nr) {
    if(!IsValid(A.infra,nl))    return false;
    for(int i=A.infra.first;i<=A.infra.last;++i)
      if(!IsValid(A[i],nl,nr))  return false;
    return true;
  }

}

#endif

