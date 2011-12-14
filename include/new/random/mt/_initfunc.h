
#ifndef _Random_MT_Func4Init_H_
#define _Random_MT_Func4Init_H_

namespace mysimulator {

  unsigned int _initFuncA(const unsigned int x) { return (x^(x>>27))*1664525U; }
  unsigned int _initFuncB(const unsigned int x) {
    return (x^(x>>27))*1566083941U;
  }

}

#endif

