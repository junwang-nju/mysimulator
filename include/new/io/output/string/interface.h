
#ifndef _InputOutput_Output_String_H_
#define _InputOutput_Output_String_H_

#include "io/output/base/interface.h"
#include "array/1d/allocate.h"
#include "array/1d/refer.h"

namespace mysimulator {

  struct StringOutput : public OutputBase {

    public:

      typedef StringOutput    Type;
      typedef OutputBase      ParentType;

      Array1D<char> buffer;
      unsigned int WriteLocation;
      unsigned int Capacity;

      StringOutput() : ParentType(), buffer(), WriteLocation(0), Capacity(0) {}
      StringOutput(const unsigned int& n)
        : ParentType(), buffer(), WriteLocation(0), Capacity(0) { open(n); }
      StringOutput(Array1D<char>& bf)
        : ParentType(), buffer(), WriteLocation(0), Capacity(0) { open(bf); }
      ~StringOutput() { clearData(); }

      void clearData() {
        release(buffer);
        static_cast<ParentType*>(this)->clearData();
        WriteLocation=0;
        Capacity=0;
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(buffer);
      }

      void open(const unsigned int& n) {
        clearData();
        allocate(buffer,n);
        _init();
      }
      void open(Array1D<char>& bf) {
        clearData();
        refer(buffer,bf);
        _init();
      }
      void close() { clearData(); }

      template <typename T>
      Type& _write(const char* pat, const T& value) {
        assert(isvalid());
        if(Capacity==0) {
          this->set(FailBit);
          fprintf(stderr,"No Free Space in Buffer to Write!\n");
        } else {
          int n=snprintf(buffer.start+WriteLocation,Capacity,pat,value);
          if(n<0) this->set(FailBit);
          else if(static_cast<unsigned int>(n)>Capacity) {
            this->set(FailBit);
            fprintf(stderr,"Buffer Overflow to StringOutput Write!\n");
            n=Capacity;
          }
          WriteLocation+=n;
          Capacity-=n;
        }
        return *this;
      }

      virtual Type& write(const bool& b) { return _write("%d",b?1:0); }
      virtual Type& write(const char& c) { return _write("%c",c); }
      virtual Type& write(const unsigned char& uc) { return _write("%c",uc); }
      virtual Type& write(const short& s) { return _write("%hd",s); }
      virtual Type& write(const unsigned short& us) { return _write("%hu",us); }
      virtual Type& write(const int& i) { return _write("%d",i); }
      virtual Type& write(const unsigned int& u) { return _write("%u",u); }
      virtual Type& write(const long& i) { return _write("%d",i); }
      virtual Type& write(const unsigned long& u) { return _write("%u",u); }
      virtual Type& write(const long long& l) { return _write("%lld",l); }
      virtual Type& write(const unsigned long long& u) {
        return _write("%llu",u);
      }
      virtual Type& write(const float& f) { return _write(FloatPat,f); }
      virtual Type& write(const double& d) { return _write(DoublePat,d); }
      virtual Type& write(const long double& ld) {
        return _write(LongDoublePat,ld);
      }
      virtual Type& write(const void* const& ptr) { return _write("%p",ptr); }
      virtual Type& write(const char* const& s) { return _write("%s",s); }

    private:

      StringOutput(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      void _init() {
        printf("%d\n",buffer.size);
        assert(IsValid(buffer));
        buffer[buffer.size-1]='\0';
        WriteLocation=0;
        Capacity=buffer.size-1;
      }

  };

  void release(StringOutput& O) { O.clearData(); }
  bool IsValid(const StringOutput& O) { return O.isvalid(); }

}

#endif

