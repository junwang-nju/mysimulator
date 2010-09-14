
/**
 * @file random-generator-mt-sfmt.h
 * @brief the random generator with SFMT implementation
 *
 * This file gives the random generator using SFMT implementation. This
 * kind of generator is said to be efficient for integer generation
 * comparing with dSFMT implementation.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Random_Generator_MT_SFMT_H_
#define _Random_Generator_MT_SFMT_H_

#include "unique-parameter-128bit.h"
#include "vector.h"
#include <cstring>

#ifdef HAVE_SSE2
#include <emmintrin.h>
#endif

namespace std {

#ifdef HAVE_SSE2
  /**
   * @brief the mask for parameter used in SSE2 implementation
   *
   * It is implemented with 128-bit integer
   */
  __m128i SFMT_SSE2_ParamMask;
#endif

  /**
   * @brief the random generator with SFMT implementation
   *
   * This is a generator to produce random numbers with uniform distribution.
   * It is said that this kind of generator is efficient to produce
   * \c unsigned \c int values.
   *
   * LoopFac is the factor related to the size of internal storage. It takes
   * 19937 as its default value.
   *
   * @note It uses UniqueParameter128b are basic internal storage. This object
   *       is useful as a generic form for internal data.
   */
  template <unsigned int LoopFac=19937>
  struct SFMT {
    static const unsigned int MExp;
    static const unsigned int N;
    static const unsigned int NStatus;
    static const unsigned int NStatusByte;
    static const unsigned int N32;
    static const unsigned int N64;
    static const unsigned int Lag;
    static const unsigned int Mid;
    static const unsigned int LagMid;
    static const unsigned int Pos1;
    static const unsigned int SL1;
    static const unsigned int SL2;
    static const unsigned int SR1;
    static const unsigned int SR2;
    static const unsigned int Msk1;
    static const unsigned int Msk2;
    static const unsigned int Msk3;
    static const unsigned int Msk4;
    static const unsigned int Parity1;
    static const unsigned int Parity2;
    static const unsigned int Parity3;
    static const unsigned int Parity4;
    static const unsigned int Parity[4];

    /**
     * @brief the status array in the generator
     */
    UniqueParameter128b *status;
    /**
     * @brief the pointer to the index to the output element
     */
    unsigned int *idx;
    /**
     * @brief the pointer to the output parameter
     */
    UniqueParameter128b *output;
    /**
     * @brief the state flag for the generator
     */
    unsigned int state;

    /**
     * @brief the abbreviation of the type of SFMT generator
     */
    typedef SFMT<LoopFac> Type;

    /**
     * @brief default initiator
     *
     * Just initiate the pointers with NULL and initiate the state flag
     * with Unused.
     */
    SFMT()
      : status(NULL), idx(NULL), output(NULL), state(Unused) {}
    /**
     * @brief initiator from another SFMT generator
     *
     * It is prohibited and pops up an error message
     *
     * @param sg [in] the input SFMT generator
     */
    SFMT(const Type& sg) { myError("Cannot create from SFMT generator"); }
    /**
     * @brief copy from another SFMT generator
     *
     * It is implemented with assign operation.
     *
     * @param sg [in] the input SFMT generator
     * @return the reference to the resultant SFMT generator
     */
    Type& operator=(const Type& sg) { assign(*this,sg); return *this; }
    /**
     * @brief the destructor
     *
     * It is implemented with release operation
     */
    ~SFMT() { release(*this); }

    /**
     * @brief initiate the generator with an \c unsigned \c int seed
     *
     * it is implemented with init operation.
     *
     * @param seed [in] the \c unsigned \c int as the seed for generator
     * @return nothing
     */
    void Init(const unsigned int seed) { init(*this,seed); }
    /**
     * @brief initiate the generator with \c unsigned \c int array
     *
     * it is implemented with init operation
     *
     * @param key [in] the arrays containing seeds
     * @param len [in] the number of seeds
     * @param off [in] the offset of the first element in array, it takes
     *                 the default value of uZero.
     * @param step [in] the separation between elements in array, it takes
     *                  the default value of uOne.
     * @return nothing
     */
    void Init(const unsigned int* key, const unsigned int len,
              const unsigned int off=uZero, const unsigned int step=uOne) {
      init(*this,key,len,off,step);
    }
    /**
     * @brief initiate the generator with a vector
     *
     * It is implemented with init operation.
     *
     * @param key [in] the vector containing the seeds
     * @return nothing
     */
    void Init(const Vector<unsigned int>& key) { init(*this,key); }

    /**
     * @brief generate a 32-bit \c unsigned \c int value
     *
     * One of the \c unsigned \c int number is picked up from internal
     * storage. When the storage is used up, it is re-generated.
     *
     * @return the 32-bit \c unsigned \c int value
     */
    const unsigned int& UInt32() {
      if(*idx>=SFMT<LoopFac>::N32) { GenRandAll(); *idx=0; }
      return status->u[(*idx)++];
    }

    /**
     * @brief generate a 64-bit \c unsigned \c long \c long \c int value
     *
     * The \c unsigned \c long \c long \c int value is picked up from
     * internal storage. The storage may be updated when it is used out.
     *
     * @return an \c unsigned \c long \c long \c int value
     */
    const unsigned long long int& UInt64() {
      assert(((*idx)&1)==0);
      if(*idx>=SFMT<LoopFac>::N32) { GenRandAll(); *idx=0; }
      output->ull[0]=status->ull[(*idx)>>1];
      *idx+=2;
      return output->ull[0];
    }

    /**
     * @brief generate \c double value in region [0,1]
     *
     * It is implemented based on linear map of \c unsigned \c int to
     * \c double value in region [0,1]
     *
     * @return the \c double value in region [0,1]
     */
    const double& DoubleClose0Close1() {
      output->d[0]=static_cast<double>(static_cast<int>(UInt32()))
                  *(1./4294967295.0)+(0.5+0.5/4294967295.0);
      return output->d[0];
    }
    /**
     * @brief generate \c double value in region [0,1)
     *
     * It is implemented based on linear map of \c unsigned \c int to
     * \c double value in region [0,1)
     *
     * @return the \c double value in region [0,1)
     */
    const double& DoubleClose0Open1() {
      output->d[0]=static_cast<double>(static_cast<int>(UInt32()))
                  *(1./4294967296.0)+0.5;
      return output->d[0];
    }
    /**
     * @brief generate \c double value in region (0,1)
     *
     * It is implemented based on linear map of \c unsigned \c int to
     * \c double value in region (0,1)
     *
     * @return the \c double value in region (0,1)
     */
    const double& DoubleOpen0Open1() {
      output->d[0]=static_cast<double>(static_cast<int>(UInt32()))
                  *(1./4294967296.0)+(0.5+0.5/4294967296.0);
      return output->d[0];
    }
    /**
     * @brief generate 53-bit \c double value in region [0,1)
     *
     * It is implemented based on linear map of two \c unsigned \c int to
     * \c double value in region [0,1). The certain bits are picked up
     * for this operation.
     *
     * @return the 53-bit \c double value in region [0,1)
     */
    const double& Double53Close0Open1() {
      long x,y;
      x=static_cast<long>(UInt32()>>5);
      y=static_cast<long>(UInt32()>>6);
      output->d[0]=(x*67108864.0+y)*(1./9007199254740992.0);
      return output->d[0];
    }
    /**
     * @brief generate 53-bit \c double value in region [0,1) (slow method)
     *
     * It is implemented based on linear map of two \c unsigned \c int to
     * \c double value in region [0,1). The certain bits are picked up
     * for this operation.
     *
     * @return the 53-bit \c double value in region [0,1)
     * @note it is said that this is a slow method since conversion from 
     *       \c unsigned \c int to \c double is slow. This is not tested.
     */
    const double& Double53Close0Open1Slow() {
      unsigned int x,y;
      x=UInt32()>>5;
      y=UInt32()>>6;
      output->d[0]=(x*67108864.0+y)*(1./9007199254740992.0);
      return output->d[0];
    }
    /**
     * @brief generate 63-bit \c long \c double value in region [0,1)
     *
     * It is implemented based on linear map of two \c unsigned \c int to
     * \c double value in region [0,1). The certain bits are picked up
     * for this operation.
     *
     * @return the 63-bit \c long \c double value in region [0,1)
     */
    const long double& LDouble63Close0Open1() {
      output->ld=static_cast<long double>(static_cast<long long>(UInt64()))
                *(1./18446744073709551616.0L)+0.5;
      return output->ld;
    }
    /**
     * @brief generate 63-bit \c long \c double value in region [0,1) (slow method)
     *
     * It is implemented based on linear map of two \c unsigned \c int to
     * \c double value in region [0,1). The certain bits are picked up
     * for this operation.
     *
     * @return the 63-bit \c long \c double value in region [0,1)
     * @note it is said that this is a slow method since conversion from 
     *       \c unsigned \c int to \c long \c double is slow. This is not
     *       tested.
     */
    const long double& LDouble63Close0Open1Slow() {
      unsigned int x,y;
      x=UInt32();
      y=UInt32();
      output->ld=(x|(static_cast<unsigned long long int>(y)<<32))
                *(1./18446744073709551616.0L);
      return output->ld;
    }

#ifdef HAVE_SSE2
    /**
     * @brief initiate constant (SSE2 operation)
     *
     * Just assign the mask for parameter in the first run.
     *
     * @return nothing
     */
    void InitConst() {
      static bool first=true;
      if(!first)  return;
      _mm_storeu_si128(&SFMT_SSE2_ParamMask,_mm_set_epi32(Msk4,Msk3,Msk2,Msk1));
      first=false;
    }
    /**
     * @brief a basic complex operation for a series of 128-bit integers
     *
     * This is a basic step with a series of complex operations.
     *
     * @param a,b,c,d [in] the 128-bit integers as input
     * @return the resultant 128-bit integer
     *
     * @note to avoid that the problem of bit alignment, the SSE2 operations
     *       without bit-alignment requirement are used.
     */
    __m128i DoRecursion(const __m128i& a, const __m128i& b, const __m128i& c,
                        const __m128i& d) {
      __m128i v,x,y,z;
      x=_mm_loadu_si128(&a);
      y=_mm_loadu_si128(&b);
      z=_mm_loadu_si128(&c);
      v=_mm_loadu_si128(&d);
      y=_mm_srli_epi32(y,SR1);
      z=_mm_srli_si128(z,SR2);
      v=_mm_slli_epi32(v,SL1);
      z=_mm_xor_si128(z,x);
      z=_mm_xor_si128(z,v);
      x=_mm_slli_si128(x,SL2);
      y=_mm_and_si128(y,SFMT_SSE2_ParamMask);
      z=_mm_xor_si128(z,x);
      z=_mm_xor_si128(z,y);
      return z;
    }
    /**
     * @brief generate all the elements of status
     *
     * It is a procedure to generate all status in the internal storage.
     * It uses the DoRecursion operation.
     *
     * @return nothing
     */
    void GenRandAll() {
      unsigned int i;
      __m128i r,r1,r2;
      r1=_mm_loadu_si128(&(status[N-2].si));
      r2=_mm_loadu_si128(&(status[N-1].si));
      for(i=0;i<N-Pos1;++i) {
        r=DoRecursion(status[i].si,status[i+Pos1].si,r1,r2);
        _mm_storeu_si128(&(status[i].si),r);
        r1=r2;
        r2=r;
      }
      for(;i<N;++i) {
        r=DoRecursion(status[i].si,status[i+Pos1-N].si,r1,r2);
        _mm_storeu_si128(&(status[i].si),r);
        r1=r2;
        r2=r;
      }
    }
    /**
     * @brief generate array with SFMT generator
     *
     * It is implemented with the operation combined with elements of
     * input array and internal status.
     *
     * @param array [in,out] the array containing parameters
     * @param size [in] the number of elements in array
     * @return nothing
     */
    void GenRandArray(UniqueParameter128b* array, const unsigned int size) {
      assert(size>=N);
      unsigned int i,j;
      __m128i r,r1,r2;
      r1=_mm_loadu_si128(&(status[N-2].si));
      r2=_mm_loadu_si128(&(status[N-1].si));
      for(i=0;i<N-Pos1;++i) {
        r=DoRecursion(status[i].si,status[i+Pos1].si,r1,r2);
        _mm_storeu_si128(&(array[i].si),r);
        r1=r2;
        r2=r;
      }
      for(;i<N;++i) {
        r=DoRecursion(status[i].si,array[i+Pos1-N].si,r1,r2);
        _mm_storeu_si128(&(array[i].si),r);
        r1=r2;
        r2=r;
      }
      for(;i+N<size;++i) {
        r=DoRecursion(array[i-N].si,array[i+Pos1-N].si,r1,r2);
        _mm_storeu_si128(&(array[i].si),r);
        r1=r2;
        r2=r;
      }
      for(j=0;j+size<N+N;++j) {
        r=_mm_loadu_si128(&(array[j+size-N].si));
        _mm_storeu_si128(&(status[j].si),r);
      }
      for(;i<size;++i) {
        r=DoRecursion(array[i-N].si,array[i+Pos1-N].si,r1,r2);
        _mm_storeu_si128(&(array[i].si),r);
        _mm_storeu_si128(&(status[j++].si),r);
        r1=r2;
        r2=r;
      }
    }
#else
    /**
     * @brief a basic complex operation for a series of 128-bit integers
     *
     * This is a version without SSE2 instruction. With a series of
     * bit operations, a parameter is produced based the input
     * parameters.
     *
     * @param a,b,c,d [in] the 128-bit parameters
     * @return the resultant 128-bit parameter
     */
    UniqueParameter128b& DoRecursion(
        const UniqueParameter128b& a, const UniqueParameter128b& b,
        const UniqueParameter128b& c, const UniqueParameter128b& d) {
      static UniqueParameter128b r,x,y;
      lshift128(x,a,SL2);
      rshift128(y,c,SR2);
      r.u[0]=a.u[0]^x.u[0]^((b.u[0]>>SR1)&Msk1)^y.u[0]^(d.u[0]<<SL1);
      r.u[1]=a.u[1]^x.u[1]^((b.u[1]>>SR1)&Msk2)^y.u[1]^(d.u[1]<<SL1);
      r.u[2]=a.u[2]^x.u[2]^((b.u[2]>>SR1)&Msk3)^y.u[2]^(d.u[2]<<SL1);
      r.u[3]=a.u[3]^x.u[3]^((b.u[3]>>SR1)&Msk4)^y.u[3]^(d.u[3]<<SL1);
      return r;
    }
    /**
     * @brief generate all status
     *
     * This is a version with SSE2 instruction. It is implemented with
     * the corresponding DoRecursion operation.
     *
     * @return nothing
     */
    void GenRandAll() {
      unsigned int i;
      UniqueParameter128b *r1=&status[N-2];
      UniqueParameter128b *r2=&status[N-1];
      for(i=0;i<N-Pos1;++i) {
        status[i]=DoRecursion(status[i],status[i+Pos1],*r1,*r2);
        r1=r2;
        r2=&status[i];
      }
      for(;i<N;++i) {
        status[i]=DoRecursion(status[i],status[i+Pos1-N],*r1,*r2);
        r1=r2;
        r2=&status[i];
      }
    }
    /**
     * @brief generate an array of parameter
     *
     * It is a version without SSE2 instruction. it is implemented with
     * the DoRecursion operation. The status and the concerned array
     * are operated in a mixed manner.
     *
     * @param array [in,out] the array to be generated.
     * @param size [in] the number of parameters
     * @return nothing
     */
    void GenRandArray(UniqueParameter128b* array, const unsigned int size) {
      unsigned int i,j;
      UniqueParameter128b *r1=&status[N-2];
      UniqueParameter128b *r2=&status[N-1];
      for(i=0;i<N-Pos1;++i) {
        array[i]=DoRecursion(status[i],status[i+Pos1],*r1,*r2);
        r1=r2;
        r2=&array[i];
      }
      for(;i<N;++i) {
        array[i]=DoRecursion(status[i],array[i+Pos1],*r1,*r2);
        r1=r2;
        r2=&array[i];
      }
      for(;i<size-N;++i) {
        array[i]=DoRecursion(array[i-N],array[i+Pos1-N],r1,r2);
        r1=r2;
        r2=&array[i];
      }
      for(j=0;j<N+N-size;++j) status[j]=array[j+size-N];
      for(;i<size;++i,++j) {
        array[i]=DoRecursion(array[i-N],array[i+Pos1-N],r1,r2);
        r1=r2;
        r2=&array[i];
        status[j]=array[i];
      }
    }
#endif
    /**
     * @brief shift right for input parameter
     *
     * This procedure mainly shifts the input parameter toward right.
     * The shift operation is cyclic. The resultant parameter is written
     * to another parameter.
     *
     * @param out [out] the output 128-bit parameter
     * @param in [in] the input 128-bit parameter
     * @param shift [in] the number of bytes to be shifted
     * @return nothing
     */
    void rshift128(UniqueParameter128b& out, const UniqueParameter128b& in,
                   const int shift) {
      unsigned long long int th,tl,oh,ol;
      th=(static_cast<unsigned long long int>(in.u[3])<<32)|
         (static_cast<unsigned long long int>(in.u[2]));
      tl=(static_cast<unsigned long long int>(in.u[1])<<32)|
         (static_cast<unsigned long long int>(in.u[0]));
      oh=th>>(shift*8);
      ol=tl>>(shift*8);
      ol|=th<<(64-shift*8);
      out.u[1]=static_cast<unsigned int>(ol>>32);
      out.u[0]=static_cast<unsigned int>(ol);
      out.u[3]=static_cast<unsigned int>(oh>>32);
      out.u[2]=static_cast<unsigned int>(oh);
    }
    /**
     * @brief shift left for input parameter
     *
     * This procedure mainly shifts the input parameter toward left.
     * The shift operation is cyclic. The resultant parameter is written
     * to another parameter.
     *
     * @param out [out] the output 128-bit parameter
     * @param in [in] the input 128-bit parameter
     * @param shift [in] the number of bytes to be shifted
     * @return nothing
     */
    void lshift128(UniqueParameter128b& out, const UniqueParameter128b& in,
                   const int shift) {
      unsigned long long int th,tl,oh,ol;
      th=(static_cast<unsigned long long int>(in.u[3])<<32)|
         (static_cast<unsigned long long int>(in.u[2]));
      tl=(static_cast<unsigned long long int>(in.u[1])<<32)|
         (static_cast<unsigned long long int>(in.u[0]));
      oh=th<<(shift*8);
      ol=tl<<(shift*8);
      oh|=tl>>(64-shift*8);
      out.u[1]=static_cast<unsigned int>(ol>>32);
      out.u[0]=static_cast<unsigned int>(ol);
      out.u[3]=static_cast<unsigned int>(oh>>32);
      out.u[2]=static_cast<unsigned int>(oh);
    }
    /**
     * @brief one complex operation for an \c unsigned \c int
     *
     * This is a kind of operation for input \c unsigned \c int.
     *
     * @param x [in] the input \c unsigned \c int
     * @return the resultant \c unsigned \c int
     */
    unsigned int func1(const unsigned int x) {
      return (x^(x>>27))*static_cast<unsigned int>(1664525UL);
    }
    /**
     * @brief another complex operation for an \c unsigned \c int
     *
     * This is a kind of operation for input \c unsigned \c int.
     *
     * @param x [in] the input \c unsigned \c int
     * @return the resultant \c unsigned \c int
     */
    unsigned int func2(const unsigned int x) {
      return (x^(x>>27))*static_cast<unsigned int>(1566083941UL);
    }
    /**
     * @brief the function certificates the period (2^MExp)
     *
     * This function is used to certificate the period of the generator.
     *
     * @return nothing.
     */
    void PeriodCertification() {
      unsigned int inner=0;
      unsigned int i,j,work;
      unsigned int *pSFMT32=&(status[0].u[0]);
      for(i=0;i<4;++i)  inner^=pSFMT32[i]&Parity[i];
      for(i=16;i>0;i>>=1) inner^=inner>>i;
      inner&=1;
      if(inner==1)  return;
      for(i=0;i<4;++i) {
        work=1;
        for(j=0;j<32;++j) {
          if((work&Parity[i])!=0) {
            pSFMT32[i]^=work;
            return;
          }
          work=work<<1;
        }
      }
    }

  };

  /**
   * @brief the exponent for SFMT generator
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This exponent equals to the template parameter LoopFac. It is
   * related to the period of the random numbers generated by SFMT.
   */
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::MExp=LoopFac;
  /**
   * @brief the factor related to the size of internal storage
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::N=SFMT<LoopFac>::MExp/128+1;
  /**
   * @brief the number of the elements in status
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::NStatus=SFMT<LoopFac>::N;
  /**
   * @brief the number of the bytes in state storage
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::NStatusByte=SFMT<LoopFac>::N*16;
  /**
   * @brief the number of the 32-bit \c unsigned \c int in status storage
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::N32=SFMT<LoopFac>::N*4;
  /**
   * @brief the number of the 64-bit \c unsigned \c int in status storage
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::N64=SFMT<LoopFac>::N*2;
  /**
   * @brief the lag for SFMT generator
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This parameter is determined by the constant N32
   */
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Lag=(SFMT<LoopFac>::N32>=263?11:
                                        (SFMT<LoopFac>::N32>68?7:
                                        (SFMT<LoopFac>::N32>=39?5:3))); 
  /**
   * @brief the mid-location in 32-bit status storage
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Mid=
    (SFMT<LoopFac>::N32-SFMT<LoopFac>::Lag)/2;
  /**
   * @brief the temporary variable corresponding to the summation of Lag and Mid
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::LagMid=
    SFMT<LoopFac>::Lag+SFMT<LoopFac>::Mid;
  /**
   * @brief the array storing the parity constants
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This array contains 4 constants, Parity1, Parity2, Parity3, and Parity4.
   */
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Parity[4]={
    SFMT<LoopFac>::Parity1, SFMT<LoopFac>::Parity2,
    SFMT<LoopFac>::Parity3, SFMT<LoopFac>::Parity4 };

  /**
   * the Pos1 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This factor is defined as zero for generic case
   */
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Pos1=0;
  /**
   * the SL1 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This factor is defined as zero for generic case
   */
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::SL1=0;
  /**
   * the SL2 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This factor is defined as zero for generic case
   */
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::SL2=0;
  /**
   * the SR1 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This factor is defined as zero for generic case
   */
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::SR1=0;
  /**
   * the SR2 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This factor is defined as zero for generic case
   */
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::SR2=0;
  /**
   * the Msk1 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This factor is defined as zero for generic case
   */
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Msk1=0;
  /**
   * the Msk2 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This factor is defined as zero for generic case
   */
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Msk2=0;
  /**
   * the Msk3 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This factor is defined as zero for generic case
   */
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Msk3=0;
  /**
   * the Msk4 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This factor is defined as zero for generic case
   */
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Msk4=0;
  /**
   * the Parity1 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This factor is defined as zero for generic case
   */
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Parity1=0;
  /**
   * the Parity2 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This factor is defined as zero for generic case
   */
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Parity2=0;
  /**
   * the Parity3 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This factor is defined as zero for generic case
   */
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Parity3=0;
  /**
   * the Parity4 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This factor is defined as zero for generic case
   */
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Parity4=0;

  /**
   * the Pos1 factor for LoopFac of 607
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<607>::Pos1=2;
  /**
   * the SL1 factor for LoopFac of 607
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<607>::SL1=15;
  /**
   * the SL2 factor for LoopFac of 607
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<607>::SL2=3;
  /**
   * the SR1 factor for LoopFac of 607
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<607>::SR1=13;
  /**
   * the SR2 factor for LoopFac of 607
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<607>::SR2=3;
  /**
   * the Msk1 factor for LoopFac of 607
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<607>::Msk1=0xFDFF37FFU;
  /**
   * the Msk2 factor for LoopFac of 607
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<607>::Msk2=0xEF7F3F7DU;
  /**
   * the Msk3 factor for LoopFac of 607
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<607>::Msk3=0xFF777B7DU;
  /**
   * the Msk4 factor for LoopFac of 607
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<607>::Msk4=0x7FF7FB2FU;
  /**
   * the Parity1 factor for LoopFac of 607
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<607>::Parity1=0x00000001U;
  /**
   * the Parity4 factor for LoopFac of 607
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<607>::Parity4=0x5986F054U;

  /**
   * the Pos1 factor for LoopFac of 1279
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<1279>::Pos1=7;
  /**
   * the SL1 factor for LoopFac of 1279
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<1279>::SL1=14;
  /**
   * the SL2 factor for LoopFac of 1279
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<1279>::SL2=3;
  /**
   * the SR1 factor for LoopFac of 1279
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<1279>::SR1=5;
  /**
   * the SR2 factor for LoopFac of 1279
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<1279>::SR2=1;
  /**
   * the Msk1 factor for LoopFac of 1279
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<1279>::Msk1=0xF7FEFFFDU;
  /**
   * the Msk2 factor for LoopFac of 1279
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<1279>::Msk2=0x7FEFCFFFU;
  /**
   * the Msk3 factor for LoopFac of 1279
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<1279>::Msk3=0xAFF3EF3FU;
  /**
   * the Msk4 factor for LoopFac of 1279
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<1279>::Msk4=0xB5FFFF7FU;
  /**
   * the Parity1 factor for LoopFac of 1279
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<1279>::Parity1=0x00000001U;
  /**
   * the Parity4 factor for LoopFac of 1279
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<1279>::Parity4=0x20000000U;

  /**
   * the Pos1 factor for LoopFac of 11213
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<11213>::Pos1=68;
  /**
   * the SL1 factor for LoopFac of 11213
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<11213>::SL1=14;
  /**
   * the SL2 factor for LoopFac of 11213
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<11213>::SL2=3;
  /**
   * the SR1 factor for LoopFac of 11213
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<11213>::SR1=7;
  /**
   * the SR2 factor for LoopFac of 11213
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<11213>::SR2=3;
  /**
   * the Msk1 factor for LoopFac of 11213
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<11213>::Msk1=0xEFFFF7F8U;
  /**
   * the Msk2 factor for LoopFac of 11213
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<11213>::Msk2=0xFFFFFFEFU;
  /**
   * the Msk3 factor for LoopFac of 11213
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<11213>::Msk3=0xDFDFBFFFU;
  /**
   * the Msk4 factor for LoopFac of 11213
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<11213>::Msk4=0x7FFFDBFDU;
  /**
   * the Parity1 factor for LoopFac of 11213
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<11213>::Parity1=0x00000001U;
  /**
   * the Parity3 factor for LoopFac of 11213
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<11213>::Parity3=0xE8148000U;
  /**
   * the Parity4 factor for LoopFac of 11213
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<11213>::Parity4=0xD0C7AFA3U;

  /**
   * the Pos1 factor for LoopFac of 19937
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<19937>::Pos1=122;
  /**
   * the SL1 factor for LoopFac of 19937
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<19937>::SL1=18;
  /**
   * the SL2 factor for LoopFac of 19937
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<19937>::SL2=1;
  /**
   * the SR1 factor for LoopFac of 19937
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<19937>::SR1=11;
  /**
   * the SR2 factor for LoopFac of 19937
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<19937>::SR2=1;
  /**
   * the Msk1 factor for LoopFac of 19937
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<19937>::Msk1=0xDFFFFFEFU;
  /**
   * the Msk2 factor for LoopFac of 19937
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<19937>::Msk2=0xDDFECB7FU;
  /**
   * the Msk3 factor for LoopFac of 19937
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<19937>::Msk3=0xBFFAFFFFU;
  /**
   * the Msk4 factor for LoopFac of 19937
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<19937>::Msk4=0xBFFFFFF6U;
  /**
   * the Parity1 factor for LoopFac of 19937
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<19937>::Parity1=0x00000001U;
  /**
   * the Parity4 factor for LoopFac of 19937
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<19937>::Parity4=0x13C9E684U;

  /**
   * the Pos1 factor for LoopFac of 132049
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<132049>::Pos1=110;
  /**
   * the SL1 factor for LoopFac of 132049
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<132049>::SL1=19;
  /**
   * the SL2 factor for LoopFac of 132049
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<132049>::SL2=1;
  /**
   * the SR1 factor for LoopFac of 132049
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<132049>::SR1=21;
  /**
   * the SR2 factor for LoopFac of 132049
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<132049>::SR2=1;
  /**
   * the Msk1 factor for LoopFac of 132049
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<132049>::Msk1=0xFFFFBB5FU;
  /**
   * the Msk2 factor for LoopFac of 132049
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<132049>::Msk2=0xFB6EBF95U;
  /**
   * the Msk3 factor for LoopFac of 132049
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<132049>::Msk3=0xFFFEFFFAU;
  /**
   * the Msk4 factor for LoopFac of 132049
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<132049>::Msk4=0xCFF77FFFU;
  /**
   * the Parity1 factor for LoopFac of 132049
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<132049>::Parity1=0x00000001U;
  /**
   * the Parity3 factor for LoopFac of 132049
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<132049>::Parity3=0xCB520000U;
  /**
   * the Parity4 factor for LoopFac of 132049
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<132049>::Parity4=0xC7E91C7DU;

  /**
   * the Pos1 factor for LoopFac of 216091
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<216091>::Pos1=627;
  /**
   * the SL1 factor for LoopFac of 216091
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<216091>::SL1=11;
  /**
   * the SL2 factor for LoopFac of 216091
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<216091>::SL2=3;
  /**
   * the SR1 factor for LoopFac of 216091
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<216091>::SR1=10;
  /**
   * the SR2 factor for LoopFac of 216091
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<216091>::SR2=1;
  /**
   * the Msk1 factor for LoopFac of 216091
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<216091>::Msk1=0xBFF7BFF7U;
  /**
   * the Msk2 factor for LoopFac of 216091
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<216091>::Msk2=0xBFFFFFFFU;
  /**
   * the Msk3 factor for LoopFac of 216091
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<216091>::Msk3=0xBFFFFA7FU;
  /**
   * the Msk4 factor for LoopFac of 216091
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<216091>::Msk4=0xFFDDFBFBU;
  /**
   * the Parity1 factor for LoopFac of 216091
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<216091>::Parity1=0xF8000001U;
  /**
   * the Parity2 factor for LoopFac of 216091
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<216091>::Parity2=0x89E80709U;
  /**
   * the Parity3 factor for LoopFac of 216091
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<216091>::Parity3=0x3BD2B64BU;
  /**
   * the Parity4 factor for LoopFac of 216091
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<216091>::Parity4=0x0C64B1E4U;

  /**
   * the Pos1 factor for LoopFac of 2281
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<2281>::Pos1=12;
  /**
   * the SL1 factor for LoopFac of 2281
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<2281>::SL1=19;
  /**
   * the SL2 factor for LoopFac of 2281
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<2281>::SL2=1;
  /**
   * the SR1 factor for LoopFac of 2281
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<2281>::SR1=5;
  /**
   * the SR2 factor for LoopFac of 2281
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<2281>::SR2=1;
  /**
   * the Msk1 factor for LoopFac of 2281
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<2281>::Msk1=0xBFF7FFBFU;
  /**
   * the Msk2 factor for LoopFac of 2281
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<2281>::Msk2=0xFDFFFFFEU;
  /**
   * the Msk3 factor for LoopFac of 2281
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<2281>::Msk3=0xF7FFEF7FU;
  /**
   * the Msk4 factor for LoopFac of 2281
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<2281>::Msk4=0xF2F7CBBFU;
  /**
   * the Parity1 factor for LoopFac of 2281
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<2281>::Parity1=0x00000001U;
  /**
   * the Parity4 factor for LoopFac of 2281
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<2281>::Parity4=0x41DFA600U;

  /**
   * the Pos1 factor for LoopFac of 4253
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<4253>::Pos1=17;
  /**
   * the SL1 factor for LoopFac of 4253
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<4253>::SL1=20;
  /**
   * the SL2 factor for LoopFac of 4253
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<4253>::SL2=1;
  /**
   * the SR1 factor for LoopFac of 4253
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<4253>::SR1=7;
  /**
   * the SR2 factor for LoopFac of 4253
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<4253>::SR2=1;
  /**
   * the Msk1 factor for LoopFac of 4253
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<4253>::Msk1=0x9F7BFFFFU;
  /**
   * the Msk2 factor for LoopFac of 4253
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<4253>::Msk2=0x9FFFFF5FU;
  /**
   * the Msk3 factor for LoopFac of 4253
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<4253>::Msk3=0x3EFFFFFBU;
  /**
   * the Msk4 factor for LoopFac of 4253
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<4253>::Msk4=0xFFFFF7BBU;
  /**
   * the Parity1 factor for LoopFac of 4253
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<4253>::Parity1=0x00000001U;
  /**
   * the Parity2 factor for LoopFac of 4253
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<4253>::Parity2=0xAF5390A3U;
  /**
   * the Parity3 factor for LoopFac of 4253
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<4253>::Parity3=0xB740B3F8U;
  /**
   * the Parity4 factor for LoopFac of 4253
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<4253>::Parity4=0x6C11486DU;

  /**
   * the Pos1 factor for LoopFac of 44497
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<44497>::Pos1=330;
  /**
   * the SL1 factor for LoopFac of 44497
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<44497>::SL1=5;
  /**
   * the SL2 factor for LoopFac of 44497
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<44497>::SL2=3;
  /**
   * the SR1 factor for LoopFac of 44497
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<44497>::SR1=9;
  /**
   * the SR2 factor for LoopFac of 44497
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<44497>::SR2=3;
  /**
   * the Msk1 factor for LoopFac of 44497
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<44497>::Msk1=0xEFFFFFFBU;
  /**
   * the Msk2 factor for LoopFac of 44497
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<44497>::Msk2=0xDFBEBFFFU;
  /**
   * the Msk3 factor for LoopFac of 44497
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<44497>::Msk3=0xBFBF7BEFU;
  /**
   * the Msk4 factor for LoopFac of 44497
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<44497>::Msk4=0x9FFD7BFFU;
  /**
   * the Parity1 factor for LoopFac of 44497
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<44497>::Parity1=0x00000001U;
  /**
   * the Parity3 factor for LoopFac of 44497
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<44497>::Parity3=0xA3AC4000U;
  /**
   * the Parity4 factor for LoopFac of 44497
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<44497>::Parity4=0xECC1327AU;

  /**
   * the Pos1 factor for LoopFac of 86243
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<86243>::Pos1=366;
  /**
   * the SL1 factor for LoopFac of 86243
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<86243>::SL1=6;
  /**
   * the SL2 factor for LoopFac of 86243
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<86243>::SL2=7;
  /**
   * the SR1 factor for LoopFac of 86243
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<86243>::SR1=19;
  /**
   * the SR2 factor for LoopFac of 86243
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<86243>::SR2=1;
  /**
   * the Msk1 factor for LoopFac of 86243
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<86243>::Msk1=0xFDBFFBFFU;
  /**
   * the Msk2 factor for LoopFac of 86243
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<86243>::Msk2=0xBFF7FF3FU;
  /**
   * the Msk3 factor for LoopFac of 86243
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<86243>::Msk3=0xFD77EFFFU;
  /**
   * the Msk4 factor for LoopFac of 86243
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<86243>::Msk4=0xBF9FF3FFU;
  /**
   * the Parity1 factor for LoopFac of 86243
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<86243>::Parity1=0x00000001U;
  /**
   * the Parity4 factor for LoopFac of 86243
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <> const unsigned int SFMT<86243>::Parity4=0xE9528D85U;

  /**
   * @brief check the availability of SFMT generator
   *
   * It is implemented by checking the availability of the internal
   * status storage.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param sg [in] the SFMT generator to be checked
   * @return the flag indicating if the generator is available
   */
  template <unsigned int LoopFac>
  bool IsAvailable(const SFMT<LoopFac>& sg) { return IsAvailable(sg.status); }

  /**
   * @brief check if SFMT generator is random generator
   *
   * This gives out the true flag since the SFMT generator is a random
   * generator.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param sg [in] the SFMT generator to be checked
   * @return always true flag indicating SFMT generator is a random generator
   */
  template <unsigned int LoopFac>
  void IsRandomGenerator(const SFMT<LoopFac>& sg) { return true; }

  /**
   * @brief release SFMT generator
   *
   * The internal storages are released based on the type of storage.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param sg [in,out] the SFMT generator to be released
   * @return nothing
   */
  template <unsigned int LoopFac>
  void release(SFMT<LoopFac>& sg) {
    if(sg.state==Allocated) {
      safe_delete_array(sg.status);
      safe_delete(sg.idx);
      safe_delete(sg.output);
    } else {
      sg.status=NULL;
      sg.idx=NULL;
      sg.output=NULL;
    }
    sg.state=Unused;
  }

  /**
   * @brief allocate SFMT generator
   *
   * The internal storage is allocated. The generator is released before this
   * operation. Then, the generator is initiated with a default seed 5489.
   *
   * @param sg [out] the SFMT generator to be allocated
   * @return nothing
   */
  template <unsigned int LoopFac>
  void allocate(SFMT<LoopFac>& sg) {
    release(sg);
    sg.status=new UniqueParameter128b[SFMT<LoopFac>::NStatus];
    sg.idx=new unsigned int;
    sg.output=new UniqueParameter128b;
    sg.state=Allocated;
    init(sg,5489U);
  }

  /**
   * @brief assign SFMT generator from another
   *
   * Just assign the internal status of the destinate generator
   * from the source. The internal index is also copied. The
   * concerned generators are checked for their availability
   * before this operation.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param dest [out] the destinate generator to accept input data
   * @param src [in] the source generator containing input data
   * @return nothing
   */
  template <unsigned int LoopFac>
  void assign(SFMT<LoopFac>& dest, const SFMT<LoopFac>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(dest.status.src.status,SFMT<LoopFac>::NStatus);
    *dest.idx=*src.idx;
  }

  /**
   * @brief refer to another SFMT generator
   *
   * Just copy the pointers from source to destinate. The source
   * generator is checked for its availability before this operation.
   * The destinate generator is released before this operation.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param dest [out] the destinate generator to accept input data
   * @param src [in] the source generator containing input data
   * @return nothing
   */
  template <unsigned int LoopFac>
  void refer(SFMT<LoopFac>& dest, const SFMT<LoopFac>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.status=src.status;
    dest.idx=src.idx;
    dest.output=src.output;
    dest.state=Reference;
  }

  /**
   * @brief initiate SFMT generator with an \c unsigned \c int seed
   *
   * It is generated with simple generation method for the status
   * in generator.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param sg [out] the SFMT generator to be initiated
   * @param seed [in] the \c unsigned \c int as the seed
   * @return nothing
   */
  template <unsigned int LoopFac>
  void init(SFMT<LoopFac>& sg, const unsigned int seed) {
    assert(IsAvailable(sg));
    unsigned int *pSFMT32=&(sg.status[0].u[0]),work;
    pSFMT32[0]=seed;
    work=pSFMT32[0];
    for(unsigned int i=1;i<SFMT<LoopFac>::N32;++i) {
      work=1812433253UL*(work^(work>>30))+i;
      pSFMT32[i]=work;
    }
    *(sg.idx)=SFMT<LoopFac>::N32;
    sg.PeriodCertification();
  }

  /**
   * @brief initiate SFMT generator with an \c unsigned \c int array
   *
   * This procedure could offer more input bits for initiation.
   * It could produce distribution with better statistical
   * property.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param sg [out] the SFMT generator to be initiated.
   * @param key [in] the array containing the seeds
   * @param len [in] the number of seeds in array key
   * @param off [in] the offset for the first elements in array key,
   *                 which takes the default value of uZero.
   * @param step [in] the separation between elements in array key,
   *                  which takes the default value of uOne
   * @return nothing
   */
  template <unsigned int LoopFac>
  void init(SFMT<LoopFac>& sg,
            const unsigned int *key, const unsigned int len,
            const unsigned int off=uZero, const unsigned int step=uOne) {
    unsigned int i,j,g,count,r,tmid,*pSFMT32;
    pSFMT32=&(sg.status[0].u[0]);
    memset(sg.status,0x8B,SFMT<LoopFac>::NStatusByte);
    count=(len+1>SFMT<LoopFac>::N32?len+1:SFMT<LoopFac>::N32);
    r=sg.func1(pSFMT32[0]^pSFMT32[SFMT<LoopFac>::Mid]
                         ^pSFMT32[SFMT<LoopFac>::N32-1]);
    pSFMT32[SFMT<LoopFac>::Mid]+=r;
    r+=len;
    pSFMT32[SFMT<LoopFac>::LagMid]+=r;
    pSFMT32[0]=r;
    --count;
    for(i=1,j=0,g=off;j<len;++j,g+=step) {
      tmid=(i+SFMT<LoopFac>::Mid)%SFMT<LoopFac>::N32;
      r=sg.func1(pSFMT32[i]^pSFMT32[tmid]
          ^pSFMT32[(i+SFMT<LoopFac>::N32-1)%SFMT<LoopFac>::N32]);
      pSFMT32[tmid]+=r;
      r+=key[g]+i;
      pSFMT32[(i+SFMT<LoopFac>::LagMid)%SFMT<LoopFac>::N32]+=r;
      pSFMT32[i]=r;
      i=(i+1)%SFMT<LoopFac>::N32;
    }
    for(;j<count;++j) {
      tmid=(i+SFMT<LoopFac>::Mid)%SFMT<LoopFac>::N32;
      r=sg.func1(pSFMT32[i]^pSFMT32[tmid]
          ^pSFMT32[(i+SFMT<LoopFac>::N32-1)%SFMT<LoopFac>::N32]);
      pSFMT32[tmid]+=r;
      r+=i;
      pSFMT32[(i+SFMT<LoopFac>::LagMid)%SFMT<LoopFac>::N32]+=r;
      pSFMT32[i]=r;
      i=(i+1)%SFMT<LoopFac>::N32;
    }
    for(j=0;j<SFMT<LoopFac>::N32;++j) {
      tmid=(i+SFMT<LoopFac>::Mid)%SFMT<LoopFac>::N32;
      r=sg.func2(pSFMT32[i]^pSFMT32[tmid]
          ^pSFMT32[(i+SFMT<LoopFac>::N32-1)%SFMT<LoopFac>::N32]);
      pSFMT32[tmid]^=r;
      r-=i;
      pSFMT32[(i+SFMT<LoopFac>::LagMid)%SFMT<LoopFac>::N32]^=r;
      pSFMT32[i]=r;
      i=(i+1)%SFMT<LoopFac>::N32;
    }
    *(sg.idx)=SFMT<LoopFac>::N32;
    sg.PeriodCertification();
  }

  /**
   * @brief initiate SFMT generator with a vector
   *
   * It is implemented with the init procedure for array.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param sg [out] the SFMT generator to be initiated.
   * @param key [in] the vector containing the seeds
   * @return nothing
   */
  template <unsigned int LoopFac>
  void init(SFMT<LoopFac>& sg, const Vector<unsigned int>& key) {
    init(sg,key(),key.size);
  }

  /**
   * @brief fill \c unsigned \c int array with SFMT generator
   *
   * an array with \c unsigned \c int elements could be filled
   * with this procedure. It requires that the internal storage
   * in the generator is just used out. it is implemented with
   * GenRandArray method of SFMT generator.
   *
   * @note It is said that this operation is faster than the
   *       regular generation of numbers in one-by-one manner.
   * @note There are restrictions for the size of the output array
   */
  template <unsigned int LoopFac>
  void fillarray(SFMT<LoopFac>& sg,
                 unsigned int* array, const unsigned int size) {
    assert(*(sg.idx)==SFMT<LoopFac>::N32);
    assert(size%4==0);
    assert(size>=SFMT<LoopFac>::N32);
    sg.GenRandArray(reinterpret_cast<UniqueParameter128b*>(array),size>>2);
    *(sg.idx)=SFMT<LoopFac>::N32;
  }

  /**
   * @brief fill \c unsigned \c long \c long \c int array with SFMT generator
   *
   * an array with \c unsigned \c long \c long \c int elements could be filled
   * with this procedure. It requires that the internal storage
   * in the generator is just used out. it is implemented with
   * GenRandArray method of SFMT generator.
   *
   * @note It is said that this operation is faster than the
   *       regular generation of numbers in one-by-one manner.
   * @note There are restrictions for the size of the output array
   */
  template <unsigned int LoopFac>
  void fillarray(SFMT<LoopFac>& sg,
                 unsigned long long int* array, const unsigned int size) {
    assert(*(sg.idx)==SFMT<LoopFac>::N32);
    assert(size%2==0);
    assert(size>=SFMT<LoopFac>::N64);
    sg.GenRandArray(reinterpret_cast<UniqueParameter128b*>(array),size>>1);
    *(sg.idx)=SFMT<LoopFac>::N32;
  }

  /**
   * @brief generate a 32-bit \c unsigned \c int value
   *
   * It is implemented with UInt32 method of generator.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param sg [in,out] the SFMT generator used for value generation
   * @return a 32-bit \c unsigned \c int value
   */
  template <unsigned int LoopFac>
  const unsigned int& rand(SFMT<LoopFac>& sg) { return sg.UInt32(); }

  /**
   * @brief generate a T-type number with SFMT generator for LoopFac of 607
   *
   * This gives the generic form. It is prohibited and pops up a message.
   *
   * T is the type of the output number
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated T-type number
   */
  template <typename T>
  const T& rand(SFMT<607>& sg) { myError("Default form is prohibited!"); }
  /**
   * @brief generate a T-type number with SFMT generator for LoopFac of 1789
   *
   * This gives the generic form. It is prohibited and pops up a message.
   *
   * T is the type of the output number
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated T-type number
   */
  template <typename T>
  const T& rand(SFMT<1279>& sg) { myError("Default form is prohibited!"); }
  /**
   * @brief generate a T-type number with SFMT generator for LoopFac of 2281
   *
   * This gives the generic form. It is prohibited and pops up a message.
   *
   * T is the type of the output number
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated T-type number
   */
  template <typename T>
  const T& rand(SFMT<2281>& sg) { myError("Default form is prohibited!"); }
  /**
   * @brief generate a T-type number with SFMT generator for LoopFac of 4253
   *
   * This gives the generic form. It is prohibited and pops up a message.
   *
   * T is the type of the output number
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated T-type number
   */
  template <typename T>
  const T& rand(SFMT<4253>& sg) { myError("Default form is prohibited!"); }
  /**
   * @brief generate a T-type number with SFMT generator for LoopFac of 11213
   *
   * This gives the generic form. It is prohibited and pops up a message.
   *
   * T is the type of the output number
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated T-type number
   */
  template <typename T>
  const T& rand(SFMT<11213>& sg) { myError("Default form is prohibited!"); }
  /**
   * @brief generate a T-type number with SFMT generator for LoopFac of 19937
   *
   * This gives the generic form. It is prohibited and pops up a message.
   *
   * T is the type of the output number
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated T-type number
   */
  template <typename T>
  const T& rand(SFMT<19937>& sg) { myError("Default form is prohibited!"); }
  /**
   * @brief generate a T-type number with SFMT generator for LoopFac of 44497
   *
   * This gives the generic form. It is prohibited and pops up a message.
   *
   * T is the type of the output number
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated T-type number
   */
  template <typename T>
  const T& rand(SFMT<44497>& sg) { myError("Default form is prohibited!"); }
  /**
   * @brief generate a T-type number with SFMT generator for LoopFac of 86243
   *
   * This gives the generic form. It is prohibited and pops up a message.
   *
   * T is the type of the output number
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated T-type number
   */
  template <typename T>
  const T& rand(SFMT<86243>& sg) { myError("Default form is prohibited!"); }
  /**
   * @brief generate a T-type number with SFMT generator for LoopFac of 132049
   *
   * This gives the generic form. It is prohibited and pops up a message.
   *
   * T is the type of the output number
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated T-type number
   */
  template <typename T>
  const T& rand(SFMT<132049>& sg) { myError("Default form is prohibited!"); }
  /**
   * @brief generate a T-type number with SFMT generator for LoopFac of 216091
   *
   * This gives the generic form. It is prohibited and pops up a message.
   *
   * T is the type of the output number
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated T-type number
   */
  template <typename T>
  const T& rand(SFMT<216091>& sg) { myError("Default form is prohibited!"); }

  /**
   * @brief generate a \c unsigned \c int number with SFMT generator for LoopFac of 607
   *
   * This is the specification for \c unsigned \c int type. It is implemented by
   * rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c int number
   */
  template <>
  const unsigned int& rand<unsigned int>(SFMT<607>& sg) { return rand(sg); }
  /**
   * @brief generate a \c unsigned \c int number with SFMT generator for LoopFac of 1279
   *
   * This is the specification for \c unsigned \c int type. It is implemented by
   * rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c int number
   */
  template <>
  const unsigned int& rand<unsigned int>(SFMT<1279>& sg) { return rand(sg); }
  /**
   * @brief generate a \c unsigned \c int number with SFMT generator for LoopFac of 2281
   *
   * This is the specification for \c unsigned \c int type. It is implemented by
   * rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c int number
   */
  template <>
  const unsigned int& rand<unsigned int>(SFMT<2281>& sg) { return rand(sg); }
  /**
   * @brief generate a \c unsigned \c int number with SFMT generator for LoopFac of 4253
   *
   * This is the specification for \c unsigned \c int type. It is implemented by
   * rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c int number
   */
  template <>
  const unsigned int& rand<unsigned int>(SFMT<4253>& sg) { return rand(sg); }
  /**
   * @brief generate a \c unsigned \c int number with SFMT generator for LoopFac of 11213
   *
   * This is the specification for \c unsigned \c int type. It is implemented by
   * rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c int number
   */
  template <>
  const unsigned int& rand<unsigned int>(SFMT<11213>& sg) { return rand(sg); }
  /**
   * @brief generate a \c unsigned \c int number with SFMT generator for LoopFac of 19937
   *
   * This is the specification for \c unsigned \c int type. It is implemented by
   * rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c int number
   */
  template <>
  const unsigned int& rand<unsigned int>(SFMT<19937>& sg) { return rand(sg); }
  /**
   * @brief generate a \c unsigned \c int number with SFMT generator for LoopFac of 44497
   *
   * This is the specification for \c unsigned \c int type. It is implemented by
   * rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c int number
   */
  template <>
  const unsigned int& rand<unsigned int>(SFMT<44497>& sg) { return rand(sg); }
  /**
   * @brief generate a \c unsigned \c int number with SFMT generator for LoopFac of 86243
   *
   * This is the specification for \c unsigned \c int type. It is implemented by
   * rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c int number
   */
  template <>
  const unsigned int& rand<unsigned int>(SFMT<86243>& sg) { return rand(sg); }
  /**
   * @brief generate a \c unsigned \c int number with SFMT generator for LoopFac of 132049
   *
   * This is the specification for \c unsigned \c int type. It is implemented by
   * rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c int number
   */
  template <>
  const unsigned int& rand<unsigned int>(SFMT<132049>& sg) { return rand(sg); }
  /**
   * @brief generate a \c unsigned \c int number with SFMT generator for LoopFac of 216091
   *
   * This is the specification for \c unsigned \c int type. It is implemented by
   * rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c int number
   */
  template <>
  const unsigned int& rand<unsigned int>(SFMT<216091>& sg) { return rand(sg); }

  /**
   * @brief generate a \c unsigned \c long \c long \c int number with SFMT generator for LoopFac of 607
   *
   * This is the specification for \c unsigned \c long \c long \c int type.
   * It is implemented by rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c long \c long \c int number
   */
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<607>& sg) {
    return sg.UInt64();
  }
  /**
   * @brief generate a \c unsigned \c long \c long \c int number with SFMT generator for LoopFac of 1297
   *
   * This is the specification for \c unsigned \c long \c long \c int type.
   * It is implemented by rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c long \c long \c int number
   */
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<1279>& sg) {
    return sg.UInt64();
  }
  /**
   * @brief generate a \c unsigned \c long \c long \c int number with SFMT generator for LoopFac of 2281
   *
   * This is the specification for \c unsigned \c long \c long \c int type.
   * It is implemented by rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c long \c long \c int number
   */
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<2281>& sg) {
    return sg.UInt64();
  }
  /**
   * @brief generate a \c unsigned \c long \c long \c int number with SFMT generator for LoopFac of 4253
   *
   * This is the specification for \c unsigned \c long \c long \c int type.
   * It is implemented by rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c long \c long \c int number
   */
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<4253>& sg) {
    return sg.UInt64();
  }
  /**
   * @brief generate a \c unsigned \c long \c long \c int number with SFMT generator for LoopFac of 11213
   *
   * This is the specification for \c unsigned \c long \c long \c int type.
   * It is implemented by rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c long \c long \c int number
   */
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<11213>& sg) {
    return sg.UInt64();
  }
  /**
   * @brief generate a \c unsigned \c long \c long \c int number with SFMT generator for LoopFac of 19937
   *
   * This is the specification for \c unsigned \c long \c long \c int type.
   * It is implemented by rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c long \c long \c int number
   */
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<19937>& sg) {
    return sg.UInt64();
  }
  /**
   * @brief generate a \c unsigned \c long \c long \c int number with SFMT generator for LoopFac of 44497
   *
   * This is the specification for \c unsigned \c long \c long \c int type.
   * It is implemented by rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c long \c long \c int number
   */
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<44497>& sg) {
    return sg.UInt64();
  }
  /**
   * @brief generate a \c unsigned \c long \c long \c int number with SFMT generator for LoopFac of 86243
   *
   * This is the specification for \c unsigned \c long \c long \c int type.
   * It is implemented by rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c long \c long \c int number
   */
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<86243>& sg) {
    return sg.UInt64();
  }
  /**
   * @brief generate a \c unsigned \c long \c long \c int number with SFMT generator for LoopFac of 132049
   *
   * This is the specification for \c unsigned \c long \c long \c int type.
   * It is implemented by rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c long \c long \c int number
   */
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<132049>& sg) {
    return sg.UInt64();
  }
  /**
   * @brief generate a \c unsigned \c long \c long \c int number with SFMT generator for LoopFac of 216091
   *
   * This is the specification for \c unsigned \c long \c long \c int type.
   * It is implemented by rand operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c unsigned \c long \c long \c int number
   */
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<216091>& sg) {
    return sg.UInt64();
  }

  /**
   * @brief generate a \c double number with SFMT generator for LoopFac of 607
   *
   * This is the specification for \c double int type.
   * It is implemented by Double53Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c double number
   */
  template <>
  const double& rand<double>(SFMT<607>& sg) {
    return sg.Double53Close0Open1();
  }
  /**
   * @brief generate a \c double number with SFMT generator for LoopFac of 1279
   *
   * This is the specification for \c double int type.
   * It is implemented by Double53Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c double number
   */
  template <>
  const double& rand<double>(SFMT<1279>& sg) {
    return sg.Double53Close0Open1();
  }
  /**
   * @brief generate a \c double number with SFMT generator for LoopFac of 2281
   *
   * This is the specification for \c double int type.
   * It is implemented by Double53Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c double number
   */
  template <>
  const double& rand<double>(SFMT<2281>& sg) {
    return sg.Double53Close0Open1();
  }
  /**
   * @brief generate a \c double number with SFMT generator for LoopFac of 4253
   *
   * This is the specification for \c double int type.
   * It is implemented by Double53Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c double number
   */
  template <>
  const double& rand<double>(SFMT<4253>& sg) {
    return sg.Double53Close0Open1();
  }
  /**
   * @brief generate a \c double number with SFMT generator for LoopFac of 11213
   *
   * This is the specification for \c double int type.
   * It is implemented by Double53Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c double number
   */
  template <>
  const double& rand<double>(SFMT<11213>& sg) {
    return sg.Double53Close0Open1();
  }
  /**
   * @brief generate a \c double number with SFMT generator for LoopFac of 19937
   *
   * This is the specification for \c double int type.
   * It is implemented by Double53Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c double number
   */
  template <>
  const double& rand<double>(SFMT<19937>& sg) {
    return sg.Double53Close0Open1();
  }
  /**
   * @brief generate a \c double number with SFMT generator for LoopFac of 44497
   *
   * This is the specification for \c double int type.
   * It is implemented by Double53Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c double number
   */
  template <>
  const double& rand<double>(SFMT<44497>& sg) {
    return sg.Double53Close0Open1();
  }
  /**
   * @brief generate a \c double number with SFMT generator for LoopFac of 86243
   *
   * This is the specification for \c double int type.
   * It is implemented by Double53Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c double number
   */
  template <>
  const double& rand<double>(SFMT<86243>& sg) {
    return sg.Double53Close0Open1();
  }
  /**
   * @brief generate a \c double number with SFMT generator for LoopFac of 132049
   *
   * This is the specification for \c double int type.
   * It is implemented by Double53Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c double number
   */
  template <>
  const double& rand<double>(SFMT<132049>& sg) {
    return sg.Double53Close0Open1();
  }
  /**
   * @brief generate a \c double number with SFMT generator for LoopFac of 216091
   *
   * This is the specification for \c double int type.
   * It is implemented by Double53Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated \c double number
   */
  template <>
  const double& rand<double>(SFMT<216091>& sg) {
    return sg.Double53Close0Open1();
  }

  /**
   * @brief generate a \c long \c double number with SFMT generator for LoopFac of 607
   *
   * This is the specification for \c long \c double int type.
   * It is implemented by Double63Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated c long \c double number
   */
  template <>
  const long double& rand<long double>(SFMT<607>& sg) {
    return sg.LDouble63Close0Open1();
  }
  /**
   * @brief generate a \c long \c double number with SFMT generator for LoopFac of 1279
   *
   * This is the specification for \c long \c double int type.
   * It is implemented by Double63Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated c long \c double number
   */
  template <>
  const long double& rand<long double>(SFMT<1279>& sg) {
    return sg.LDouble63Close0Open1();
  }
  /**
   * @brief generate a \c long \c double number with SFMT generator for LoopFac of 2281
   *
   * This is the specification for \c long \c double int type.
   * It is implemented by Double63Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated c long \c double number
   */
  template <>
  const long double& rand<long double>(SFMT<2281>& sg) {
    return sg.LDouble63Close0Open1();
  }
  /**
   * @brief generate a \c long \c double number with SFMT generator for LoopFac of 4253
   *
   * This is the specification for \c long \c double int type.
   * It is implemented by Double63Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated c long \c double number
   */
  template <>
  const long double& rand<long double>(SFMT<4253>& sg) {
    return sg.LDouble63Close0Open1();
  }
  /**
   * @brief generate a \c long \c double number with SFMT generator for LoopFac of 11213
   *
   * This is the specification for \c long \c double int type.
   * It is implemented by Double63Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated c long \c double number
   */
  template <>
  const long double& rand<long double>(SFMT<11213>& sg) {
    return sg.LDouble63Close0Open1();
  }
  /**
   * @brief generate a \c long \c double number with SFMT generator for LoopFac of 19937
   *
   * This is the specification for \c long \c double int type.
   * It is implemented by Double63Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated c long \c double number
   */
  template <>
  const long double& rand<long double>(SFMT<19937>& sg) {
    return sg.LDouble63Close0Open1();
  }
  /**
   * @brief generate a \c long \c double number with SFMT generator for LoopFac of 44497
   *
   * This is the specification for \c long \c double int type.
   * It is implemented by Double63Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated c long \c double number
   */
  template <>
  const long double& rand<long double>(SFMT<44497>& sg) {
    return sg.LDouble63Close0Open1();
  }
  /**
   * @brief generate a \c long \c double number with SFMT generator for LoopFac of 86243
   *
   * This is the specification for \c long \c double int type.
   * It is implemented by Double63Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated c long \c double number
   */
  template <>
  const long double& rand<long double>(SFMT<86243>& sg) {
    return sg.LDouble63Close0Open1();
  }
  /**
   * @brief generate a \c long \c double number with SFMT generator for LoopFac of 132049
   *
   * This is the specification for \c long \c double int type.
   * It is implemented by Double63Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated c long \c double number
   */
  template <>
  const long double& rand<long double>(SFMT<132049>& sg) {
    return sg.LDouble63Close0Open1();
  }
  /**
   * @brief generate a \c long \c double number with SFMT generator for LoopFac of 216091
   *
   * This is the specification for \c long \c double int type.
   * It is implemented by Double63Close0Open1 operation.
   *
   * @param sg [in,out] the SFMT generator
   * @return the generated c long \c double number
   */
  template <>
  const long double& rand<long double>(SFMT<216091>& sg) {
    return sg.LDouble63Close0Open1();
  }

  template <unsigned int LoopFac>
  ostream& operator<<(ostream& os, const SFMT<LoopFac>& sg) {
    assert(IsAvailable(sg));
    os<<LoopFac<<"\t";
    for(unsigned int i=0;i<SFMT<LoopFac>::NStatus;++i) os<<sg.status[i]<<"\t";
    os<<*(sg.idx);
    return os;
  }

  template <unsigned int LoopFac>
  istream& operator>>(istream& is, SFMT<LoopFac>& sg) {
    assert(IsAvailable(sg));
    unsigned int expLoopFac;
    is>>expLoopFac;
    if(expLoopFac!=LoopFac) myError("Imcompatible data for SFMT generator");
    for(unsigned int i=0;i<SFMT<LoopFac>::NStatus;++i) is>>sg.status[i];
    is>>*(sg.idx);
    return is;
  }

}

#endif

