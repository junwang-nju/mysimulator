
#ifndef _File_Input_H_
#define _File_Input_H_

#include "data/basic/input-base.h"

namespace std {

  struct FileInput;
  void release(FileInput&);
  void allocate(FileInput&,const char*,const char*);

  struct FileInput : public InputBase {
    FILE *fpoint;
    bool rflag;
    FileInput() : InputBase(), fpoint(NULL), rflag(false) {}
    FileInput(const FILE* fp)
        : InputBase(), fpoint(const_cast<FILE*>(fp)), rflag(true) {
      allocate(static_cast<InputOutputBase&>(*this));
    }
    FileInput(const char* fname, const char* fmode="r") 
        : InputBase(), fpoint(NULL), rflag(false) {
      allocate(*this,fname,fmode);
    }
    FileInput(const FileInput& FI) { Error("Cannot create FileInput"); }
    FileInput& operator=(const FileInput& FI) {
      Error("Cannot copy FileInput");
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
    FileInput& read(double& d) { return __read("%lf",d); }
    FileInput& read(long double& ld) { return __read("%Lf",ld); }
    FileInput& read(void*& ptr) { return __read("%p",ptr); }
    FileInput& read(char* s) {
      assert(IsAvailable(fpoint));
      char c;
      read(c);
      while(isspace(c)) read(c);
      int i=0;
      while((!isspace(c))&&(s[i]!=CharEOF)) {
        s[i++]=c;
        read(c);
      }
      if(s[i]==CharEOF) ungetc(c,fpoint);
      s[i]='\0';
      return *this;
    }
    FileInput& unget(const char& c) {
      ungetc(c,fpoint);
      return *this;
    }

  };

  void initString(char* s, const unsigned int len) {
    unsigned int last=len-1;
    for(unsigned int i=0;i<last;++i) s[i]='\0';
    s[last]=static_cast<char>(26);
  }

  bool IsAvailable(const FileInput& I) { return IsAvailable(I.fpoint); }
  void release(FileInput& I) {
    if((!I.rflag)&&(I.fpoint!=NULL)) {
      fclose(I.fpoint);
      I.rflag=false;
    }
    release(static_cast<InputOutputBase&>(I));
  }
  void refer(FileInput& I, const FILE* fp) {
    assert(IsAvailable(fp));
    release(I);
    I.fpoint=const_cast<FILE*>(fp);
    I.rflag=true;
    allocate(static_cast<InputOutputBase&>(I));
  }
  void refer(FileInput& I, const FileInput& cI) { refer(I,cI.fpoint); }
  void allocate(FileInput& I, const char* fname, const char* fmode="r") {
    release(I);
    allocate(static_cast<InputOutputBase&>(I));
    I.fpoint=fopen(fname,fmode);
    I.rflag=false;
  }

}

#endif
