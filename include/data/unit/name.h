
#ifndef _Unit_Name_H_
#define _Unit_Name_H_

#include "operation/basic/map-op.h"
#include "data/basic/file-input.h"
#include <cstring>

namespace std {

  static Map<Vector<char>,unsigned int>     UnitNameResolver;
  static Map<unsigned int,Vector<char> >    UnitIDResolver;
  static Map<unsigned int,Vector<char> >    UnitNameSimplifier;
  static Map<unsigned int,char>             UnitNameCoder;

  void loadAminoAcid(const char* ROOT=".") {
    unsigned int id;
    if(!IsAvailable(UnitNameResolver))  {
      allocate(UnitNameResolver);
      id=0;
    } else id=UnitNameResolver.MapData.head->parent->content->value+1;
    if(!IsAvailable(UnitIDResolver)) allocate(UnitIDResolver);
    if(!IsAvailable(UnitNameSimplifier))  allocate(UnitNameSimplifier);
    if(!IsAvailable(UnitNameCoder)) allocate(UnitNameCoder);
    char *buff=new char[1024];
    strncpy(buff,ROOT,strlen(ROOT));
    strcpy(buff+strlen(ROOT),"/name.amino-acid");
    FileInput FI;
    allocate(FI,buff);
    Vector<char> name;
    unsigned int nc;
    nc=0;
    while (!IsFail(FI)) {
      FI>>buff;
      if(strcmp(buff,"..")==0) break;
      if(strcmp(buff,".")==0) {
        nc=0;
        ++id;
      }
      else {
        refer(name,buff,strlen(buff));
        add(UnitNameResolver,name,id,Allocated,Allocated);
        if(nc==0) add(UnitIDResolver,id,name,Allocated,Allocated);
        if(nc==1) add(UnitNameSimplifier,id,name,Allocated,Allocated);
        if(nc==2) {
          assert(name.size==1);
          add(UnitNameCoder,id,name[0],Allocated,Allocated);
        }
        ++nc;
      }
    }
    delete[] buff;
  }

}

#endif

