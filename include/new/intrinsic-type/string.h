
#ifndef _Intrinsic_Type_String_H_
#define _Intrinsic_Type_String_H_

namespace mysimulator {

  unsigned int LineSize(const char* s) {
    unsigned int n=0;
    char* l=const_cast<char*>(s);
    while(((*l)!='\n')&&((*l)!='\0')) { ++n; ++l; }
    return n;
  }

  void SubString(char* sub, const char* src, const unsigned int& begin,
                 const unsigned int& end) {
    char* p=const_cast<char*>(src)+begin;
    char* pend=const_cast<char*>(src)+end+1;
    char* q=sub;
    for(;p!=pend;)  *(q++)=*(p++);
    *q='\0';
  }

}

#endif

