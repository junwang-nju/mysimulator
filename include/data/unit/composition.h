
#ifndef _Unit_Composition_H_
#define _Unit_Composition_H_

#include "operation/basic/map-op.h"
#include "data/basic/file-input.h"
#include "operation/basic/str-util.h"
#include <cstring>

namespace std {

  static Map<Vector<char>,unsigned int>   CompositionNameResolver;
  static Map<unsigned int,Vector<char> >  CompositionIDResolver;
  static Map<unsigned int,Vector<char> >  CompositionPDBNameResolver;
  static bool IsAminoAcidCompositionLoaded=false;

  void loadAminoAcidComposition(const char* ROOT=".") {
    if(IsAminoAcidCompositionLoaded)  return;
    unsigned int id;
    if(!IsAvailable(CompositionNameResolver)) {
      allocate(CompositionNameResolver);
      id=0;
    } else id=CompositionNameResolver.MapData.head->parent->content->value+1;
    if(!IsAvailable(CompositionIDResolver)) allocate(CompositionIDResolver);
    if(!IsAvailable(CompositionPDBNameResolver))
      allocate(CompositionPDBNameResolver);
    char *buff=new char[1024];
    strncpy(buff,ROOT,strlen(ROOT));
    strcpy(buff+strlen(ROOT),"/name.amino-acid-atom");
    FileInput FI;
    allocate(FI,buff);
    Vector<char> name;
    unsigned int nc;
    strncpy(buff,"   -",4);
    while(!IsFail(FI)) {
      FI>>(buff+4);
      if(strcmp(buff+4,"..")==0)  break;
      if(strcmp(buff+4,".")==0) {
        nc=0;
        ++id;
      } else if(strcmp(buff+4,":")==0) {
        FI>>buff;
        buff[3]=' ';
      } else {
        refer(name,buff,strlen(buff));
        if(nc==0) {
          buff[3]='-';
          normalize(name);
          add(CompositionIDResolver,id,name,Allocated,Allocated);
        } else {
          buff[3]=' ';
          capitalize(name);
          if(nc==1) add(CompositionPDBNameResolver,id,name,Allocated,Allocated);
        }
        add(CompositionNameResolver,name,id,Allocated,Allocated);
        ++nc;
      }
    }
    release(FI);
    delete[] buff;
    IsAminoAcidCompositionLoaded=true;
  }

}

#endif

