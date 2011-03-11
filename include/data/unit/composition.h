
#ifndef _Unit_Composition_H_
#define _Unit_Composition_H_

#include "operation/basic/map-op.h"
#include "data/basic/file-input.h"

namespace std {

  static Map<Vector<char>,unsigned int>   CompositionNameResolver;

  void loadCompositionName(const char* ROOT=".") {
    unsigned int id;
    if(!IsAvailable(CompositionNameResolver)) {
      allocate(CompositionNameResolver);
      id=0;
    } else id=CompositionNameResolver.MapData.head->parent->content->value+1;
    char buff=new char[1024];
    strncpy(buff,ROOT,strlen(ROOT));
    strncpy(buff+strlen(ROOT),"/name.amino-acid-atom");
    FileInput FI;
    allocate(FI,buff);
    Vector<char> name;
    while(!IsFail(FI)) {
    }
    release(FI);
    delete[] buff;
  }

}

#endif

