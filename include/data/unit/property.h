
#ifndef _Unit_Property_H_
#define _Unit_Property_H_

#include "operation/unit/composition-op.h"

namespace std {

  static Map<unsigned int,bool> HeavyAtomFlag;
  static bool IsHeavyAtomFlagLoaded=false;

  void loadAminoAcidHeavyAtomFlag(const char* ROOT=".") {
    if(IsHeavyAtomFlagLoaded) return;
    if(!IsAvailable(HeavyAtomFlag)) allocate(HeavyAtomFlag);
    loadAminoAcidComposition(ROOT);
    char* buff=new char[1024];
    strncpy(buff,ROOT,strlen(ROOT));
    strcpy(buff+strlen(ROOT),"/heavy.amino-acid-atom");
    FileInput FI;
    allocate(FI,buff);
    Vector<char> name;
    unsigned int nc=0;
    unsigned int id,fg;
    strncpy(buff,"   -",4);
    while(!IsFail(FI)) {
      FI>>(buff+4);
      if(strcmp(buff+4,"..")==0)    break;
      if(strcmp(buff+4,".")==0)     nc=0;
      else if(strcmp(buff+4,":")==0) {
        FI>>buff;
        buff[3]='-';
      } else {
        if(nc==0) {
          refer(name,buff,strlen(buff));
          const unsigned int* pid=getCompositionID(name);
          if(pid==NULL) Error("Unknown Atom Name");
          id=*pid;
        } else if(nc==1) {
          fg=atol(buff+4);
          add(HeavyAtomFlag,id,(fg==1?true:false),Allocated,Allocated);
        }
        ++nc;
      }
    }
    release(FI);
    delete[] buff;
    IsHeavyAtomFlagLoaded=true;
  }

}

#endif

