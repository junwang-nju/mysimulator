
#ifndef _Memory_H_
#define _Memory_H_

#include <cstdlib>

namespace std {

  template <typename T>
  int safe_delete(T* ptr) {
    if(ptr==NULL)   return 0;
    delete[] ptr;
    ptr=NULL;
    return 1;
  }

}

#endif
