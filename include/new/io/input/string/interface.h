
#ifndef _InputOutput_Input_String_Interface_H_
#define _InputOutput_Input_String_Interface_H_

#include "io/input/base/interface.h"
#include "array/1d/allocate.h"
#include "array/1d/refer.h"

namespace mysimulator {

  struct StringInput : public InputBase {

    public:

      typedef StringInput   Type;
      typedef InputBase     ParentType;

      Array1D<char> buffer;
      unsigned int ReadLocation;
      unsigned int Capacity;

      StringInput() : buffer(), ReadLocation(0), Capacity(0) {}
      StringInput(const unsigned int& n)
        : ParentType(), buffer(), ReadLocation(0), Capacity(0) { open(n); }
      StringInput(const Array1D<char>& bf)
        : ParentType(), buffer(), ReadLocation(0), Capacity(0) { open(bf); }
      ~StringInput() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        release(buffer); ReadLocation=0;  Capacity=0;
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(buffer);
      }

      void open(const unsigned int& n) { allocate(buffer,n); _init(); }
      void open(const Array1D<char>& bf) { refer(buffer,bf); _init(); }
      void close() { clearData(); }

      template <typename T>
      void _read_part(char* inf, const unsigned int& len, const char* pat,
                      const T& value) {
        char nowc=inf[len];
        inf[len]='\0';
        sscanf(inf,pat,&value);
        inf[len]=nowc;
      }
      template <typename T>
      Type& _read(const char* pat, T& value) {
        assert(isvalid());
        char *inf=buffer.start+ReadLocation;
        unsigned int n=0;
        unsigned int sc=Capacity;
        while(isspace(inf[n])&&(n<=sc))   ++n;
        ReadLocation+=n;
        Capacity-=n;
        inf=buffer.start+ReadLocation;
        sc=Capacity;
        if(sc>0) {
          n=1;
          _read_part(inf,n,pat,value);
          ++n;
          while(n<=sc) {
            T tmvalue;
            _read_part(inf,n,pat,tmvalue);
            if(tmvalue==value)  break;
            value=tmvalue;
            ++n;
          }
          --n;
          ReadLocation+=n;
          Capacity-=n;
        } else {
          fprintf(stderr,"Buffer Exhausted in StringInput!");
          this->set(FailBit);
        }
        return *this;
      }

      virtual Type& read(char& c) { return _read("%c",c); }
      virtual Type& read(unsigned char& uc) { return _read("%c",uc); }
      virtual Type& read(int& i) { return _read("%d",i); }
      virtual Type& read(unsigned int& u) { return _read("%u",u); }
      virtual Type& read(long& l) { return _read("%d",l); }
      virtual Type& read(unsigned long& l) { return _read("%u",l); }
      virtual Type& read(long long& l) { return _read("%lld",l); }
      virtual Type& read(unsigned long long& l) { return _read("%llu",l); }
      virtual Type& read(float& f) { return _read("%f",f); }
      virtual Type& read(double& d) { return _read("%lf",d); }
      virtual Type& read(long double& ld) { return _read("%Lf",ld); }
      virtual Type& read(void*& ptr) { return _read("%p",ptr); }
      virtual Type& read(char* str) {
        assert(isvalid());
        char* inf=buffer.start+ReadLocation;
        unsigned int n=0;
        unsigned int sc=Capacity;
        while(isspace(inf[n])&&(n<=sc))   ++n;
        ReadLocation+=n;
        Capacity-=n;
        inf=buffer.start+ReadLocation;
        sc=Capacity;
        if(sc>0) {
          n=0;
          while((!isspace(inf[n]))&&(n<=sc)&&(str[n]!=CharEOF)) {
            str[n]=inf[n];
            ++n;
          }
          str[n]='\0';
          ReadLocation+=n;
          Capacity-=n;
        } else {
          fprintf(stderr,"Buffer Exhausted in StringInput!");
          this->set(FailBit);
        }
        return *this;
      }
      virtual Type& unget() {
        --ReadLocation;
        ++Capacity;
        return *this;
      }
      virtual Type& unget(const char& c) {
        assert(c==buffer[ReadLocation-1]);
        return unget();
      }

    private:

      StringInput(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      void _init() {
        buffer[buffer.size-1]='\0';
        ReadLocation=0;
        Capacity=buffer.size-1;
      }

  };

  void release(StringInput& I) { I.clearData(); }
  bool IsValid(const StringInput& I) { return I.isvalid(); }

}

#endif

