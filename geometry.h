
/**
 * @file geometry.h
 * @brief objects descibing boundary condition and geometry for distance metric
 *
 * This file includes the objects describing (1) the boundary condition
 * (2) the geometric metric related to distance calculation. This kind of
 * separation of data and operation from simulations is useful.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 * @todo Some useful boundary conditions need to be implemented in future.
 */

#ifndef _Geometry_H_
#define _Geometry_H_

#include "fix-vector.h"

namespace std {

  /**
   * @brief the identity related to the geometry types
   *
   * To ease the input and reflection of the geometric types, the
   * identities for various geometry are defined (as \c int type).
   */
  enum GeometryType {

    /**
     * @brief the type with no boundary
     */
    FreeSpaceType

  };

  /**
   * @brief the class indicating a free space
   *
   * This is the simplest boundary (no boundary). With this kind of boundary,
   * the distance and geometry-related quantities are all calculated based on
   * naive definitions. This is often used for isolated systems.
   */
  class FreeSpace {
  
    public:

      /**
       * @brief the type identity for free-space boundary
       *
       * This is used for the reflection of this kind of object
       */
      static const uint Type;
      
      /**
       * @brief default initiator
       *
       * Do nothing
       */
      FreeSpace() {}

      /**
       * @brief initiator from another free-space object
       *
       * it is prohibited by popping up an error.
       *
       * @param [in] FS
       *        The input free-space object.
       */      
      FreeSpace(const FreeSpace& FS) {
        myError("Copier for FreeSpace is disabled");
      }

      /**
       * @brief copier from another free-space object
       *
       * Do nothing since there are no data to be operated.
       *
       * @param [in] FS
       *        The input free-space object
       *
       * @return the reference to the present object
       */
      FreeSpace& operator=(const FreeSpace& FS) { return *this; }

  };

  /**
   * @brief the type identity for free-space object
   *
   * It is defined as the const \c int FreeSpaceType for reflection.
   */ 
  const FreeSpace::Type=FreeSpaceType;

  /**
   * @brief the box structure with periodicity
   *
   * This class describes a structure with periodicity. The dimensions
   * are not relevant with each other. So, the whole structure looks
   * like a box. Some dimensions may not have periodicity, which are
   * marked with flags. This is the most popular boundary structure.
   * It is used to realize the large-scale system with small-scale boxes.
   *
   * \a Dim
   *    The dimension of the concerned space.
   */
  template <uint Dim>
  class PeriodicBox {

    public:

      /**
       * @brief alias for the box structure with periodicity
       */
      typedef PeriodicBox<Dim>    Type;

      /**
       * @brief the dimension of the concerned space.
       *
       * It is explicitly defined for further use.
       */
      static const uint Dimension;

      /**
       * @brief the sizes of periodic box
       */
      fixVector<double,Dim> Box;

      /**
       * @brief the flags for each dimension
       */ 
      fixVector<uint,Dim> EdgeFlag;

    private:

      /**
       * @brief half of the sizes of the periodic box
       */
      fixVector<double,Dim> halfBox;

    public:

      /**
       * @brief default initiator
       *
       * Just initiate all the internal objects with null parameter.
       * The flags are activated (are assigned as one) to enable the
       * periodicity along all dimensions.
       */
      PeriodicBox() : Box(), EdgeFlag(), halfBox() { EdgeFlag=1; }

      /**
       * @brief initiator from another periodic box
       *
       * It is prohibited by popping up an error.
       *
       * @param [in] PB
       *        The input periodic box
       */
      PeriodicBox(const Type& PB) {
        myError("Copier for PeriodicBox is disabled");
      }

      /**
       * @brief copier from another periodic box
       *
       * Just copy all the internal objects into the corresponding objects
       * in present class.
       *
       * @param [in] PB
       *        The input periodic box
       *
       * @return the reference to the present object
       */ 
      Type& operator=(const Type& PB) {
        Box=PB.Box;
        EdgeFlag=PB.EdgeFlag;
        halfBox=PB.halfBox;
        return *this;
      }

      /**
       * @brief set the box sizes and a uniform flag
       *
       * The size of box is set based on the input data. Half size of box
       * is calculated accordingly. The flag is set based on the input
       * value.
       *
       * @param [in] pbBox
       *        The vector containing size information
       *
       * @param [in] fg
       *        The \c int type value indicating the flag for all dimensions.
       *        It takes a default value of one indicating all dimensions
       *        are activated.
       */
      void Set(const VectorBase<double>& pbBox, const uint& fg=1) {
        assert(pbBox.size()>=Dim);
        Box=pbBox;
        EdgeFlag=fg;
        halfBox=Box;
        halfBox.scale(0.5);
      }

      /**
       * @brief set the box sizesand flags
       *
       * The size and flags are assigned with input vectors. Half sizes
       * of box is consequently calculated.
       *
       * @param [in] pbBox
       *        The vector containing the size information
       *
       * @param [in] fgBox
       *        The vector containing the flag information 
       */
      void Set(const VectorBase<double>& pbBox,
               const VectorBase<uint>& fgBox) {
        assert(pbBox.size()>=Dim);
        assert(fgBox.size()>=Dim);
        Box=pbBox;
        EdgeFlag=fgBox;
        halfBox=Box;
        halfBox.scale(0.5);
      }

      /**
       * @brief shift a vector the main domain
       *
       * For the structure of the periodic box, the center region around
       * the origin, whose edges equal to the box size, is defined as
       * main domain. This function shifts the vector to the main domain.
       * It is implemented by iteratively shifting, rather than the
       * deleting the residual quantity. This would be efficient when
       * vector is not far away from main domain. This function is defined
       * as const to enable this function could be used for const instance
       * periodic box.
       *
       * @param [in,out] v
       *        The input and output vector. The input vector is used
       *        to avoid temporary vector definition for efficiency. 
       */
      void Shift2Main(VectorBase<double>& v) const {
        double *it=v.begin();
        double *bt=const_cast<double*>(Box.data());
        double *be;
        double  hftmd,tmd,*nowtmd;
        for(uint i=0;i<Dim;++i) {
          if(EdgeFlag[i]==0)  continue;
          nowtmd=&v[i];
          hftmd=halfBox[i];
          tmd=Box[i];
          while(*nowtmd<-tmd)  *nowtmd+=tmd;
          while(*nowtmd>=tmd)  *nowtmd-=tmd;
        }
      }

  };

  /**
   * @brief spatial dimension of the periodic box
   *
   * It is defined as the template parameter and is used as the reflection
   * for the template parameter.
   *
   * \a Dim
   *    The dimension of the concerned space
   */
  template <uint Dim>
  const uint PeriodicBox<Dim>::Dimension=Dim;

}

#endif
