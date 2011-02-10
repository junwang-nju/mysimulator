
#ifndef _File_Output_H_
#define _File_Output_H_

#include "operation/basic/output-base.h"
#include "operation/basic/util.h"
#include <cstdio>
#include <cassert>

namespace std {
  
  struct FileOutput;
  void release(FileOutput&);

  struct FileOutput : public OutputBase {
    FILE *fpoint;
    bool rflag;
    FileOutput() : fpoint(NULL), rflag(false) {}
    FileOutput(const FILE* fp) : fpoint(const_cast<FILE*>(fp)), rflag(true) {}
    FileOutput(const FileOutput& FO) {
      fprintf(stderr,"%s\n","Cannot create FileOutput"); }
    FileOutput& operator=(const FileOutput& FO) {
      fprintf(stderr,"%s\n","Cannot copy FileOutput");
      return *this;
    }
    ~FileOutput() { release(*this); }
    template <typename T>
    FileOutput& __write(const char* pat, const T& value) {
      assert(IsAvailable(fpoint));
      fprintf(fpoint,pat,value);
      return *this;
    }
    FileOutput& write(const bool& b) { return __write("%d",b?1:0); }
    FileOutput& write(const char& c) { return __write("%c",c); }
    FileOutput& write(const unsigned char& uc) { return __write("%c",uc); }
    FileOutput& write(const short& s) { return __write("%hd",s); }
    FileOutput& write(const unsigned short& us) { return __write("%hu",us); }
    FileOutput& write(const int& i) { return __write("%d",i); }
    FileOutput& write(const unsigned int& ui) { return __write("%u",ui); }
    FileOutput& write(const long& l) { return __write("%d",l); }
    FileOutput& write(const unsigned long& ul) { return __write("%u",ul); }
    FileOutput& write(const long long int& ll) { return __write("%lld",ll); }
    FileOutput& write(const unsigned long long int& ull) {
      return __write("%llu",ull);
    }
    FileOutput& write(const float& f) { return __write("%g",f); }
    FileOutput& write(const double& d) { return __write("%g",d); }
    FileOutput& write(const long double& ld) { return __write("%Lg",ld); }
    FileOutput& write(const void* ptr) { return __write("%p",ptr); }
    FileOutput& write(const char* s) { return __write("%s",s); }

  };

  bool IsAvailable(const FileOutput& O) { return IsAvailable(O.fpoint); }
  void release(FileOutput& O) {
    if((!O.rflag)&&(O.fpoint!=NULL)) {
      fclose(O.fpoint);
      O.rflag=false;
    }
  }
  void copy(FileOutput& O, const FILE* fp) {
    assert(IsAvailable(fp));
    release(O);
    O.fpoint=const_cast<FILE*>(fp);
    O.rflag=true;
  }
  void copy(FileOutput& O, const FileOutput& cO) { copy(O,cO.fpoint); }
  void allocate(FileOutput& O, const char* fname, const char* fmode="w") {
    release(O);
    O.fpoint=fopen(fname,fmode);
    O.rflag=false;
  }

}

#endif
