
#ifndef _Basic_Align_H_
#define _Basic_Align_H_

namespace mysimulator {

  template <typename T>
  unsigned int __span16(unsigned int n) {
    unsigned int nbyte=n*sizeof(T);
    return ((nbyte&(~0xFU))+((nbyte&0xFU)==0?0:0x10U))/sizeof(T);
  }

}

#endif

