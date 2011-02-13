
#ifndef _File_Output_H_
#define _File_Output_H_

#include "data/basic/output-base.h"

namespace std {
  
  struct FileOutput;
  void release(FileOutput&);
  void allocate(FileOutput&, const char*, const char*);

  struct FileOutput : public OutputBase {
    FILE *fpoint;
    bool rflag;
    FileOutput() : OutputBase(), fpoint(NULL), rflag(false) {}
    FileOutput(const FILE* fp)
        : OutputBase(), fpoint(const_cast<FILE*>(fp)), rflag(true) {
      allocate(static_cast<OutputBase&>(*this));
    }
    FileOutput(const char* fname, const char* fmode="w")
        : OutputBase(), fpoint(NULL), rflag(false) {
      allocate(*this,fname,fmode);
    }
    FileOutput(const FileOutput& FO) { Error("Cannot create FileOutput"); }
    FileOutput& operator=(const FileOutput& FO) {
      Error("Cannot copy FileOutput");
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
    FileOutput& write(const float& f) {
      return __write(patString[FloatOutput].data,f);
    }
    FileOutput& write(const double& d) {
      return __write(patString[DoubleOutput].data,d);
    }
    FileOutput& write(const long double& ld) {
      return __write(patString[LongDoubleOutput].data,ld);
    }
    FileOutput& write(const void* ptr) { return __write("%p",ptr); }
    FileOutput& write(const char* s) { return __write("%s",s); }

  };

  bool IsAvailable(const FileOutput& O) { return IsAvailable(O.fpoint); }
  void release(FileOutput& O) {
    if((!O.rflag)&&(O.fpoint!=NULL)) {
      fclose(O.fpoint);
      O.rflag=false;
    }
    release(static_cast<InputOutputBase&>(O));
  }
  void refer(FileOutput& O, const FILE* fp) {
    assert(IsAvailable(fp));
    release(O);
    allocate(static_cast<OutputBase&>(O));
    O.fpoint=const_cast<FILE*>(fp);
    O.rflag=true;
  }
  void refer(FileOutput& O, const FileOutput& cO) { refer(O,cO.fpoint); }
  void allocate(FileOutput& O, const char* fname, const char* fmode="w") {
    release(O);
    allocate(static_cast<OutputBase&>(O));
    O.fpoint=fopen(fname,fmode);
    O.rflag=false;
  }

}

#endif
