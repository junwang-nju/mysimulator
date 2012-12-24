
#ifndef _Basic_Configuration_File_Space_Remove_H_
#define _Basic_Configuration_File_Space_Remove_H_

#include "basic/util/string.h"
#include "basic/memory/deleter.h"
#include <cstring>
#include <cassert>

namespace mysimulator {

  void __space_remove(char*& item) {
    unsigned int n=strlen(item);
    unsigned int bg=0,ed=n-1;
    bool fg=false;
    for(unsigned int i=bg;i<=ed;++i)
      if(!isspace(item[i]))  { bg=i; fg=true; break; }
    assert(fg);
    for(unsigned int i=ed;i>=bg;--i) if(!isspace(item[i])) { ed=i;  break; }
    char *content=new char[ed-bg+2];
    SubString(content,item,bg,ed);
    __delete_array<char>(item);
    item=content;
  }

}

#endif

