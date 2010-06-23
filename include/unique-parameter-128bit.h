
/**
 * @file unique-parameter-128bit.h
 * @brief 128-bit data with many interfaces
 *
 * This file defines a 128-bit structure with various interfaces. This
 * is implemented with 128-bit registers related to SSE operations.
 * This is used for random generators.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Unique_Parameter_128bit_H_
#define _Unique_Parameter_128bit_H_

#include "error-proc.h"
#include "vector-impl.h"

#ifdef HAVE_SSE2
#include <emmintrin.h>
#endif

namespace std {

  /**
   * @brief 128-bit data with various interfaces
   *
   * This object encapsulates the __m128i (128-bit int), __m128d (128-bit
   * double), long double, double, unsigned int, int, unsigned long long
   * int, void pointer. All the bits could be accessed with various
   * interfaces. This is different from UniqueParameter object. The
   * interface with larger size may ease the operation of the data.
   */
  union UniqueParameter128b {

#ifdef HAVE_SSE2
    /**
     * @brief the 128-bit int object
     */
    __m128i si;
    /**
     * @brief the 128-bit double object
     */
    __m128d sd;
#endif
    /**
     * @brief \c long \c double interface
     */
    long double ld;
    /**
     * @brief \c double interface
     */
    double d[2];
    /**
     * @brief \c unsigned \c int interface
     */
    unsigned int u[4];
    /**
     * @brief \c int interface
     */
    int i[4];
    /**
     * @brief \c unsigned \c long \c long \c int interface
     */
    unsigned long long int ull[2];
    /**
     * @brief \c void pointer interface
     */
    void* ptr[4];

    /**
     * @brief abbreviation for unique-parameter-128bit object
     */
    typedef UniqueParameter128b   Type;
    
    /**
     * @brief default initiator
     *
     * initialize all the bits through \c unsigned \c long \c long
     * interface.
     */
    UniqueParameter128b() { ull[0]=0; ull[1]=0; }
    
    /**
     * @brief initiator from another UniqueParameter128b object
     *
     * This is prohibited and pop-up an error message.
     *
     * @param UP [in] the input UniqueParameter128b object
     */
    UniqueParameter128b(const Type& UP) {
      myError("Cannot create from 128bit Unique Parameter");
    }
    
    /**
     * @brief copy from another UniqueParameter128b object
     *
     * It is implemented through the copy operation for \c unsigned
     * \c long \c long \c int object.
     *
     * @param UP [in] the input UniqueParameter128b object
     * @return the reference to the resultant UniqueParameter128b object
     */
    Type& operator=(const Type& UP) { return operator=(UP.ull); }
    Type& operator=(const long double rld) { ld=rld; return *this; }
    Type& operator=(const double rd[2]) { assign(d,rd,2); return *this; }
    Type& operator=(const unsigned int ru[4]) { assign(u,ru,4); return *this; }
    Type& operator=(const int ri[8]) { assign(i,ri,4); return *this; }
    Type& operator=(const unsigned long long rull[2]) {
      assign(ull,rull,2);
      return *this;
    }
    template <typename T>
    Type& operator=(T* const rptr[4]) {
      assign(reinterpret_cast<unsigned int*>(ptr),
             reinterpret_cast<const unsigned int*>(rptr),4);
      return *this;
    }

    long double& operator()() { return ld; }
    const long double& operator()() const { return ld; }

  };

  void assign(UniqueParameter128b* dest, const UniqueParameter128b* src,
              const unsigned int size,
              const int soff=iZero, const int doff=iZero) {
    assign(reinterpret_cast<double*>(dest),
           reinterpret_cast<const double*>(src),size+size,
           soff+soff,lOne,doff+doff,lOne);
  }

  void assign(UniqueParameter128b* dest, const UniqueParameter128b* src,
              const unsigned int size,
              const int soff, const long sstep,
              const int doff, const long dstep) {
    assign(reinterpret_cast<double*>(dest),
           reinterpret_cast<const double*>(src),size,
           soff+soff,sstep+sstep,doff+doff,dstep+dstep);
    assign(reinterpret_cast<double*>(dest),
           reinterpret_cast<const double*>(src),size,
           soff+soff+1,sstep+sstep,doff+doff+1,dstep+dstep);
  }

  void assign(UniqueParameter128b* dest, const UniqueParameter128b& src,
              const unsigned int size,
              const int doff=iZero, const long dstep=lOne) {
    assign(dest,&src,size,uZero,uZero,doff,dstep);
  }

  istream& operator>>(istream& is, UniqueParameter128b& UP) {
    static char flag;
    static char buff[1024];
    is>>flag;
    if((flag=='G')||(flag=='g'))  is>>UP.ld;
    else if((flag=='D')||(flag=='d')) {
      is>>buff; is>>UP.d[0]; is>>UP.d[1]; is>>buff;
    } else if((flag=='U')||(flag=='u')) {
      is>>buff; for(unsigned int i=0;i<4;++i) is>>UP.u[i];  is>>buff;
    } else if((flag=='I')||(flag=='i')) {
      is>>buff; for(unsigned int i=0;i<4;++i) is>>UP.i[i];  is>>buff;
    } else if((flag=='L')||(flag=='l')) {
      is>>buff; is>>UP.ull[0];  is>>UP.ull[1];  is>>buff;
    } else if((flag=='P')||(flag=='p')) {
      is>>buff; for(unsigned int i=0;i<4;++i) is>>UP.ptr[i];  is>>buff;
    } else is.setstate(ios_base::failbit);
    return is;
  }

  ostream& operator<<(ostream& os, const UniqueParameter128b& UP) {
    os<<"L [ "<<UP.ull[0]<<"  "<<UP.ull[1]<<" ] ";
    return os;
  }

}

#endif

