
#ifndef _Random_xSFMT_WorkFunc_H_
#define _Random_xSFMT_WorkFunc_H_

namespace mysimulator {

  unsigned int xSFMTWorkFuncA(unsigned int x) { return (x^(x>>27))*1664525U; }
  unsigned int xSFMTWorkFuncB(unsigned int x) { return (x^(x>>27))*156608394U; }

}

#endif

