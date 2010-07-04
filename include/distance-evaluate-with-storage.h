
/**
 * @file distance-evaluate-with-storage.h
 * @brief object for distance evaluation with storage
 *
 * This file describes the data structure for distance evaluation with
 * storage of distance and some related operations.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */
#ifndef _Distance_Evaluate_With_Storage_H_
#define _Distance_Evaluate_With_Storage_H_

#include "distance-evaluate-base.h"
#include "distance-displacement-calc.h"
#include "matrix-storage.h"

namespace std {

  /**
   * @brief declaration of object for distance evaluation with storage
   */
  struct DistanceEvalWStorage;

  void release(DistanceEvalWStorage&);
  void assign(DistanceEvalWStorage&, const DistanceEvalWStorage&);

  /**
   * @brief data structure for distance evaluation with storage
   *
   * This object is the child of DistanceEvalBase type. The storage
   * of distance in matrix format is included. This may avoid the
   * calculation of distances twice, which may save some calculation
   * time.
   *
   * @note The visiting of elements in distance storage may use some more
   *       time comparing with direct calculation. Which one is faster,
   *       DistanceEvalWStorage or DistanceEvalDirect? It would depend on
   *       type of application.
   */
  struct DistanceEvalWStorage : public DistanceEvalBase {

    /**
     * @brief abbreviation of the DistanceEvalWStorage type
     */
    typedef DistanceEvalWStorage  Type;
    /**
     * @brief abbreviation of the parent DistanceEvalBase type
     */
    typedef DistanceEvalBase      ParentType;

    /**
     * @brief the matrix to store distances
     */
    MatrixStorage<double> distsqmat;

    /**
     * @brief default initiator
     *
     * Just initiate the parent class and the matrix storing matrix
     */
    DistanceEvalWStorage() : ParentType(), distsqmat() {}
    /**
     * @brief initiator from another DistanceEvalWStorage object
     *
     * it is prohibited and pop up an error message
     *
     * @param DEW [in] the input DistanceEvalWStorage object
     */
    DistanceEvalWStorage(const Type& DEW) {
      myError("Cannot create from Distance Evaluate With Storage");
    }
    /**
     * @brief copy from another DistanceEvalWStorage object
     *
     * It is implemented with assign operation.
     *
     * @param DEW [in] the input DistanceEvalWStorage object
     * @return the reference to the resultant DistanceEvalWStorage object
     */
    Type& operator=(const Type& DEW) { assign(*this,DEW); return *this; }
    /**
     * @brief destructor
     *
     * it is implemented with release operation.
     */
    ~DistanceEvalWStorage() { release(*this); }

  };

  /**
   * @brief check if the DistanceEvalWStorage object is method for distance evaluation
   *
   * DistanceEvalWStorage is used for distance evaluation. This procedure
   * always gives positive result.
   *
   * @param DEW [in] the DistanceEvalWStorage object to be checked
   * @return true flag
   */
  bool IsDistanceEvalMethod(const DistanceEvalWStorage& DEW) { return true; }

  /**
   * @brief release DistanceEvalWStorage object
   *
   * it is implemented by releasing the parent class and the matrix storing
   * distance information.
   *
   * @param DEW [in,out] the DistanceEvalWStorage object to be released
   * @return nothing
   */
  void release(DistanceEvalWStorage& DEW) {
    release(DEW.distsqmat);
    release(static_cast<DistanceEvalBase&>(DEW));
  }

  /**
   * @brief assign DistanceEvalWStorage object from another
   *
   * it is implemented by assigning the parent object and the matrix
   * from the source object to the destination. These two objects are
   * checked for availability before this assign operaion.
   *
   * @param dest [out] the DistanceEvalWStorage object to accept input
   * @param src [in] the DistanceEvalWStorage object storing input
   * @return nothing
   */
  void assign(DistanceEvalWStorage& dest, const DistanceEvalWStorage& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(dest.distsqmat,src.distsqmat);
    assign(static_cast<DistanceEvalBase&>(dest),
           static_cast<const DistanceEvalBase&>(src));
  }

  /**
   * @brief allocate DistanceEvalWStorage object
   *
   * It is implemented by allocating the parent object and the matrix
   * for distance storage.
   *
   * @param DEW [out] the DistanceEvalWStorage object to be allocated
   * @param dim [in] the dimension of space
   * @param nunit [in] the number of units
   * @return nothing
   */
  void allocate(DistanceEvalWStorage& DEW,
                const unsigned int dim, const unsigned int nunit) {
    allocate(DEW.distsqmat,nunit);
    allocate(static_cast<DistanceEvalBase&>(DEW),dim,nunit);
  }

  /**
   * @brief refer to another DistanceEvalWStorage object
   *
   * It is implemented by refer operation for parent class and matrix.
   *
   * @param dest [out] the DistanceEvalWStorage object to accept input
   * @param src [in] the DistanceEvalWStorage object storing input
   * @return nothing
   */
  void refer(DistanceEvalWStorage& dest, const DistanceEvalWStorage& src) {
    refer(dest.distsqmat,src.distsqmat);
    refer(static_cast<DistanceEvalBase&>(dest),
          static_cast<const DistanceEvalBase&>(src));
  }

  /**
   * @brief update the DistanceEvalWStorage object
   *
   * Just update internal matrix with refresh operation
   *
   * @param DEW [in,out] the DistanceEvalWStorage object to be updated
   * @return nothing
   */
  void update(DistanceEvalWStorage& DEW) { refresh(DEW.distsqmat); }

  /**
   * @brief evaluate distance for \c double array with distance storage
   *
   * This operation checks first if the distance has been calculated.
   * If so, the distance is extracted, the displacement is calculated.
   * Otherwise, the distance and displacement are calculated.
   *
   * GeomType is the type of geometry
   *
   * @param DEW [in,out] The DistanceEvalWStorage object
   * @param va, vb [in] the \c double arrays storing coordinates
   * @param aidx, bidx [in] the indices related to va, vb
   * @param dim [in] the dimension of space
   * @param Geo [in] the geometry
   * @param aoff, boff [in] the offsets for the first elements in arrays
   *                        va, vb. They take default value iZero.
   * @param astep, bstep [in] the separations between used elements in arrays
   *                          va,vb. They take default value lOne.
   * @return nothing
   */
  template <typename GeomType>
  void Evaluate(DistanceEvalWStorage& DEW,
                const double* va, const double* vb,
                const unsigned int aidx, const unsigned int bidx,
                const unsigned int dim, const GeomType& Geo,
                const int aoff=iZero, const long astep=lOne,
                const int boff=iZero, const long bstep=lOne) {
    if(IsUpToDate(DEW.distsqmat,aidx,bidx)) {
      DEW()=DEW.distsqmat(aidx,bidx)();
      DisplacementFunc(va,vb,dim,DEW.displacement,Geo,aoff,astep,boff,bstep);
    } else {
      DistanceDisplacementFunc(va,vb,dim,DEW.displacement,DEW(),Geo,
                               aoff,astep,boff,bstep);
      update(DEW.distsqmat,aidx,bidx,DEW());
    }
  }

  /**
   * @brief evaluate distance for Vector objects with distance storage
   *
   * It is implemented with the similar logic as Evaluate operation
   * for arrays.
   *
   * GeomType is the type of geometry related to evaluation.
   *
   * @param DEW [in,out] the DistanceEvalWStorage object
   * @param va, vb [in] the Vector objects storing coordinates
   * @param aidx, bidx [in] the indices related to va, vb
   * @param Geo [in] the geometry related to evaluation
   * @return nothing
   */
  template <typename GeomType>
  void Evaluate(DistanceEvalWStorage& DEW,
                const Vector<double>& va, const Vector<double>& vb,
                const unsigned int aidx, const unsigned int bidx,
                const GeomType& Geo) {
    if(IsUpToDate(DEW.distsqmat,aidx,bidx)) {
      DEW()=DEW.distsqmat(aidx,bidx)();
      DisplacementFunc(va,vb,DEW.displacementvec,Geo);
    } else {
      DistanceDisplacementFunc(va,vb,DEW.displacementvec,DEW(),Geo);
      update(DEW.distsqmat,aidx,bidx,DEW());
    }
  }

}

#endif

