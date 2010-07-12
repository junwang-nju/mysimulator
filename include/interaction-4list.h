
/**
 * @file interaction-4list.h
 * @brief operations to calculate energy and gradient for a list of indices and parameters
 *
 * This file describes the methods to calculate energy and gradients for
 * a list of indices and parameters related to a certain kind of interaction. 
 * This is a basic interface relatd to energy and gradient.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Interaction_for_List_H_
#define _Interaction_for_List_H_

#include "interaction-method.h"

namespace std {

  /**
   * @brief calculate energy for a set of indices and parameters related to an interaction
   *
   * It is implemented by summing the energy for each corresponding
   * index and parameter. It is a common interface to use specific
   * calculation of energy for the related interaction method.
   *
   * DistEvalMethod is the type of the functor to calculate distance.
   * GeomType is the type of the concerned geometry.
   *
   * @param Coor [in] the pointer to the array of coordinates of units
   *                  in the system.
   * @param IdxLst [in] the pointer to the array of indices
   * @param PrmLst [in] the pointer to the array of parameters
   * @param nLst [in] the number of elements in the list of indices
   *                  and parameters (IdxLst and PrmLst)
   * @param IM [in,out] the interaction method
   * @param DEval [in,out] the functor to calculate distance and displacement
   * @param Geo [in] the concerned geometry
   * @param Energy [in,out] the energy of the system. The calculated
   *                        energy is accumulated into this variable
   * @return nothing
   */
  template <typename DistEvalMethod, typename GeomType>
  void EFunc(const Vector<double>* Coor, const Vector<unsigned int>* IdxLst,
             const Vector<UniqueParameter>* PrmLst, const unsigned int nLst,
             InteractionMethod<DistEvalMethod,GeomType>& IM,
             DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    for(unsigned int i=0;i<nLst;++i)
      IM.EFunc(Coor,IdxLst[i](),PrmLst[i](),IdxLst[i].size,
               IM.tmpvec->structure,IM.tmpvec->nunit,DEval,Geo,Energy);
  }

  /**
   * @brief calculate gradient for a set of indices and parameters related to an interaction
   *
   * It is implemented by summing the gradient for each corresponding
   * index and parameter. It is a common interface to use specific
   * calculation of gradient for the related interaction method.
   *
   * DistEvalMethod is the type of the functor to calculate distance.
   * GeomType is the type of the concerned geometry.
   *
   * @param Coor [in] the pointer to the array of coordinates of units
   *                  in the system.
   * @param IdxLst [in] the pointer to the array of indices
   * @param PrmLst [in] the pointer to the array of parameters
   * @param nLst [in] the number of elements in the list of indices
   *                  and parameters (IdxLst and PrmLst)
   * @param IM [in,out] the interaction method
   * @param DEval [in,out] the functor to calculate distance and displacement
   * @param Geo [in] the concerned geometry
   * @param G [in,out] the gradient of the system. The calculated
   *                   gradient is accumulated into this variable
   * @return nothing
   */
  template <typename DistEvalMethod, typename GeomType>
  void GFunc(const Vector<double>* Coor, const Vector<unsigned int>* IdxLst,
             const Vector<UniqueParameter>* PrmLst, const unsigned int nLst,
             InteractionMethod<DistEvalMethod,GeomType>& IM,
             DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* G) {
    for(unsigned int i=0;i<nLst;++i)
      IM.GFunc(Coor,IdxLst[i](),PrmLst[i](),IdxLst[i].size,
               IM.tmpvec->structure,IM.tmpvec->nunit,DEval,Geo,G);
  }

  /**
   * @brief calculate energy and gradient for a set of indices and parameters related to an interaction
   *
   * It is implemented by summing the energy and gradient for corresponding
   * index and parameter. It is a common interface to use specific
   * calculation of energy and gradient for the related interaction method.
   *
   * DistEvalMethod is the type of the functor to calculate distance.
   * GeomType is the type of the concerned geometry.
   *
   * @param Coor [in] the pointer to the array of coordinates of units
   *                  in the system.
   * @param IdxLst [in] the pointer to the array of indices
   * @param PrmLst [in] the pointer to the array of parameters
   * @param nLst [in] the number of elements in the list of indices
   *                  and parameters (IdxLst and PrmLst)
   * @param IM [in,out] the interaction method
   * @param DEval [in,out] the functor to calculate distance and displacement
   * @param Geo [in] the concerned geometry
   * @param Energy [in,out] the energy of the system. The calculated
   *                        energy is accumulated into this variable
   * @param G [in,out] the gradient of the system. The calculated
   *                   gradient is accumulated into this variable
   * @return nothing
   */
  template <typename DistEvalMethod, typename GeomType>
  void BFunc(const Vector<double>* Coor, const Vector<unsigned int>* IdxLst,
             const Vector<UniqueParameter>* PrmLst, const unsigned int nLst,
             InteractionMethod<DistEvalMethod,GeomType>& IM,
             DistEvalMethod& DEval, const GeomType& Geo,
             double& Energy, Vector<double>* G) {
    for(unsigned int i=0;i<nLst;++i)
      IM.BFunc(Coor,IdxLst[i](),PrmLst[i](),IdxLst[i].size,
               IM.tmpvec->structure,IM.tmpvec->nunit,DEval,Geo,Energy,G);
  }

}

#endif

