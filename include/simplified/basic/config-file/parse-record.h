
#ifndef _Basic_Configuration_File_Parse_Record_H_
#define _Basic_Configuration_File_Parse_Record_H_

#include "basic/config-file/is-record.h"
#include "basic/config-file/space-remove.h"

namespace mysimulator {

  void __parse_conf_record(const char* rec, char*& key, char*& value) {
    assert(__is_conf_record(rec));
    unsigned int n=strlen(rec);
    unsigned int bg,ed;
    bg=0; ed=n;
    for(unsigned int i=bg;i<ed;++i)  if(rec[i]=='[') { bg=i+1; break; }
    ed=n;
    for(unsigned int i=bg;i<=ed;++i)  if(rec[i]==':') { ed=i-1; break; }
    assert(ed<n);
    assert(bg<=ed);
    if(key!=nullptr)  { __delete_array<char>(key); key=nullptr; }
    key=new char[ed-bg+2];
    SubString(key,rec,bg,ed);
    __space_remove(key);
    bg=ed+2;
    ed=n-1;
    for(unsigned int i=ed;i>=bg;--i)  if(rec[i]==']') { ed=i-1; break; }
    assert(bg<=ed);
    if(value!=nullptr)  { __delete_array<char>(value); value=nullptr; }
    value=new char[ed-bg+2];
    SubString(value,rec,bg,ed);
    __space_remove(value);
  }

}

#endif

