
/**
 * @brief utility programs
 * @file util.h
 *
 * This file contans the procedures for various utilities.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Utility_H_
#define _Utility_H_

#include <cstdlib>
#include <cctype>

namespace std {

  /**
   * @brief nullify an integer
   *
   * Just assign with a zero-value integer. It is explicitly inline.
   *
   * @param [in,out] I The integer varible to nullify
   * @return nothing.
   */
  inline void Nullify(int& I) { I=0; }

  /**
   * @brief nullify an unsigned integer
   *
   * Just assign with a zero-value unsigned integer. It is explicitly inline.
   *
   * @param [in,out] I The unsigned integer varible to nullify
   * @return nothing.
   */
  inline void Nullify(unsigned int& I) { I=0U; }

  /**
   * @brief nullify a double
   *
   * Just assign with a zero-value double. It is explicitly inline.
   *
   * @param [in,out] D The double varible to nullify
   * @return nothing.
   */
  inline void Nullify(double& D) { D=0.; }

  /**
   * @brief compare two intergers
   *
   * Compare two integers and give out the information about their relation
   *
   * @param [in] I,J two integers for comparison
   * @return positive 1 when the first number is larger, negative 1 when
   *         it is smaller,and zero for equal case.
   */
  inline int compare(const int I, const int J) { return (I<J?-1:(I>J?1:0)); }

  /**
   * @brief compare two doubles 
   *
   * Compare two doubles and give out the information about their relation
   *
   * @param [in] DI,DJ two doubles for comparison
   * @return positive 1 when the first number is larger, negative 1 when
   *         it is smaller,and zero for equal case.
   */
  inline int compare(const double DI, const double DJ){
    return DI<DJ?-1:(DI>DJ?1:0);
  }

  /**
   * @brief convert a string to upper case
   *
   * The characters in an input string is converted to their upper case.
   * The resultant string is stored in another string. The input string
   * is kept untouched.
   *
   * @param [out] dest the string containing the output
   * @param [in] src the string containing the input
   * @param [n] n the number of characters in input string
   * @return nothing
   * @note only the first n string is converted. The user should be
   *       responsible for the validity of the sizes of two concerned strings.
   * @note The terminal character \\0 of string is not used or assigned. Be
   *       careful when using the output string.
   */
  inline void toupper(char* dest, const char* src, const unsigned int n) {
    for(unsigned int i=0;i<n;++i) dest[i]=static_cast<char>(toupper(src[i]));
  }
  /**
   * @brief convert a string to lower case
   *
   * The characters in an input string is converted to their lower case.
   * The resultant string is stored in another string. The input string
   * is kept untouched.
   *
   * @param [out] dest the string containing the output
   * @param [in] src the string containing the input
   * @param [n] n the number of characters in input string
   * @return nothing
   * @note only the first n string is converted. The user should be
   *       responsible for the validity of the sizes of two concerned strings.
   * @note The terminal character \\0 of string is not used or assigned. Be
   *       careful when using the output string.
   */
  inline void tolower(char* dest, const char* src, const unsigned int n) {
    for(unsigned int i=0;i<n;++i) dest[i]=static_cast<char>(tolower(src[i]));
  }

  /**
   * @brief swap two arrays of T-type data
   *
   * Just swap the pointers (rather than the content). This is a generic
   * and efficient form for swapping operation.
   *
   * T is the type of data in concerned arrays.
   *
   * @param [in,out] a,b The pointers to the arrays to swap.
   * @return nothing
   * @note The temporary pointer is assigned as NULL finally to avoid
   *       unexpected running of the destructor of T-type object.
   */
  template <typename T>
  inline void swap(T*& a, T*& b) { T* t; t=a; a=b; b=t; t=NULL; }

  /**
   * @brief swap two unsigned integers
   *
   * Just swap the content since this is a simple data type.
   *
   * @param [in,out] a,b two unsigned integers
   * @return nothing
   */
  inline void swap(unsigned int& a, unsigned int& b) {
    unsigned int t=a; a=b; b=t;
  }

  /**
   * @brief swap two doubles
   *
   * Just swap the content since this is a simple data type.
   *
   * @param [in,out] a,b two doubles
   * @return nothing
   */
  void swap(double& a, double& b) { double t=a; a=b; b=t; }

  /**
   * @brief swap two integers
   *
   * Just swap the content since this is a simple data type.
   *
   * @param [in,out] a,b two integers
   * @return nothing
   */
  void swap(int& a, int& b) { int t=a; a=b; b=t; }

  /**
   * @brief check if a pointer is available
   *
   * Just check if the concerned pointer is NULL. It is the basic to check
   * validity of other objects in this package.
   *
   * T is any type.
   *
   * @param [in] ptr The pointer to be checked
   * @return true when the pointer is not NULL, false otherwise
   * @note it is the responsibility of user to nullify the useless pointers
   */
  template <typename T>
  inline bool IsAvailable(const T* ptr) { return ptr!=NULL; }

  /**
   * @brief check if the concerned object is geometry-related
   *
   * Just return false for generic objects. This is used for compatibility
   * to use this check.
   *
   * T is any type.
   *
   * @param [in] t The reference of T-type object.
   * @return false value
   *
   * @note This function should be explicitly declared for geomtry-related
   *       objects.
   */
  template <typename T>
  inline bool IsGeometry(const T& t) { return false; }

  /**
   * @brief check if the concerned object is random number generator
   *
   * Just return false for generic objects. This is used for compatibility
   * to use this check.
   *
   * T is any type.
   *
   * @param [in] t The reference of T-type object.
   * @return false value
   *
   * @note This function should be explicitly declared for random number
   *       generators
   */
  template <typename T>
  inline bool IsRandomGenerator(const T& t) { return false; }

  /**
   * @brief assign double with double value
   *
   * This is introduced for compatibility of assign operations.
   * It just assigns the input value to the output variable.
   *
   * @param [out] dest The reference to output double variable
   * @param [in] src the input double value
   * @return nothing
   */
  void assign(double& dest, const double src) { dest=src; }

  /**
   * @brief assign unsigned int with unsigned int value
   *
   * This is introduced for compatibility of assign operations.
   * It just assigns the input value to the output variable.
   *
   * @param [out] dest The reference to output unsigned int variable
   * @param [in] src the input unsigned int value
   * @return nothing
   */
  void assign(unsigned int& dest, const unsigned int src) { dest=src; }

  /**
   * @brief assign int with int value
   *
   * This is introduced for compatibility of assign operations.
   * It just assigns the input value to the output variable.
   *
   * @param [out] dest The reference to output int variable
   * @param [in] src the input int value
   * @return nothing
   */
  void assign(int& dest, const int src) { dest=src; }

  /**
   * @brief shift double variable
   *
   * This is introduced for compatibility of shift operations.
   * It adds the product of other two factors into the output variable.
   *
   * @param [out] dest The reference to output double variable
   * @param [in] fac,src The double values related to this operation.
   * @return nothing
   */
  void shift(double& dest, const double fac, const double src) {
    dest+=fac*src;
  }

  /**
   * @brief shift unsigned int variable
   *
   * This is introduced for compatibility of shift operations.
   * It adds the product of other two factors into the output variable.
   *
   * @param [out] dest The reference to output unsigned int variable
   * @param [in] fac,src The unsigned int values related to this operation.
   * @return nothing
   */
  void shift(unsigned int& dest, const unsigned int fac,
             const unsigned int src) {
    dest+=fac*src;
  }

  /**
   * @brief shift int variable
   *
   * This is introduced for compatibility of shift operations.
   * It adds the product of other two factors into the output variable.
   *
   * @param [out] dest The reference to output int variable
   * @param [in] fac,src The int values related to this operation.
   * @return nothing
   */
  void shift(int& dest, const int fac, const int src) { dest+=fac*src; }

  /**
   * @brief dot product between two double values
   *
   * This is introduced for compatibility of dot operations.
   * This just gives out the regular product of two values.
   *
   * @param [in] a,b the input double values
   * @return the product of input values
   */
  double dot(const double a, const double b) { return a*b; }

  /**
   * @brief dot product between two unsigned int values
   *
   * This is introduced for compatibility of dot operations.
   * This just gives out the regular product of two values.
   *
   * @param [in] a,b the input unsigned int values
   * @return the product of input values
   */
  unsigned int dot(const unsigned int a, const unsigned int b) { return a*b; }

  /**
   * @brief dot product between two int values
   *
   * This is introduced for compatibility of dot operations.
   * This just gives out the regular product of two values.
   *
   * @param [in] a,b the input int values
   * @return the product of input values
   */
  int dot(const int a, const int b) { return a*b; }

  /**
   * @brief update double-type parameter
   *
   * This is introduced for compatibility of updateParameter in
   * minimization. It does nothing here.
   *
   * @param [in,out] p the double-type parameter
   * @return nothing
   */
  inline void updateParameter(double& p) {}

  /**
   * @brief update unsigned-int-type parameter
   *
   * This is introduced for compatibility of updateParameter in
   * minimization. It does nothing here.
   *
   * @param [in,out] p the unsigned-int-type parameter
   * @return nothing
   */
  inline void updateParameter(unsigned int& p) {}

  /**
   * @brief update int-type parameter
   *
   * This is introduced for compatibility of updateParameter in
   * minimization. It does nothing here.
   *
   * @param [in,out] p the int-type parameter
   * @return nothing
   */
  inline void updateParameter(int& p) {}

}

#endif

