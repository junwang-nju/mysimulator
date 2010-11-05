
/**
 * @file unique-parameter.h
 * @brief data with many interfaces
 *
 * This file defines a data structure with various interfaces. That is
 * various kinds of data can be stored in one object. It includes
 * the intrinsic data type now and is implemented with union.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Unique_Parameter_H_
#define _Unique_Parameter_H_

#include "error-proc.h"
#include <cstdlib>
#include <cctype>

namespace std {

  /**
   * @brief object with various interface
   *
   * This object encapsulates the double, unsigned int, int, unsigned long
   * long int, and pointer types with same storage. it is implemented with
   * union to enable storage sharing. This object enables the storage of
   * various kinds of data in one array.
   */
  union UniqueParameter {

    /**
     * @brief double interface
     */
    double d;
    /**
     * @brief unsigned int interface
     */
    unsigned int u;
    /**
     * @brief integer interface
     */
    int i;
    /**
     * @brief unsigned long long int interface
     *
     * This kind of data has the same size as double data. It is used for
     * precise storage and importing of internal data.
     */
    unsigned long long int ull;
    /**
     * @brief pointer interface
     *
     * This interface is used as the entrance of complex data object.
     */
    void *ptr;

    /**
     * @brief abbreviation for unique-parameter object
     */
    typedef UniqueParameter Type;

    /**
     * @brief default initiator
     *
     * initialize all the bits as zero through \c unsigned \c long \c long
     * interface.
     */
    UniqueParameter() : ull(0) {}
    
    /**
     * @brief initiator from another UniqueParameter object
     *
     * This is prohibited and pop-up an error message.
     *
     * @param UP [in] the input UniqueParameter object.
     */
    UniqueParameter(const Type& UP) {
      myError("Cannot create from Unique Parameter");
    }
    
    /**
     * @brief copy from another UniqueParameter object
     *
     * Just copy the internal data of input UniqueParameter object through
     * \c unsigned \c long \c long interface. This enables the precise copy
     * of all information.
     *
     * @param UP [in] the input UniqueParameter object
     * @return the reference to the resultant UniqueParameter object
     */
    Type& operator=(const Type& UP) { ull=UP.ull; return *this; }
    
    /**
     * @brief copy from a \c double value
     *
     * copy through \c double interface.
     *
     * @param dv [in] the input \c double value
     * @return the reference to the resultant UniqueParameter object
     */
    Type& operator=(const double dv) { d=dv; return *this; }
    
    /**
     * @brief copy from a pointer
     *
     * The const flag of input pointer is firstly removed through const_cast.
     * Then, it is copied into object through pointer interface. An implicit
     * conversion to void pointer is used.
     *
     * T is the type of data that the pointer points to.
     *
     * @param tptr [in] the input pointer to T-type data
     * @return the reference to the resultant UniqueParameter object
     */
    template <typename T>
    Type& operator=(const T* tptr) { ptr=const_cast<T*>(tptr); return *this; }
    
    /**
     * @brief copy from an \c unsigned \c int value
     *
     * copy through \c unsigned \c int interface.
     *
     * @param uv [in] the input \c unsigned \c int value
     * @return the reference to the resultant UniqueParameter object
     */
    Type& operator=(const unsigned int uv) { u=uv; return *this; }

    /**
     * @brief copy from an \c int value
     *
     * copy through \c int interface.
     *
     * @param iv [in] the input \c int value
     * @return the reference to the resultant UniqueParameter object
     */
    Type& operator=(const int iv) { i=iv; return *this; } 

    /**
     * @brief access content as \c double variable
     *
     * This is a method to access content as double-type value.
     *
     * @return the reference to the content as \c double value.
     * @note \c double type is the most used case in simulations. 
     *       It is the reason to define this method.
     */
    double& operator()() { return d; }

    /**
     * @brief visit content as \c double value
     *
     * This is a method to visit content as double-type value.
     *
     * @return the const reference to the content as \c double value
     * @note This is const version of the method to access the
     *       content of UniqueParameter object.
     */
    const double& operator()() const { return d; }

  };

  /**
   * @brief read a UniqueParameter object from istream
   *
   * Since the UniqueParameter object may store multiple types of data,
   * a flag indicating the type of data is read at first. Then, based
   * on the type, the data is imported. For unknown types, a failbit
   * is produced. Here, D(d) means \c double, U(u) means \c unsigned
   * \c int, I(i) indicates \c int, and P(p) gives pointer. If there
   * are no flags, the data would be regarded as \c unsigned \c long
   * \c long \c int when the import content is a number. Otherwise,
   * errors would be produced.
   *
   * @param is [in,out] the istream object, which would be accessed and
   *                    altered during the reading
   * @param UP [out] the UniqueParameter object storing the data
   * @return the istream after reading.
   */
  istream& operator>>(istream& is, UniqueParameter& UP) {
    static char flag;
    is>>flag;
    if((flag=='D')||(flag=='d'))  is>>UP.d;
    else if((flag=='U')||(flag=='u')) is>>UP.u;
    else if((flag=='I')||(flag=='i')) is>>UP.i;
    else if((flag=='P')||(flag=='p')) is>>UP.ptr;
    else if(isdigit(flag)||(flag=='+')) {
      is.unget();
      is>>UP.ull;
    }
    else is.setstate(ios_base::failbit);
    return is;
  }

  /**
   * @brief write a UniqueParameter object to ostream
   *
   * Just write out the \c unsigned \c long \c long \c int interface
   * as output to keep all bit information.
   *
   * @param os [in,out] the ostream object which would be changed
   *                    after output operation.
   * @param UP [in] the UniqueParameter object to be output.
   * @return the ostream object after output.
   */
  ostream& operator<<(ostream& os, const UniqueParameter& UP) {
    os<<UP.ull;
    return os;
  }

}

#endif

