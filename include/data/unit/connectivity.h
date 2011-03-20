
#ifndef _Unit_Connectivity_H_
#define _Unit_Connectivity_H_

#include "operation/unit/composition-op.h"

namespace std {

  static Map<Vector<unsigned int>,char>  ConnectedID;
  static bool IsAminoAcidConnectivityLoaded=false;

  void loadAminoAcidConnectivity(const char* ROOT=".") {
    if(!IsAvailable(ConnectedID)) allocate(ConnectedID);
    loadAminoAcidComposition(ROOT);
    char *buff=new char[1024];
    strncpy(buff,ROOT,strlen(ROOT));
    strcpy(buff+strlen(ROOT),"/connect.amino-acid");
    FileInput FI;
    allocate(FI,buff);
    Vector<char> name;
    Vector<unsigned int> id(2);
    unsigned int nc=0;
    strncpy(buff,"   -",4);
    while(!IsFail(FI)) {
      FI>>(buff+4);
      if(strcmp(buff+4,"..")==0)  break;
      if(strcmp(buff+4,".")==0)  nc=0;
      else if(strcmp(buff+4,":")==0)  {
        FI>>buff;
        buff[3]='-';
      }
      else {
        refer(name,buff,strlen(buff));
        normalize(name);
        const unsigned int* pid=getCompositionID(name);
        if(pid==NULL) Error("Unknown Amino Acid Composition");
        id[nc]=*pid;
        if(nc==1) {
          add(ConnectedID,id,' ',Allocated,Allocated);
          nc=id[0]; id[0]=id[1];  id[1]=nc;
          add(ConnectedID,id,' ',Allocated,Allocated);
        }
        ++nc;
      }
    }
    release(FI);
    delete[] buff;
    IsAminoAcidConnectivityLoaded=true;
  }

}

#endif

