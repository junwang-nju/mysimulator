
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
    ~MT_Standard() { release(*this); }

    void Init(const unsigned int seed) { std::init(*this,seed); }
    void Init(const unsigned int* key, const unsigned int len,
              const unsigned int off=uZero, const unsigned int step=uOne) {
      std::init(*this,key,len,off,step);
    }
    void Init(const Vector<unsigned int>& key) { std::init(*this,key); }

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

    const int& Int31() {
      output->i[0]=static_cast<int>(UInt32()>>1);
      return output->i[0];
    }

    const double& DoubleClose0Close1() {
      UInt32();
      output->d[0]=static_cast<double>(output->i[0])*(1.0/4294967295.0)
        +(0.5+0.5/4294967295.0);
      return output->d[0];
    }

    const double& DoubleClose0Open1() {
      UInt32();
      output->d[0]=static_cast<double>(output->i[0])*(1.0/4294967296.0)
        +0.5;
      return output->d[0];
    }

    const double& DoubleOpen0Open1() {
      UInt32();
      output->d[0]=static_cast<double>(output->i[0])*(1.0/4294967296.0)
        +(0.5+0.5/4294967296.0);
      return output->d[0];
    }

    const double& Double53Close0Open1() {
      long x,y;
      x=static_cast<long>(UInt32()>>5);
      y=static_cast<long>(UInt32()>>6);
      output->d[0]=(x*67108864.0+y)*(1.0/9007199254740992.0);
      return output->d[0];
    }

    const double& Double53Close0Open1Slow() {
      unsigned int x,y;
      x=UInt32()>>5;
      y=UInt32()>>6;
      output->d[0]=(static_cast<double>(x)*67108864.0+static_cast<double>(y))
        *(1.0/9007199254740992.0);
      return output->d[0];
    }

    const long double& LDouble63Close0Open1() {
      long x,y;
      x=static_cast<long>(UInt32());
      y=static_cast<long>(UInt32());
      output->ld=static_cast<long double>(x*(1.0/4294967296.0))+
                 static_cast<long double>(y*(1.0/18446744073709551616.0L))+
                 (0.5+0.5/4294967296.0);
      return output->ld;
    }

    const long double& LDouble63Close0Open1Slow() {
      unsigned int x,y;
      x=UInt32();
      y=UInt32();
      output->ld=(x|(static_cast<unsigned long long int>(y)<<32))*
                 (1.0/18446744073709551616.0L);
      return output->ld;
    }

  };

  const unsigned int MT_Standard::N=624;
  const unsigned int MT_Standard::M=397;
  const unsigned int MT_Standard::dNM=MT_Standard::N-MT_Standard::M;
  const unsigned int MT_Standard::Nm1=MT_Standard::N-1;
  const unsigned int MT_Standard::Mm1=MT_Standard::M-1;
  const unsigned int MT_Standard::MatrixA=0x9908B0DFUL;
  const unsigned int MT_Standard::UppMask=0x80000000UL;
  const unsigned int MT_Standard::LowMask=0x7FFFFFFFUL;
  const unsigned int MT_Standard::Mag01[2]={0x0UL,MatrixA};
  const unsigned int MT_Standard::Mask32b=0xFFFFFFFFUL;

  bool IsAvailable(const MT_Standard& MS) { return IsAvailable(MS.mt); }
  bool IsRandomGenerator(const MT_Standard&) { return true; }

  void assign(MT_Standard& dest, const MT_Standard& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(dest.mt,src.mt,MT_Standard::N);
    *(dest.mti)=*(src.mti);
    *(dest.output)=*(src.output);
  }

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

  void allocate(MT_Standard& MS) {
    release(MS);
    MS.mt=new unsigned int[MT_Standard::N];
    MS.mti=new unsigned int;
    MS.output=new UniqueParameter128b;
    MS.state=Allocated;
    init(MS,5489UL);
  }

  void refer(MT_Standard& dest, const MT_Standard& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.mt=src.mt;
    dest.mti=src.mti;
    dest.output=src.output;
    dest.state=Reference;
  }

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

