
/**
 * @file free-space.h
 * @brief the gepmetry with no boundary
 *
 * This file describes the geometry with no boundary. This is regularly
 * used for isolated or small-size systems.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */
#ifndef _Free_Space_H_
#define _Free_Space_H_

#include "error-proc.h"
#include "geometry-name.h"
#include "displacement-direct.h"

namespace std {

  /**
   * @brief the geometry indicating no boundary
   *
   * This is the simplest geometry. There are no boundary for this geometry.
   * It is widely used for isolated systems. There are no constraints for
   * coordinates.
   */
  struct FreeSpace {

    /**
     * @brief abbreviation for the geometry with no boundary
     */
    typedef FreeSpace Type;

    static const unsigned int TypeID;

    /**
     * @brief default initiator
     *
     * Do nothing
     */
    FreeSpace() {}
    /**
     * @brief initiator from another FreeSpace
     *
     * it is prohibited and pop up an error message
     *
     * @param FS [in] the input FreeSpace object
     */
    FreeSpace(const  Type& FS) { myError("Cannot create from Free Space"); }
    /**
     * @brief copy from another FreeSpace object
     *
     * It is implemented with assign operation.
     *
     * @param  FS [in] the input FreeSpace object
     * @return the reference to the resultant FreeSpace object
     */
    Type& operator=(const Type& FS) { return *this; }
    /**
     * @brief destructor
     *
     * Do nothing
     */
    ~FreeSpace() {}

  };

  /**
   * @brief the ID for this kind of geometry
   *
   * It thakes the value of FreeSpaceType, and is used for type reflection
   */
  const unsigned int FreeSpace::TypeID=FreeSpaceType;

  /**
   * @brief check the availability of FreeSpace object
   *
   * Since there are no data inside, this is always true.
   *
   * @param FS [in] the FreeSpace object to be checked.
   * @return true flag
   */
  bool IsAvailable(const FreeSpace& FS) { return true; }
  
  /**
   * @brief check if this FreeSpace object is a geometry
   *
   * FreeSpace object describes a geometry. Therefore, it is always true.
   *
   * @param FS [in] the FreeSpace object to be checked
   * @return true flag.
   */
  bool IsGeometry(const FreeSpace& FS) { return true; }

  /**
   * @brief assign FreeSpace object from another
   *
   * Do nothing
   *
   * @param dest [out] the FreeSpace object to accept input
   * @param src [in] the FreeSpace object storing the input
   * @return nothing
   */
  void assign(FreeSpace& dest, const FreeSpace& src) {}
  /**
   * @brief release a FreeSpace object
   *
   * Do nothing since there are no data inside.
   *
   * @param FS [in] the FreeSpace object to be released
   * @return nothing.
   */
  void release(FreeSpace& FS) {}
  /**
   * @brief allocate FreeSpace object
   *
   * Do nothing since there are no data inside.
   *
   * @param FS [out] the FreeSpace object to be allocated
   * @param dim [in] the dimension of the space
   * @return nothing
   */
  void allocate(FreeSpace& FS, const unsigned int dim) {}
  /**
   * @brief refer to another FreeSpace object
   *
   * Do nothing.
   *
   * @param dest [out] the FreeSpace object to accept input
   * @param src [in] the FreeSpace object storing the input
   * @return nothing
   */
  void refer(FreeSpace& dest, const FreeSpace& src) {}

  /**
   * @brief calculate displacement for \c double array in free space
   *
   * It is implemented with DisplacementFunc without geometry.
   *
   * @param va, vb [in] the arrays to store the coordinates
   * @param dim [in] the dimension of the space
   * @param Dsp [out] the array to store displacement
   * @param FS [in] the FreeSpace object for this evaluation
   * @param aoff, boff, doff [in] the offsets for the first elements of
   *                              the arrays va, vb, Dsp. They takes the
   *                              default value iZero.
   * @param astep, bstep, dstep [in] the separations between elements to be
   *                                 used in the arrays va, vb. They takes
   *                                 the default value lOne.
   * @return nothing
   */
  void DisplacementFunc(const double* va, const double* vb,
                        const unsigned int dim, double* Dsp,
                        const FreeSpace& FS,
                        const int aoff=iZero, const long astep=lOne,
                        const int boff=iZero, const long bstep=lOne,
                        const int doff=iZero, const long dstep=lOne) {
    DisplacementFunc(va,vb,dim,Dsp,aoff,astep,boff,bstep,doff,dstep);
  }

  /**
   * @brief calculate displacement for Vector objects in free space
   *
   * It is implemented with DisplacementFunc without geometry.
   *
   * @param va,vb [in] the Vector objects to store the coordinates
   * @param Dsp [out] the Vector object to store displacement
   * @param FS [in] the FreeSpace object for this evaluation
   * @return nothing
   */
  void DisplacementFunc(const Vector<double>& va, const Vector<double>& vb,
                        Vector<double>& Dsp, const FreeSpace& FS) {
    DisplacementFunc(va,vb,Dsp);
  }

}

#endif

