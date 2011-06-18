
#ifndef _InputOutput_Output_File_Interface_H_
#define _InputOutput_Output_File_Interface_H_

#include "io/output/interface.h"
#include <cassert>

namespace mysimulator {

  struct FileOutput : public OutputBase {

    typedef FileOutput  Type;
    typedef OutputBase  ParentType;

    FILE * fptr;

    FileOutput() : ParentType(), fptr(NULL) {}
    FileOutput(const FILE* fp) : ParentType(), fptr(const_cast<FILE*>(fp)) {}
    FileOutput(const char* fname, const char* fmode="w")
      : ParentType(), fptr(NULL) {
      open(fname,fmode);
    }
    FileOutput(const Type&) {
      fprintf(stderr,"Copier of FileOutput Disabled!\n");
    }
    Type& operator=(const Type&) {
      fprintf(stderr,"Operator= for FileOutput Disabled!\n");
      return *this;
    }
    ~FileOutput() { clearData(); }

    template <typename T>
    FileOutput& _write(const char* pat, const T& value) {
      assert(fptr!=NULL);
      fprintf(fptr,pat,value);
      return *this;
    }

    void clearData() {
      if((fptr!=NULL)&&(fptr!=stdout))    fclose(fptr);
      fptr=NULL;
      release(static_cast<ParentType&>(*this));
    }
    void open(const char* fname, const char* fmode="w") {
      close();
      fptr=fopen(fname,fmode);
      if(fptr==NULL)  SetState(FailBit);
    }
    void close() { clearData(); clearState(); }
    Type& write(const bool& b) { return _write("%d",b?1:0); }
    Type& write(const char& c) { return _write("%c",c); }
    Type& write(const unsigned char& uc) { return _write("%c",uc); }
    Type& write(const short& s) { return _write("%hd",s); }
    Type& write(const unsigned short& us) { return _write("%hu",us); }
    Type& write(const int& i) { return _write("%d",i); }
    Type& write(const unsigned int& u) { return _write("%u",u); }
    Type& write(const long& l) { return _write("%d",l); }
    Type& write(const unsigned long& ul) { return _write("%u",ul); }
    Type& write(const long long int& ll) { return _write("%lld",ll); }
    Type& write(const unsigned long long int& ul) { return _write("%llu",ul); }
    Type& write(const float& f) { return _write(FloatPat,f); }
    Type& write(const double& d) { return _write(DoublePat,d); }
    Type& write(const long double& ld) { return _write(LongDoublePat,ld); }
    Type& write(const void* ptr) { return _write("%p",ptr); }
    Type& write(const char* s) { return _write("%s",s); }

  };

  bool IsValid(const FileOutput& O) { return O.fptr!=NULL; }
  void release(FileOutput& O) { O.clearData(); }

}

#endif

