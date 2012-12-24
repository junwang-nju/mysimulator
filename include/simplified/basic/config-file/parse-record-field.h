
#ifndef _Basic_Configuration_File_Parse_Record_Field_H_
#define _Basic_Configuration_File_Parse_Record_Field_H_

#include "basic/config-file/is-record-field.h"
#include "array/interface.h"

namespace mysimulator {

  void __parse_conf_record_field(const char* field, Array<char*>& items) {
    assert(__is_conf_record_field(field));
    unsigned int n=strlen(field);
    unsigned int m=0;
    for(unsigned int i=0;i<n-1;++i)
      if(i==0 && !isspace(field[i]))  ++m;
      else if(isspace(field[i]) && !isspace(field[i+1])) ++m; 
    assert(m>0);
    items.allocate(m);
    items=nullptr;
    unsigned int bg=0,ed=0,fg=0;
    m=0;
    for(unsigned int i=0;i<n;++i) {
      if((i==0||i==n-1) && !isspace(field[i]))  { bg=i; fg=1; }
      else if(isspace(field[i]) && !isspace(field[i+1])) { bg=i+1; fg=1; }
      if(i==n-1 && !isspace(field[i]) && fg==1)  { ed=i; fg=2; }
      else if(!isspace(field[i]) && isspace(field[i+1]) && fg==1) { ed=i; fg=2; }
      if(fg==2) {
        items[m]=new char[ed-bg+2];
        SubString(items[m],field,bg,ed);
        ++m;
        fg=0;
      }
    }
  }

}

#endif

