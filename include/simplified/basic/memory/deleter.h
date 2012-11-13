
#ifndef _Basic_Memory_Deleter_H_
#define _Basic_Memory_Deleter_H_

#include <cstdlib>

namespace mysimulator {

  template <typename T>
  void __delete_unit(void* ptr) { if( ptr!=nullptr )  delete (T*&)ptr; }

  template <typename T>
  void __delete_array(void* ptr) { if( ptr!=nullptr ) delete[] (T*&)ptr; }

}

#endif

