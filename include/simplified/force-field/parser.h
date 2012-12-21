
#ifndef _Force_Field_Parser_H_
#define _Force_Field_Parser_H_

#include "basic/memory/deleter.h"
#include "basic/util/string.h"
#include <cstring>
#include <cassert>

namespace mysimulator {

  bool IsForceFieldRecord(const char* rec) {
    unsigned int n=strlen(rec), m=0;
    for(unsigned int i=0;i<n;++i)
      if( rec[i]=='[' || rec[i]==']' )  return false;
      else if(rec[i]==':')  ++m;
    if(m!=2)  return false;
    return true;
  }

  void __parse_key_for_forcefield_record(char*& key, const char* rec) {
    assert(IsForceFieldRecord(rec));
    unsigned int n=strlen(rec),bg=0,ed=n-1;
    for(unsigned int i=0;i<n;++i) if(rec[i]==':') { ed=i-1; break; }
    bool fg=false;
    for(unsigned int i=bg;i<=ed;++i) if(!isspace(rec[i])) { bg=i; fg=true; break; }
    assert(fg);
    for(unsigned int i=ed;i>=bg;--i) if(!isspace(rec[i])) { ed=i; break; }
    __delete_array<char>(key);  key=nullptr;
    key=new char[ed-bg+2];
    SubString(key,rec,bg,ed);
  }

  void __parse_type_for_forcefield_record(char*& type, const char* rec) {
    assert(IsForceFieldRecord(rec));
    unsigned int n=strlen(rec),bg=0,ed=n-1;
    for(unsigned int i=0;i<n;++i)     if(rec[i]==':') { bg=i+1; break; }
    for(unsigned int i=n-1;i>bg;--i)  if(rec[i]==':') { ed=i-1; break; }
    bool fg=false;
    for(unsigned int i=bg;i<=ed;++i) if(!isspace(rec[i])) { bg=i; fg=true; break; }
    assert(fg);
    for(unsigned int i=ed;i>=bg;--i) if(!isspace(rec[i])) { ed=i; break; }
    __delete_array<char>(type); type=nullptr;
    type=new char[ed-bg+2];
    SubString(type,rec,bg,ed);
  }

  void __parse_value_for_forcefield_record(char*& value, const char* rec) {
    assert(IsForceFieldRecord(rec));
    unsigned int n=strlen(rec),bg=0,ed=n-1;
    for(unsigned int i=n-1;i>=0;--i)  if(rec[i]==':') { bg=i+1; break; }
    bool fg=false;
    for(unsigned int i=bg;i<=ed;++i) if(!isspace(rec[i])) { bg=i; fg=true; break; }
    assert(fg);
    for(unsigned int i=ed;i>=bg;--i) if(!isspace(rec[i])) { ed=i; break; }
    __delete_array<char>(value);  value=nullptr;
    value=new char[ed-bg+2];
    SubString(value,rec,bg,ed);
  }

  char* __parse_item_for_forcefield_value(char*& item,
                                         const char* value,unsigned int w) {
    unsigned int n=strlen(value),bg=0,ed=0,m=0;
    for(unsigned int i=0;i<n;++i) {
      if(isspace(value[i])) continue;
      else if(bg==0)  { bg=i; ed=0; }
      else if(ed==0)  { ed=i; if(m==w) break; ++m; bg=0; }
    }
    __delete_array<char>(item);  item=nullptr;
    item=new char[ed-bg+2];
    SubString(item,value,bg,ed);
    return item;
  }

}

#include "force-field/name.h"

namespace mysimulator {

  ForceFieldName __parse_name_for_forcefield(const char* content) {
    assert(content[0]=='#');
    unsigned int n=strlen(content),bg=1,ed=n-1;
    for(unsigned int i=bg;i<=ed;++i)
      if(content[i]=='[' || content[i]==':')  { ed=i-1; break; }
    bool fg=false;
    for(unsigned int i=bg;i<=ed;++i)
      if(!isspace(content[i]))  { bg=i; fg=true; break; }
    assert(fg);
    for(unsigned int i=ed;i>=bg;--i) if(!isspace(content[i])) { ed=i; break; }
    char* field=new char[ed-bg+2];
    SubString(field,content,bg,ed);
    ForceFieldName runName=ForceFieldName::Unknown;
    if(strcmp(field,"ResidueGo")==0)  runName=ForceFieldName::ResidueGo;
    __delete_array<char>(field); field=nullptr;
    return runName;
  }

}

#endif

