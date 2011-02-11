
#ifndef _File_Input_H_
#define _File_Input_H_

#include "operation/basic/input-base.h"
#include "operation/basic/memory.h"
#include "operation/basic/util.h"
#include <cstdio>
#include <cassert>

namespace std {

  struct FileInput;
  void release(FileInput&);

  struct FileInput : public InputBase {
    FILE *fpoint;
    bool rflag;
    FileInput() : fpoint(NULL), rflag(false) {}
    FileInput(const FILE* fp) : fpoint(const_cast<FILE*>(fp)), rflag(true) {}
    FileInput(const FileInput& FI) {
      fprintf(stderr,"%s\n","Cannot create FileInput");
      exit(0);
    }
    FileInput& operator=(const FileInput& FI) {
      fprintf(stderr,"%s\n","Cannot copy FileInput");
      exit(0);
      return *this;
    }
    ~FileInput() { release(*this); }
    template <typename T>
    FileInput& __read(const char* pat, T& value) {
      assert(IsAvailable(fpoint));
      fscanf(fpoint,pat,&value);
      return *this;
    }
    FileInput& read(bool& b) {
      assert(IsAvailable(fpoint));
      int i=1;
      fscanf(fpoint,"%d",&i);
      b=(i==0?false:true);
      return *this;
    }
    FileInput& read(char& c) { return __read("%c",c); }
    FileInput& read(unsigned char& uc) { return __read("%c",uc); }
    FileInput& read(short& s) { return __read("%hd",s); }
    FileInput& read(unsigned short& us) { return __read("%hu",us); }
    FileInput& read(int& i) { return __read("%d",i); }
    FileInput& read(unsigned int& ui) { return __read("%u",ui); }
    FileInput& read(long& l) { return __read("%d",l); }
    FileInput& read(unsigned long& ul) { return __read("%u",ul); }
    FileInput& read(long long int& ll) { return __read("%lld",ll); }
    FileInput& read(unsigned long long int& ull) { return __read("%llu",ull); }
    FileInput& read(float& f) { return __read("%f",f); }
    FileInput& read(double& d) { return __read("%f",d); }
    FileInput& read(long double& ld) { return __read("%Lf",ld); }
    FileInput& read(void*& ptr) { return __read("%p",ptr); }
    FileInput& read(char* s) {
      assert(IsAvailable(fpoint));
      fscanf(fpoint,"%s",s);
      return *this;
    }

  };

  bool IsAvailable(const FileInput& I) { return IsAvailable(I.fpoint); }
  void release(FileInput& I) {
    if((!I.rflag)&&(I.fpoint!=NULL)) {
      fclose(I.fpoint);
      I.rflag=false;
    }
  }
  void copy(FileInput& I, const FILE* fp) {
    assert(IsAvailable(fp));
    release(I);
    I.fpoint=const_cast<FILE*>(fp);
    I.rflag=true;
  }
  void copy(FileInput& I, const FileInput& cI) { copy(I,cI.fpoint); }
  void allocate(FileInput& I, const char* fname, const char* fmode="r") {
    release(I);
    I.fpoint=fopen(fname,fmode);
    I.rflag=false;
  }

}

#endif
