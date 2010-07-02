
/**
 * @file distance-evaluate-base.h
 * @brief the base object for distance evaluation
 *
 * To evaluate distance may relate to some temporary storage for distances.
 * This file defines the base object for distance evaluation and the
 * related operations.

 * @note IsDistanceEvalMethod function is defined to check the type of
 *       objects. This kind of functions help to avoid definitions of
 *       constants to indicate the type of objects.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Distance_Evaluate_Base_H_
#define _Distance_Evaluate_Base_H_

#include "storage-state-name.h"
#include "error-proc.h"
#include "vector.h"

namespace std {

  /**
   * @brief declaration of base object for distance evaluation
   */
  struct DistanceEvalBase;

  void assign(DistanceEvalBase&, const DistanceEvalBase&);
  void release(DistanceEvalBase&);

  /**
   * @brief the base object with the data for distance evaluation
   *
   * This data structure contains the basic data for distance evaluation,
   * including the storage for displacement and square of distance. The
   * dimension and number of units are also included. These data objects
   * are common for various child classes.
   */
  struct DistanceEvalBase {

    /**
     * @brief abbreviation for base type of distance evaluation
     */
    typedef DistanceEvalBase  Type;

    /**
     * @brief data of displacement
     */
    double* displacement;
    /**
     * @brief data of square of distance
     */
    double* distancesq;
    /**
     * @brief size of displacement array (namely the dimension)
     */
    unsigned int size;
    /**
     * @brief number of units
     */
    unsigned int nunit;
    /**
     * @brief Vector interface of displacement
     */
    Vector<double> displacementvec;
    /**
     * @brief storage state for this base class
     */
    unsigned int state;

    /**
     * @brief default initiator
     *
     * Just initiate the pointers and data with null information
     */
    DistanceEvalBase()
      : displacement(NULL), distancesq(NULL), size(0), nunit(0),
        displacementvec(), state(Unused) {}
    /**
     * @brief initiator from another DistanceEvalBase object
     *
     * it is prohibited and pop up an error message
     *
     * @param DEB [in] the input DistanceEvalBase object
     */
    DistanceEvalBase(const Type& DEB) {
      myError("Cannot create from Distance Evaluate Base");
    }
    /**
     * @brief copy from another DistanceEvalBase object
     *
     * It is implemented with the assign operation.
     *
     * @param DEB [in] the input DistanceEvalBase object
     * @return the reference to the resultant DistanceEvalBase object
     */
    Type& operator=(const Type& DEB) { assign(*this,DEB); return *this; }
    /**
     * @brief destructor
     *
     * It is implemented with release operation
     */
    ~DistanceEvalBase() { release(*this); }

    /**
     * @brief access the square of distance
     *
     * It is accessed through the pointer to the square of distance.
     * The concerned pointer is checked for the availability before
     * this operation.
     *
     * @return the reference to the square of distance
     */
    double& operator()() {
      assert(IsAvailable(distancesq));
      return *distancesq;
    }
    /**
     * @brief visit the square of the distance
     *
     * It is visited through the pointer of square of distance. The concerned
     * pointer is checked for the availability before the operation.
     *
     * @return the const reference to the square of distance
     */
    const double& operator()() const {
      assert(IsAvailable(distancesq)); 
      return *distancesq;
    }

  };

  /**
   * @brief check the availability of DistanceEvalBase object
   *
   * It is implemented by checking the availability of the pointer
   * to the square of distance.
   *
   * @param DEB [in] the concerned DistanceEvalBase object
   * @return the availability of the input DistanceEvalBase object
   */
  bool IsAvailable(const DistanceEvalBase& DEB) {
    return IsAvailable(DEB.distancesq);
  }

  /**
   * @brief release the storage of DistanceEvalBase object
   *
   * The data of displacement and the square of distance are cleaned
   * and the corresponding storage are freed when they are allocated.
   * Other components are nullified correspondingly. The flag of
   * storage state is set as Unused.
   *
   * @param DEB [in,out] the DistanceEvalBase object to be released
   * @return nothing
   */
  void release(DistanceEvalBase& DEB) {
    if(DEB.state==Allocated) {
      safe_delete_array(DEB.displacement);
      safe_delete(DEB.distancesq);
    } else {
      DEB.displacement=NULL;
      DEB.distancesq=NULL;
    }
    release(DEB.displacementvec);
    DEB.size=0;
    DEB.nunit=0;
    DEB.state=Unused;
  }

  /**
   * @brief assign DistanceEvalBase object from another
   *
   * This operation just copy the data from source DistanceEvalBase object
   * to the destination DistanceEvalBase object, including the square
   * of distance and displacement. The minimum of the size of displacement
   * array is used during the copy of displacement. These two DistanceEvalBase
   * objects are also checked for their availability.
   *
   * @param dest [out] the DistanceEvalBase object to accept input
   * @param src [in] the DistanceEvalBase object storing the input
   * @return nothing
   */
  void assign(DistanceEvalBase& dest, const DistanceEvalBase& src) {
    assert(IsAvailable(src));
    assert(IsAvailable(dest));
    dest()=src();
    unsigned int n=(dest.size<src.size?dest.size:src.size);
    assign(dest.displacement,src.displacement,n);
  }

  /**
   * @brief allocate a DistanceEvalBase object
   *
   * The displacement and square of distance are allocated based on the input
   * parameters. Other internal parameters are also assigned. Before this
   * operation, the input DistanceEvalBase object is released to avoid
   * memory leak.
   *
   * @param DEB [out] the DistanceEvalBase object to be allocated
   * @param dim [in] the dimension of space
   * @param nunit [in] the number of units
   * @return nothing
   */
  void allocate(DistanceEvalBase& DEB,
                const unsigned int dim, const unsigned int nunit) {
    release(DEB);
    DEB.displacement=new double[dim];
    DEB.distancesq=new double;
    DEB.size=dim;
    DEB.nunit=nunit;
    refer(DEB.displacementvec,DEB.displacement,DEB.size);
    DEB.state=Allocated;
  }

  /**
   * @brief refer to another DistanceEvalBase object
   *
   * it is implemented by copying all the pointers and flags from source
   * object into the destination. Before this operation, the destination
   * object is released to avoid memory leak.
   *
   * @param dest [out] the DistanceEvalBase object to accept input
   * @param src [in] the DistanceEvalBase object storing input information
   * @return nothing
   */
  void refer(DistanceEvalBase& dest, const DistanceEvalBase& src) {
    release(dest);
    dest.displacement=src.displacement;
    dest.distancesq=src.distancesq;
    dest.size=src.size;
    dest.nunit=src.nunit;
    refer(dest.displacementvec,dest.displacement,dest.size);
    dest.state=Reference;
  }

  /**
   * @brief check if this is a method for distance evaluation
   *
   * This is a check for generic type as a screening for unexpected types.
   * It generally returns false.
   *
   * T is the type of the input object.
   *
   * @param t [in] the object with type T.
   * @return false always to screen generic types.
   */
  template <typename T>
  bool IsDistanceEvalMethod(const T&t ) { return false; }

  /**
   * @brief check if the DistanceEvalBase object is a method for distance evaluation
   *
   * The answer is always true since DistanceEvalBase object is generally
   * used for distance evaluation.
   *
   * @param DEB [in] the input DistanceEvalBase object
   * @return true.
   */
  bool IsDistanceEvalMethod(const DistanceEvalBase& DEB) { return true; }

}

#endif

