
#ifndef _Random_Generator_MT_DSFMT_H_
#define _Random_Generator_MT_DSFMT_H_

#include "data/basic/vector.h"
#include "data/basic/unique-parameter-128bit.h"

namespace std {

#ifdef HAVE_SSE2
  __m128i   dSFMT_SSE2_ParamMask;
  __m128i   dSFMT_SSE2_IntOne;
  __m128i   dSFMT_SSE2_DoubleTwo;
  __m128i   dSFMT_SSE2_DoubleMOne;
#endif

  template <unsigned int LoopFac=19937>
  struct dSFMT : public Vector<UniqueParameter128b> {
    static const unsigned int MExp;
    static const unsigned int N;
    static const unsigned int NStatus;
    static const unsigned int NStatusU32;
    static const unsigned int NStatusByte;
    static const unsigned int Lag;
    static const unsigned int Mid;
    static const unsigned int LagMid;
    static const unsigned int N32;
    static const unsigned int N64;
    static const unsigned long long int LowMask;
    static const unsigned long long int HighConst;
    static const unsigned int SR;
#ifdef HAVE_SSE2
    static const unsigned int SSE2_Shuff;
#endif
    static const unsigned int Pos1;
    static const unsigned int SL1;
    static const unsigned long long int Msk1;
    static const unsigned long long int Msk2;
    static const unsigned int Msk32_1;
    static const unsigned int Msk32_2;
    static const unsigned int Msk32_3;
    static const unsigned int Msk32_4;
    static const unsigned long long int Fix1;
    static const unsigned long long int Fix2;
    static const unsigned long long int Pcv1;
    static const unsigned long long int Pcv2;
    static const unsigned long long int pcv[2];

    unsigned int *idx;
    UniqueParameter128b output;

    typedef dSFMT<LoopFac>    Type;
    typedef Vector<UniqueParameter128b> ParentType;

    dSFMT() : ParentType(), idx(NULL), output() {}
    dSFMT(const Type& G) { myError("Cannot create dSFMT"); }
  };

}

#endif

