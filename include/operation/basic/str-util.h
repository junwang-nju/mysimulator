
#ifndef _String_Utility_H_
#define _String_Utility_H_

#include "data/basic/vector.h"

namespace std {

  void normalize(char* name, const unsigned int size) {
    if(islower(name[0]))  name[0]=toupper(name[0]);
    for(unsigned int i=1;i<size;++i) {
      if(name[i-1]=='-')  {
        if(islower(name[i]))  name[i]=toupper(name[i]);
      } else name[i]=tolower(name[i]);
    }
  }

  void normalize(Vector<char>& name) { normalize(name.data,name.size); }

  void capitalize(char* name, const unsigned int size) {
    for(unsigned int i=0;i<size;++i) {
      if(name[i]=='_')  name[i]=' ';
      name[i]=toupper(name[i]);
    }
  }

  void capitalize(Vector<char>& name) { capitalize(name.data,name.size); }

}

#endif


