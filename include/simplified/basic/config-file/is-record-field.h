
#ifndef _Basic_Configuration_File_Is_Record_Field_H_
#define _Basic_Configuration_File_Is_Record_Field_H_

#include <cstring>

namespace mysimulator {

  bool __is_conf_record_field(const char* field) {
    unsigned int n=strlen(field);
    char c;
    for(unsigned int i=0;i<n;++i) {
      c=field[i];
      if(c=='[' || c==']' || c==':')  return false;
    }
    return true;
  }

}

#endif

