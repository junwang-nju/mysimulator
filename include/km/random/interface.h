
#ifndef _Random_Interface_H_
#define _Random_Interface_H_

#include "array/data/interface.h"
#include "random/name.h"
#include <ctime>

namespace mysimulator {

  class Random {

    public:

      typedef Random    Type;
      friend void Clear(Random&);

      Random() : _tag(UnknownRNG) {}
      virtual ~Random() { Clear(*this); }

      virtual bool IsValid() const = 0;
      virtual void Allocate() = 0;
      virtual void Init(unsigned int) = 0;
      virtual void Init(const ArrayData<unsigned int>&) = 0;
      virtual double Double() = 0;
      virtual unsigned int UInt() = 0;

      const RandomName Name() const { return _tag; }

      void InitWithTime() { Init(static_cast<unsigned int>(time(0))); }
      void Produce(ArrayData<double>& A) {
        assert(A.IsValid());
        const unsigned int n=A.Size();
        for(unsigned int i=0;i<n;++i) A[i]=Double();
      }
      void Produce(ArrayData<unsigned int>& A) {
        assert(A.IsValid());
        const unsigned int n=A.Size();
        for(unsigned int i=0;i<n;++i) A[i]=UInt();
      }
      template <typename T>
      void Produce(ArrayData<T>& A) {
        assert(A.IsValid());
        const unsigned int n=A.Size();
        for(unsigned int i=0;i<n;++i) Produce(A[i]);
      }

    protected:

      RandomName _tag;

    private:

      Random(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(Random& R) { R._tag=UnknownRNG; }

}

#include "random/mt-standard/interface.h"
#include "random/mt-dsfmt/interface.h"
#include "random/box-muller/interface.h"
#include <cstdarg>

namespace mysimulator {

  void Introduce(Random*& R, RandomName RN, ...) {
    if(R!=NULL) { delete R; R=NULL; }
    unsigned int fac;
    va_list vl;
    va_start(vl,RN);
    RandomName RN1;
    switch(RN) {
      case MTStandardRNG: R=new MersenneTwisterStandard;  break;
      case MTDSFMTRNG:
        fac=va_arg(vl,unsigned int);
        switch(fac) {
          case 19937: R=new MersenneTwisterDSFMT<19937>;  break;
          default:
            fprintf(stderr,"Unknown Factor for MersenneTwisterDSFMT!\n");
        }
        break;
      case BoxMullerRNG:
        RN1=static_cast<RandomName>(va_arg(vl,unsigned int));
        switch(RN1) {
          case MTStandardRNG: R=new BoxMuller<MersenneTwisterStandard>; break;
          case MTDSFMTRNG:
            fac=va_arg(vl,unsigned int);
            switch(fac) {
              case 19937: R=new BoxMuller<MersenneTwisterDSFMT<19937> >; break;
              default:
                fprintf(stderr,"Unknown Factor for MersenneTwisterDSFMT!\n");
            }
            break;
          default:
            fprintf(stderr,"Unknown Uniform RNG!\n");
        }
        break;
      default:
        fprintf(stderr,"Unknown RNG!\n");
    }
    if(R!=NULL) {
      R->Allocate();
      R->InitWithTime();
    }
  }

}

#endif

