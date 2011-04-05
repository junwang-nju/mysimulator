
#ifndef _Generic_Release_H_
#define _Generic_Release_H_

namespace mysimulator {

  template <typename T>
  void release(T*& ptr) {
    if(ptr==NULL) return;
    delete ptr;
    ptr=NULL;
  }

  template <typename T>
  void releaseArray(T*& ptr) {
    if(ptr==NULL) return;
    delete[] ptr;
    ptr=NULL;
  }

}

#endif

