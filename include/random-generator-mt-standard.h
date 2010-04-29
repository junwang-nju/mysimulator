
#ifndef _Random_Generator_MT_Standard_H_
#define _Random_Generator_MT_Standard_H_

#include "error-proc.h"
#include "vector-impl.h"

namespace std {

  struct MT_Standard;

  void assign(MT_Standard&,const MT_Standard&);
  void release(MT_Standard&);

  struct MT_Standard {

    static const unsigned int N;
    static const unsigned int M;
    static const unsigned int MatrixA;
    static const unsigned int UppMask;
    static const unsigned int LowMask;
    static const unsigned int Mag01[2];
    unsigned int *mt;
    int *intfac;
    unsigned int *outfac;
    int oi;
    double od;
    long double old;

    typedef MT_Standard Type;

    MT_Standard() {}
    MT_Standard(const Type&) { myError("Cannot create from MT Standard"); }
    Type& operator=(const Type& MS) { assign(*this,MT); return *this; }
    ~MT_Standard() { release(*this); }

  };

  void assign(MT_Standard& dest, const MT_Standard& src) {
  }

  void release(MT_Standard& MS) { assign(MS.mt,0U,624); mti=MS.N+1; }

}

#endif

