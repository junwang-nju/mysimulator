
/**
 * @file random-generator-boxmuller.h
 * @brief random generator with Box-Muller method
 *
 * This file gives the random generator with gaussian distribution which is
 * implemented using Box-Muller Method.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Random_Generator_BoxMuller_H_
#define _Random_Generator_BoxMuller_H_

#include <cmath>
#include "error-proc.h"
#include "memory.h"
#include "storage-state-name.h"
#include "random-generator-uniform.h"

namespace std {

  /**
   * @brief random generator with Box-Muller method
   *
   * This is a random generator to generate random numbers with gaussian
   * distribution. This generator uses the box-muller method, which is the
   * most popular method to produce gaussian-distributed random numbers.
   * Only \c double value output is produced in this generator. 
   *
   * UniformRNG is the type of the random generator producing numbers with
   * uniform distribution
   */
  template <typename UniformRNG>
  struct BoxMuller {

    /**
     * @brief abbreviation for random generator with Box-Muller method
     */
    typedef BoxMuller<UniformRNG>   Type;

    /**
     * @brief the pointer to the random generator with uniform distribution
     */
    UniformRNG *urng;
    /**
     * @brief the array containing \c double factor
     */
    double *DbFac;
    /**
     * @brief the pointer to the flag indicating if the second value is used
     */
    bool *isSecond;
    /**
     * @brief the pointer to the \c double value for output
     */
    double *output;
    /**
     * @brief the flag indicating the storage state of this object
     */
    unsigned int state;

    /**
     * @brief default initiator
     *
     * Just initiate the pointers with NULL and the state with Unused flag.
     */
    BoxMuller()
      : urng(NULL), DbFac(NULL), isSecond(NULL), output(NULL), state(Unused) {}
    /**
     * @brief initiator from another BoxMuller generator
     *
     * It is prohibited and pops up an error message
     *
     * @param BM [in] the input BoxMuller generator
     */
    BoxMuller(const Type& BM) { myError("Cannot create from BoxMuller"); }

    /**
     * @brief copy from another BoxMuller generator
     *
     * It is implemented with assign operation.
     *
     * @param BM [in] the input BoxMuller generator
     * @return the reference to the resultant BoxMuller generator
     */
    Type& operator=(const Type& BM) { assign(*this,BM); return *this; }

    /**
     * @brief destructor
     *
     * It is implemented with release operation
     */
    ~BoxMuller() { release(*this); }

    /**
     * @brief initialize the generator with a \c unsigned \c int seed
     *
     * It is implemented with the init operation.
     *
     * @param seed [in] the \c unsigned \c int as the seed
     * @return nothing
     */
    void Init(const unsigned  int seed) { init(*this,seed); }

    /**
     * @brief produce a \c double number with normal distribution
     *
     * This is the core part of the generator. It uses box-muller method.
     * It is a combination of the inverse method and the trial method.
     * The resultant number follows the gaussian distribution with
     * zero average and unit variance.
     *
     * @return the \c double number of gaussian distribution
     */
    const double& DoubleNormal() {
      if(*isSecond) *output=DbFac[1]*DbFac[2];
      else {
        do {
          DbFac[0]=rand<double>(*urng);  DbFac[0]+=DbFac[0]; DbFac[0]-=1.;
          DbFac[1]=rand<double>(*urng);  DbFac[1]+=DbFac[1]; DbFac[1]-=1.;
          DbFac[2]=DbFac[0]*DbFac[0]+DbFac[1]*DbFac[1];
        } while( (DbFac[2]>1.) || (DbFac[2]==0.) );
        DbFac[2]=sqrt(-2.0*log(DbFac[2])/DbFac[2]);
        *output=DbFac[0]*DbFac[2];
      }
      *isSecond=!(*isSecond);
      return *output;
    }

  };

  /**
   * @brief check if the storage of the generator is available
   *
   * It is implemented by checking the availability of the
   * pointer to the internal random generator with uniform generator.
   *
   * UniformRNG is the type of the generator with uniform distribution.
   *
   * @param bm [in] the random generator with gaussian distribution to be
   *                checked
   * @return the flag indicating the availability of input generator
   */
  template <typename UniformRNG>
  bool IsAvailable(const BoxMuller<UniformRNG>& bm) {
    return IsAvailable(bm.urng);
  }
  
  /**
   * @brief check if this object is random generator
   *
   * The BoxMuller object is definitely a random generator
   *
   * UniformRNG is the type of the generator with uniform distribution.
   *
   * @param bm [in] the input BoxMuller generator
   * @return true flag indicating BoxMuller generator is a random generator
   */
  template <typename UniformRNG>
  bool IsRandomGenerator(const BoxMuller<UniformRNG>& bm) { return true; }

  /**
   * @brief allocate BoxMuller generator
   *
   * It is implemented by allocating each component and set the state flag
   * as Allocated. It would be released before this operation.
   * This would avoid the dual allocation for storage.
   *
   * UniformRNG is the type of the generator with uniform distribution.
   *
   * @param BM [in,out] the BoxMuller generator to be allocated
   * @return nothing
   */
  template <typename UniformRNG>
  void allocate(BoxMuller<UniformRNG>& BM) {
    release(BM);
    BM.urng=new UniformRNG;
    allocate(*BM.urng);
    BM.DbFac=new double[3];
    BM.isSecond=new bool;
    BM.output=new double;
    BM.state=Allocated;
    *BM.isSecond=true;
  }

  /**
   * @brief release BoxMuller generator
   *
   * The internal storages are released when the state flag is Allocated.
   * Otherwise, the pointers are nullified. The flag is set as Unused.
   *
   * UniformRNG is the type of the generator with uniform distribution.
   *
   * @param BM [out] the BoxMuller generator to be released
   * @return nothing
   */
  template <typename UniformRNG>
  void release(BoxMuller<UniformRNG>& BM) {
    if(BM.state==Allocated) {
      safe_delete(BM.urng);
      safe_delete_array(BM.DbFac);
      safe_delete(BM.isSecond);
      safe_delete(BM.output);
    } else {
      BM.urng=NULL;
      BM.DbFac=NULL;
      BM.isSecond=NULL;
      BM.output=NULL;
    }
    BM.state=Unused;
  }

  /**
   * @brief refer to another BoxMuller generator
   *
   * it is implemented by assigning pointers in dest object with those
   * in src object. The src generator is checked for its availability.
   * The dest object is released before refer operation to avoid dual
   * allocation of pointers.
   *
   * UniformRNG is the type of generator with uniform distribution.
   *
   * @param dest [out] the BoxMuller generator to accept the input
   * @param src [in] the BoxMuller generator to store the input
   * @return nothing
   */
  template <typename UniformRNG>
  void refer(BoxMuller<UniformRNG>& dest, const BoxMuller<UniformRNG>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.urng=src.urng;
    dest.DbFac=src.DbFac;
    dest.isSecond=src.isSecond;
    dest.output=src.output;
    dest.state=Reference;
  }

  /**
   * @brief assign BoxMuller object from another
   *
   * It is implemented by copy internal generator with uniform distribution
   * and some factors. The concerned dest and src objects are checked before
   * this operation.
   *
   * UniformRNG is the type of generator with uniform distribution.
   *
   * @param dest [out] the BoxMuller generator to accept the input
   * @param src [in] the BoxMuller generator to store the input
   * @return nothing
   */
  template <typename UniformRNG>
  void assign(BoxMuller<UniformRNG>& dest, const BoxMuller<UniformRNG>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(dest.urng,src.urng);
    assign(dest.DbFac,src.DbFac,3);
    *(dest.isSecond)=*(src.isSecond);
  }

  /**
   * @brief initiate a BoxMuller generator with a seed
   *
   * It is implemented by initializing the internal generator with uniform
   * distribution with the input seed. The output flag is also assigned.
   * The concerned BoxMuller object is checked before this operation.
   *
   * UniformRNG is the type of generator with uniform distribution.
   *
   * @param bm [in,out] the BoxMuller object to be initialized
   * @param seed [in] the \c unsigned \c int number as the seed
   * @return nothing
   */
  template <typename UniformRNG>
  void init(BoxMuller<UniformRNG>& bm, const unsigned int seed) {
    assert(IsAvailable(bm));
    init(*bm.urng,seed);
    *bm.isSecond=false;
  }

  /**
   * @brief generate \c double random number
   *
   * This function generates the \c double random number with gaussian
   * distribution. It is implemented with the method of generator.
   *
   * UniformRNG is the type of generator with uniform distribution
   *
   * @param bm [in,out] the BoxMuller generator to produce random number
   * @return the random number following the gaussian distribution
   */ 
  template <typename UniformRNG>
  const double& rand(BoxMuller<UniformRNG>& bm) { return bm.DoubleNormal(); }

  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using MT_Standard generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<MT_Standard>& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using dSFMT<521> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<dSFMT<521> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using dSFMT<1279> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<dSFMT<1279> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using dSFMT<2203> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<dSFMT<2203> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using dSFMT<4253> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<dSFMT<4253> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using dSFMT<11213> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<dSFMT<11213> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using dSFMT<19937> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<dSFMT<19937> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using dSFMT<44497> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<dSFMT<44497> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using dSFMT<86243> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<dSFMT<86243> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using dSFMT<132049> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<dSFMT<132049> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using dSFMT<216091> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<dSFMT<216091> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using SFMT<607> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<SFMT<607> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using SFMT<1279> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<SFMT<1279> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using SFMT<2281> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<SFMT<2281> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using SFMT<4253> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<SFMT<4253> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using SFMT<11213> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<SFMT<11213> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using SFMT<19937> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<SFMT<19937> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using SFMT<44497> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<SFMT<44497> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using SFMT<86243> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<SFMT<86243> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using SFMT<132049> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<SFMT<132049> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }
  /**
   * @brief generate T-type random number
   *
   * For generic type, this procedure is prohibited. Error messages are
   * proposed. This provides the generic interface to use rand method.
   *
   * T is the type of number to be output.
   *
   * @param bm [in,out] the BoxMuller generator with the internal generator
   *                    implemented using SFMT<216091> generator
   * @return T-type zero
   */
  template <typename T>
  const T& rand(BoxMuller<SFMT<216091> >& bm) {
    myError("Default form is prohibited");
    return static_cast<T>(0);
  }

  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using MT_Standard generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<MT_Standard>& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using dSFMT<521> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<dSFMT<521> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using dSFMT<1279> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<dSFMT<1279> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using dSFMT<2203> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<dSFMT<2203> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using dSFMT<4253> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<dSFMT<4253> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using dSFMT<11213> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<dSFMT<11213> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using dSFMT<19937> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<dSFMT<19937> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using dSFMT<44497> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<dSFMT<44497> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using dSFMT<86243> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<dSFMT<86243> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using dSFMT<132049> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<dSFMT<132049> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using dSFMT<216091> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<dSFMT<216091> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using SFMT<607> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<SFMT<607> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using SFMT<607> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<SFMT<1279> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using SFMT<2281> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<SFMT<2281> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using SFMT<4253> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<SFMT<4253> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using SFMT<11213> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<SFMT<11213> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using SFMT<19937> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<SFMT<19937> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using SFMT<44497> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<SFMT<44497> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using SFMT<86243> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<SFMT<86243> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using SFMT<132049> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<SFMT<132049> >& bm) { return rand(bm); }
  /**
   * @brief generator \c double random number
   *
   * This is a specification of rand operation for \c double type.
   * It is implemented with basic rand operation.
   *
   * @param bm [out] the BoxMuller generator with the internal generator
   *                 implemented using SFMT<216091> generator
   * @return \c double type random number
   */
  template <>
  const double& rand<double>(BoxMuller<SFMT<216091> >& bm) { return rand(bm); }

  /**
   * @brief output a BoxMuller generator to ostream
   *
   * The internal generator with uniform distribution is output at first.
   * The other flags are also written out.
   *
   * UniformRNG is the type of internal random-number generator with
   * uniform distribution. The separation between elements is the tab
   * character.
   *
   * @param os [out] the ostream to accept output
   * @param bm [in] the BoxMuller generator to be output
   * @return the ostream after output operation
   */
  template <typename UniformRNG>
  ostream& operator<<(ostream& os, const BoxMuller<UniformRNG>& bm) {
    os<<*bm.urng<<"\t";
    unsigned long long int *p;
    p=reinterpret_cast<unsigned long long int*>(const_cast<double*>(bm.DbFac));
    for(unsigned int i=0;i<3;++i) os<<p[i]<<"\t";
    os<<*(bm.isSecond);
    return os;
  }

  /**
   * @brief read BoxMuller generator from istream
   *
   * The internal generator with uniform distribution is read at first.
   * The other flags are also read.
   *
   * @param is [in,out] the istream containing the input information
   * @param bm [out] BoxMuller generator to contain information from istream
   * @return the istream after reading
   */
  template <typename UniformRNG>
  istream& operator>>(istream& is, BoxMuller<UniformRNG>& bm) {
    is>>*bm.urng;
    unsigned long long int *p;
    p=reinterpret_cast<unsigned long long int*>(const_cast<double*>(bm.DbFac));
    for(unsigned int i=0;i<3;++i) is>>p[i];
    is>>*(bm.isSecond);
    return is;
  }

}

#endif

