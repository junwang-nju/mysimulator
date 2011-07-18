
#ifndef _InputOutput_Output_File_H_
#define _InputOutput_Output_File_H_

#include "io/output/base/interface.h"
#include "intrinsic-type/valid.h"
#include <cassert>

namespace mysimulator {

  struct FileOutput : public OutputBase {

    public:

      typedef FileOutput    Type;
      typedef OutputBase    ParentType;

      FILE* fptr;

      FileOutput() : ParentType(), fptr(NULL) {}
      FileOutput(const FILE* const& fp)
        : ParentType(), fptr(const_cast<FILE* const&>(fp)) {}
      FileOutput(const char* const& fname, const char* const& fmode="w")
        : ParentType(), fptr(NULL) { open(fname,fmode); }
      ~FileOutput() { clearData(); }

      void clearData() {
        if((fptr!=NULL)&&(fptr!=stdout)&&(fptr!=stderr))  fclose(fptr);
        fptr=NULL;
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return (fptr!=NULL)&&
               static_cast<const ParentType* const&>(this)->isvalid();
      }

      void open(const char* const& fname, const char* const& fmode="w") {
        close();
        fptr=fopen(fname,fmode);
        if(fptr==NULL)  set(FailBit);
      }
      void close() { clearData(); }
      template <typename T>
      FileOutput& _write(const char* const& pat, const T& value) {
        assert(isvalid());
        fprintf(fptr,pat,value);
        return *this;
      }
      Type& write(const bool& b) { return _write("%d",b?1:0); }
      Type& write(const char& c) { return _write("%c",c); }
      Type& write(const unsigned char& uc) { return _write("%c",uc); }
      Type& write(const short& s) { return _write("%hd",s); }
      Type& write(const unsigned short& us) { return _write("%hu",us); }
      Type& write(const int& i) { return _write("%d",i); }
      Type& write(const unsigned int& u) { return _write("%u",u); }
      Type& write(const long& l) { return _write("%d",l); }
      Type& write(const unsigned long& ul) { return _write("%u",ul); }
      Type& write(const long long& ll) { return _write("%lld",ll); }
      Type& write(const unsigned long long& ull) { return _write("%llu",ull); }
      Type& write(const float& f) { return _write(FloatPat,f); }
      Type& write(const double& d) { return _write(DoublePat,d); }
      Type& write(const long double& ld) { return _write(LongDoublePat,ld); }
      Type& write(const void* const& p) { return _write("%p",p); }
      Type& write(const char* const& s) { return _write("%s",s); }

    private:

      FileOutput(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  bool IsValid(const FileOutput& F) { return F.isvalid(); }
  void release(FileOutput& F) { F.clearData(); }

}

#endif

