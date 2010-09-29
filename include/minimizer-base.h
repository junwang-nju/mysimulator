
/**
 * @file minimizer-base.h
 * @brief the Base Structure for minimizer
 *
 * This file contains the base data structure for minimizer and some
 * related operations. These defines the basic interface for generic
 * minimizer.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Minimizer_Base_H_
#define _Minimizer_Base_H_

#include "error-proc.h"
#include "util.h"
#include "storage-state-name.h"
#include "memory.h"
#include <cassert>

namespace std {

  /**
   * @brief The base data structure for minimizer
   *
   * This data structure includes the common data for minimizer.
   *
   * SpaceDataType is the type of the data describing the spatial vector.
   * ParameterType is the type of the parameter vector.
   */
  template <typename SpaceDataType, typename ParameterType>
  struct MinimizerKernelBase {

    /**
     * @brief abbreviation for base type of minimizer
     */
    typedef MinimizerKernelBase<SpaceDataType,ParameterType>  Type;
    /**
     * @brief type of function pointer to calculate energy
     */
    typedef void (*EFuncType)(const SpaceDataType&, double&, ParameterType&);
    /**
     * @brief type of function pointer to calculate gradient
     */
    typedef void (*GFuncType)(const SpaceDataType&, SpaceDataType&,
                              ParameterType&);
    /**
     * @brief type of function pointer to calculate energy and gradient
     */
    typedef void (*BFuncType)(const SpaceDataType&, double&, SpaceDataType&,
                              ParameterType&);

    /**
     * @brief the function pointer to calculate energy in minimizer
     */
    EFuncType MinEFunc;
    /**
     * @brief the function pointer to calculate gradient in minimizer
     */
    GFuncType MinGFunc;
    /**
     * @brief the function pointer to calculate energy and gradient in minimizer
     */
    BFuncType MinBFunc;
    /**
     * @brief the pointer to the coordinate corresponding to minimum
     */
    SpaceDataType *MinCoor;
    /**
     * @brief the pointer to the gradient related to minimum
     */
    SpaceDataType *MinGrad;
    /**
     * @brief the pointer to the energy related to minimum
     */
    double *MinEnergy;
    /**
     * @brief the pointer to the parameters in calculating minimum
     */
    ParameterType *MinParam;
    /**
     * @brief the pointer to the projected distance related to minimum
     */
    double *MinProject;
    /**
     * @brief the pointer to the move distance to search minimum
     */
    double *MinMove;
    /**
     * @brief the pointer to the count of gradient calculation
     */
    unsigned int *GCalcCount;
    /**
     * @brief the pointer to the smallest scale in search minimum
     */
    double *SearchScale;
    /**
     * @brief the storage state for this object
     */
    unsigned int state;

    /**
     * @brief default initiator
     *
     * Just initiate pointers with NULL and set the state as Unused.
     */
    MinimizerKernelBase()
      : MinEFunc(NULL), MinGFunc(NULL), MinBFunc(NULL), MinCoor(NULL),
        MinGrad(NULL), MinEnergy(NULL), MinParam(NULL), MinProject(NULL),
        MinMove(NULL), GCalcCount(NULL), SearchScale(NULL), state(Unused) {}
    /**
     * @brief initiator with another base minimizer
     *
     * It is prohibited and pops up an error message.
     *
     * @param M [in] the input minimizer of base type
     */
    MinimizerKernelBase(const Type& M) {
      myError("Cannot create from MinimizerKernelBase");
    }
    /**
     * @brief copy from another base type of minimizer
     *
     * it is implemented with assign operation.
     *
     * @param M [in] the input minimizer of base type
     * @return the reference to the base type of minimizer
     */
    Type& operator=(const Type& M) { assign(*this,M); return *this; }
    /**
     * @brief destructor to the base type of minimizer
     *
     * It is implemented with release operation.
     */
    ~MinimizerKernelBase() { release(*this); }
  };

  /**
   * @brief check the availability of the base minimizer
   *
   * It is implemented by checking the availability of the pointer of
   * coordinate related to minimization
   *
   * SpaceDataType is the type of the data describing the spatial vector.
   * ParameterType is the type of the parameter vector.
   *
   * @param M [in] the base minimizer to be checked
   * @return the flag indicating the availability of minimizer.
   */
  template <typename SpaceDataType, typename ParameterType>
  bool IsAvailable(const MinimizerKernelBase<SpaceDataType,ParameterType>& M) {
    return IsAvailable(M.MinCoor);
  }

  /**
   * @brief release the object of base type of minimizer
   *
   * delete all the storages related to the pointers and reset the state.
   *
   * SpaceDataType is the type of the data describing the spatial vector.
   * ParameterType is the type of the parameter vector.
   *
   * @param M [in,out] the base minimizer to be released
   * @return nothing
   */
  template <typename SpaceDataType, typename ParameterType>
  void release(MinimizerKernelBase<SpaceDataType,ParameterType>& M) {
    if(M.state==Allocated) {
      safe_delete(M.MinCoor);
      safe_delete(M.MinGrad);
      safe_delete(M.MinEnergy);
      safe_delete(M.MinParam);
      safe_delete(M.MinProject);
      safe_delete(M.MinMove);
      safe_delete(M.GCalcCount);
      safe_delete(M.SearchScale);
    } else {
      M.MinCoor=NULL;
      M.MinGrad=NULL;
      M.MinEnergy=NULL;
      M.MinParam=NULL;
      M.MinProject=NULL;
      M.MinMove=NULL;
      M.GCalcCount=NULL;
      M.SearchScale=NULL;
    }
    M.MinEFunc=NULL;
    M.MinGFunc=NULL;
    M.MinBFunc=NULL;
    M.state=Unused;
  }

  /**
   * @brief assign base minimizer from another
   *
   * copy the contents of internal storages from source to destination.
   *
   * SpaceDataType is the type of the data describing the spatial vector.
   * ParameterType is the type of the parameter vector.
   *
   * @param dest [out] destination object of base minimizer to accept inputs
   * @param src [in] source object of base minimizer to bring information
   * @return nothing
   */
  template <typename SpaceDataType, typename ParameterType>
  void assign(MinimizerKernelBase<SpaceDataType,ParameterType>& dest,
              const MinimizerKernelBase<SpaceDataType,ParameterType>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    dest.MinEFunc=src.MinEFunc;
    dest.MinGFunc=src.MinGFunc;
    dest.MinBFunc=src.MinBFunc;
    *(dest.MinCoor)=*(src.MinCoor);
    *(dest.MinGrad)=*(src.MinGrad);
    *(dest.MinEnergy)=*(src.MinEnergy);
    *(dest.MinParam)=*(src.MinParam);
    *(dest.MinProject)=*(src.MinProject);
    *(dest.MinMove)=*(src.MinMove);
    *(dest.GCalcCount)=*(src.GCalcCount);
    *(dest.SearchScale)=*(src.SearchScale);
  }

  /**
   * @brief allocate an object of base minimizer
   *
   * Just allocate the storages to the internal pointers, and update
   * the state flag.
   *
   * SpaceDataType is the type of the data describing the spatial vector.
   * ParameterType is the type of the parameter vector.
   *
   * @param M [out] the base minimizer to be allocated
   * @return nothing
   */
  template <typename SpaceDataType, typename ParameterType>
  void allocate(MinimizerKernelBase<SpaceDataType,ParameterType>& M) {
    release(M);
    M.MinCoor=new SpaceDataType;
    M.MinGrad=new SpaceDataType;
    M.MinEnergy=new double;
    M.MinParam=new ParameterType;
    M.MinProject=new double;
    M.MinMove=new double;
    M.GCalcCount=new unsigned int;
    M.SearchScale=new double;
    M.state=Allocated;
    *(M.GCalcCount)=0;
    *(M.SearchScale)=0.1;
  }

  /**
   * @brief refer to another object of base minimizer
   *
   * Just copy the pointers from another object of base minimizer and
   * update the state flag.
   *
   * SpaceDataType is the type of the data describing the spatial vector.
   * ParameterType is the type of the parameter vector.
   *
   * @param dest [out] destination object of base minimizer to accept inputs
   * @param src [in] source object of base minimizer to bring information
   * @return nothing
   */
  template <typename SpaceDataType, typename ParameterType>
  void refer(MinimizerKernelBase<SpaceDataType,ParameterType>& dest,
             const MinimizerKernelBase<SpaceDataType,ParameterType>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.MinEFunc=src.MinEFunc;
    dest.MinGFunc=src.MinGFunc;
    dest.MinBFunc=src.MinBFunc;
    dest.MinCoor=src.MinCoor;
    dest.MinGrad=src.MinGrad;
    dest.MinEnergy=src.MinEnergy;
    dest.MinParam=src.MinParam;
    dest.MinProject=src.MinProject;
    dest.MinMove=src.MinMove;
    dest.GCalcCount=src.GCalcCount;
    dest.SearchScale=src.SearchScale;
    dest.state=Reference;
  }

  template <typename SpaceDataType, typename ParameterType>
  void GenerateNewLocation(
      const MinimizerKernelBase<SpaceDataType,ParameterType>& M,
      const SpaceDataType& Origin, const SpaceDataType& Dirc,
      const double step, SpaceDataType& Dest, double& DestY,
      SpaceDataType& DestG, double& DestPrj) {
    assign(Dest,Origin);
    shift(Dest,step,Dirc);
    updateParameter(*(M.MinParam));
    DestY=0;
    assign(DestG,0.);
    M.MinBFunc(Dest,DestY,DestG,*(M.MinParam));
    ++(*(M.GCalcCount));
    DestPrj=dot(DestG,Dirc);
  }

}

#endif

