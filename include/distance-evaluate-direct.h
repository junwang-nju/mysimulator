
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

    DistanceEvalDirect() : ParentType() {}
    DistanceEvalDirect(const Type&) {
      myError("Cannot create from Distance Evaluate Direct");
    }
    Type& operator=(const Type& DED) { assign(*this,DED); return *this; }
    ~DistanceEvalDirect() { release(*this); }

  };

  bool IsDistanceEvalMethod(const DistanceEvalDirect&) { return true; }

  void update(DistanceEvalDirect&) {}

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

  template <typename GeomType>
  void Evaluate(DistanceEvalDirect& DED,
                const Vector<double>& va, const Vector<double>& vb,
                const unsigned int aidx, const unsigned int bidx,
                const GeomType& Geo) {
    DistanceDisplacementFunc(va,vb,DED.displacementvec,DED(),Geo);
  }

}

#endif

