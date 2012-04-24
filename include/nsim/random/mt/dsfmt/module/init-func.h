
#ifndef _Random_MT_dSFMT_Module_InitFunc_H_
#define _Random_MT_dSFMT_Module_InitFunc_H_

namespace mysimulator {

  unsigned int _dSFMTInitFuncA(unsigned int x) { return (x^(x>>27))*1664525U; }

  unsigned int _dSFMTInitFuncB(unsigned int x) {
    return (x^(x>>27))*156608394U;
  }

}

#endif

