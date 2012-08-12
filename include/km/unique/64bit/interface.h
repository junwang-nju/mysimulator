
/**
 * @file unique/64bit/interface.h
 * @brief the object with 64 bits and various data formats
 *
 * To provide a unique interface for various kinds of number, an encapsulation
 * of various kinds of data using \c union is implemented here. This may simplify
 * the interface. In this file, a 64-bit data interface is realized.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Unique_64Bit_Interface_H_
#define _Unique_64Bit_Interface_H_

#include "type/is-copyable.h"
#include "type/is-fillable.h"

namespace mysimulator {

  union Unique64Bit;
  union Unique128Bit;
  void Clear(Unique64Bit&);

  /** @union Unique64Bit
   * @brief the 64-bit data container
   *
   * This is a unique interface of intrinsic data. It contains all possible
   * intrinsic data types with their sizes smaller than 64-bit. Since it is
   * only the interface of various data, a \c union is used to save storage.
   *
   * @note Since the pointer is a special object which may produce memory leak,
   *       the array interface of pointer is not defined.
   */
  union Unique64Bit {

    public:

      /** @typedef Type
       * @brief the definition of trait type
       */
      typedef Unique64Bit   Type;
      template <typename T> friend T& Value(Unique64Bit&);
      template <typename T> friend const T& Value(const Unique64Bit&);
      template <typename T> friend T& Value(Unique64Bit&,unsigned int);
      template <typename T>
      friend const T& Value(const Unique64Bit&,unsigned int);
      template <typename T> friend T*& Pointer(Unique64Bit&);
      template <typename T> friend const T* const& Pointer(const Unique64Bit&);

      /** @brief the default initiator
       *
       * It is implemented by initing the \c unsigned \c long \c long data with
       * \c 0. It just fills all the bits of the present data storage with \c 0.
       */
      Unique64Bit() : ull(0) {}
      /** @brief initiator with \c unsigned \c long \c long data
       *
       * Since the size of present data storage is same as that of \c unsigned
       * \c long \c long data, this kind of initiation could initiate all the
       * bits of the present storage.
       *
       * @param u [in] the input \c unsigned \c long \c long value
       */
      Unique64Bit(const unsigned long long& u) : ull(u) {}
      /** @brief initiatoe with \c double data
       *
       * \c double data is frequently used simulations. Since the copy of
       * \c double data may not totally identical in all bits, the storage of
       * \c double variable is converted into \c unsigned \c long \c long type
       * (namely the \c unsigned \c long \c long data and \c double data are
       * identical in bits). Then, the present data structure is initiated
       * this \c unsigned \c long \c long data.
       *
       * @param d [in] the input \c double data
       */
      Unique64Bit(const double& d)
        : ull(*reinterpret_cast<const unsigned long long*>(&d)) {}
      /** @brief the destructor
       *
       * It is implemented with \c Clear function
       */
      ~Unique64Bit() { Clear(*this); }

      /** @fn bool IsValid()
       * @brief the validity check of the storage
       *
       * Since this storage is pre-assigned (namely 64-bit), the storage is always
       * available. therefore \c true flag is returned.
       *
       * @return the \c true flag indicating that the storage is valid.
       */
      bool IsValid() const { return true; }

      /** @fn void Imprint(const Unique64Bit&)
       * @brief imprint structure from input object
       *
       * This is an interface to imprint structure from another \c Unique64Bit
       * object. Since \c Unique64Bit object is pre-assigned, this operation
       * does nothing.
       *
       * @param P [in] the input \c Unique64Bit object
       */
      void Imprint(const Unique64Bit& P) {}
      /** @fn void Copy(const Unique64Bit&)
       * @brief copy another \c Unique64Bit object
       *
       * It is implemented by copying the \c unsigned \c long \c long content
       * into present object. All the bits are copied from the input object.
       *
       * @param P [in] the input \c Unique64Bit object
       */
      void Copy(const Unique64Bit& P) { ull=P.ull; }
      /** @fn void Copy(const T&)
       * @brief copy a \c T -type value
       *
       * It is implemented with \c Value procedure. Only the related interface
       * is written. The validity of the related type is checked with \c CopyCheck.
       *
       * @tparam T the type of the input data
       *
       * @param v [in] the input \c T -type data
       */
      template <typename T>
      void Copy(const T& v) {
        typedef typename IsCopyable<Unique64Bit,T>::Type  CopyCheck;
        Value<T>(*this)=v;
      }
      /** @fn void Copy(const Unique128Bit&)
       * @brief copy from a \c Unique128Bit object
       */
      void Copy(const Unique128Bit&);
      /** @fn void Fill(const T& v)
       * @brief fill \c Unique64Bit with \c T -type data
       *
       * The \c Unique64Bit object is 64-bit. When the size of input data is
       * smaller than \c Unique64Bit, the \c Unique64Bit object could be filled
       * with several copies of the input data. Here it is implemented with
       * \c Value to access the array interface of \c Unique64Bit. To check
       * the validity of type of the input data, the input type is check with
       * \c IsFillable.
       *
       * @tparam T the type of the input data
       *
       * @param v [in] the input \c T -type data
       */
      template <typename T>
      void Fill(const T& v) {
        typedef typename IsFillable<Unique64Bit,T>::Type  FillCheck;
        for(unsigned int i=0;i<sizeof(double)/sizeof(T);++i)
          Value<T>(*this,i)=v;
      }

    protected:

      /** @var d
       * @brief the \c double interface
       */
      double                d;
      /** @var dv
       * @brief the \c double array interface
       *
       * Since the \c double type has the size of \c 8 bytes, the array interface
       * has only \c 1 element.
       */
      double                dv[1];
      /** @var f
       * @brief the \c float interface
       */
      float                 f;
      /** @var fv
       * @brief the \c float array interface
       *
       * Since \c float type has the size of \c 4 bytes, the array interface
       * has \c 2 elements.
       */
      float                 fv[2];
      /** @var ll
       * @brief the \c long \c long interface
       */
      long long             ll;
      /** @var llv
       * @brief the \c long \c long array interface
       *
       * Since \c long \c long type has the size of \c 8 bytes, the array interface
       * has only \c 1 elements.
       */
      long long             llv[1];
      /** @var ull
       * @brief the \c unsigned \c long \c long interface
       */
      unsigned long long    ull;
      /** @var ullv
       * @brief the \c unsigned \c long \c long array interface
       *
       * Since \c unsigned \c long \c long type has the size of \c 8 bytes,
       * the array interface has only \c 1 elements.
       */
      unsigned long long    ullv[1];
      /** @var i
       * @brief the \c int interface
       */
      int                   i;
      /** @var iv
       * @brief the \c int array interface
       *
       * Since \c int type has the size of \c 4 bytes, the array interface
       * has \c 2 elements.
       */
      int                   iv[2];
      /** @var u
       * @brief the \c unsigned \c int interface
       */
      unsigned int          u;
      /** @var uv
       * @brief the \c unsigned \c int array interface
       *
       * Since \c unsigned \c int type has the size of \c 4 bytes, the array
       * interface has \c 2 elements.
       */
      unsigned int          uv[2];
      /** @var l
       * @brief the \c long interface
       */
      long                  l;
      /** @var lv
       * @brief the \c long array interface
       *
       * Since \c long type has the size of \c 4 bytes, the array interface
       * has \c 2 elements.
       */
      long                  lv[2];
      /** @var ul
       * @brief the \c unsigned \c long interface
       */
      unsigned long         ul;
      /** @var ulv
       * @brief the \c unsigned \c long array interface
       *
       * Since \c unsigned \c long type has the size of \c 4 bytes, the array
       * interface has \c 2 elements.
       */
      unsigned long         ulv[2];
      /** @var s
       * @brief the \c short interface
       */
      short                 s;
      /** @var sv
       * @brief the \c short array interface
       *
       * Since \c short type has the size of \c 2 bytes, the array interface
       * has \c 4 elements.
       */
      short                 sv[4];
      /** @var us
       * @brief the \c unsigned \c short interface
       */
      unsigned short        us;
      /** @var usv
       * @brief the \c unsigned \c short array interface
       *
       * Since \c unsigned \c short type has the size of \c 2 bytes, the array
       * interface has \c 4 elements.
       */
      unsigned short        usv[4];
      /** @var c
       * @brief the \c char interface
       */
      char                  c;
      /** @var cv
       * @brief the \c char array interface
       *
       * Since \c char type has the size of \c 1 bytes, the array interface
       * has \c 8 elements.
       */
      char                  cv[8];
      /** @var uc
       * @brief the \c unsigned \c char interface
       */
      unsigned char         uc;
      /** @var ucv
       * @brief the \c unsigned \c char array interface
       *
       * Since \c unsigned \c char type has the size of \c 1 bytes, the array
       * interface has \c 8 elements.
       */
      unsigned char         ucv[8];
      /** @var ptr
       * @brief the \c void pointer interface
       */
      void*                 ptr;

    private:

      /** @brief disabled copy initiator
       *
       * This copy initiator is set as \c private to disable this operation
       */
      Unique64Bit(const Type&) {}
      /** @brief the disabled copier
       *
       * This copier is set as \c private to disable this operation.
       *
       * @param P [in] the input object
       * @return the reference of present object
       */
      Type& operator=(const Type& P) { return *this; }

  };

  /** @fn void _Imprint(Unique64Bit&,const Unique64Bit&)
   * @brief imprint \c Unique64Bit object from another \c Unique64Bit object
   *
   * Similar to \c Unique64Bit::Imprint method, this procedure has no contents.
   *
   * @param P [out] the resultant \c Unique64Bit object
   * @param CP [in] the input \c Unique64Bit object
   */
  void _Imprint(Unique64Bit& P,const Unique64Bit& CP) {}
  /** @fn void _Copy(Unique64Bit&,const T&)
   * @brief copy from \c T -type data to \c Unique64Bit object
   *
   * It is implemented with the Unique64Bit::Copy method. This function provides
   * the common interface of copy operation, which would be used in copy of 
   * advanced objects (such as Array)
   *
   * @tparam T the type of the input data
   *
   * @param P [out] the resultant \c Unique64Bit object
   * @param v [in] the input \c T -type data
   */
  template <typename T>
  void _Copy(Unique64Bit& P,const T& v) { P.Copy(v); }
  /** @fn void _Copy(T&,const Unique64Bit&)
   */
  template <typename T>
  void _Copy(T& v,const Unique64Bit& P) {
    typedef typename IsCopyable<T,Unique64Bit>::Type  CopyCheck;
    v=Value<T>(P);
  }
  /** @fn void _Fill(Unique64Bit&,const T&)
   */
  template <typename T>
  void _Fill(Unique64Bit& P,const T& v) { P.Fill(v); }

}

#include <cstdio>

namespace mysimulator {

  /** @fn T& Value(Unique64Bit&)
   */
  template <typename T>
  T& Value(Unique64Bit& P) {
    fprintf(stderr,"Unknown Type for Unique64Bit!\n");
    return static_cast<T&>(P.d);
  }
  /** @fn const T& Value(const Unique64Bit&)
   */
  template <typename T>
  const T& Value(const Unique64Bit& P) {
    fprintf(stderr,"Unknown Type for Unique64Bit!\n");
    return static_cast<const T&>(P.d);
  }

}

/** @def _VValueDEF_
 */
#ifndef _VValueDEF_
#define _VValueDEF_(T,v) \
  template <> T& Value<T>(Unique64Bit& P) { return P.v; }
#else
#error "Duplicate _VValueDEF_"
#endif

/** @def _CValueDEF_
 */
#ifndef _CValueDEF_
#define _CValueDEF_(T,v)  \
  template <> const T& Value<T>(const Unique64Bit& P) { return P.v; }
#else
#error "Duplicate _CValueDEF_"
#endif

/** @def _ValueDEF_
 */
#ifndef _ValueDEF_
#define _ValueDEF_(T,v) \
  _VValueDEF_(T,v) \
  _CValueDEF_(T,v)
#endif

namespace mysimulator {

  _ValueDEF_(double,d)
  _ValueDEF_(float,f)
  _ValueDEF_(long long,ll)
  _ValueDEF_(unsigned long long,ull)
  _ValueDEF_(int,i)
  _ValueDEF_(unsigned int,u)
  _ValueDEF_(long,l)
  _ValueDEF_(unsigned long,ul)
  _ValueDEF_(short,s)
  _ValueDEF_(unsigned short,us)
  _ValueDEF_(char,c)
  _ValueDEF_(unsigned char, uc)

}

#ifdef _ValueDEF_
#undef _ValueDEF_
#endif

#ifdef _CValueDEF_
#undef _CValueDEF_
#endif

#ifdef _VValueDEF_
#undef _VValueDEF_
#endif

namespace mysimulator {

  /** @fn T Value(Unique64Bit&,unsigned int)
   */
  template <typename T>
  T& Value(Unique64Bit& P, unsigned int n) {
    fprintf(stderr,"Unknown Type for Unique64Bit!\n");
    return static_cast<T&>(P.d);
  }

  /** @fn const T Value(const Unique64Bit&,unsigned int)
   */
  template <typename T>
  const T& Value(const Unique64Bit& P, unsigned int n) {
    fprintf(stderr,"Unknown Type for Unique64Bit!\n");
    return static_cast<const T&>(P.d);
  }

}

#include <cassert>

#ifndef _VValueDEF_
#define _VValueDEF_(T,u) \
  template <> T& Value<T>(Unique64Bit& P,unsigned int n) { \
    assert(n<sizeof(double)/sizeof(T)); \
    return P.u[n]; \
  }
#else
#error "Duplicate _VValueDEF_"
#endif

#ifndef _CValueDEF_
#define _CValueDEF_(T,u) \
  template <> const T& Value<T>(const Unique64Bit& P,unsigned int n) { \
    assert(n<sizeof(double)/sizeof(T)); \
    return P.u[n]; \
  }
#else
#error "Duplicate _CValueDEF_"
#endif

#ifndef _ValueDEF_
#define _ValueDEF_(T,u) \
  _VValueDEF_(T,u) \
  _CValueDEF_(T,u)
#else
#error "Duplicate _ValueDEF_"
#endif

namespace mysimulator {

  _ValueDEF_(double,dv)
  _ValueDEF_(float,fv)
  _ValueDEF_(long long,llv)
  _ValueDEF_(unsigned long long,ullv)
  _ValueDEF_(int,iv)
  _ValueDEF_(unsigned int,uv)
  _ValueDEF_(long,lv)
  _ValueDEF_(unsigned long,ulv)
  _ValueDEF_(short,sv)
  _ValueDEF_(unsigned short,usv)
  _ValueDEF_(char,cv)
  _ValueDEF_(unsigned char, ucv)

}

#ifdef _ValueDEF_
#undef _ValueDEF_
#endif

#ifdef _CValueDEF_
#undef _CValueDEF_
#endif

#ifdef _VValueDEF_
#undef _VValueDEF_
#endif

namespace mysimulator {

  /** @fn T*& Pointer(Unique64Bit&)
   */
  template <typename T>
  T*& Pointer(Unique64Bit& P) { return reinterpret_cast<T*&>(P.ptr); }

  /** @fn const T* const& Pointer(const Unique64Bit&)
   */
  template <typename T>
  const T* const& Pointer(const Unique64Bit& P) {
    return reinterpret_cast<const T* const&>(P.ptr);
  }

  /** @fn void Clear(Unique64Bit&)
   */
  void Clear(Unique64Bit& P) { Value<unsigned long long>(P)=0; }

}

#include "unique/128bit/interface.h"

namespace mysimulator {

  /** @fn void Unique64Bit::Copy(const Unique128Bit&)
   */
  void Unique64Bit::Copy(const Unique128Bit& U) {
    Copy(Value<unsigned long long>(U));
  }

  void _Copy(Unique64Bit& U,const Unique128Bit& LU) { U.Copy(LU); }

}

#endif

