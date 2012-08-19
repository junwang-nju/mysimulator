
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
   * It is implemented with the \c Unique64Bit::Copy method. This function
   * provides the common interface of copy operation, which would be used in
   * copy of advanced objects (such as \c Array)
   *
   * @tparam T the type of the input data
   *
   * @param P [out] the resultant \c Unique64Bit object
   * @param v [in] the input \c T -type data
   */
  template <typename T>
  void _Copy(Unique64Bit& P,const T& v) { P.Copy(v); }
  /** @fn void _Copy(T&,const Unique64Bit&)
   * @brief copy a \c T -type value from \c Unique64Bit
   *
   * This procedure extracts the \c T -type content fron \c Unique64Bit
   * (using the \c Value function) and then assigns it to the output variable.
   * Therefore it only works for the types that are supported by \c Unique64Bit.
   * The validity of copy operation is checked by \c IsCopyable. This module
   * is implemented so that some copy of advanced objects could work on the
   * base of this operation.
   *
   * @tparam T the type of output data
   *
   * @param v [out] the resultant \c T -type variable
   * @param P [in] the input \c Unique64Bit object
   */
  template <typename T>
  void _Copy(T& v,const Unique64Bit& P) {
    typedef typename IsCopyable<T,Unique64Bit>::Type  CopyCheck;
    v=Value<T>(P);
  }
  /** @fn void _Fill(Unique64Bit&,const T&)
   * @brief fill \c Unique64Bit object with \c T -type data
   *
   * It is implemented with \c Unique64Bit::Fill method. The definition
   * of this module provides common interface for fill operation, which
   * may be used in advanced fill operations (such as for \c Array).
   *
   * @tparam T the type of data which are used to carry out fill operation
   *
   * @param P [out] the \c Unique64Bit object to be filled
   * @param v [in] the \c T -type data to be filled with
   */
  template <typename T>
  void _Fill(Unique64Bit& P,const T& v) { P.Fill(v); }

}

#include <cstdio>

namespace mysimulator {

  /** @fn T& Value(Unique64Bit&)
   * @brief the function to get \c T -type data from \c Unique64Bit
   *
   * It is an interface to access and change the content of the \c T -type 
   * member in \c Unique64Bit. for the default case, a warning message
   * is created. the returned reference does not have any meaning.
   *
   * @tparam T the type of the output data
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference
   *                   of the member is returned, the is object may be changed.
   * @return the reference to internal data, this does not have any meaning
   *         and it is just used to match the format of function.
   */
  template <typename T>
  T& Value(Unique64Bit& P) {
    fprintf(stderr,"Unknown Type for Unique64Bit!\n");
    return static_cast<T&>(P.d);
  }
  /** @fn const T& Value(const Unique64Bit&)
   * @brief the function to get \c const \c T -type reference from \c Unique64Bit
   *
   * It is an interface to access the content of \c const \c T -type
   * member in \c Unique64Bit. for the default case, a warning message
   * is created. the returned \c const reference does not have any meaning.
   *
   * @tparam T the type of output data
   *
   * @param P [in] the input \c const \c Unique64Bit object
   * @return the \c const reference to internal data, this does not have any
   *         meaning and it is just used to match the format of function.
   */
  template <typename T>
  const T& Value(const Unique64Bit& P) {
    fprintf(stderr,"Unknown Type for Unique64Bit!\n");
    return static_cast<const T&>(P.d);
  }

}

/** @def _VValueDEF_
 * @brief the macro to define the function to get reference to specialized value
 *
 * To ease the definition of the specialization of the function to get
 * reference to certain type of value, this macro is used. It is implemented
 * through the value interface of \c Unique64Bit.
 *
 * @param T the expected type
 * @param v the value name of the concerned type in the \c union \c Unique64Bit
 */
#ifndef _VValueDEF_
#define _VValueDEF_(T,v) \
  template <> T& Value<T>(Unique64Bit& P) { return P.v; }
#else
#error "Duplicate _VValueDEF_"
#endif

/** @def _CValueDEF_
 * @brief the macro to define functions to get \c const reference to specialized value
 *
 * To ease the definition of the specialization of functions to get \c const
 * reference to certain type of value, thie macro is used. It is implemented
 * through the value interface of \c Unique64Bit.
 *
 * @param T the expected type
 * @param v the value name of the concerned type in the \c union \c Unique64Bit
 */
#ifndef _CValueDEF_
#define _CValueDEF_(T,v)  \
  template <> const T& Value<T>(const Unique64Bit& P) { return P.v; }
#else
#error "Duplicate _CValueDEF_"
#endif

/** @def _ValueDEF_
 * @brief the macro for functions to get specialized value
 *
 * This is a combination of two macros (\c _VValueDEF_ and \c _CValueDEF_ ).
 * This macro includes all the definitions related to the functions to get 
 * reference (or \c onnst reference) of specialized value.
 *
 * @param T the expected type
 * @param v the value name of the concerned type in the \c union \c Unique64Bit
 */
#ifndef _ValueDEF_
#define _ValueDEF_(T,v) \
  _VValueDEF_(T,v) _CValueDEF_(T,v)
#endif

namespace mysimulator {

  /** @fn double& Value<double>(Unique64Bit&)
   * @brief the function to get \c double reference from \c Unique64Bit
   *
   * It is an interface to access and change the content of the \c double
   * member in \c Unique64Bit. It just returns the reference to related member.
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference of the
   *                   member is returned, the is object may be changed.
   * @return the reference to the \c double value in \c Unique64Bit.
   */
  /** @fn const double& Value<double>(const Unique64Bit&)
   * @brief the function to get \c const \c double reference from \c Unique64Bit
   *
   * It is an interface to access the content of the \c double member in
   * \c Unique64Bit. It just returns the \c const  reference to related member.
   *
   * @param P [in] the input \c const \c Unique64Bit object.
   * @return the const reference to the \c double value in \c Unique64Bit.
   */
  _ValueDEF_(double,d)
  /** @fn float& Value<float>(Unique64Bit&)
   * @brief the function to get \c float reference from \c Unique64Bit
   *
   * It is an interface to access and change the content of the \c float
   * member in \c Unique64Bit. It just returns the reference to related member.
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference of the
   *                   member is returned, the is object may be changed.
   * @return the reference to the \c float value in \c Unique64Bit.
   */
  /** @fn const float & Value<float>(const Unique64Bit&)
   * @brief the function to get \c const \c float reference from \c Unique64Bit
   *
   * It is an interface to access the content of the \c float member in
   * \c Unique64Bit. It just returns the \c const  reference to related member.
   *
   * @param P [in] the input \c const \c Unique64Bit object.
   * @return the const reference to the \c float value in \c Unique64Bit.
   */
  _ValueDEF_(float,f)
  /** @fn long long& Value<long long>(Unique64Bit&)
   * @brief the function to get \c long \c long reference from \c Unique64Bit
   *
   * It is an interface to access and change the content of the \c long \c long
   * member in \c Unique64Bit. It just returns the reference to related member.
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference of the
   *                   member is returned, the is object may be changed.
   * @return the reference to the \c long \c long value in \c Unique64Bit.
   */
  /** @fn const long long& Value<long long>(const Unique64Bit&)
   * @brief the function to get \c const \c long \c long reference from \c Unique64Bit
   *
   * It is an interface to access the content of the \c long \c long member in
   * \c Unique64Bit. It just returns the \c const  reference to related member.
   *
   * @param P [in] the input \c const \c Unique64Bit object.
   * @return the const reference to the \c long \c long value in \c Unique64Bit.
   */
  _ValueDEF_(long long,ll)
  /** @fn unsigned long long& Value<unsigned long long>(Unique64Bit&)
   * @brief the function to get \c unsigned \c long \c long reference from \c Unique64Bit
   *
   * It is an interface to access and change the content of the \c unsigned \c long
   * \c long member in \c Unique64Bit. It just returns the reference to related
   * member.
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference of the
   *                   member is returned, the is object may be changed.
   * @return the reference to the \c unsigned \c long \c long value in
   *         \c Unique64Bit.
   */
  /** @fn const unsigned long long& Value<unsigned long long>(const Unique64Bit&)
   * @brief the function to get \c const \c unsigned \c long \c long reference from \c Unique64Bit
   *
   * It is an interface to access the content of the \c unsigned \c long \c long
   * member in \c Unique64Bit. It just returns the \c const  reference to related
   * member.
   *
   * @param P [in] the input \c const \c Unique64Bit object.
   * @return the const reference to the \c unsigned \c long \c long value in
   *         \c Unique64Bit.
   */
  _ValueDEF_(unsigned long long,ull)
  /** @fn int& Value<int>(Unique64Bit&)
   * @brief the function to get \c int reference from \c Unique64Bit
   *
   * It is an interface to access and change the content of the \c int
   * member in \c Unique64Bit. It just returns the reference to related member.
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference of the
   *                   member is returned, the is object may be changed.
   * @return the reference to the \c int value in \c Unique64Bit.
   */
  /** @fn const int& Value<int>(const Unique64Bit&)
   * @brief the function to get \c const \c int reference from \c Unique64Bit
   *
   * It is an interface to access the content of the \c int member in
   * \c Unique64Bit. It just returns the \c const  reference to related member.
   *
   * @param P [in] the input \c const \c Unique64Bit object.
   * @return the const reference to the \c int value in \c Unique64Bit.
   */
  _ValueDEF_(int,i)
  /** @fn unsigned int& Value<unsigned int>(Unique64Bit&)
   * @brief the function to get \c unsigned \c int reference from \c Unique64Bit
   *
   * It is an interface to access and change the content of the \c unsigned
   * \c int member in \c Unique64Bit. It just returns the reference to related
   * member.
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference of the
   *                   member is returned, the is object may be changed.
   * @return the reference to the \c unsigned \c int value in \c Unique64Bit.
   */
  /** @fn const unsigned int& Value<unsigned int>(const Unique64Bit&)
   * @brief the function to get \c const \c unsigned \c int reference from \c Unique64Bit
   *
   * It is an interface to access the content of the \c unsigned \c int member
   * in \c Unique64Bit. It just returns the \c const  reference to related
   * member.
   *
   * @param P [in] the input \c const \c Unique64Bit object.
   * @return the const reference to the \c unsigned \c int value in
   *         \c Unique64Bit.
   */
  _ValueDEF_(unsigned int,u)
  /** @fn long& Value<long>(Unique64Bit&)
   * @brief the function to get \c long reference from \c Unique64Bit
   *
   * It is an interface to access and change the content of the \c long
   * member in \c Unique64Bit. It just returns the reference to related member.
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference of the
   *                   member is returned, the is object may be changed.
   * @return the reference to the \c long value in \c Unique64Bit.
   */
  /** @fn const long& Value<long>(const Unique64Bit&)
   * @brief the function to get \c const \c long reference from \c Unique64Bit
   *
   * It is an interface to access the content of the \c long member in
   * \c Unique64Bit. It just returns the \c const  reference to related member.
   *
   * @param P [in] the input \c const \c Unique64Bit object.
   * @return the const reference to the \c long value in \c Unique64Bit.
   */
  _ValueDEF_(long,l)
  /** @fn unsigned long& Value<unsigned long>(Unique64Bit&)
   * @brief the function to get \c unsigned \c long reference from \c Unique64Bit
   *
   * It is an interface to access and change the content of the \c unsigned
   * \c long member in \c Unique64Bit. It just returns the reference to related
   * member.
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference of the
   *                   member is returned, the is object may be changed.
   * @return the reference to the \c unsigned \c long value in \c Unique64Bit.
   */
  /** @fn const unsigned long& Value<unsigned long>(const Unique64Bit&)
   * @brief the function to get \c const \c unsigned \c long reference from \c Unique64Bit
   *
   * It is an interface to access the content of the \c unsigned \c long member
   * in \c Unique64Bit. It just returns the \c const  reference to related
   * member.
   *
   * @param P [in] the input \c const \c Unique64Bit object.
   * @return the const reference to the \c unsigned \c long value in
   *         \c Unique64Bit.
   */
  _ValueDEF_(unsigned long,ul)
  /** @fn short& Value<short>(Unique64Bit&)
   * @brief the function to get \c short reference from \c Unique64Bit
   *
   * It is an interface to access and change the content of the \c short
   * member in \c Unique64Bit. It just returns the reference to related member.
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference of the
   *                   member is returned, the is object may be changed.
   * @return the reference to the \c short value in \c Unique64Bit.
   */
  /** @fn const short& Value<short>(const Unique64Bit&)
   * @brief the function to get \c const \c short reference from \c Unique64Bit
   *
   * It is an interface to access the content of the \c short member in
   * \c Unique64Bit. It just returns the \c const  reference to related member.
   *
   * @param P [in] the input \c const \c Unique64Bit object.
   * @return the const reference to the \c short value in \c Unique64Bit.
   */
  _ValueDEF_(short,s)
  /** @fn unsigned short& Value<unsigned short>(Unique64Bit&)
   * @brief the function to get \c unsigned \c short reference from \c Unique64Bit
   *
   * It is an interface to access and change the content of the \c unsigned
   * \c short member in \c Unique64Bit. It just returns the reference to related
   * member.
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference of the
   *                   member is returned, the is object may be changed.
   * @return the reference to the \c unsigned \c short value in \c Unique64Bit.
   */
  /** @fn const unsigned short& Value<unsigned short>(const Unique64Bit&)
   * @brief the function to get \c const \c unsigned \c short reference from \c Unique64Bit
   *
   * It is an interface to access the content of the \c unsigned \c short member
   * in \c Unique64Bit. It just returns the \c const  reference to related
   * member.
   *
   * @param P [in] the input \c const \c Unique64Bit object.
   * @return the const reference to the \c unsigned \c short value in
   *         \c Unique64Bit.
   */
  _ValueDEF_(unsigned short,us)
  /** @fn char& Value<char>(Unique64Bit&)
   * @brief the function to get \c char reference from \c Unique64Bit
   *
   * It is an interface to access and change the content of the \c char
   * member in \c Unique64Bit. It just returns the reference to related member.
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference of the
   *                   member is returned, the is object may be changed.
   * @return the reference to the \c char value in \c Unique64Bit.
   */
  /** @fn const char& Value<char>(const Unique64Bit&)
   * @brief the function to get \c const \c char reference from \c Unique64Bit
   *
   * It is an interface to access the content of the \c char member in
   * \c Unique64Bit. It just returns the \c const  reference to related member.
   *
   * @param P [in] the input \c const \c Unique64Bit object.
   * @return the const reference to the \c char value in \c Unique64Bit.
   */
  _ValueDEF_(char,c)
  /** @fn unsigned char& Value<unsigned char>(Unique64Bit&)
   * @brief the function to get \c unsigned \c char reference from \c Unique64Bit
   *
   * It is an interface to access and change the content of the \c unsigned
   * \c char member in \c Unique64Bit. It just returns the reference to related
   * member.
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference of the
   *                   member is returned, the is object may be changed.
   * @return the reference to the \c unsigned \c char value in \c Unique64Bit.
   */
  /** @fn const unsigned char& Value<unsigned char>(const Unique64Bit&)
   * @brief the function to get \c const \c unsigned \c char reference from \c Unique64Bit
   *
   * It is an interface to access the content of the \c unsigned \c char member
   * in \c Unique64Bit. It just returns the \c const  reference to related
   * member.
   *
   * @param P [in] the input \c const \c Unique64Bit object.
   * @return the const reference to the \c unsigned \c char value in
   *         \c Unique64Bit.
   */
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
   * @brief the function to get the member reference of \c T -type array from \c Unique64Bit
   *
   * This is an interface to access and change the content of the member
   * in the array of \c Unique64Bit object. For the default case, a warning
   * message is returned, and the returned reference does not have any
   * meaning.
   *
   * @tparam T the type of output data
   *
   * @param P [in,out] the input \c Unique64Bit object. Since the reference
   *                   of the member is returned, the is object may be changed.
   * @param n [in] the index of member in array
   * @return the reference to internal data. For this default case, the
   *         reference has no meanings.
   */
  template <typename T>
  T& Value(Unique64Bit& P, unsigned int n) {
    fprintf(stderr,"Unknown Type for Unique64Bit!\n");
    return static_cast<T&>(P.d);
  }

  /** @fn const T Value(const Unique64Bit&,unsigned int)
   * @brief the function to get the \c const member reference of \c T -type array in \c Unique64Bit
   *
   * This is an interface to access the content of the member in the array
   * of \c const \c Unique64Bit object. For the default case, a warning message
   * is returned, and the returned reference does not have any meaning.
   *
   * @tparam T the type of the output data
   *
   * @param P [in] the input \c const \c Unique64Bit object.
   * @param n [in] the index of member in array
   * @return the \c const reference to internal data. For this default case,
   *         the reference has not meaning.
   */
  template <typename T>
  const T& Value(const Unique64Bit& P, unsigned int n) {
    fprintf(stderr,"Unknown Type for Unique64Bit!\n");
    return static_cast<const T&>(P.d);
  }

}

#include <cassert>

/** @def _VValueDEF1_
 * @brief the macro to define the function to get reference to member of specialized array
 *
 * To ease the definition of the specialization of the function to get
 * reference to member of certain type of array, this macro is used.
 * It is implemented through the array interface of \c Unique64Bit.
 *
 * @param T the expected type
 * @param u the array name of the concerned type in the \c union \c Unique64Bit
 */
#ifndef _VValueDEF1_
#define _VValueDEF1_(T,u) \
  template <> T& Value<T>(Unique64Bit& P,unsigned int n) { \
    assert(n<sizeof(double)/sizeof(T)); \
    return P.u[n]; \
  }
#else
#error "Duplicate _VValueDEF1_"
#endif

/** @def _CValueDEF1_
 * @brief the macro to define the function to get \c const reference to member of specialized array
 *
 * To ease the definition of the specialization of the function to get \c const
 * reference to member of certain type of array in \c Unique64Bit, the macro is
 * defined. It is implemented through the array interface of \c Unique64Bit.
 *
 * @param T the expected type
 * @param u the array name of the concerned type in the \c union \c Unique64Bit
 */
#ifndef _CValueDEF1_
#define _CValueDEF1_(T,u) \
  template <> const T& Value<T>(const Unique64Bit& P,unsigned int n) { \
    assert(n<sizeof(double)/sizeof(T)); \
    return P.u[n]; \
  }
#else
#error "Duplicate _CValueDEF1_"
#endif

/** @def _ValueDEF1_
 */
#ifndef _ValueDEF1_
#define _ValueDEF1_(T,u) \
  _VValueDEF1_(T,u)   _CValueDEF1_(T,u)
#else
#error "Duplicate _ValueDEF1_"
#endif

namespace mysimulator {

  _ValueDEF1_(double,dv)
  _ValueDEF1_(float,fv)
  _ValueDEF1_(long long,llv)
  _ValueDEF1_(unsigned long long,ullv)
  _ValueDEF1_(int,iv)
  _ValueDEF1_(unsigned int,uv)
  _ValueDEF1_(long,lv)
  _ValueDEF1_(unsigned long,ulv)
  _ValueDEF1_(short,sv)
  _ValueDEF1_(unsigned short,usv)
  _ValueDEF1_(char,cv)
  _ValueDEF1_(unsigned char, ucv)

}

#ifdef _ValueDEF1_
#undef _ValueDEF1_
#endif

#ifdef _CValueDEF1_
#undef _CValueDEF1_
#endif

#ifdef _VValueDEF1_
#undef _VValueDEF1_
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

