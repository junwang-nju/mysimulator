
/**
 * @file type/is-included.h
 * @brief checking if the range of one type can cover that of another type
 *
 * In many operations, we need to check if the range of one type is larger
 * than (thus could cover) the range of another type. This information could
 * help to derive types after the calculations between these types. This
 * file implements the objects related to this purpose.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsIncluded_H_
#define _Type_IsIncluded_H_

namespace mysimulator {

  /** @class IsIncludedFlag
   * @brief the class to produce a flag indicating inclusion relation
   *
   * This class contains a flag, which indicates the inclusion relation
   * between two input types. This is the basic component to evaluate
   * the inclusion relation between types.
   *
   * @tparam T1 the input type which is larger when the inclusion relation
   *            is \c true
   * @tparam T2 the input type which is smaller when the inclusion relation
   *            is \c true
   */
  template <typename T1, typename T2>
  class IsIncludedFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating the relation of input types
       *
       * When the range of \c T1 is larger than the range of \c T2, the
       * flag would be set as \c true, otherwise \c false.
       */
      static const bool Flag;
  };

  /** @var IsIncludedFlag::Flag
   *
   * The default flag is set as \c false.
   */
  template <typename T1, typename T2>
  const bool IsIncludedFlag<T1,T2>::Flag=false;

}

/** @def _IncDEF_
 *
 * To ease the specialization of the class \c IsIncludedFlag, this macro
 * is implemented for the specialized class and the corresponding flags.
 * Since the relation cannot be derived based on simple logic, here we
 * enumerate the possible combinations as specializations.
 * These specialized classes are defined as to fit the requirement of
 * present version of doxygen.
 *
 * @param T1 the first input type which is regular larger
 * @param T2 the second input type which is regularly smaller
 */
#ifndef _IncDEF_
#define _IncDEF_(T1,T2) \
  template <> class IsIncludedFlag<T1,T2> { public: static const bool Flag; }; \
  const bool IsIncludedFlag<T1,T2>::Flag=true;
#else
#error "Duplicate _IncDEF_"
#endif

namespace mysimulator {

  /** @var IsIncludedFlag<long double,double>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c long \c double is
   * larger that \c double
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c long \c double and \c double
   *
   * This is a specialization of \c IsIncludedFlag for types of \c long
   * \c double and \c double. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(long double, double)
  /** @var IsIncludedFlag<long double,float>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c long \c double is
   * larger that \c float
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c long \c double and \c float
   *
   * This is a specialization of \c IsIncludedFlag for types of \c long
   * \c double and \c float. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(long double, float)
  /** @var IsIncludedFlag<long double,long long>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c long \c double is
   * larger that \c long \c long
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c long \c double and \c long \c long
   *
   * This is a specialization of \c IsIncludedFlag for types of \c long
   * \c double and \c long \c long. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(long double, long long)
  /** @var IsIncludedFlag<long double,unsigned long long>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c long \c double is
   * larger that \c unsigned \c long \c long
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c long \c double and \c unsigned \c long \c long
   *
   * This is a specialization of \c IsIncludedFlag for types of \c long
   * \c double and \c unsigned \c long \c long. The definition of the
   * specialized class is used for the the implementation of documents
   * related to the specialized member.
   */
  _IncDEF_(long double, unsigned long long)
  /** @var IsIncludedFlag<long double,int>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c long \c double is
   * larger that \c int
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c long \c double and \c int
   *
   * This is a specialization of \c IsIncludedFlag for types of \c long
   * \c double and \c int. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(long double, int)
  /** @var IsIncludedFlag<long double,unsigned int>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c long \c double is
   * larger that \c unsigned \c int
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c long \c double and \c unsigned \c int
   *
   * This is a specialization of \c IsIncludedFlag for types of \c long
   * \c double and \c unsigned \c int. The definition of the specialized class
   * is used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(long double, unsigned int)
  /** @var IsIncludedFlag<long double,long>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c long \c double is
   * larger that \c long
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c long \c double and \c long
   *
   * This is a specialization of \c IsIncludedFlag for types of \c long
   * \c double and \c long. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(long double, long)
  /** @var IsIncludedFlag<long double,unsigned long>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c long \c double is
   * larger that \c unsigned \c long
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c long \c double and \c unsigned \c long
   *
   * This is a specialization of \c IsIncludedFlag for types of \c long
   * \c double and \c unsigned \c long. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(long double, unsigned long)
  /** @var IsIncludedFlag<long double,short>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c long \c double is
   * larger that \c short
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c long \c double and \c short
   *
   * This is a specialization of \c IsIncludedFlag for types of \c long
   * \c double and \c short. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(long double, short)
  /** @var IsIncludedFlag<long double,unsigned short>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c long \c double is
   * larger that \c unsigned \c short
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c long \c double and \c unsigned \c short
   *
   * This is a specialization of \c IsIncludedFlag for types of \c long
   * \c double and \c unsigned \c short. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(long double, unsigned short)
  /** @var IsIncludedFlag<long double,char>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c long \c double is
   * larger that \c char
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c long \c double and \c char
   *
   * This is a specialization of \c IsIncludedFlag for types of \c long
   * \c double and \c char. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(long double, char)
  /** @var IsIncludedFlag<long double,unsigned char>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c long \c double is
   * larger that \c unsigned \c char
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c long \c double and \c unsigned \c char
   *
   * This is a specialization of \c IsIncludedFlag for types of \c long
   * \c double and \c unsigned \c char. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(long double, unsigned char)

  /** @var IsIncludedFlag<double,float>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c double is
   * larger that \c float
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c double and \c float
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c double and \c float. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(double, float)
  /** @var IsIncludedFlag<double,long long>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c double is
   * larger that \c long \c long
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c double and \c long \c long
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c double and \c long \c long. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(double, long long)
  /** @var IsIncludedFlag<double,unsigned long long>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c double is
   * larger that \c unsigned \c long \c long
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c double and \c unsigned \c long \c long
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c double and \c unsigned \c long \c long. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(double, unsigned long long)
  /** @var IsIncludedFlag<double,int>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c double is
   * larger that \c int
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c double and \c int
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c double and \c int. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(double, int)
  /** @var IsIncludedFlag<double,unsigned int>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c double is
   * larger that \c unsigned \c int
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c double and \c unsigned \c int
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c double and \c unsigned \c int. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(double, unsigned int)
  /** @var IsIncludedFlag<double,long>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c double is
   * larger that \c long
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c double and \c long
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c double and \c long. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(double, long)
  /** @var IsIncludedFlag<double,unsigned long>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c double is
   * larger that \c unsigned \c long
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c double and \c unsigned \c long
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c double and \c unsigned \c long. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(double, unsigned long)
  /** @var IsIncludedFlag<double,short>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c double is
   * larger that \c short
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c double and \c short
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c double and \c short. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(double, short)
  /** @var IsIncludedFlag<double,unsigned short>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c double is
   * larger that \c unsigned \c short
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c double and \c unsigned \c short
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c double and \c unsigned \c short. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(double, unsigned short)
  /** @var IsIncludedFlag<double,char>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c double is
   * larger that \c char
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c double and \c char
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c double and \c char. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(double, char)
  /** @var IsIncludedFlag<double,unsigned char>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c double is
   * larger that \c unsigned \c char
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c double and \c unsigned \c char
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c double and \c unsigned \c char. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(double, unsigned char)

  _IncDEF_(float, long long)
  _IncDEF_(float, unsigned long long)
  /** @var IsIncludedFlag<float,int>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c floatis
   * larger that \c int
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c floatand \c int
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c floatand \c int. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(float, int)
  _IncDEF_(float, unsigned int)
  /** @var IsIncludedFlag<float,long>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c floatis
   * larger that \c long
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c floatand \c long
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c floatand \c long. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(float, long)
  _IncDEF_(float, unsigned long)
  /** @var IsIncludedFlag<float,short>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c floatis
   * larger that \c short
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c floatand \c short
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c floatand \c short. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(float, short)
  _IncDEF_(float, unsigned short)
  /** @var IsIncludedFlag<float,char>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c floatis
   * larger that \c char
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c floatand \c char
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c floatand \c char. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(float, char)
  /** @var IsIncludedFlag<float,unsigned char>::Flag
   * @brief the static flag indicating the relation of input types
   *
   * This takes the value \c true, indicating \c floatis
   * larger that \c unsigned \c char
   */
  /**
   * @brief the specialization of \c IsIncludedFlag for \c floatand \c unsigned \c char
   *
   * This is a specialization of \c IsIncludedFlag for types of 
   * \c floatand \c unsigned \c char. The definition of the specialized class is
   * used for the the implementation of documents related to the specialized
   * member.
   */
  _IncDEF_(float, unsigned char)

  _IncDEF_(long long, int)
  _IncDEF_(long long, unsigned int)
  _IncDEF_(long long, long)
  _IncDEF_(long long, unsigned long)
  _IncDEF_(long long, short)
  _IncDEF_(long long, unsigned short)
  _IncDEF_(long long, char)
  _IncDEF_(long long, unsigned char)

  _IncDEF_(unsigned long long, unsigned int)
  _IncDEF_(unsigned long long, unsigned long)
  _IncDEF_(unsigned long long, unsigned short)
  _IncDEF_(unsigned long long, unsigned char)

  _IncDEF_(int, long)
  _IncDEF_(int, short)
  _IncDEF_(int, unsigned short)
  _IncDEF_(int, char)
  _IncDEF_(int, unsigned char)

  _IncDEF_(unsigned int, unsigned long)
  _IncDEF_(unsigned int, unsigned short)
  _IncDEF_(unsigned int, unsigned char)

  _IncDEF_(long, int)
  _IncDEF_(long, short)
  _IncDEF_(long, unsigned short)
  _IncDEF_(long, char)
  _IncDEF_(long, unsigned char)

  _IncDEF_(unsigned long, unsigned int)
  _IncDEF_(unsigned long, unsigned short)
  _IncDEF_(unsigned long, unsigned char)

  _IncDEF_(short, char)
  _IncDEF_(short, unsigned char)

  _IncDEF_(unsigned short, unsigned char)

}

#ifdef _IncDEF_
#undef _IncDEF_
#endif

namespace mysimulator {

  template <typename T>
  class IsIncludedFlag<T,T> {
    public:
      /** @var Flag
       */
      static const bool Flag;
  };

  /** @var IsIncludedFlag<T,T>::Flag
   */
  template <typename T>
  const bool IsIncludedFlag<T,T>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  /** @class IsIncluded
   */
  template <typename T1,typename T2>
  class IsIncluded {
    public:
      /** @typedef Type
       */
      typedef typename Check<IsIncludedFlag<T1,T2>::Flag>::Type   Type;
  };

}

#endif

