
#ifndef _Array_1D_Content_Interface_H_
#define _Array_1D_Content_Interface_H_

#include "intrinsic-type/valid.h"
#include <cassert>

namespace mysimulator {

  template <typename T>
  struct Array1DContent {

    public:

      typedef Array1DContent<T>   Type;

      unsigned int size;
      int first;
      int last;
      T* head;
      T* start;

      Array1DContent() : size(0), first(0), last(0), head(NULL), start(NULL) {}
      ~Array1DContent() { clearData(); }

      void clearData() { size=0; first=last=0; head=NULL; start=NULL; }
      bool isvalid() const { return (size>0)&&IsValid(head)&&IsValid(start); }

      T& operator[](const int& I) {
        assert(isvalid());
        assert((I>=first)&&(I<=last));
        return *(head+I);
      }
      const T& operator[](const int& I) const {
        assert(isvalid());
        assert((I>=first)&&(I<=last));
        return *(head+I);
      }

    private:

      Array1DContent(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  bool IsValid(const Array1DContent<T>& AC) { return AC.isvalid(); }

  template <typename T>
  void release(Array1DContent<T>& AC) { AC.clearData(); }

  template <typename T>
  bool IsValid(const Array1DContent<T>& AC, const int& fst,
               const unsigned int& del, const unsigned int& n) {
    return IsValid(AC)&&(fst>=AC.first)&&
           (fst+static_cast<int>((n-1)*del)<=AC.last);
  }

  template <typename T>
  bool IsValid(const Array1DContent<T>& AC, const int& fst,
               const unsigned int& n) {
    return IsValid(AC)&&(fst>=AC.first)&&
           (fst+static_cast<int>(n-1)<=AC.last);
  }

  template <typename T>
  bool IsValid(const Array1DContent<T>& AC, const unsigned int& n) {
    return IsValid(AC)&&(n<=AC.size);
  }

}

#endif

