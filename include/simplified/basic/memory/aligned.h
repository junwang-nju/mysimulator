
#ifndef _Basic_Memory_Aligned_H_
#define _Basic_Memory_Aligned_H_

#include <cstdlib>

namespace mysimulator {

  static const unsigned int _align_bytes = 16; // 128 bits

  inline void * __aligned_malloc(unsigned int size) {
    static_assert(sizeof(unsigned int) == sizeof(void*),
                  "void pointer and unsigned int have different size!\n");
    void * real = std::malloc( size + _align_bytes + sizeof(void*) );
    if(real == nullptr)   return real;
    unsigned int iptr = reinterpret_cast<unsigned int>(real) + sizeof(void*);
    void * used = reinterpret_cast<void*>((iptr&(~0xFU))+0x10U);
    reinterpret_cast<void**>(used)[-1]=real;
    return used;
  }

  inline void __aligned_free(void* ptr) {
    if( ptr != nullptr )  std::free( *(reinterpret_cast<void**>(ptr)-1) );
    ptr = nullptr;
  }

  template <typename T>
  unsigned int __span16_byte( unsigned int n ) {
    unsigned int nbyte = n * sizeof(T);
    return ( ( nbyte & (~0xFU) ) + ( (nbyte&0xFU)==0 ? 0 : 0x10U ) ) ;
  }

  template <typename T>
  unsigned int __span16( unsigned int n ) {
    return __span16_byte<T>(n) / sizeof(T);
  }

}

#endif

