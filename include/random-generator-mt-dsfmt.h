
/**
 * @file random-generator-mt-dsfmt.h
 * @brief random generator with MT-dSFMT algorithm
 *
 * This file implements the generator with uniform distribution
 * using MT-dSFMT algorithm.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Random_Generator_MT_DSFMT_H_
#define _Random_Generator_MT_DSFMT_H_

#include "unique-parameter-128bit.h"
#include "vector.h"
#include <cstring>

namespace std {

#ifdef HAVE_SSE2
  /**
   * @brief a mask for SSE2 calculation which is a type of 128-bit \c int
   */
  __m128i   dSFMT_SSE2_ParamMask;
  /**
   * @brief a 128-bit \c int with the value of one
   */
  __m128i   dSFMT_SSE2_IntOne;
  /**
   * @brief a 128-bit \c double with the value of two
   */
  __m128d   dSFMT_SSE2_DoubleTwo;
  /**
   * @brief a 128-bit \c double with the value of negative one
   */
  __m128d   dSFMT_SSE2_DoubleMOne;  
#endif

  /**
   * @brief convert parameter to the region [1,2)
   *
   * This procedure does nothing, and only provides an interface.
   *
   * @param w [in,out] the parameter to be converted
   * @return nothing
   */
  void ConvertClose1Open2(UniqueParameter128b& w) {}
#ifdef HAVE_SSE2
  /**
   * @brief convert parameter to region [0,1) with SSE2 instruction
   *
   * It uses the SSE2 instructions to carry out the convert operation.
   *
   * @param w [in,out] the parameter to be converted
   * @return nothing
   *
   * @note Several loadu instructions are used to avoid align problem.
   *       However the penalty of efficiency may occur.
   */
  void ConvertClose0Open1(UniqueParameter128b& w) {
    __m128d wd,cd;
    wd=_mm_loadu_pd(w.d);
    cd=_mm_loadu_pd((double*)(&dSFMT_SSE2_DoubleMOne));
    _mm_storeu_pd(w.d,_mm_add_pd(wd,cd));
  }
  /**
   * @brief convert parameter to region (0,1] with SSE2 instruction
   *
   * It uses the SSE2 instructions to carry out the convert operation.
   *
   * @param w [in,out] the parameter to be converted
   * @return nothing
   *
   * @note Several loadu instructions are used to avoid align problem.
   *       However the penalty of efficiency may occur.
   */
  void ConvertOpen0Close1(UniqueParameter128b& w) {
    __m128d wd,cd;
    wd=_mm_loadu_pd(w.d);
    cd=_mm_loadu_pd((double*)(&dSFMT_SSE2_DoubleTwo));
    _mm_storeu_pd(w.d,_mm_sub_pd(cd,wd));
  }
  /**
   * @brief convert parameter to region (0,1) with SSE2 instruction
   *
   * It uses the SSE2 instructions to carry out the convert operation.
   *
   * @param w [in,out] the parameter to be converted
   * @return nothing
   *
   * @note Several loadu instructions are used to avoid align problem.
   *       However the penalty of efficiency may occur.
   */
  void ConvertOpen0Open1(UniqueParameter128b& w) {
    __m128i wi,ci;
    wi=_mm_loadu_si128(&(w.si));
    ci=_mm_loadu_si128(&dSFMT_SSE2_IntOne);
    _mm_storeu_si128(&(w.si),_mm_or_si128(wi,ci));
    __m128d wd,cd;
    wd=_mm_loadu_pd(w.d);
    cd=_mm_loadu_pd((double*)(&dSFMT_SSE2_DoubleMOne));
    _mm_storeu_pd(w.d,_mm_add_pd(wd,cd));
  }
#else
  /**
   * @brief convert parameter to region [0,1) without SSE2 instruction
   *
   * Just minus the parameter with unit. It is assumed that the parameter
   * contains \c double values in region [1,2)
   *
   * @param w [in,out] the parameter to be converted
   * @return nothing
   */
  void ConvertClose0Open1(UniqueParameter128b& w) { w.d[0]-=1.0; w.d[1]-=1.0; }
  /**
   * @brief convert parameter to region (0,1] without SSE2 instruction
   *
   * Just the result is 2 minus the parameter. It is assumed that the parameter
   * contains \c double values in region [1,2)
   *
   * @param w [in,out] the parameter to be converted
   * @return nothing
   */
  void ConvertOpen0Close1(UniqueParameter128b& w) {
    w.d[0]=2.0-w.d[0];
    w.d[1]=2.0-w.d[1];
  }
  /**
   * @brief convert parameter to region (0,1) without SSE2 instruction
   *
   * It firstly masks the lowest bit. Then, the result is the parameter
   * minus unit. It is assumed that the parameter contains \c double values
   * in region [1,2)
   *
   * @param w [in,out] the parameter to be converted
   * @return nothing
   */
  void ConvertOpen0Open1(UniqueParameter128b& w) {
    w.ull[0]|=1;
    w.ull[1]|=1;
    w.d[0]-=1.0;
    w.d[1]-=1.0;
  }
#endif

  /**
   * @brief dSFMT generator
   *
   * This is a generator to produce random numbers with uniform distribution.
   * It is said that this kind of generator is efficient to produce
   * \c double values.
   *
   * LoopFac is the factor related to the size of internal storage.
   */ 
  template <unsigned int LoopFac=19937>
  struct dSFMT {

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
    static const unsigned int IsFacAvailable;

    /**
     * @brief the internal storage storing status
     */
    UniqueParameter128b *status;
    /**
     * @brief the pointer to the location indicator
     */
    unsigned int *idx;
    /**
     * @brief the pointer to the parameter storing output information
     */
    UniqueParameter128b *output;
    /**
     * @brief the storage state for dSFMT generator
     */
    unsigned int state;

    /**
     * @brief abbreviation of the name for dSFMT generator
     */
    typedef dSFMT<LoopFac>    Type;
    /**
     * @brief the type of the function pointer to convert function
     */
    typedef void (*ConvertFuncType)(UniqueParameter128b&);

    /**
     * @brief default initiator
     *
     * Just set all the pointers as NULL and initiate the state as Unused.
     * Besides, the check for the availability of the LoopFac factor is
     * also done.
     */
    dSFMT() : status(NULL), idx(NULL), output(NULL), state(Unused) {
      assert(IsFacAvailable!=0);
    }
    /**
     * @brief initiator with another dSFMT generator
     *
     * It is prohibited and pop up an error message.
     *
     * @param dg [in] the input dSFMT generator.
     */ 
    dSFMT(const Type& dg) { myError("Cannot create from dSFMT generator"); }
    /**
     * @brief copy from another dSFMT generator
     *
     * It is implemented with assign operation.
     *
     * @param dg [in] the input dSFMT generator
     * @return the reference to the resultant dSFMT generator
     */
    Type& operator=(const Type& dg) { assign(*this,dg); return *this; }
    /**
     * @brief destructor
     *
     * it is implemented with release operation.
     */
    ~dSFMT() { release(*this); }

    /**
     * @brief initiate generator with \c unsigned \c int seed
     *
     * It is implemented with init operation.
     *
     * @param seed [in] the \c unsigned \c int as seed
     * @return nothing
     */
    void Init(const unsigned int seed) { init(*this,seed); }
    /**
     * @brief initiate generator with an array
     *
     * It is implemented with init operation.
     *
     * @param key [in] the array containing seeds
     * @param len [in] the number of seeds
     * @param off [in] the offset for the first element in array key. It
     *                 takes the default value of uZero.
     * @param step [in] the step between elements in array key. It takes
     *                  the default value of uOne.
     * @return nothing
     */
    void Init(const unsigned int* key, const unsigned int len,
              const unsigned int off=uZero, const unsigned int step=uOne) {
      init(*this,key,len,off,step);
    }
    /**
     * @brief initiate generator with a vector
     *
     * It is implemented with init operation.
     *
     * @param key [in] the vector containing seeds
     * @return nothing
     */
    void Init(const Vector<unsigned int>& key) { init(*this,key); }

    /**
     * @brief produce a \c unsigned \c int value
     *
     * First set the parameter array as the type of \c unsigned \c long
     * \c long. Certain element is picked out as output.
     *
     * @return the \c unsigned \c int value.
     */
    const unsigned int& UInt32() {
      unsigned long long int *pSFMT=&(status[0].ull[0]);
      if(*idx>=N64) { GenRandAll(); *idx=0; }
      output->u[0]=pSFMT[(*idx)++]&0xFFFFFFFFUL;
      return output->u[0];
    }
    /**
     * @brief produce a \c double value in region [1,2)
     *
     * First set the parameter array as the type of \c double. Certain
     * element is picked up as output.
     *
     * @return the \c double value in region [1,2) 
     */
    const double& DoubleClose1Open2() {
      double* pSFMT=&(status[0].d[0]);
      if(*idx>=N64) { GenRandAll(); *idx=0; }
      output->d[0]=pSFMT[(*idx)++];
      return output->d[0];
    }
    /**
     * @brief produce a \c double value in region [0,1)
     *
     * Just shift the \c double value from [1,2) to [0,1)
     *
     * @return the \c double value in region [0,1)
     */
    const double& DoubleClose0Open1() {
      output->d[1]=DoubleClose1Open2()-1.0;
      return output->d[1];
    }
    /**
     * @brief produce a \c double value in region (0,1]
     *
     * Just shift the \c double value from [1,2) to (0,1]
     *
     * @return the \c double value in region (0,1]
     */
    const double& DoubleOpen0Close1() {
      output->d[1]=2.0-DoubleClose1Open2();
      return output->d[1];
    }
    /**
     * @brief produce a \c double value in region (0,1)
     *
     * Just shift the \c double value from [1,2) to (0,1) after masking
     * the lowest bit.
     *
     * @return the \c double value in region (0,1)
     */
    const double& DoubleOpen0Open1() {
      double *pSFMT=&(status[0].d[0]);
      if(*idx>=N64) { GenRandAll(); *idx=0; }
      output->d[0]=pSFMT[(*idx)++];
      output->ull[0]|=1;
      output->d[1]=output->d[0]-1.0;
      return output->d[1];
    }

    /**
     * @brief fill array with numbers in region [1,2)
     *
     * It is implemented with the internal module to produce a series of
     * random numbers in region [1,2)
     *
     * @param array [out] the array to be filled with
     * @param sz [in] the number of elements in array
     * @return nothing
     */
    void fillarrayClose1Open2(double* array, const unsigned int sz) {
      FillArrayImpl(array,sz,ConvertClose1Open2);
    }

    /**
     * @brief fill array with number in region [0,1)
     *
     * It is implemented with the internal module to produce a series of
     * random numbers in region [0,1)
     *
     * @param array [out] the array to be filled with
     * @param sz [in] the number of elements in array
     * @return nothing
     */
    void fillarrayClose0Open1(double* array, const unsigned int sz) {
      FillArrayImpl(array,sz,ConvertClose0Open1);
    }

    /**
     * @brief fill array with number in region (0,1]
     *
     * It is implemented with the internal module to produce a series of
     * random numbers in region (0,1]
     *
     * @param array [out] the array to be filled with
     * @param sz [in] the number of elements in array
     * @return nothing
     */
    void fillarrayOpen0Close1(double* array, const unsigned int sz) {
      FillArrayImpl(array,sz,ConvertOpen0Close1);
    }

    /**
     * @brief fill array with number in region (0,1)
     *
     * It is implemented with the internal module to produce a series of
     * random numbers in region (0,1)
     *
     * @param array [out] the array to be filled with
     * @param sz [in] the number of elements in array
     * @return nothing
     */
    void fillarrayOpen0Open1(double* array, const unsigned int sz) {
      FillArrayImpl(array,sz,ConvertOpen0Open1);
    }

#ifdef HAVE_SSE2
    /**
     * @brief initiate the constants related to SSE2 operation
     *
     * The global variables for SSE2 operation are initiated. A flag
     * is set to disable further operations.
     *
     * @return nothing
     */
    void InitConst() {
      static bool first=true;
      if(!first)  return;
      // Endian?
      dSFMT_SSE2_ParamMask=_mm_set_epi32(Msk32_3,Msk32_4,Msk32_1,Msk32_2);
      dSFMT_SSE2_IntOne=_mm_set_epi32(0,1,0,1);
      dSFMT_SSE2_DoubleTwo=_mm_set_pd(2.0,2.0);
      dSFMT_SSE2_DoubleMOne=_mm_set_pd(-1.0,-1.0);
      first=false;
    }
    /**
     * @brief the complex operation related to a series of variables (SSE2 Version)
     *
     * This is complex bit operations for a series of variables using
     * SSE2 commands. This is core part of generator.
     *
     * @param a,b [in] two constant variables
     * @param r,u [in,out] two variables as input and containing output
     * @return nothing
     */
    void DoRecursion(const UniqueParameter128b& a,
                     const UniqueParameter128b& b,
                     UniqueParameter128b& r, UniqueParameter128b& u) {
      __m128i v,w,x,y,z,mask,bs;
      mask=_mm_loadu_si128(&dSFMT_SSE2_ParamMask);
      x=_mm_loadu_si128(&(a.si));
      bs=_mm_loadu_si128(&(b.si));
      z=_mm_slli_epi64(x,SL1);
      y=_mm_shuffle_epi32(u.si,SSE2_Shuff);
      z=_mm_xor_si128(z,bs);
      y=_mm_xor_si128(y,z);
      v=_mm_srli_epi64(y,SR);
      w=_mm_and_si128(y,dSFMT_SSE2_ParamMask);
      v=_mm_xor_si128(v,x);
      v=_mm_xor_si128(v,w);
      _mm_storeu_si128(&(r.si),v);
      _mm_storeu_si128(&(u.si),y);
    }
#else
    /**
     * @brief the complex operation related to a series of parameters
     *
     * This is complex bit operations for a series of variables.
     * This is core part of generator.
     *
     * @param a,b [in] two constant variables
     * @param r,u [in,out] two variables as input and containing output
     * @return nothing
     */
    void DoRecursion(const UniqueParameter128b& a,
                     const UniqueParameter128b& b,
                     UniqueParameter128b& r, UniqueParameter128b& u) {
      unsigned long long int t0,t1,L0,L1;
      t0=a.ull[0];
      t1=a.ull[1];
      L0=u.ull[0];
      L1=u.ull[1];
      u.ull[0]=(t0<<SL1)^(L1>>32)^(L1<<32)^b.ull[0];
      u.ull[1]=(t1<<SL1)^(L0>>32)^(L0<<32)^b.ull[1];
      r.ull[0]=(u.ull[0]>>SR)^(u.ull[0]&Msk1)^t0;
      r.ull[1]=(u.ull[1]>>SR)^(u.ull[1]&Msk1)^t1;
    }
#endif

    /**
     * @brief basic implementation to generate array of random numbers
     *
     * It uses DoRecursion operation to generate and to operate
     * the array of random numbers.
     *
     * @param array [in,out] the array to be operated. It also stores
     *                       the numbers to output
     * @param size [in] the number of elements in array
     * @param cvfunc [in] the pointer of convert function
     */
    void GenRandArrayImpl(UniqueParameter128b* array, const unsigned int size,
                          const ConvertFuncType& cvfunc) {
      unsigned int i,j;
      UniqueParameter128b lung;
      lung=status[N];
      DoRecursion(status[0],status[Pos1],array[0],lung);
      for(i=0;i<N-Pos1;++i)
        DoRecursion(status[i],status[i+Pos1],array[i],lung);
      for(;i<N;++i)
        DoRecursion(status[i],array[i+Pos1-N],array[i],lung);
      for(;i+N<size;++i) {
        DoRecursion(array[i-N],array[i+Pos1-N],array[i],lung);
        cvfunc(array[i-N]);
      }
      for(j=0;j+size<N+N;++j) status[j]=array[j+size-N];
      for(;i<size;++i,++j) {
        DoRecursion(array[i-N],array[i+Pos1-N],array[i],lung);
        status[j]=array[i];
        cvfunc(array[i-N]);
      }
      for(i=size-N;i<size;++i)  cvfunc(array[i]);
      status[N]=lung;
    }

    /**
     * @brief the function-1 for initiation
     *
     * This function operates the input number, and acts as the
     * transformation-2 to another number.
     *
     * @param x [in] the \c unsigned \c int
     * @return the result after this operation
     */
    unsigned int initfunc1(const unsigned int x) {
      return (x^(x>>27))*1664525UL;
    }

    /**
     * @brief the function-2 for initiation
     *
     * This function operates the input number, and acts as the
     * transformation-2 to another number.
     *
     * @param x [in] the \c unsigned \c int
     * @return the result after this operation
     */
    unsigned int initfunc2(const unsigned int x) {
      return (x^(x>>27))*1566083941UL;
    }

    /**
     * @brief mask internal storage
     *
     * The internal storage is masked with certain masks. It is a basic
     * operation for initiation.
     *
     * @return nothing
     */
    void initmask() {
      unsigned long long int *pSFMT;
      pSFMT=&(status[0].ull[0]);
      for(unsigned int i=0;i<N+N;++i) pSFMT[i]=(pSFMT[i]&LowMask)|HighConst;
    }

    /**
     * @brief modification for period certification
     *
     * Based on the certain elements, the period for generator is controlled.
     *
     * @return nothing
     * @note the actual meaning for this function is not clean.
     */
    void PeriodCertification() {
      unsigned long long int tmp[2], inner;
      tmp[0]=status[N].ull[0]^Fix1;
      tmp[1]=status[N].ull[1]^Fix2;
      inner=tmp[0]&pcv[0];
      inner^=tmp[1]&pcv[1];
      for(unsigned int i=32;i>0;i>>=1)   inner^=inner>>i;
      inner&=1;
      if(inner==1)  return;
      status[N].ull[1]^=1;
      return;
    }

    /**
     * @brief generate all the numbers in internal storage
     *
     * The internal storage is filled withrandom numbers for further
     * usage.
     *
     * @return nothing
     */
    void GenRandAll() {
      unsigned int i;
      UniqueParameter128b lung;
      DoRecursion(status[0],status[Pos1],status[0],lung);
      for(i=1;i<N-Pos1;++i)
        DoRecursion(status[i],status[i+Pos1],status[i],lung);
      for(;i<N;++i) DoRecursion(status[i],status[i+Pos1-N],status[i],lung);
      status[N]=lung;
    }

    /**
     * @brief the implementation for the operation to fill an array
     *
     * it is implemented with GenRandArrayImpl operation. It is required
     * that the size of double in array is larger than N64 and should be
     * even (to match the requirement of UniqueParameter128b type.
     *
     * @param array [in,out] the array to be filled with
     * @param size [in] the number of \c double elements in array
     * @param cvfunc [in] the pointer to convert function
     * @return nothing
     */
    void FillArrayImpl(double *array, unsigned int size,
                       const ConvertFuncType& cvfunc) {
      assert((size&1)==0);
      assert(size>=N64);
      GenRandArrayImpl(reinterpret_cast<UniqueParameter128b*>(array),size>>1,
                       cvfunc);
    }

  };

  /**
   * @brief the exponent for dSFMT generator
   *
   * LoopFac is the template \c int to define the generator.
   *
   * This exponent equals to the template parameter LoopFac.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::MExp=LoopFac;
  /**
   * @brief the size of internal storage in dSFMT generator
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::N=((dSFMT<LoopFac>::MExp-128)/104+1);
  /**
   * @brief the number of elements for status
   *
   * LoopFac is the template \c int to define the generator.
   */ 
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::NStatus=dSFMT<LoopFac>::N+1;
  /**
   * @brief the number of 32-bit elements in status
   *
   * LoopFac is the template \c int to define the generator.
   *
   * Typical parameter type in this kind of generator is UniqueParameter128b,
   * which is 4 times of 32-bit data.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::NStatusU32=dSFMT<LoopFac>::NStatus*4;
  /**
   * @brief the number of bytes in status
   *
   * LoopFac is the template \c int to define the generator.
   *
   * Since parameter type in this generator is UniqueParameter128b, the
   * number of bytes is 16 times of bytes.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::NStatusByte=dSFMT<LoopFac>::NStatus*16;
  /** @brief lag factor for this generator
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Lag=
    (dSFMT<LoopFac>::NStatusU32>=623?11:
    (dSFMT<LoopFac>::NStatusU32>68?7:
    (dSFMT<LoopFac>::NStatusU32>39?5:3)));
  /**
   * @brief the mid-number in status
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Mid=
    (dSFMT<LoopFac>::NStatusU32-dSFMT<LoopFac>::Lag)/2;
  /**
   * @brief the temporary summation of lag and mid-number
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::LagMid=
    dSFMT<LoopFac>::Lag+dSFMT<LoopFac>::Mid;
  /**
   * @brief the number of 32-bit elements in storage
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::N32=dSFMT<LoopFac>::N*4;
  /**
   * @brief the number of 64-bit elements in storage
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::N64=dSFMT<LoopFac>::N*2;
  /**
   * @brief the mask for lower bits
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::LowMask=0x000FFFFFFFFFFFFFULL;
  /**
   * @brief the mask for upper bits
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::HighConst=0x3FF0000000000000ULL;
  /**
   * @brief a factor named as SR
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::SR=12;
#ifdef HAVE_SSE2
  /**
   * @brief the factor related to shuffle with SSE2 operations
   *
   * LoopFac is the template \c int to define the generator.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::SSE2_Shuff=0x1BU;
#endif 
  /**
   * @brief the first 32-bit mask
   *
   * LoopFac is the template \c int to define the generator.
   *
   * It takes the upper 32-bit of the mask Msk1.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_1=
    (dSFMT<LoopFac>::Msk1>>32)&0xFFFFFFFFUL;
  /**
   * @brief the second 32-bit mask
   *
   * LoopFac is the template \c int to define the generator.
   *
   * It takes the lower 32-bit of the mask Msk1.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_2=dSFMT<LoopFac>::Msk1&0xFFFFFFFFUL;
  /**
   * @brief the third 32-bit mask
   *
   * LoopFac is the template \c int to define the generator.
   *
   * It takes the upper 32-bit of the mask Msk2.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_3=
    (dSFMT<LoopFac>::Msk2>>32)&0xFFFFFFFFUL;
  /**
   * @brief the fourth 32-bit mask
   *
   * LoopFac is the template \c int to define the generator.
   *
   * It takes the lower 32-bit of the mask Msk2.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_4=dSFMT<LoopFac>::Msk1&0xFFFFFFFFUL;
  /**
   * @brief an array of two factors
   *
   * LoopFac is the template \c int to define the generator.
   *
   * the array may ease the access these elements with their indices easily.
   */
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::pcv[2]={dSFMT<LoopFac>::Pcv1,
                                                       dSFMT<LoopFac>::Pcv2};
  /**
   * @brief the Pos1 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * it is defined as zero for generic cases
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Pos1=0U;
  /**
   * @brief the SL1 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * it is defined as zero for generic cases
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::SL1=0U;
  /**
   * @brief the \c unsigned \c long \c long Msk1 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * it is defined as zero for generic cases
   */
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Msk1=0ULL;
  /**
   * @brief the \c unsigned \c long \c long Msk2 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * it is defined as zero for generic cases
   */
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Msk2=0ULL;
  /**
   * @brief the \c unsigned \c long \c long Fix1 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * it is defined as zero for generic cases
   */
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Fix1=0ULL;
  /**
   * @brief the \c unsigned \c long \c long Fix2 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * it is defined as zero for generic cases
   */
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Fix2=0ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv1 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * it is defined as zero for generic cases
   */
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Pcv1=0ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv2 factor
   *
   * LoopFac is the template \c int to define the generator.
   *
   * it is defined as zero for generic cases
   */
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Pcv2=0ULL;
  /**
   * @brief the availability flag
   *
   * LoopFac is the template \c int to define the generator.
   *
   * it is defined as zero for generic cases, which indicates that the
   * generator with generic factor is not availability.
   */
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::IsFacAvailable=0;

  /**
   * @brief the Pos1 factor for LoopFac of 521
   *
   * This is a specification for the case with LoopFac of 521
   */
  template <> const unsigned int dSFMT<521>::Pos1=3;
  /**
   * @brief the SL1 factor for LoopFac of 521
   *
   * This is a specification for the case with LoopFac of 521
   */
  template <> const unsigned int dSFMT<521>::SL1=25;
  /**
   * @brief the \c unsigned \c long \c long Msk1 factor for LoopFac of 521
   *
   * This is a specification for the case with LoopFac of 521
   */
  template <>
  const unsigned long long int dSFMT<521>::Msk1=0x000FBFEFFF77EFFFULL;
  /**
   * @brief the \c unsigned \c long \c long Msk2 factor for LoopFac of 521
   *
   * This is a specification for the case with LoopFac of 521
   */
  template <>
  const unsigned long long int dSFMT<521>::Msk2=0x000FFEEBFBDFBFDFULL;
  /**
   * @brief the \c unsigned \c long \c long Fix1 factor for LoopFac of 521
   *
   * This is a specification for the case with LoopFac of 521
   */
  template <>
  const unsigned long long int dSFMT<521>::Fix1=0xCFB393D661638469ULL;
  /**
   * @brief the \c unsigned \c long \c long Fix2 factor for LoopFac of 521
   *
   * This is a specification for the case with LoopFac of 521
   */
  template <>
  const unsigned long long int dSFMT<521>::Fix2=0xC166867883AE2ADBULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv1 factor for LoopFac of 521
   *
   * This is a specification for the case with LoopFac of 521
   */
  template <>
  const unsigned long long int dSFMT<521>::Pcv1=0xCCAA588000000000ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv2 factor for LoopFac of 521
   *
   * This is a specification for the case with LoopFac of 521
   */
  template <>
  const unsigned long long int dSFMT<521>::Pcv2=0x0000000000000001ULL;
  /**
   * @brief the availability flag for LoopFac of 521
   *
   * This is a specification for the case with LoopFac of 521
   */
  template <> const unsigned int dSFMT<521>::IsFacAvailable=1;

  /**
   * @brief the Pos1 factor for LoopFac of 1279
   *
   * This is a specification for the case with LoopFac of 1279
   */
  template <> const unsigned int dSFMT<1279>::Pos1=9;
  /**
   * @brief the SL1 factor for LoopFac of 1279
   *
   * This is a specification for the case with LoopFac of 1279
   */
  template <> const unsigned int dSFMT<1279>::SL1=19;
  /**
   * @brief the \c unsigned \c long \c long Msk1 factor for LoopFac of 1279
   *
   * This is a specification for the case with LoopFac of 1279
   */
  template <>
  const unsigned long long int dSFMT<1279>::Msk1=0x000EFFF7FFDDFFEEULL;
  /**
   * @brief the \c unsigned \c long \c long Msk2 factor for LoopFac of 1279
   *
   * This is a specification for the case with LoopFac of 1279
   */
  template <>
  const unsigned long long int dSFMT<1279>::Msk2=0x000FBFFFFFF77FFFULL;
  /**
   * @brief the \c unsigned \c long \c long Fix1 factor for LoopFac of 1279
   *
   * This is a specification for the case with LoopFac of 1279
   */
  template <>
  const unsigned long long int dSFMT<1279>::Fix1=0xB66627623D1A31BEULL;
  /**
   * @brief the \c unsigned \c long \c long Fix2 factor for LoopFac of 1279
   *
   * This is a specification for the case with LoopFac of 1279
   */
  template <>
  const unsigned long long int dSFMT<1279>::Fix2=0x04B6C51147B6109BULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv1 factor for LoopFac of 1279
   *
   * This is a specification for the case with LoopFac of 1279
   */
  template <>
  const unsigned long long int dSFMT<1279>::Pcv1=0x7049F2DA382A6AEBULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv2 factor for LoopFac of 1279
   *
   * This is a specification for the case with LoopFac of 1279
   */
  template <>
  const unsigned long long int dSFMT<1279>::Pcv2=0xDE4CA84A40000001ULL;
  /**
   * @brief the availability flag for LoopFac of 1279
   *
   * This is a specification for the case with LoopFac of 1279
   */
  template <> const unsigned int dSFMT<1279>::IsFacAvailable=1;

  /**
   * @brief the Pos1 factor for LoopFac of 2203
   *
   * This is a specification for the case with LoopFac of 2203
   */
  template <> const unsigned int dSFMT<2203>::Pos1=7;
  /**
   * @brief the SL1 factor for LoopFac of 2203
   *
   * This is a specification for the case with LoopFac of 2203
   */
  template <> const unsigned int dSFMT<2203>::SL1=19;
  /**
   * @brief the \c unsigned \c long \c long Msk1 factor for LoopFac of 2203
   *
   * This is a specification for the case with LoopFac of 2203
   */
  template <>
  const unsigned long long int dSFMT<2203>::Msk1=0x000FDFFFF5EDBFFFULL;
  /**
   * @brief the \c unsigned \c long \c long Msk2 factor for LoopFac of 2203
   *
   * This is a specification for the case with LoopFac of 2203
   */
  template <>
  const unsigned long long int dSFMT<2203>::Msk2=0x000F77FFFFFFFBFEULL;
  /**
   * @brief the \c unsigned \c long \c long Fix1 factor for LoopFac of 2203
   *
   * This is a specification for the case with LoopFac of 2203
   */
  template <>
  const unsigned long long int dSFMT<2203>::Fix1=0xB14E907A39338485ULL;
  /**
   * @brief the \c unsigned \c long \c long Fix2 factor for LoopFac of 2203
   *
   * This is a specification for the case with LoopFac of 2203
   */
  template <>
  const unsigned long long int dSFMT<2203>::Fix2=0xF98F0735C637EF90ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv1 factor for LoopFac of 2203
   *
   * This is a specification for the case with LoopFac of 2203 
   */
  template <>
  const unsigned long long int dSFMT<2203>::Pcv1=0x8000000000000000ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv2 factor for LoopFac of 2203
   *
   * This is a specification for the case with LoopFac of 2203 
   */
  template <>
  const unsigned long long int dSFMT<2203>::Pcv2=0x0000000000000001ULL;
  /**
   * @brief the availability flag for LoopFac of 2203
   *
   * This is a specification for the case with LoopFac of 2203
   */
  template <> const unsigned int dSFMT<2203>::IsFacAvailable=1;

  /**
   * @brief the Pos1 factor for LoopFac of 4253
   *
   * This is a specification for the case with LoopFac of 4253
   */
  template <> const unsigned int dSFMT<4253>::Pos1=19;
  /**
   * @brief the SL1 factor for LoopFac of 4253
   *
   * This is a specification for the case with LoopFac of 4253
   */
  template <> const unsigned int dSFMT<4253>::SL1=19;
  /**
   * @brief the \c unsigned \c long \c long Msk1 factor for LoopFac of 4253
   *
   * This is a specification for the case with LoopFac of 4253
   */
  template <>
  const unsigned long long int dSFMT<4253>::Msk1=0x0007B7FFFEF5FEFFULL;
  /**
   * @brief the \c unsigned \c long \c long Msk2 factor for LoopFac of 4253
   *
   * This is a specification for the case with LoopFac of 4253
   */
  template <>
  const unsigned long long int dSFMT<4253>::Msk2=0x000FFDFFEFFEFBFCULL;
  /**
   * @brief the \c unsigned \c long \c long Fix1 factor for LoopFac of 4253
   *
   * This is a specification for the case with LoopFac of 4253
   */
  template <>
  const unsigned long long int dSFMT<4253>::Fix1=0x80901B5FD7A11C65ULL;
  /**
   * @brief the \c unsigned \c long \c long Fix2 factor for LoopFac of 4253
   *
   * This is a specification for the case with LoopFac of 4253
   */
  template <>
  const unsigned long long int dSFMT<4253>::Fix2=0x5A63FF0E7CB0BA74ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv1 factor for LoopFac of 4253
   *
   * This is a specification for the case with LoopFac of 4253
   */
  template <>
  const unsigned long long int dSFMT<4253>::Pcv1=0x1AD277BE12000000ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv2 factor for LoopFac of 4253
   *
   * This is a specification for the case with LoopFac of 4253
   */
  template <>
  const unsigned long long int dSFMT<4253>::Pcv2=0x0000000000000001ULL;
  /**
   * @brief the availability flag for LoopFac of 4253
   *
   * This is a specification for the case with LoopFac of 4253
   */
  template <> const unsigned int dSFMT<4253>::IsFacAvailable=1;

  /**
   * @brief the Pos1 factor for LoopFac of 11213
   *
   * This is a specification for the case with LoopFac of 11213
   */
  template <> const unsigned int dSFMT<11213>::Pos1=37;
  /**
   * @brief the SL1 factor for LoopFac of 11213
   *
   * This is a specification for the case with LoopFac of 11213
   */
  template <> const unsigned int dSFMT<11213>::SL1=19;
  /**
   * @brief the \c unsigned \c long \c long Msk1 factor for LoopFac of 11213
   *
   * This is a specification for the case with LoopFac of 11213
   */
  template <>
  const unsigned long long int dSFMT<11213>::Msk1=0x000FFFFFFDF7FFFDULL;
  /**
   * @brief the \c unsigned \c long \c long Msk2 factor for LoopFac of 11213
   *
   * This is a specification for the case with LoopFac of 11213
   */
  template <>
  const unsigned long long int dSFMT<11213>::Msk2=0x000DFFFFFFF6BFFFULL;
  /**
   * @brief the \c unsigned \c long \c long Fix1 factor for LoopFac of 11213
   *
   * This is a specification for the case with LoopFac of 11213
   */
  template <>
  const unsigned long long int dSFMT<11213>::Fix1=0xD0EF7B7C75B06793ULL;
  /**
   * @brief the \c unsigned \c long \c long Fix2 factor for LoopFac of 11213
   *
   * This is a specification for the case with LoopFac of 11213
   */
  template <>
  const unsigned long long int dSFMT<11213>::Fix2=0x9C50FF4CAAE0A641ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv1 factor for LoopFac of 11213
   *
   * This is a specification for the case with LoopFac of 11213
   */
  template <>
  const unsigned long long int dSFMT<11213>::Pcv1=0x8234C51207C80000ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv2 factor for LoopFac of 11213
   *
   * This is a specification for the case with LoopFac of 11213
   */
  template <>
  const unsigned long long int dSFMT<11213>::Pcv2=0x0000000000000001ULL;
  /**
   * @brief the availability flag for LoopFac of 11213
   *
   * This is a specification for the case with LoopFac of 11213
   */
  template <> const unsigned int dSFMT<11213>::IsFacAvailable=1;

  /**
   * @brief the Pos1 factor for LoopFac of 19937
   *
   * This is a specification for the case with LoopFac of 19937
   */
  template <> const unsigned int dSFMT<19937>::Pos1=117;
  /**
   * @brief the SL1 factor for LoopFac of 19937
   *
   * This is a specification for the case with LoopFac of 19937
   */
  template <> const unsigned int dSFMT<19937>::SL1=19;
  /**
   * @brief the \c unsigned \c long \c long Msk1 factor for LoopFac of 19937
   *
   * This is a specification for the case with LoopFac of 19937
   */
  template <>
  const unsigned long long int dSFMT<19937>::Msk1=0x000FFAFFFFFFFB3FULL;
  /**
   * @brief the \c unsigned \c long \c long Msk2 factor for LoopFac of 19937
   *
   * This is a specification for the case with LoopFac of 19937
   */
  template <>
  const unsigned long long int dSFMT<19937>::Msk2=0x000FFDFFFC90FFFDULL;
  /**
   * @brief the \c unsigned \c long \c long Fix1 factor for LoopFac of 19937
   *
   * This is a specification for the case with LoopFac of 19937
   */
  template <>
  const unsigned long long int dSFMT<19937>::Fix1=0x90014964B32F4329ULL;
  /**
   * @brief the \c unsigned \c long \c long Fix2 factor for LoopFac of 19937
   *
   * This is a specification for the case with LoopFac of 19937
   */
  template <>
  const unsigned long long int dSFMT<19937>::Fix2=0x3B8D12AC548A7C7AULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv1 factor for LoopFac of 19937
   *
   * This is a specification for the case with LoopFac of 19937
   */
  template <>
  const unsigned long long int dSFMT<19937>::Pcv1=0x3D84E1AC0DC82880ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv2 factor for LoopFac of 19937
   *
   * This is a specification for the case with LoopFac of 19937
   */
  template <>
  const unsigned long long int dSFMT<19937>::Pcv2=0x0000000000000001ULL;
  /**
   * @brief the availability flag for LoopFac of 19937
   *
   * This is a specification for the case with LoopFac of 19937
   */
  template <> const unsigned int dSFMT<19937>::IsFacAvailable=1;

  /**
   * @brief the Pos1 factor for LoopFac of 44497
   *
   * This is a specification for the case with LoopFac of 44497
   */
  template <> const unsigned int dSFMT<44497>::Pos1=304;
  /**
   * @brief the SL1 factor for LoopFac of 44497
   *
   * This is a specification for the case with LoopFac of 44497
   */
  template <> const unsigned int dSFMT<44497>::SL1=19;
  /**
   * @brief the \c unsigned \c long \c long Msk1 factor for LoopFac of 44497
   *
   * This is a specification for the case with LoopFac of 44497
   */
  template <>
  const unsigned long long int dSFMT<44497>::Msk1=0x000FF6DFFFFFFFEFULL;
  /**
   * @brief the \c unsigned \c long \c long Msk2 factor for LoopFac of 44497
   *
   * This is a specification for the case with LoopFac of 44497
   */
  template <>
  const unsigned long long int dSFMT<44497>::Msk2=0x0007FFDDDEEFFF6FULL;
  /**
   * @brief the \c unsigned \c long \c long Fix1 factor for LoopFac of 44497
   *
   * This is a specification for the case with LoopFac of 44497
   */
  template <>
  const unsigned long long int dSFMT<44497>::Fix1=0x75D910F235F6E10EULL;
  /**
   * @brief the \c unsigned \c long \c long Fix2 factor for LoopFac of 44497
   *
   * This is a specification for the case with LoopFac of 44497
   */
  template <>
  const unsigned long long int dSFMT<44497>::Fix2=0x7B32158AEDC8E969ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv1 factor for LoopFac of 44497
   *
   * This is a specification for the case with LoopFac of 44497
   */
  template <>
  const unsigned long long int dSFMT<44497>::Pcv1=0x4C3356B2A0000000ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv2 factor for LoopFac of 44497
   *
   * This is a specification for the case with LoopFac of 44497
   */
  template <>
  const unsigned long long int dSFMT<44497>::Pcv2=0x0000000000000001ULL;
  /**
   * @brief the availability flag for LoopFac of 44497
   *
   * This is a specification for the case with LoopFac of 44497
   */
  template <> const unsigned int dSFMT<44497>::IsFacAvailable=1;

  /**
   * @brief the Pos1 factor for LoopFac of 86243
   *
   * This is a specification for the case with LoopFac of 86243
   */
  template <> const unsigned int dSFMT<86243>::Pos1=231;
  /**
   * @brief the SL1 factor for LoopFac of 86243
   *
   * This is a specification for the case with LoopFac of 86243
   */
  template <> const unsigned int dSFMT<86243>::SL1=13;
  /**
   * @brief the \c unsigned \c long \c long Msk1 factor for LoopFac of 86243
   *
   * This is a specification for the case with LoopFac of 86243
   */
  template <>
  const unsigned long long int dSFMT<86243>::Msk1=0x000FFEDFF6FFFFDFULL;
  /**
   * @brief the \c unsigned \c long \c long Msk2 factor for LoopFac of 86243
   *
   * This is a specification for the case with LoopFac of 86243
   */
  template <>
  const unsigned long long int dSFMT<86243>::Msk2=0x000FFFF7FDFFFF7EULL;
  /**
   * @brief the \c unsigned \c long \c long Fix1 factor for LoopFac of 86243
   *
   * This is a specification for the case with LoopFac of 86243
   */
  template <>
  const unsigned long long int dSFMT<86243>::Fix1=0x1D553E776B975E68ULL;
  /**
   * @brief the \c unsigned \c long \c long Fix2 factor for LoopFac of 86243
   *
   * This is a specification for the case with LoopFac of 86243
   */
  template <>
  const unsigned long long int dSFMT<86243>::Fix2=0x648FAADF1416BF91ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv1 factor for LoopFac of 86243
   *
   * This is a specification for the case with LoopFac of 86243
   */
  template <>
  const unsigned long long int dSFMT<86243>::Pcv1=0x5F2CD03E2758A373ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv2 factor for LoopFac of 86243
   *
   * This is a specification for the case with LoopFac of 86243
   */
  template <>
  const unsigned long long int dSFMT<86243>::Pcv2=0xC0B7EB8410000001ULL;
  /*
   * @brief the availability flag for LoopFac of 86243
   *
   * This is a specification for the case with LoopFac of 86243
   */
  template <> const unsigned int dSFMT<86243>::IsFacAvailable=1;

  /**
   * @brief the Pos1 factor for LoopFac of 132049
   *
   * This is a specification for the case with LoopFac of 132049
   */
  template <> const unsigned int dSFMT<132049>::Pos1=371;
  /**
   * @brief the SL1 factor for LoopFac of 132049
   *
   * This is a specification for the case with LoopFac of 132049
   */
  template <> const unsigned int dSFMT<132049>::SL1=23;
  /**
   * @brief the \c unsigned \c long \c long Msk1 factor for LoopFac of 132049
   *
   * This is a specification for the case with LoopFac of 132049
   */
  template <>
  const unsigned long long int dSFMT<132049>::Msk1=0x000FB9F4EFF4BF77ULL;
  /**
   * @brief the \c unsigned \c long \c long Msk2 factor for LoopFac of 132049
   *
   * This is a specification for the case with LoopFac of 132049
   */
  template <>
  const unsigned long long int dSFMT<132049>::Msk2=0x000FFFFFBFEFFF37ULL;
  /**
   * @brief the \c unsigned \c long \c long Fix1 factor for LoopFac of 132049
   *
   * This is a specification for the case with LoopFac of 132049
   */
  template <>
  const unsigned long long int dSFMT<132049>::Fix1=0x4CE24C0E4E234F3BULL;
  /**
   * @brief the \c unsigned \c long \c long Fix2 factor for LoopFac of 132049
   *
   * This is a specification for the case with LoopFac of 132049
   */
  template <>
  const unsigned long long int dSFMT<132049>::Fix2=0x62612409B5665C2DULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv1 factor for LoopFac of 132049
   *
   * This is a specification for the case with LoopFac of 132049
   */
  template <>
  const unsigned long long int dSFMT<132049>::Pcv1=0x181232889145D000ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv2 factor for LoopFac of 132049
   *
   * This is a specification for the case with LoopFac of 132049
   */
  template <>
  const unsigned long long int dSFMT<132049>::Pcv2=0x0000000000000001ULL;
  /**
   * @brief the availability flag for LoopFac of 132049
   *
   * This is a specification for the case with LoopFac of 132049
   */
  template <> const unsigned int dSFMT<132049>::IsFacAvailable=1;

  /**
   * @brief the Pos1 factor for LoopFac of 216091
   *
   * This is a specification for the case with LoopFac of 216091
   */
  template <> const unsigned int dSFMT<216091>::Pos1=1890;
  /**
   * @brief the SL1 factor for LoopFac of 216091
   *
   * This is a specification for the case with LoopFac of 216091
   */
  template <> const unsigned int dSFMT<216091>::SL1=23;
  /**
   * @brief the \c unsigned \c long \c long Msk1 factor for LoopFac of 216091
   *
   * This is a specification for the case with LoopFac of 216091
   */
  template <>
  const unsigned long long int dSFMT<216091>::Msk1=0x000BF7DF7FEFCFFFULL;
  /**
   * @brief the \c unsigned \c long \c long Msk2 factor for LoopFac of 216091
   *
   * This is a specification for the case with LoopFac of 216091
   */
  template <>
  const unsigned long long int dSFMT<216091>::Msk2=0x000E7FFFFEF737FFULL;
  /**
   * @brief the \c unsigned \c long \c long Fix1 factor for LoopFac of 216091
   *
   * This is a specification for the case with LoopFac of 216091
   */
  template <>
  const unsigned long long int dSFMT<216091>::Fix1=0xD7F95A04764C27D7ULL;
  /**
   * @brief the \c unsigned \c long \c long Fix2 factor for LoopFac of 216091
   *
   * This is a specification for the case with LoopFac of 216091
   */
  template <>
  const unsigned long long int dSFMT<216091>::Fix2=0x6A483861810BEBC2ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv1 factor for LoopFac of 216091
   *
   * This is a specification for the case with LoopFac of 216091
   */
  template <>
  const unsigned long long int dSFMT<216091>::Pcv1=0x3AF0A8F3D5600000ULL;
  /**
   * @brief the \c unsigned \c long \c long Pcv2 factor for LoopFac of 216091
   *
   * This is a specification for the case with LoopFac of 216091
   */
  template <>
  const unsigned long long int dSFMT<216091>::Pcv2=0x0000000000000001ULL;
  /**
   * @brief the availability flag for LoopFac of 216091
   *
   * This is a specification for the case with LoopFac of 216091
   */
  template <> const unsigned int dSFMT<216091>::IsFacAvailable=1;

  /**
   * @brief check the availability of dSFMT generator
   *
   * It is implemented by checking the availability of status in generator.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param dg [in] the dSFMT generator
   * @return the flag indicating if the generator is available
   */
  template <unsigned int LoopFac>
  bool IsAvailable(const dSFMT<LoopFac>& dg) { return IsAvailable(dg.status); }

  /**
   * @brief check if the dSFMT generator is a random generator
   *
   * It always gives out true flag since dSFMT generator is random generator.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param dg [in] the dSFMT generator
   * @return the true flag indicating that dSFMT generator is a random generator
   */
  template <unsigned int LoopFac>
  bool IsRandomGenerator(const dSFMT<LoopFac>& dg) { return true; }

  /**
   * @brief assign dSFMT generator from another
   *
   * Just copy the content of status and index. The concerned generators
   * are checked for their availability before this operation.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param dest [out] the generator to accept the input
   * @param src [in] the generator storing the input
   * @return nothing
   */
  template <unsigned int LoopFac>
  void assign(dSFMT<LoopFac>& dest, const dSFMT<LoopFac>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(dest.status.src.status,dSFMT<LoopFac>::NStatus);
    *dest.idx=*src.idx;
  }

  /**
   * @brief release a dSFMT generator
   *
   * The internal storages of status, index and output are freed in this
   * procedure. The state of generator is updated as Unused.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param dg [in,out] the generator to be released
   * @return nothing.
   */
  template <unsigned int LoopFac>
  void release(dSFMT<LoopFac>& dg) {
    if(dg.state==Allocated) {
      safe_delete_array(dg.status);
      safe_delete(dg.idx);
      safe_delete(dg.output);
    } else {
      dg.status=NULL;
      dg.idx=NULL;
      dg.output=NULL;
    }
    dg.state=Unused;
  }

  /**
   * @brief allocate dSFMT generator
   *
   * The internal storages of status, index, and output are allocated.
   * The state is updated as Allocated. The generator is then initiated
   * with default seed 5489. This generator is released before this operation.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param dg [in,out] the generator to be allocated
   * @return nothing
   */
  template <unsigned int LoopFac>
  void allocate(dSFMT<LoopFac>& dg) {
    release(dg);
    dg.status=new UniqueParameter128b[dSFMT<LoopFac>::NStatus];
    dg.idx=new unsigned int;
    dg.output=new UniqueParameter128b;
    dg.state=Allocated;
    dg.Init(5489UL);
  }

  /**
   * @brief refer to another dSFMT generator
   *
   * Just copy the pointers of the status, index, and output of source
   * generator to destination generator. The source generator is checked
   * for its availability for this operation. The destination generator
   * is released before the refer-to operation.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param dest [in,out] the generator to accept the input
   * @param src [in] the generator storing the input
   * @return nothing
   */
  template <unsigned int LoopFac>
  void refer(dSFMT<LoopFac>& dest, const dSFMT<LoopFac>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.status=src.status;
    dest.idx=src.idx;
    dest.output=src.output;
    dest.state=Reference;
  }

  /**
   * @brief initiate dSFMT generator with a \c unsigned \c int seed
   *
   * It is implemented by filling the internal status with regular
   * algorithm. For the case with SSE2 enabled, the related constants
   * are also initiated. The generator is checked for availability
   * before this operation.
   *
   * @param dg [out] the generator to be initiated.
   * @param seed [in] the seed for generator
   * @return nothing
   */
  template <unsigned int LoopFac>
  void init(dSFMT<LoopFac>& dg, const unsigned int seed) {
    assert(IsAvailable(dg));
    unsigned int *pSFMT;
    pSFMT=&dg.status[0].u[0];
    pSFMT[0]=seed;
    unsigned int rmt;
    rmt=pSFMT[0];
    for(unsigned int i=1;i<dSFMT<LoopFac>::NStatusU32;++i) {
      rmt=1812433253UL*(rmt^(rmt>>30))+i;
      pSFMT[i]=rmt;
    }
    dg.initmask();
    dg.PeriodCertification();
    *(dg.idx)=dSFMT<LoopFac>::N64;
#ifdef HAVE_SSE2
    dg.InitConst();
#endif
  }

  /**
   * @brief initiate the dSFMT generator with an array of seeds
   *
   * it is implemented with complex operations for the elements in arrays
   * and the status in generator. The generator is checked for its
   * availability before this operation. For the case with SSE2 enabled,
   * the related constants are also initiated.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param dg [in,out] the generator to be initiated
   * @param key [in] the array containing seeds
   * @param len [in] the number of seeds
   * @param off [in] the offset of the first element in array key. It takes
   *                 the default value of uZero.
   * @param step [in] the step between elements in array key. It takes the
   *                  default value of uOne.
   * @return nothing
   */
  template <unsigned int LoopFac>
  void init(dSFMT<LoopFac>& dg,
            const unsigned int* key, const unsigned int len,
            const unsigned int off=uZero, const unsigned int step=uOne) {
    assert(IsAvailable(dg));
    unsigned int i,j,g,count,tmid,r, *pSFMT;
    pSFMT=&dg.status[0].u[0];
    memset(dg.status,0x8B,dSFMT<LoopFac>::NStatusByte);
    count=(len+1>dSFMT<LoopFac>::NStatusU32?len+1:dSFMT<LoopFac>::NStatusU32);
    tmid=dSFMT<LoopFac>::Mid%dSFMT<LoopFac>::NStatusU32;
    r=dg.initfunc1(pSFMT[0]^pSFMT[tmid]^pSFMT[dSFMT<LoopFac>::NStatusU32-1]);
    pSFMT[tmid]+=r;
    r+=len;
    pSFMT[dSFMT<LoopFac>::LagMid%dSFMT<LoopFac>::NStatusU32]+=r;
    pSFMT[0]=r;
    --count;
    for(i=0,j=0,g=off;j<len;++j,g+=step) {
      tmid=(i+dSFMT<LoopFac>::Mid)%dSFMT<LoopFac>::NStatusU32;
      r=dg.initfunc1(pSFMT[i]^pSFMT[tmid]
          ^pSFMT[(i+dSFMT<LoopFac>::NStatusU32-1)%dSFMT<LoopFac>::NStatusU32]);
      pSFMT[tmid]+=r;
      r+=key[g]+i;
      pSFMT[(i+dSFMT<LoopFac>::LagMid)%dSFMT<LoopFac>::NStatusU32]+=r;
      pSFMT[i]=r;
      i=(i+1)%dSFMT<LoopFac>::NStatusU32;
    }
    for(;j<count;++j) {
      tmid=(i+dSFMT<LoopFac>::Mid)%dSFMT<LoopFac>::NStatusU32;
      r=dg.initfunc1(pSFMT[i]^pSFMT[tmid]
          ^pSFMT[(i+dSFMT<LoopFac>::NStatusU32-1)%dSFMT<LoopFac>::NStatusU32]);
      pSFMT[tmid]+=r;
      r+=i;
      pSFMT[(i+dSFMT<LoopFac>::LagMid)%dSFMT<LoopFac>::NStatusU32]+=r;
      pSFMT[i]=r;
      i=(i+1)%dSFMT<LoopFac>::NStatusU32;
    }
    for(j=0;j<dSFMT<LoopFac>::NStatusU32;++j) {
      tmid=(i+dSFMT<LoopFac>::Mid)%dSFMT<LoopFac>::NStatusU32;
      r=dg.initfunc2(pSFMT[i]+pSFMT[tmid]
          +pSFMT[(i+dSFMT<LoopFac>::NStatusU32-1)%dSFMT<LoopFac>::NStatusU32]);
      pSFMT[tmid]^=r;
      r-=i;
      pSFMT[(i+dSFMT<LoopFac>::LagMid)%dSFMT<LoopFac>::NStatusU32]^=r;
      pSFMT[i]=r;
      i=(i+1)%dSFMT<LoopFac>::NStatusU32;
    }
    dg.initmask();
    dg.PeriodCertification();
    *(dg.idx)=dSFMT<LoopFac>::N64;
#ifdef HAVE_SSE2
    dg.InitConst();
#endif
  }

  /**
   * @brief initiate dSFMT generator with a vector
   *
   * It is implemented with the operation to initiate generator with
   * an array.
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param dg [in,out] the generator to be initiated
   * @param key [in] the vector containing seeds
   * @return nothing
   */
  template <unsigned int LoopFac>
  void init(dSFMT<LoopFac>& dg, const Vector<unsigned int>& key) {
    init(dg,key(),key.size);
  }

  /**
   * @brief generate a random \c double value
   *
   * It generates a random number in the region [0,1).
   *
   * LoopFac is the template \c int to define the generator.
   *
   * @param dg [in,out] the dSFMT generator for this generation
   * @return the generated \c double number 
   */
  template <unsigned int LoopFac>
  const double& rand(dSFMT<LoopFac>& dg) { return dg.DoubleClose0Open1(); }

  /**
   * @brief generate a T-type number with dSFMT generator
   *
   * This gives the generic form. It is prohibited and pops up a message.
   *
   * T is the type of the output number
   *
   * @param dg [in,out] the dSFMT generator
   * @return the generated T-type number
   */
  template <typename T>
  const T& rand(dSFMT<521>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<1279>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<2203>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<4253>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<11213>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<19937>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<44497>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<86243>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<132049>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<216091>& dg) { myError("Default Form is prohibited"); }

  template <>
  const double& rand<double>(dSFMT<521>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<1279>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<2203>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<4253>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<11213>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<19937>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<44497>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<86243>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<132049>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<216091>& dg) { return rand(dg); }

  template <>
  const unsigned int& rand<unsigned int>(dSFMT<521>& dg){ return dg.UInt32(); }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<1279>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<2203>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<4253>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<11213>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<19937>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<44497>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<86243>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<132049>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<216091>& dg) {
    return dg.UInt32();
  }

  template <unsigned int LoopFac>
  void fillarray(dSFMT<LoopFac>& dg, double* array, const unsigned int size) {
    dg.fillarrayClose0Open1(array,size);
  }

  template <unsigned int LoopFac>
  ostream& operator<<(ostream& os, const dSFMT<LoopFac>& dg) {
    assert(IsAvailable(dg));
    os<<LoopFac<<"\t";
    for(unsigned int i=0;i<dSFMT<LoopFac>::NStatus;++i) os<<dg.status[i]<<"\t";
    os<<*(dg.idx);
    return os;
  }

  template <unsigned int LoopFac>
  istream& operator>>(istream& is, dSFMT<LoopFac>& dg) {
    assert(IsAvailable(dg));
    unsigned int expLoopFac;
    is>>expLoopFac;
    if(expLoopFac!=LoopFac) myError("Imcompatiable data for dSFMT generator");
    for(unsigned int i=0;i<dSFMT<LoopFac>::NStatus;++i) is>>dg.status[i];
    is>>*(dg.idx);
    return is;
  }

}

#endif
