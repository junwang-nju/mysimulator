
#ifndef _Array_1D_H_
#define _Array_1D_H_

#include "pointer/allocate.h"
#include <cassert>

namespace mysimulator {

  template <typename T>
  struct Array1D : public Pointer<T> {

    public:

      typedef Array1D<T>      Type;
      typedef Pointer<T>      ParentType;

      unsigned int size;
      int first,last;
      T* head;
      T* start;

      Array1D()
        : ParentType(), size(0), first(0), last(0), head(NULL), start(NULL) {}
      Array1D(const unsigned int n)
        : ParentType(),size(n),first(0),last(n-1), head(NULL), start(NULL) {
        allocate(*static_cast<ParentType*>(this),size);
        head=this->operator()();
        start=head+first;
      }
      Array1D(const int& fst, const int& lst)
        : ParentType(), size(lst-fst+1), first(fst), last(lst), head(NULL),
          start(NULL) {
        assert(fst<lst);
        allocate(*static_cast<ParentType*>(this),size);
        head=this->operator()()-first;
        start=head+first;
      }
      ~Array1D() { clearData(); }

      void clearData() {
        static_cast<ParentType* const&>(this)->clearData();
        size=0;
        first=last=0;
        head=NULL;
        start=NULL;
      }
      bool isvalid() const {
        return static_cast<const ParentType* const&>(this)->isvalid()&&(size>0);
      }

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

      Array1D(const Type&) {}
      Type& operatorr(const Type&) { return *this; }

  };

  template <typename T>
  bool IsValid(const Array1D<T>& v) { return v.isvalid(); }

  template <typename T>
  void release(Array1D<T>& v) { v.clearData(); }

}

#endif

