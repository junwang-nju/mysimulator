
#ifndef _Meomry_AlignedMemory_H_
#define _Meomry_AlignedMemory_H_

#include <cstdlib>

namespace mysimulator {

  static const unsigned int alignedBytes=16; // 64bit

  inline void* __aligned_malloc(unsigned int size) {
    static_assert(sizeof(unsigned int)==sizeof(void*),
                  "void pointer and unsigned int have different size!\n");
    void *real=std::malloc(size+alignedBytes+sizeof(void*));
    if(real==nullptr)   return real;
    void* used=reinterpret_cast<void*>(
             ((reinterpret_cast<unsigned int>(real)+sizeof(void*))&(~15U))+16U);
    reinterpret_cast<void**>(used)[-1]=real;
    return used;
  }

  inline void __aligned_free(void* ptr) {
    if(ptr!=nullptr)  std::free(*(reinterpret_cast<void**>(ptr)-1));
    ptr=nullptr;
  }

}

void* operator new(unsigned int size) {
  return mysimulator::__aligned_malloc(size);
}

void operator delete(void* ptr) _GLIBCXX_USE_NOEXCEPT {
  mysimulator::__aligned_free(ptr);
}

#endif

