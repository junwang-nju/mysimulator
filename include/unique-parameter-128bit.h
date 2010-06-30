
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

    /**
     * @brief copy from a \c long \c double value
     *
     * copy through \c long \c double interface.
     *
     * @param rld [in] the input \c long \c double value
     * @return the reference to the resultant UniqueParameter128b object
     */
    Type& operator=(const long double rld) { ld=rld; return *this; }

    /**
     * @brief copy from \c double array
     *
     * copy through \c double interface.
     *
     * @param rd [in] the input \c double array with 2 elements
     * @return the reference to the resultant UniqueParameter128b object
     */
    Type& operator=(const double rd[2]) { assign(d,rd,2); return *this; }

    /**
     * @brief copy from \c unsigned \c int array
     *
     * copy through \c unsigned \c int interface.
     *
     * @param ru [in] the input \c unsigned \c int array with 4 elements
     * @return the reference to the resultant UniqueParameter128b object
     */
    Type& operator=(const unsigned int ru[4]) { assign(u,ru,4); return *this; }

    /**
     * @brief copy from \c int array
     *
     * copy through \c int interface.
     *
     * @param ri [in] the input \c int array with 8 elements
     * @return the reference to the resultant UniqueParameter128b object
     */
    Type& operator=(const int ri[8]) { assign(i,ri,4); return *this; }

    /**
     * @brief copy from \c unsigned \c long \c long array
     *
     * copy through \c unsigned \c long \c long interface.
     *
     * @param rull [in] the input \c unsigned \c long \c long array
     *                  with 2 elements
     * @return the reference to the resultant UniqueParameter128b object
     */
    Type& operator=(const unsigned long long rull[2]) {
      assign(ull,rull,2);
      return *this;
    }
    
    /**
     * @brief copy from pointer array
     *
     * copy through pointer interface.
     *
     * T is the type of data that the pointers point to.
     *
     * @param rptr [in] the input array of pointers to T-type data.
     * @return the reference to the resultant UniqueParameter128b object
     */ 
    template <typename T>
    Type& operator=(T* const rptr[4]) {
      assign(reinterpret_cast<unsigned int*>(ptr),
             reinterpret_cast<const unsigned int*>(rptr),4);
      return *this;
    }

    /**
     * @brief access content as \c long \c double variable
     *
     * This is a method to access the content as a \c long \c double value.
     *
     * @return the reference to content as \c long \c double value
     * @note this method is defined because \c long \c double type is an
     *       intrinsic 128-bit type of data.
     */
    long double& operator()() { return ld; }
    
    /**
     * @brief visit content as \c long \c double value
     *
     * This is a method to visit content as a \c long \c double value.
     *
     * @return the const reference to the content as \c long \c double value
     * @note this is const version of the method to access the content of
     *       UniqueParameter128b object.
     */ 
    const long double& operator()() const { return ld; }

  };

  /**
   * @brief assign UniqueParameter128b array from another array (with offset)
   *
   * It is implemented by converting the UniqueParameter128b object as
   * double value. The assign function for double-type values is used.
   * One UniqueParameter128b element corresponds to two double values.
   *
   * @param dest [out] the output UniqueParameter128b array
   * @param src [in] the input UniqueParameter128b array
   * @param size [in] the number of elements related to the assign operation
   * @param soff [in] the offset of elements in the array src
   * @param doff [in] the offset of elements in the array dest
   * @return nothing
   */
  void assign(UniqueParameter128b* dest, const UniqueParameter128b* src,
              const unsigned int size,
              const int soff=iZero, const int doff=iZero) {
    assign(reinterpret_cast<double*>(dest),
           reinterpret_cast<const double*>(src),size+size,
           soff+soff,lOne,doff+doff,lOne);
  }

  /**
   * @brief assign UniqueParameter128b array from another array (with offset and step)
   *
   * It is implemented by converting the UniqueParameter128b object as
   * double value. The assign function for double-type values is used.
   * Since one UniqueParameter128b object contains two double values,
   * two assign operations are used.
   *
   * @param dest [out] the output UniqueParameter128b array
   * @param src [in] the input UniqueParameter128b array
   * @param size [in] the number of elements related to the assign operation
   * @param soff [in] the offset of elements in the array src
   * @param sstep [in] the step between elements in the array src
   * @param doff [in] the offset of elements in the array dest
   * @param dstep [in] the step between elements in the array dest
   * @return nothing
   */
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

  /**
   * @brief assign UniqueParameter128b array from a UniqueParameter128b value (with offset and step)
   *
   * It is implemented with array copy operation.
   *
   * @param dest [out] the output UniqueParameter128b array
   * @param src [in] the input UniqueParameter128b object
   * @param size [in] the number of elements related to the copy operation
   * @param doff [in] the offset of elements in the array dest
   * @param dstep [in] the step between elements in the array dest
   */
  void assign(UniqueParameter128b* dest, const UniqueParameter128b& src,
              const unsigned int size,
              const int doff=iZero, const long dstep=lOne) {
    assign(dest,&src,size,uZero,uZero,doff,dstep);
  }

  /**
   * @brief read a UniqueParameter128b object from istream
   *
   * Since UniqueParameter128b object may store multiple types data,
   * a flag indicating the type is read at first. Then, based on the
   * type information, the data is imported. For unknown types, a failbit
   * is produced. Here, G(g) means \c long \c double, D(d) means \c double,
   * U(u) means \c unsigned \c int, I(i) means \c int, L(l) means \c unsigned
   * \c long \c long, P(p) means pointer.
   *
   * @param is [in,out] the istream object, which would be accessed and
   *                    altered during reading
   * @param UP [out] the UniqueParameter128b object storing input data
   * @return the istream after reading.
   */
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

  /**
   * @brief write a UniqueParameter128b object to ostream
   *
   * Just write out the data through \c unsigned \c long \c long \c int
   * interface as output to keep all bit information
   *
   * @param os [in,out] the ostream object which would be changed after
   *                    output operation.
   * @param UP [in] the UniqueParameter128b object to be output
   * @return the ostream object after output.
   */
  ostream& operator<<(ostream& os, const UniqueParameter128b& UP) {
    os<<"L [ "<<UP.ull[0]<<"  "<<UP.ull[1]<<" ] ";
    return os;
  }

}

#endif

