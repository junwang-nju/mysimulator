
#ifndef _Random_Generator_MT_Standard_H_
#define _Random_Generator_MT_Standard_H_

#include "unique-parameter-128bit.h"
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
    int *mti;
    UniqueParameter128b *output;
    unsigned int state;

    typedef MT_Standard Type;

    MT_Standard() mt(NULL), mti(NULL), output(NULL), state(Unused) {}
    MT_Standard(const Type&) { myError("Cannot create from MT Standard"); }
    Type& operator=(const Type& MS) { assign(*this,MT); return *this; }
    ~MT_Standard() { release(*this); }

  };

  void assign(MT_Standard& dest, const MT_Standard& src) {
  }

  void release(MT_Standard& MS) {
    if(MS.state=Allocated) {
      safe_delete_array(MS.mt);
      safe_delete(MS.mti);
      safe_delete(MS.output);
    } else {
      MS.mt=NULL;
      MS.mti=NULL;
      MS.output=NULL;
    }
    MS.state=Unused;

}

#endif

