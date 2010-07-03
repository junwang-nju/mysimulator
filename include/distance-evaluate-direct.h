
/**
 * @file distance-evaluate-direct.h
 * @brief data structure related to direct calculation of distance
 *
 * This file describes the data structure and related operations related to
 * direct calculation of distance and displacement. This related data structure
 * is a child of the DistanceEvalBase class.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Distance_Evaluate_Direct_H_
#define _Distance_Evaluate_Direct_H_

#include "distance-evaluate-base.h"
#include "distance-displacement-calc.h"

namespace std {

  /**
   * @brief the data structure related to direct distance evaluation
   *
   * This is a child class of DistanceEvalBase class. There are no new
   * components inrtoduced.
   */
  struct DistanceEvalDirect : public DistanceEvalBase {

    /**
     * @brief abbreviation of the type of direct distance evaluation
     */
    typedef DistanceEvalDirect  Type;
    /**
     * @brief abbreviation of the parent base type of distance evaluation
     */
    typedef DistanceEvalBase    ParentType;

    /**
     * @brief default initiator
     *
     * Just initiate the parent class.
     */
    DistanceEvalDirect() : ParentType() {}
    /**
     * @brief initiator from another DistanceEvalDirect object
     *
     * It is prohibited and pop up an error message.
     *
     * @param DED [in] the input DistanceEvalDirect object
     */
    DistanceEvalDirect(const Type& DED) {
      myError("Cannot create from Distance Evaluate Direct");
    }
    /**
     * @brief copy from another DistanceEvalDirect object
     *
     * It is implemented with assign operation.
     *
     * @param DED [in] the input DistanceEvalDirect object
     * @return the reference to the resultant DistanceEvalDirect object
     */
    Type& operator=(const Type& DED) { assign(*this,DED); return *this; }
    /**
     * @brief destructor
     *
     * it is implemented with release operation.
     */
    ~DistanceEvalDirect() { release(*this); }

  };

  /**
   * @brief Check if DistanceEvalDirect object is method for distance evaluation
   *
   * It always gives the positive answer to confirm the DistanceEvalDirect
   * object is a method for distance evaluation.
   *
   * @param DED [in] the concerned DistanceEvalDirect object
   * @return true flag
   */ 
  bool IsDistanceEvalMethod(const DistanceEvalDirect& DED) { return true; }

  /**
   * @brief update the DistanceEvalDirect objct
   *
   * Do nothing here. It is used for compatibility
   *
   * @return nothing
   */
  void update(DistanceEvalDirect&) {}

  /**
   * @brief distance evaluate based on \c double array
   *
   * It is implemented with DistanceDisplacementFunc operation. The
   * DistanceEvalDirect object is used to offer the storage of distance
   * and displacement. 
   *
   * GeomType is the type of the concerned geometry
   *
   * @param DED [out] the DistanceEvalDirect object to store distance
   *                  and displacement
   * @param va, vb [in] the arrays to store the coordinates
   * @param aidx,bidx [in] the indices corresponding to va, and vb.
   *                       it is useless for the case of direct distance
   *                       evaluation. 
   * @param dim [in] the dimension of the space
   * @param Geo [in] the geomtry for this evaluation
   * @param aoff, boff [in] the offsets for the first elements of
   *                        the arrays va, vb. They takes the default
   *                        value iZero.
   * @param astep, bstep [in] the separations between elements to be used
   *                          in the arrays va, vb. They takes the default
   *                          value lOne.
   * @return nothing
   */
  template <typename GeomType>
  void Evaluate(DistanceEvalDirect& DED,
                const double* va, const double* vb,
                const unsigned int aidx, const unsigned int bidx,
                const unsigned int dim, const GeomType& Geo,
                const int aoff=iZero, const long astep=lOne,
                const int boff=iZero, const long bstep=lOne) {
    DistanceDisplacementFunc(va,vb,dim,DED.displacement,DED(),Geo,
                             aoff,astep,boff,bstep);
  }

  /**
   * @brief distance evaluation based on Vector objects
   *
   * It is implemented with DistanceDisplacementFunc operation. The
   * DistanceEvalDirect object is used to offer the storage of distance
   * and displacement.
   *
   * GeomType is the type of the concerned geometry
   *
   * @param DED [out] the DistanceEvalDirect object to store distance
   *                  and displacement
   * @param va, vb [in] the Vector objects storing coordinates.
   * @param aidx,bidx [in] the indices corresponding to va, and vb.
   *                       it is useless for the case of direct distance
   *                       evaluation. 
   * @param Geo [in] the geomtry for this evaluation
   * @return nothing
   */
  template <typename GeomType>
  void Evaluate(DistanceEvalDirect& DED,
                const Vector<double>& va, const Vector<double>& vb,
                const unsigned int aidx, const unsigned int bidx,
                const GeomType& Geo) {
    DistanceDisplacementFunc(va,vb,DED.displacementvec,DED(),Geo);
  }

}

#endif

