
#ifndef _Basic_String_H_
#define _Basic_String_H_

namespace mysimulator {

  unsigned int LineSize(const char* s) {
    char* l=const_cast<char*>(s);
    while(((*l)!='\n')&&((*l)!='\0')) ++l;
    return static_cast<unsigned int>(l-s);
  }

  void SubString(char* sub,const char* src,unsigned int bg,unsigned int ed) {
    char* p=const_cast<char*>(src)+bg;
    char* pend=const_cast<char*>(src)+ed+1;
    char* q=sub;
    for(;p!=pend;)  *(q++)=*(p++);
    *q='\0';
  }

}

#endif

