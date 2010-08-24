
/**
 * @file random-generator-mt-standard.h
 * @brief the random generator with standard MT algorithm
 *
 * This file describes a random generator with uniform distribution
 * which is implemented with standard MT algorithm.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Random_Generator_MT_Standard_H_
#define _Random_Generator_MT_Standard_H_

#include "unique-parameter-128bit.h"
#include "vector.h"

namespace std {

  /**
   * @brief declaration of MT_Standard object
   */
  struct MT_Standard;

  /**
   * @brief declaration of assign operation for MT_Standard object from another
   */
  void assign(MT_Standard&,const MT_Standard&);
  /**
   * @brief declaration of release operation for MT_Standard
   */
  void release(MT_Standard&);
  /**
   * @brief declaration of init operation for MT_Standard from an \c int
   */
  void init(MT_Standard&, const unsigned int);
  /**
   * @brief declaration of init operation for MT_Standard from an array
   */
  void init(MT_Standard&, const unsigned int*, const unsigned int,
                          const unsigned int, const unsigned int);
  /**
   * @brief declaration of init operation for MT_Standard from a vector
   */
  void init(MT_Standard&, const Vector<unsigned int>&);

  /**
   * @brief the random generator using standard MT algorithm
   *
   * It is based on the MT algorithm. There are no accelerations with
   * SSE instructions. It is stable in various platform.
   */
  struct MT_Standard {

    static const unsigned int N;
    static const unsigned int M;
    static const unsigned int dNM;
    static const unsigned int Nm1;
    static const unsigned int Mm1;
    static const unsigned int MatrixA;
    static const unsigned int UppMask;
    static const unsigned int LowMask;
    static const unsigned int Mag01[2];
    static const unsigned int Mask32b;
    /**
     * @brief the array to store random numbers internally
     *
     * This buffer stores random numbers and enables the operations for
     * these numbers to re-shuffle them, so that the output numbers
     * are more random in statistical sense.
     */
    unsigned int *mt;
    /**
     * @brief pointer to the running number
     *
     * This is used as a temporary internal variable.
     */
    unsigned int *mti;
    /**
     * @brief output parameter
     *
     * This is a temporary internal parameter to avoid allocation
     * instance when output
     */
    UniqueParameter128b *output;
    /**
     * @brief storage state of the generator
     */
    unsigned int state;

    /**
     * @brief abbreviation for MT_Standard object
     */
    typedef MT_Standard Type;

    /**
     * @brief defualt initiator
     *
     * Just initiate the pointers with NULL and set the storage state as
     * Unused.
     */
    MT_Standard() : mt(NULL), mti(NULL), output(NULL), state(Unused) {}
    /**
     * @brief initiator from anothe MT_Standard generator
     *
     * It is prohibited and pops up an error message.
     *
     * @param MS [in] the input MT_Standard generator
     */
    MT_Standard(const Type& MS) { myError("Cannot create from MT Standard"); }
    /**
     * @brief copy from another generator
     *
     * It is implemented with assign method.
     *
     * @param MS [in] the input MT_Standard generator
     * @return the reference to the resultant generator
     */
    Type& operator=(const Type& MS) { assign(*this,MS); return *this; }
    /**
     * @brief destructor of MT_Standard generator
     *
     * it is implemented with release operation.
     */
    ~MT_Standard() { release(*this); }

    /**
     * @brief initiate generator with a \c unsigned \c int
     *
     * It is implemented with the init operation in std namespace.
     *
     * @param seed [in] the \c unsigned \c int as the seed
     * @return nothing.
     */ 
    void Init(const unsigned int seed) { std::init(*this,seed); }
    /**
     * @brief initiate generator with \c unsigned \c int array
     *
     * It is implemented with the init operation using array.
     *
     * @param key [in] the \c unsigned \c int array containing the seeds
     * @param len [in] the number of seeds
     * @param off [in] the offset of the fisrt seed in array key, which takes
     *                 the default value uZero
     * @param step [in] the step between seeds in array key, which takes
     *                  the default value uOne
     * @return nothing
     */
    void Init(const unsigned int* key, const unsigned int len,
              const unsigned int off=uZero, const unsigned int step=uOne) {
      std::init(*this,key,len,off,step);
    }
    /**
     * @brief initiate generator with vector
     *
     * it is implemented with init operation using vector
     *
     * @param key [in] the vector containing seeds
     * @return nothing
     */
    void Init(const Vector<unsigned int>& key) { std::init(*this,key); }

    /**
     * @brief generate a \c unsigned \c int random number (32-bit)
     *
     * This is the basic generator of MT_Standard generator. It is
     * a complex operation for the internal storage.
     *
     * @return a 32-bit random number
     */
    const unsigned int& UInt32() {
      unsigned int& ri=*mti;
      unsigned int& u=output->u[0];
      if(ri>=MT_Standard::N) {
        unsigned int kk;
        for(kk=0;kk<dNM;++kk) {
          u=(mt[kk]&UppMask)|(mt[kk+1]&LowMask);
          mt[kk]=mt[kk+M]^(u>>1)^Mag01[u&0x1UL];
        }
        for(;kk<Nm1;++kk) {
          u=(mt[kk]&UppMask)|(mt[kk+1]&LowMask);
          mt[kk]=mt[kk-dNM]^(u>>1)^Mag01[u&0x1UL];
        }
        u=(mt[Nm1]&UppMask)|(mt[0]&LowMask);
        mt[Nm1]=mt[Mm1]^(u>>1)^Mag01[u&0x1UL];
        ri=0;
      }
      u=mt[ri++];
      u^=(u>>11);
      u^=(u<<7)&0x9D2C5680UL;
      u^=(u<<15)&0xEFC60000UL;
      u^=(u>>18);
      return u;
    }

    /**
     * @brief generate a 31-bit int
     *
     * Just pick the lower 31-bit part of 32-bit \c unsigned \c int random
     * number.
     *
     * @return the 31-bit random number
     */
    const int& Int31() {
      output->i[0]=static_cast<int>(UInt32()>>1);
      return output->i[0];
    }

    /**
     * @brief generate a \c double value in region [0,1]
     *
     * it is implemented by a proper conversion from \c int to \c double.
     *
     * @return the \c double value in the region [0,1] 
     */
    const double& DoubleClose0Close1() {
      UInt32();
      output->d[0]=static_cast<double>(output->i[0])*(1.0/4294967295.0)
        +(0.5+0.5/4294967295.0);
      return output->d[0];
    }

    /**
     * @brief generate a \c double value in region [0,1)
     *
     * it is implemented by a proper conversion from \c int to \c double.
     *
     * @return the \c double value in region [0,1)
     */
    const double& DoubleClose0Open1() {
      UInt32();
      output->d[0]=static_cast<double>(output->i[0])*(1.0/4294967296.0)
        +0.5;
      return output->d[0];
    }

    /**
     * @brief generate a \c double value in region (0,1)
     *
     * it is implemented by a proper conversion from \c int to \c double
     *
     * @return a \c double value in region (0,1)
     */
    const double& DoubleOpen0Open1() {
      UInt32();
      output->d[0]=static_cast<double>(output->i[0])*(1.0/4294967296.0)
        +(0.5+0.5/4294967296.0);
      return output->d[0];
    }

    /**
     * @brief generate a 53-bit \c double value in [0,1)
     *
     * It is a certain combination of two 32-bit \c int.
     *
     * @return the 53-bit \c double value
     * @note It is assumed that the conversion from \c long to \c double is
     *       fast. This kind of implementation is believed to be fast, but the
     *       efficiency is not tested.
     */
    const double& Double53Close0Open1() {
      long x,y;
      x=static_cast<long>(UInt32()>>5);
      y=static_cast<long>(UInt32()>>6);
      output->d[0]=(x*67108864.0+y)*(1.0/9007199254740992.0);
      return output->d[0];
    }

    /**
     * @brief generate a 53-bit \c double value in [0,1) in slow mode
     *
     * It is a combination of two 32-bit \c int.
     *
     * @return the 53-bit \c double value
     * @note the conversion from \c unsigned \c int to \c double is believed
     *       to be slow. The efficiency is not tested.
     */
    const double& Double53Close0Open1Slow() {
      unsigned int x,y;
      x=UInt32()>>5;
      y=UInt32()>>6;
      output->d[0]=(static_cast<double>(x)*67108864.0+static_cast<double>(y))
        *(1.0/9007199254740992.0);
      return output->d[0];
    }

    /**
     * @brief generate 63-bit \c long \c double in region [0,1)
     *
     * It is a combination with two \c int.
     *
     * @return the 63-bit \c long \c double value
     * @note the conversion from \c long to \c long \c double is believed
     *       to be fast. The effeciency is not tested.
     */
    const long double& LDouble63Close0Open1() {
      long x,y;
      x=static_cast<long>(UInt32());
      y=static_cast<long>(UInt32());
      output->ld=static_cast<long double>(x*(1.0/4294967296.0))+
                 static_cast<long double>(y*(1.0/18446744073709551616.0L))+
                 (0.5+0.5/4294967296.0);
      return output->ld;
    }

    /**
     * @brief generate a 63-bit \c long \c double in region [0,1) in slow mode
     *
     * It is a combination with two \c int.
     *
     * @return the 63-bit \c long \c double value.
     * @note the conversion from \c unsigned \c int to \c long \c double
     *       is believed to be fast. The efficiency is not tested.
     */
    const long double& LDouble63Close0Open1Slow() {
      unsigned int x,y;
      x=UInt32();
      y=UInt32();
      output->ld=(x|(static_cast<unsigned long long int>(y)<<32))*
                 (1.0/18446744073709551616.0L);
      return output->ld;
    }

  };

  /**
   * @brief the size of internal storage in MT_Standard generator
   */
  const unsigned int MT_Standard::N=624;
  /**
   * @brief the wrap size in MT_Standard generator
   */
  const unsigned int MT_Standard::M=397;
  /**
   * @brief the difference between N and M in MT_Standard
   */
  const unsigned int MT_Standard::dNM=MT_Standard::N-MT_Standard::M;
  /**
   * @brief the temporary quantity of N mius 1 in MT_Standard
   */
  const unsigned int MT_Standard::Nm1=MT_Standard::N-1;
  /**
   * @brief the temporary quantity of M minus 1 in MT_Standard
   */
  const unsigned int MT_Standard::Mm1=MT_Standard::M-1;
  /**
   * @brief the quantity for bit operation in MT_Standard
   */
  const unsigned int MT_Standard::MatrixA=0x9908B0DFUL;
  /**
   * @brief the mask to pick the upper bit in \c unsigned \c int
   */
  const unsigned int MT_Standard::UppMask=0x80000000UL;
  /**
   * @brief the mask to pick the lower 31 bits in \c unsigned \c int
   */
  const unsigned int MT_Standard::LowMask=0x7FFFFFFFUL;
  /**
   * @brief the array storing the temporary quantities
   */ 
  const unsigned int MT_Standard::Mag01[2]={0x0UL,MatrixA};
  /**
   * @brief the mask to pick 32-bit \c unsigned \c int
   *
   * @note This is used to pick 32-bit part in 64-bit system.
   */
  const unsigned int MT_Standard::Mask32b=0xFFFFFFFFUL;

  /**
   * @brief check the availability of MT_Standard generator
   *
   * It is implemented by checking the availability of the internal storage.
   *
   * @param MS [in] the input MT_Standard generator
   * @return the flag indicating if the input MT_Standard generator is valid
   */
  bool IsAvailable(const MT_Standard& MS) { return IsAvailable(MS.mt); }
  /**
   * @brief check if MT_Standard is a random generator
   *
   * The MT_Standard generator is certainly a random generator.
   *
   * @param MS [in] the input MT_Standard generator
   * @return true since MT_Standard generator is a random generator
   */
  bool IsRandomGenerator(const MT_Standard& MS) { return true; }

  /**
   * @brief assign MT_Standard generator from another
   *
   * Just copy the internal storage from that in the source generator.
   * The location indicator and output are also copied. The generators
   * dest and src are checked for their availability before this operation.
   *
   * @param dest [out] the MT_Standard generator to accept the input
   * @param src [in] the MT_Standard generator containing the information
   * @return nothing 
   */
  void assign(MT_Standard& dest, const MT_Standard& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(dest.mt,src.mt,MT_Standard::N);
    *(dest.mti)=*(src.mti);
    *(dest.output)=*(src.output);
  }

  /**
   * @brief release a MT_Standard generator
   *
   * The internal storage, the internal location and the output variable
   * are released based on the state od storage.
   *
   * @param MS [in,out] the MT_Standard generator to be released
   * @return nothing 
   */
  void release(MT_Standard& MS) {
    if(MS.state==Allocated) {
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

  /**
   * @brief allocate a MT_Standard generator
   *
   * The internal storage, the location flag and the output are allocated.
   * The corresponding state is set as Allocated. Then, the generator is
   * initiated with a default seed of 5489. The input generator is
   * released before this operation.
   *
   * @param MS [in,out] the MT_Standard generator to be allocated
   * @return nothing
   */ 
  void allocate(MT_Standard& MS) {
    release(MS);
    MS.mt=new unsigned int[MT_Standard::N];
    MS.mti=new unsigned int;
    MS.output=new UniqueParameter128b;
    MS.state=Allocated;
    init(MS,5489UL);
  }

  /**
   * @brief refer to another MT_Standard generator
   *
   * Just assign the pointers of internal variable from source object to
   * destinate object. The state is updated as Reference. Before this
   * operation, the source obejct is checked for its availability.
   *
   * @param dest [out] the MT_Standard generator to accept the input
   * @param src [in] the MT_Standard generator containing the information
   * @return nothing
   */
  void refer(MT_Standard& dest, const MT_Standard& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.mt=src.mt;
    dest.mti=src.mti;
    dest.output=src.output;
    dest.state=Reference;
  }

  /**
   * @brief initiate MT_Standard generator with a \c unsigned \c int seed
   *
   * The first element in the internal storage is assigned with seed.
   * The other elements are generated sequentially. Before this operation,
   * the MT_Standard generator is checked for its availability.
   *
   * @param MS [in,out] the MT_Standard generator to be initiated
   * @param seed [in] the \c unsigned \c int seed to initiate generator
   * @return nothing
   */
  void init(MT_Standard& MS, const unsigned int seed) {
    assert(IsAvailable(MS));
    unsigned int& ri=*(MS.mti);
    unsigned int rmt;
    MS.mt[0]=seed&MT_Standard::Mask32b;
    rmt=MS.mt[0];
    for(ri=1;ri<MT_Standard::N;++ri) {
      rmt=1812433253UL*(rmt^(rmt>>30))+ri;
      rmt&=MT_Standard::Mask32b;
      MS.mt[ri]=rmt;
    }
  }

  /**
   * @brief initiate MT_Standard generator with an array
   *
   * The internal storage are filled with the results calculated based on
   * elementes in arrays. The generator is first initiated with a default
   * value of 19650218 before the operation on array. The array and generator
   * are checked for their availability before this operation.
   *
   * @param MS [out] the MT_Standard genrator to be initiated
   * @param key [in] the array containing the seeds
   * @param len [in] the number of elements for initiation
   * @param off [in] the offset for the first element in array key. It takes
   *                 a default value of uZero.
   * @param step [in] the step between elements in array key. It takes
   *                  a default value of uOne.
   * @return nothing
   * @note it is proved that the initiation with array may produce better
   *       uniform distribution. basically, the array may provide more
   *       control (more bits of information) in input.
   */
  void init(MT_Standard& MS, const unsigned int *key, const unsigned int len,
                             const unsigned int off=uZero,
                             const unsigned int step=uOne) {
    assert(IsAvailable(MS));
    assert(IsAvailable(key));
    unsigned int i,j,k,g;
    unsigned int rmt;
    init(MS,19650218UL);
    i=1;    j=0;  g=off;
    rmt=MS.mt[0];
    k=(MT_Standard::N>len?MT_Standard::N:len);
    for(;k;--k) {
      rmt=(MS.mt[i]^((rmt^(rmt>>30))*1664525UL))+key[g]+j;
      rmt&=MT_Standard::Mask32b;
      MS.mt[i]=rmt;
      ++i;    ++j;  g+=step;
      if(i>=MT_Standard::N) { MS.mt[0]=rmt; i=1; }
      if(j>=len) { j=0; g=off; }
    }
    for(k=MT_Standard::N-1;k;--k) {
      rmt=(MS.mt[i]^((rmt^(rmt>>30))*1566083941UL))-i;
      rmt&=MT_Standard::Mask32b;
      ++i;
      if(i>=MT_Standard::N) { MS.mt[0]=rmt; i=1; }
    }
    MS.mt[0]=MT_Standard::UppMask;
  }

  /**
   * @brief initiate MT_Standard generator with a vector
   *
   * It is implemented by init operation with array.
   *
   * @param MS [out] the MT_Standard generator to be initiated
   * @param key [in] the vector containing seeds
   * @return nothing
   */
  void init(MT_Standard& MS, const Vector<unsigned int>& key) {
    init(MS,key(),key.size);
  }

  const double& rand(MT_Standard& MS) { return MS.Double53Close0Open1(); }

  template <typename T>
  const T& rand(MT_Standard& MS) { myError("Default Form is prohibited"); }

  template <>
  const unsigned int& rand<unsigned int>(MT_Standard& MS) {
    return MS.UInt32();
  }

  template <>
  const int& rand<int>(MT_Standard& MS) { return MS.Int31(); }

  template <>
  const double& rand<double>(MT_Standard& MS) {
    return MS.Double53Close0Open1();
  }

  template <>
  const long double& rand<long double>(MT_Standard& MS) {
    return MS.LDouble63Close0Open1();
  }

  ostream& operator<<(ostream& os, const MT_Standard& MS) {
    assert(IsAvailable(MS));
    for(unsigned int i=0;i<MT_Standard::N;++i)  os<<MS.mt[i]<<"\t";
    os<<*(MS.mti);
    return os;
  }

  istream& operator>>(istream& is, MT_Standard& MS) {
    assert(IsAvailable(MS));
    for(unsigned int i=0;i<MT_Standard::N;++i)  is>>MS.mt[i];
    is>>*(MS.mti);
    return is;
  }

}

#endif

