
#ifndef _Basic_Configuration_File_IsRecord_H_
#define _Basic_Configuration_File_IsRecord_H_

#include <cstring>

namespace mysimulator {

  bool __is_conf_record(const char* rec) {
    unsigned int n=strlen(rec);
    unsigned int m;
    m=n;
    for(unsigned int i=0;i<n;++i) if(rec[i]=='[') { m=i; break; }
    if(m==n)  return false;
    for(unsigned int i=0;i<m;++i) if(!isspace(rec[i]))  return false;
    m=n;
    for(unsigned int i=n-1;i>=0;--i)  if(rec[i]==']') { m=i; break; }
    if(m==n)  return false;
    for(unsigned int i=m+1;i<n;++i) if(!isspace(rec[i]))  return false;
    return true;
  }

}

#endif

