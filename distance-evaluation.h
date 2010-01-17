
/**
 * @file distance-evaluation.h
 * @brief the evaluation method of distance
 *
 * This file defines several methods to evaluate displacement and distance.
 * The geometry and boundary condition may be incorporated into the
 * evaluation. These operations are defined as unique objects to enhance
 * the ability of extension.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Distance_Evaluation_H_
#define _Distance_Evaluation_H_

#include "geometry.h"
#include "vector-op.h"
#include "distance-storage.h"

namespace std {

  /**
   * @brief functor to evaluate displacement
   *
   * This functor defines the methods to calculate the displacement.
   * For various kinds of boundary conditions, the methods are implemented
   * separately. It is defined as a child class of fixVector class
   * to define an internal storage for calculation.
   *
   * \a N
   *    The dimension of the vector
   */
  template <uint N>
  class Displacement : public fixVector<double,N> {

    public:

      /**
       * @brief alias for the displacement object
       */
      typedef Displacement<N>       Type;

      /**
       * @brief alias for the parent fixVector class
       */
      typedef fixVector<double,N>   ParentType;
      
      /**
       * @brief default initiator
       *
       * Just initiate the parent class with null parameter
       */
      Displacement() : ParentType() {}

      /**
       * @brief initiator from another Displacement object
       *
       * It is prohibited by popping up an error.
       *
       * @param [in] Dsp
       *        The input Displacement functor
       */
      Displacement(const Type& Dsp) {
        myError("copier for Displacement is disabled!");
      }

      /**
       * @brief copier from another Displacement object
       *
       * It is implemented with the copier of the parent class.
       *
       * @param [in] Dsp
       *        The input Displacement functor
       *
       * @return the reference to the present object
       */
      Type& operator=(const Type& Dsp) {
        static_cast<ParentType*>(this)->operator=(Dsp);
        return *this;
      }
      
      /**
       * @brief the operator to access the internal data
       *
       * Just give out the internal parent object.
       *
       * @return the reference to the parent class.
       */
      fixVector<double,N>& operator()() {
        return *static_cast<ParentType*>(this);
      }

      /**
       * @brief calculate the naive displacement of two vectors
       *
       * The naive displacement is calculated as the difference
       * between two input vectors. The sizes of two vectors are
       * checked. The difference is stored in the internal object.
       *
       * @param [in] va
       *        The input VectorBase object
       *
       * @param [in] vb
       *        The input VectorBase object
       *
       * @return the reference to the internal class
       */
      fixVector<double,N>& operator()(const VectorBase<double>& va,
                                      const VectorBase<double>& vb) {
        assert(va.size()==vb.size());
        assert(this->size()>=va.size());
        static_cast<ParentType*>(this)->operator=(va);
        this->shift(-1.,vb);
        return operator()();
      }

      /**
       * @brief calculate displacement for free-space condition
       *
       * It is calculated with the method for the naive displacement.
       *
       * @param [in] va
       *        The input VectorBase object
       *
       * @param [in] vb
       *        The input VectorBase object
       *
       * @param [in] FS
       *        The free-space object.
       *
       * @return the reference to the internal class
       */
      fixVector<double,N>& operator()(const VectorBase<double>& va,
                                      const VectorBase<double>& vb,
                                      const FreeSpace& FS) {
        return operator()(va,vb);
      }

  };

  /**
   * @brief the functor to calculate square of distance
   *
   * This functor defines the methods to calculate the square of distance.
   * For various kinds of boundary conditions, the methods are implemented
   * separately. It is defined as a child class of Displacement class
   * to store the displacement information.
   *
   * \a N
   *    The dimension of the vector
   */
  template <uint N>
  class DistanceSquare : public Displacement<N> {

    public:

      /**
       * @brief the alias for the functor to calculate square of distance
       */
      typedef DistanceSquare<N>   Type;

      /**
       * @brief the alias for the functor tp calculate displacement
       */
      typedef Displacement<N>     ParentType;

      /**
       * @brief default initiator
       *
       * Just initiate the parent class with null parameter
       */
      DistanceSquare() : ParentType() {}

      /**
       * @brief initiator from another DistanceSquare functor
       *
       * It is prohibited by popping up an error.
       *
       * @param [in] DSq
       *        The input functor to calculate square of distance
       */
      DistanceSquare(const Type& DSq) {
        myError("copier for DistanceSquare is disabled!");
      }

      /**
       * @brief copier from another DistanceSquare functor
       *
       * It is prohibited by popping up an error.
       *
       * @param [in] DSq
       *        The input functor to calculate square of distance
       *
       * @return the reference to the present object
       */
      Type& operator=(const Type& DSq) {
        static_cast<ParentType*>(this)->operator=(DSq);
        return *this;
      }

      /**
       * @brief extract displacement information
       *
       * Just extract the information from the internal object.
       *
       * @return the reference to the parent class.
       */
      ParentType& Direction() { return *static_cast<ParentType*>(this); }

      /**
       * @brief visit the displacement information
       *
       * Just read the information from the internal object.
       *
       * @return the const reference to the parent class.
       */
      const ParentType& Direction() const {
        return *static_cast<const ParentType*>(this);
      }

      /**
       * @brief calculate the naive square of distance
       *
       * Just calculate the square of distance of the naive
       * displacement of two input vectors.
       *
       * @param [in] va
       *        The input VectorBase object
       *
       * @param [in] vb
       *        The input VectorBase object
       *
       * @return the square of distance of the naive displacement
       *         of two input vectors
       */
      double operator()(const VectorBase<double>& va,
                        const VectorBase<double>& vb) {
        return normSQ(Direction()(va,vb)); 
      }

      /**
       * @brief calculate square of distance for certain geometry
       *
       * This is calculated as the square of distance for the
       * displacement related to the geometry.
       *
       * \a GeomType
       *    The type of related geometry
       *
       * @param [in] va
       *        The input VectorBase object
       *
       * @param [in] vb
       *        The input VectorBase object
       *
       * @param [in] Geo
       *        The input geometry
       *
       * @return the square of distance of the displacement
       *         of two input vectors under input geometry.
       */
      template <typename GeomType>
      double operator()(const VectorBase<double>& va,
                        const VectorBase<double>& vb,
                        const GeomType& Geo) {
        return normSQ(Direction()(va,vb,Geo));
      }

  };

  template <uint N>
  class DistanceEvalDirect {
  
    private:
    
      DistanceSquare<N> GetDistSQ;
      
      double nowDistSQ;
      
      fixVector<double,N> nowDisp;
      
    public:
    
      DistanceEvalDirect() : GetDistSQ(), nowDistSQ(0.), nowDisp() {}
      
      DistanceEvalDirect(const DistanceEvalDirect<N>& DEval) {
        myError("copier for Direct DistanceEval is disabled!");
      }
      
      const double& DistanceSQ() { return nowDistSQ; }
      
      const fixVector<double,N>& DisplaceVector() { return nowDisp; }

      template <typename GeomType>
      double operator()(const VectorBase<double>& pa,
                        const VectorBase<double>& pb,
                        const uint& aIdx, const uint& bIdx,
                        const GeomType& Geo) {
        nowDistSQ=GetDistSQ(pa,pb,Geo);
        return nowDistSQ;
      }

      template <typename GeomType>
      double operator()(const VectorBase<double>& pa,
                        const VectorBase<double>& pb,
                        const uint& aIdx, const uint& bIdx,
                        const GeomType& Geo, const char) {
        nowDistSQ=GetDistSQ(pa,pb,Geo);
        nowDisp=GetDistSQ.Direction()();
        return nowDistSQ;
      }
      
      void Update() {}

  };

  template <uint N>
  class DistanceEvalwStorage {
  
    private:
    
      DistanceSquare<N> GetDistSQ;
    
      double nowDistSQ;
      
      fixVector<double,N> nowDisp;
      
      DistanceSqStorage DistSQPack;

    public:

      typedef DistanceEvalwStorage<N>   Type;
    
      DistanceEvalwStorage()
        : GetDistSQ(), nowDistSQ(0.), nowDisp(), DistSQPack() {
      }
      
      DistanceEvalwStorage(const DistanceEvalwStorage<N>& DEval) {
        myError("copier for storage-base DistanceEval is disabled!");
      }

      const double& DistanceSQ() { return nowDistSQ; }
      
      const fixVector<double,N>& DisplaceVector() { return nowDisp; }
      
      template <typename GeomType>
      double operator()(const VectorBase<double>& pa,
                        const VectorBase<double>& pb,
                        const uint& aIdx, const uint& bIdx,
                        const GeomType& Geo) {
        DistanceSqStorage::Item &DItem=DistSQPack(aIdx,bIdx);
        if(DItem.Status!=DistSQPack.GStatus) {
          DItem.DistanceSQ=GetDistSQ(pa,pb,Geo);
          DItem.Status=DistSQPack.GStatus;
        } 
        nowDistSQ=DItem.DistanceSQ;
        return nowDistSQ;
      }

      template <typename GeomType>
      double operator()(const VectorBase<double>& pa,
                        const VectorBase<double>& pb,
                        const uint& aIdx, const uint& bIdx,
                        const GeomType& Geo, const char) {
        DistanceSqStorage::Item &DItem=DistSQPack(aIdx,bIdx);
        if(DItem.Status!=DistSQPack.GStatus) {
          DItem.DistanceSQ=GetDistSQ(pa,pb,Geo);
          DItem.Status=DistSQPack.GStatus;
        } else
          GetDistSQ.Direction()(pa,pb,Geo); 
        nowDistSQ=DItem.DistanceSQ;
        nowDisp=GetDistSQ.Direction()();
        return nowDistSQ;
      }
      
      void Update() { DistSQPack.Inc(); }

      void allocate_storage(const uint& NS) { DistSQPack.allocate(NS); }

  };

}

#endif
