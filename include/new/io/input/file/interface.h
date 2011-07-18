
#ifndef _InputOutput_Input_File_H_
#define _InputOutput_Input_File_H_

#include "io/input/base/interface.h"
#include "io/special-char.h"
#include <cstdio>
#include <cctype>
#include <cassert>

namespace mysimulator {

  struct FileInput : public InputBase {

    public:

      typedef FileInput       Type;
      typedef InputBase       ParentType;

      FILE* fptr;

      FileInput() : ParentType(), fptr(NULL) {}
      FileInput(const FILE* const& fp)
        : ParentType(), fptr(const_cast<FILE* const&>(fp)) {}
      FileInput(const char* const& fname, const char* const& fmode="r")
        : ParentType(), fptr(NULL) { open(fname,fmode); }
      ~FileInput() { clearData(); }

      void clearData() {
        if((fptr!=NULL)&&(fptr!=stdin))   fclose(fptr);
        fptr=NULL;
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType* const&>(this)->isvalid();
      }

      void open(const char* const& fname, const char* const& fmode="r") {
        close();
        fptr=fopen(fname,fmode);
        if(fptr==NULL)  set(FailBit);
      }
      void close() { clearData(); }
      template <typename T>
      Type& _read(const char* const& pat, T& val) {
        assert(isvalid());
        int n=fscanf(fptr,pat,&val);
        if(n!=1)  set(FailBit);
        return *this;
      }
      Type& read(bool& b) {
        int i; _read("%d",i); b=(i==0?false:true);
        return *this;
      }
      virtual Type& read(char& c) { return _read("%c",c); }
      virtual Type& read(unsigned char& uc) { return _read("%c",uc); }
      virtual Type& read(short& s) { return _read("%hd",s); }
      virtual Type& read(unsigned short& us) { return _read("%hu",us); }
      virtual Type& read(int& i) { return _read("%d",i); }
      virtual Type& read(unsigned int& u) { return _read("%u",u); }
      virtual Type& read(long& l) { return _read("%d",l); }
      virtual Type& read(unsigned long& ul) { return _read("%u",ul); }
      virtual Type& read(long long& ll) { return _read("%lld",ll); }
      virtual Type& read(unsigned long long& ull) { return _read("%llu",ull); }
      virtual Type& read(float& f) { return _read("%f",f); }
      virtual Type& read(double& d) { return _read("%lf",d); }
      virtual Type& read(long double& ld) { return _read("%Lf",ld); }
      virtual Type& read(void*& ptr) { return _read("%p",ptr); }
      virtual Type& read(char* const& s) {
        assert(isvalid());
        char c=' ';
        while(isspace(c)) read(c); // may be a dead end
        int i=0;
        while(!isspace(c)) {
          if(s[i]==CharEOF) { unget(c); break; }
          s[i++]=c;
          read(c);
        }
        s[i]='\0';
        return *this;
      }
      virtual Type& unget(const char& c) { ungetc(c,fptr); return *this; }
      virtual Type& unget() { return *this; }

    private:

      FileInput(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  bool IsValid(const FileInput& I) { return I.isvalid(); }
  void release(FileInput& I) { I.clearData(); }

}

#endif

