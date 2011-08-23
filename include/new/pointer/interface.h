
#ifndef _Pointer_Interface_H_
#define _Pointer_Interface_H_

#include <cstdlib>
#include <cstdio>

namespace mysimulator {

  template <typename T>
  struct Pointer {

    public:

      typedef Pointer<T>    Type;
      typedef void (*DelFuncType)(T*&);

      T* ptr;
      int state;
      Type* parent;
      int pstate;
      DelFuncType delfunc;

      Pointer()
        : ptr(NULL), state(-1), parent(NULL), pstate(-1), delfunc(NULL) {}
      ~Pointer() { clearData(); }

      void clearData() {
        if(state>=0) {
          if(pstate<0) {
            if(state==0) {
              if(ptr!=NULL) delfunc(ptr);
            } else {
              fprintf(stderr,"state prohibits clearData Operation");
              exit(1);
            }
          } else if(parent!=NULL) --(parent->state);
        }
        ptr=NULL;
        state=-1;
        parent=NULL;
        pstate=-1;
        delfunc=NULL;
      }
      bool isvalid() const { return (ptr!=NULL)&&(state>=0); }

      T*& operator()() { return ptr; }
      const T* const& operator()() const { return ptr; }

    private:

      Pointer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  bool IsValid(const Pointer<T>& P) { return P.isvalid(); }

  template <typename T>
  void release(Pointer<T>& P) { return P.clearData(); }

}

#endif

