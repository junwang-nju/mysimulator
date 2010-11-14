
#ifndef _Random_Generator_MT_Standard_H_
#define _Random_Generator_MT_Standard_H_

#include "data/basic/vector.h"
#include "data/basic/unique-parameter-128bit.h"

namespace std {

  struct MT_Standard : public Vector<unsigned int> {
    static const unsigned int N;
    static const unsigned int M;
    static const unsigned int dNM;
    static const unsigned int NmOne;
    static const unsigned int MmOne;
    static const unsigned int MatrixA;
    static const unsigned int UppMask;
    static const unsigned int LowMask;
    static const unsigned int Mag01[2];
    static const unsigned int Mask32b;

    typedef MT_Standard   Type;
    typedef Vector<unsigned int>  ParentType;

    unsigned int *mti;
    UniqueParameter128b output;

    MT_Standard() : ParentType(), mti(NULL), output() {}
    MT_Standard(const Type& G) { myError("Cannot create MT-Standard Generator"); }
    Type& operator=(const Type& G) {
      myError("Cannot copy MT-Standard Generator");
      return *this;
    }
    ~MT_Standard() { release(*this); }
  };

  const unsigned int MT_Standard::N=624;
  const unsigned int MT_Standard::M=397;
  const unsigned int MT_Standard::dNM=MT_Standard::N-MT_Standard::M;
  const unsigned int MT_Standard::NmOne=MT_Standard::N-1;
  const unsigned int MT_Standard::MmOne=MT_Standard::M-1;
  const unsigned int MT_Standard::MatrixA=0x9908B0DFUL;
  const unsigned int MT_Standard::UppMask=0x80000000UL;
  const unsigned int MT_Standard::LowMask=0x7FFFFFFFUL;
  const unsigned int MT_Standard::Mag01[2]={0x0UL,MT_Standard::MatrixA};
  const unsigned int MT_Standard::Mask32b=0xFFFFFFFFUL;

  void init(MT_Standard&,const unsigned int);

  bool IsAvailable(const MT_Standard& G) {
    return IsAvailable(static_cast<const Vector<unsigned int>&>(G));
  }
  bool IsRandomGenerator(const MT_Standard& G) { return true; }
  void copy(MT_Standard& G, const MT_Standard& cG) {
    assert(IsAvailable(G));
    assert(IsAvailable(cG));
    copy(static_cast<Vector<unsigned int>&>(G),
         static_cast<const Vector<unsigned int>&>(cG));
    copy(*(G.mti),*(cG.mti));
    copy(G.output,cG.output);
  }
  void release(MT_Standard& G) {
    if(G.state==Allocated)  safe_delete(G.mti);
    else                    G.mti=NULL;
    release(static_cast<Vector<unsigned int>&>(G));
    copy(G.output,0);
  }
  void allocate(MT_Standard& G) {
    release(G);
    allocate(static_cast<Vector<unsigned int>&>(G),G.N);
    G.mti=new unsigned int;
    init(G,5489UL);
  }
  void refer(MT_Standard& G, const MT_Standard& rG) {
    refer(static_cast<Vector<unsigned int>&>(G),
          static_cast<const Vector<unsigned int>&>(rG));
    G.mti=rG.mti;
  }

  ostream& operator<<(ostream& os, const MT_Standard& G) {
    assert(IsAvailable(G));
    os<<static_cast<const Vector<unsigned int>&>(G)<<"\t"<<*(G.mti);
    return os;
  }
  istream& operator>>(istream& is, MT_Standard& G) {
    assert(IsAvailable(G));
    is>>static_cast<Vector<unsigned int>&>(G)>>*(G.mti);
    return is;
  }

}

#endif
