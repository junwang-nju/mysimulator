
#ifndef _Error_Process_H_
#define _Error_Process_H_

#include <iostream>
#include <cstdlib>

namespace std {

  void myWarn(const char* msg) { cerr<<msg<<endl; }
  
  void myError(const char* msg) { myWarn(msg); exit(0); }

}

#endif
