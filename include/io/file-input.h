
#ifndef _InputOutput_File_Input_H_
#define _InputOutput_File_Input_H_

#include "io/input.h"
#include "io/special-char.h"
#include <cctype>
#include <cassert>

namespace mysimulator {

  struct FileInput : public InputBase {

    typedef FileInput   Type;
    typedef InputBase   ParentType;

    FILE *fptr;

    FileInput() : ParentType(), fptr(NULL) {}
    FileInput(const FILE* fp) : ParentType(), fptr(const_cast<FILE*>(fp)) {}
    FileInput(const char* fname, const char* fmode="r")
      : ParentType(), fptr(NULL) {
      open(fname,fmode);
    }
    FileInput(const Type&) {
      fprintf(stderr,"Copier of FileInput Disabled!\n");
    }
    Type& operator=(const Type&) {
      fprintf(stderr,"Operator= for FileInput Disabled!\n");
      return *this;
    }
    ~FileInput() { clearData(); }

    template <typename T>
    Type& _read(const char* pat, T& value) {
      assert(IsValid(*this));
      int n=fscanf(fptr,pat,&value);
      if(n!=1)  SetState(FailBit);
      return *this;
    }

    void clearData() {
      if(fptr!=NULL)  fclose(fptr);
      fptr=NULL;
      release(static_cast<ParentType&>(*this));
    }
    void open(const char* fname, const char* fmode="r") {
      close();
      fptr=fopen(fname,fmode);
      if(fptr==NULL)  SetState(FailBit);
    }
    void close() { clearData(); ClearState(); }
    Type& read(bool& b) {
      int i;
      _read("%d",i);
      b=(i==0?false:true);
      return *this;
    }
    Type& read(char& c) { return _read("%c",c); }
    Type& read(unsigned char& uc) { return _read("%c",uc); }
    Type& read(short& s) { return _read("%hd",s); }
    Type& read(unsigned short& us) { return _read("%hu",us); }
    Type& read(int& i) { return _read("%d",i); }
    Type& read(unsigned int& u) { return _read("%u",u); }
    Type& read(long& l) { return _read("%d",l); }
    Type& read(unsigned long& ul) { return _read("%u",ul); }
    Type& read(long long int& ll) { return _read("%lld",ll); }
    Type& read(unsigned long long int& ull) { return _read("%llu",ull); }
    Type& read(float& f) { return _read("%f",f); }
    Type& read(double& d) { return _read("%lf",d); }
    Type& read(long double& ld) { return _read("%Lf",ld); }
    Type& read(void*& ptr) { return _read("%p",ptr); }
    Type& read(char* s) {
      assert(IsValid(*this));
      char c=' ';
      while(isspace(c)) read(c);
      int i=0;
      while(!isspace(c)) {
        if(s[i]==CharEOF) { ungetc(c,fptr); break; }
        s[i++]=c;
        read(c);
      }
      s[i]='\0';
      return *this;
    }
    Type& unget(const char& c) { ungetc(c,fptr); return *this; }
    Type& unget() { return *this; }

  };

  void initString(char* s, const unsigned int len) {
    unsigned int last=len-1;
    for(unsigned int i=0;i<last;++i)  s[i]='\0';
    s[last]=CharEOF;
  }

  bool IsValid(const FileInput& I) { return I.fptr!=NULL; }
  void release(FileInput& I) { I.clearData(); }
  void copy(FileInput& I, const FileInput& cI) {
    release(I);
    copy(static_cast<InputBase&>(I),static_cast<const InputBase&>(cI));
    I.fptr=cI.fptr;
  }

}

#endif

