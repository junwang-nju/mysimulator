
#ifndef _Random_MT_SFMT_Module_InitFunc_H_
#define _Random_MT_SFMT_Module_InitFunc_H_

namespace mysimulator {

  unsigned int _SFMTInitFuncA(unsigned int x) { return (x^(x>>27))*1664525U; }

  unsigned int _SFMTInitFuncB(unsigned int x) {
    return (x^(x>>27))*156608394U;
  }

}

#endif

