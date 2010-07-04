
/**
 * @file periodic-box.h
 * @brief the geometry with periodic boundary
 *
 * This file describes the geometry with periodic boundary and some related
 * operations for displacement calcution. It is a popular geometry for
 * extended system.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Periodic_Box_H_
#define _Periodic_Box_H_

#include "geometry-name.h"
#include "displacement-direct.h"

namespace std {

  /**
   * @brief declaration of the geometry with periodic boundary
   */
  struct PeriodicBox;

  void assign(PeriodicBox&, const PeriodicBox&);
  void release(PeriodicBox&);

  /**
   * @brief the name of state of the periodicity
   *
   * This is a collection of the name for the state of periodicity.
   * It is a flag for the state of each dimension.
   */
  enum PeriodicStateName {
    /**
     * @brief the flag indicating that periodicity exists
     */
    HavePeriodic=1,
    /**
     * @brief the flag indicating that no periodicity exists
     */
    NoPeriodic=0
  };

  /**
   * @brief the data structure describing periodicity along each axis.
   *
   * This data structure includes the flags of periodicity along each
   * axis, and the size of period. The half size of period is also
   * stored for temporary use.
   */
  struct PeriodicBox {

    static const unsigned int TypeID;

    /**
     * @brief the size of period
     */
    double* box;
    /**
     * @brief the size of half period
     */
    double* halfbox;
    /**
     * @brief the flag indicating the existence of periodicity
     */
    unsigned int* edgeflag;
    /**
     * @brief the dimension of space
     */
    unsigned int size;
    /**
     * @brief storage state of this kind of object
     */
    unsigned int state;

    /**
     * @brief abbreviation of PeriodicBox type
     */
    typedef PeriodicBox Type;

    /**
     * @brief default initiator
     *
     * Just initiate all the pointers with NULL, and assign the flags
     * with no information
     */
    PeriodicBox()
      : box(NULL), halfbox(NULL), edgeflag(NULL), size(0), state(Unused) {}
    /**
     * @brief initiator from another PeriodicBox object
     *
     * It is prohibited and pop up an error message
     *
     * @param PB [in] the input PeriodicBox object
     */
    PeriodicBox(const Type& PB) { myError("Cannot create from Periodic Box"); }
    /**
     * @brief copy from another PeriodicBox object
     *
     * It is implemented with assign operation.
     *
     * @param PB [in] the input PeriodicBox object
     * @return the reference to the resultant PeriodicBox object
     */
    Type& operator=(const Type& PB) { assign(*this,PB); return *this; }
    /**
     * @brief destructor
     *
     * It is implemented with release operation
     */
    ~PeriodicBox() { release(*this); }

  };

  /**
   * @brief the ID related to the type of PeriodicBox object
   *
   * it takes the value of PeriodicBoxType and is used for type reflection.
   */
  const unsigned int PeriodicBox::TypeID=PeriodicBoxType;

  /**
   * @brief check the availability of PeriodicBox object
   *
   * It is implemented by checking the availability of the size array
   * in the input PeriodicBox object.
   *
   * @param PB [in] the PeriodicBox object to be checked
   * @return the availability of the input PeriodicBox object
   */
  bool IsAvailable(const PeriodicBox& PB) { return IsAvailable(PB.box); }
  /**
   * @brief check if the PeriodicBox object is a description of geometry
   *
   * Since PeriodicBox object describes a kind of geometry, this procedure
   * always gives out positive answer.
   *
   * @param PB [in] the PeriodicBox object to be checked
   * @return true flag
   */
  bool IsGeometry(const PeriodicBox& PB) { return true; }

  /**
   * @brief release a PeriodicBox object
   *
   * The internal storage is released based on the state flag which indicating
   * their status of allocation. The flags are also updated.
   *
   * @param PB [in] the PeriodicBox object to be released
   * @return nothing
   */
  void release(PeriodicBox& PB) {
    if(PB.state==Allocated) {
      safe_delete_array(PB.box);
      safe_delete_array(PB.halfbox);
      safe_delete_array(PB.edgeflag);
    } else {
      PB.box=NULL;
      PB.halfbox=NULL;
      PB.edgeflag=NULL;
    }
    PB.size=0;
    PB.state=Unused;
  }

  /**
   * @brief assign PeriodicBox object from another
   *
   * The internal data are copied with assign operation for array.
   * The size takes the minimum of the size property of the related
   * PeriodicBox objects. The concerned PeriodicBox objects are checked
   * for availability before this operation.
   *
   * @param dest [out] the PeriodicBox object to accept the input
   * @param src [in] the PeriodicBox object storing the input
   * @return nothing
   */
  void assign(PeriodicBox& dest, const PeriodicBox& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    unsigned int n=(dest.size<src.size?dest.size:src.size);
    assign(dest.box,src.box,n);
    assign(dest.halfbox,src.halfbox,n);
    assign(dest.edgeflag,src.edgeflag,n);
  }

  /**
   * @brief allocate PeriodicBox object
   *
   * The internal storage is allocated based on the input dimension.
   * The corresponding flags are also assigned. The input PeriodicBox
   * object is released before this operation to avoid memory leak.
   *
   * @param PB [out] the PeriodicBox object to be allocated.
   * @param dim [in] the dimension of space.
   * @return nothing
   */
  void allocate(PeriodicBox& PB,const unsigned int dim) {
    release(PB);
    PB.box=new double[dim];
    PB.halfbox=new double[dim];
    PB.edgeflag=new unsigned int[dim];
    PB.size=dim;
    PB.state=Allocated;
  }

  /**
   * @brief refer to another PeriodicBox object
   * 
   * It is implemented by copying the pointers and flags from source
   * PeriodicBox object to the destination object. The source object
   * is checked for its availability before using. The destination
   * object is released for this operation to avoid memory leak.
   *
   * @param dest [out] the PeriodicBox object to accept the input
   * @param src [in] the PeriodicBox object storing the input
   * @return nothing
   */
  void refer(PeriodicBox& dest, const PeriodicBox& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.box=src.box;
    dest.halfbox=src.halfbox;
    dest.edgeflag=src.edgeflag;
    dest.size=src.size;
    dest.state=Reference;
  }

  /**
   * @brief update PeriodicBox object
   *
   * This is used to update internal temporary storage (half period)
   * after the modification of some data (period). The update operation
   * provides the common interface with other kinds of geometry. The
   * concerned PeriodicBox object is checked for availability before
   * this operation.
   *
   * @param PB [in] the PeriodicBox object to be updated
   * @return nothing
   */
  void update(PeriodicBox& PB) {
    assert(IsAvailable(PB));
    assign(PB.halfbox,PB.box,PB.size);
    scale(PB.halfbox,0.5,PB.size);
  }

  /**
   * @brief set PeriodicBox object with input arrays of periods and flags
   *
   * The input data are copied into the PeriodicBox object, and the
   * PeriodicBox object is updated after reading inputs. The input
   * arrays and PeriodicBox object are checked for availability before
   * this operation.
   *
   * @param PB [out] the PeriodicBox obejct to accept the input
   * @param box [in] the \c double array containing periods
   * @param flag [in] the \c unsigned \c int array containing the flags for
   *                  existence of periodicity
   * @param m [in] the size of input arrays (box and flag)
   * @param boff, foff [in] the offsets for the first elements in the input
   *                        arrays box and flag. They takes the default
   *                        value of iZero.
   * @param bstep, fstep [in] the separations between elements in the input
   *                        arrays box and flag. They takes the default
   *                        value of lOne.
   * @return nothing
   */
  void set(PeriodicBox& PB,
           const double* box, const unsigned int* flag, const unsigned int m,
           const int boff=iZero, const long bstep=lOne,
           const int foff=iZero, const long fstep=lOne) {
    assert(IsAvailable(PB));
    assert(IsAvailable(box));
    assert(IsAvailable(flag));
    unsigned int n=(m<PB.size?m:PB.size);
    assign(PB.box,box,n,boff,bstep);
    assign(PB.edgeflag,flag,n,foff,fstep);
    update(PB);
  }

  /**
   * @brief set PeriodicBox object with Vector objects of periods and flags
   *
   * It is implemented with set operation related to \c double arrays.
   * The minimum of the sizes of Vector objects is used for set operation.
   *
   * @param PB [out] the PeriodicBox obejct to accept the input
   * @param box [in] the Vector object containing periods
   * @param flag [in] the Vector object containing flags for periodicity
   * @return nothing.
   */
  void set(PeriodicBox& PB,
           const Vector<double>& box, const Vector<unsigned int>& flag) {
    unsigned int m=(box.size<flag.size?box.size:flag.size);
    set(PB,box(),flag(),m);
  }

  /**
   * @brief set PeriodicBox object with \c double array of periods and constants for flag
   *
   * The internal data are copied with assign operation for \c double array
   * and for constant. The PeriodicBox object is updated after reading
   * input. The PeriodicBox and array are checked for their availability
   * for this set operation.
   *
   * @param PB [out] the PeriodicBox obejct to accept the input
   * @param box [in] the \c double array containing periods
   * @param m [in] the size of input array box
   * @param fg [in] the periodicity flag for all dimensions
   * @param boff [in] the offset for the first element in array box.
   *                  it takes the default value iZero
   * @param bstep [in] the separation between used elements in array box.
   *                   it takes the default value lOne.
   * @return nothing
   */
  void set(PeriodicBox& PB,
           const double* box, const unsigned int m,
           const unsigned int fg=HavePeriodic,
           const int boff=iZero, const long bstep=lOne) {
    assert(IsAvailable(PB));
    assert(IsAvailable(box));
    unsigned int n=(m<PB.size?m:PB.size);
    assign(PB.box,box,n,boff,bstep);
    assign(PB.edgeflag,fg,n);
    update(PB);
  }

  /**
   * @brief set PeriodicBox object with Vector object of periods and constants for flag
   *
   * It is implemented with the set operation for \c double array and constant.
   *
   * @param PB [out] the PeriodicBox obejct to accept the input
   * @param box [in] the Vector object containing periods
   * @param fg [in] the periodicity flag for all dimensions
   * @return nothing
   */
  void set(PeriodicBox& PB,
           const Vector<double>& box, const unsigned int fg=HavePeriodic) {
    set(PB,box(),box.size,fg);
  }

  /**
   * @brief compress a vector into main region
   *
   * Considering the periodic boundary condition, the mirror in
   * region with minimal size of coordinates is calculated.
   * Here, the region is from negative half period to positive
   * half period.
   *
   * @param PB [in] the PeriodicBox object
   * @param v [in,out] the array representing vector to be shifted
   * @param vdim [in] the size of the array
   * @param voff [in] the offset of the first element in array v.
   *                  It takes the default value uZero.
   * @param vstep [in] the separation between elements in array v.
   *                   It takes the default value uOne.
   * @return nothing
   */
  void Compress2MainRegion(const PeriodicBox& PB, double* v,
                           const unsigned int vdim,
                           const unsigned int voff=uZero,
                           const unsigned int vstep=uOne) {
    assert(IsAvailable(PB));
    assert(IsAvailable(v));
    double bmd, bhd;
    unsigned int n=(PB.size<vdim?PB.size:vdim);
    double *pv=v+voff;
    for(unsigned int i=0;i<n;++i,pv+=vstep) {
      bhd=PB.halfbox[i];
      bmd=PB.box[i];
      while(*pv<-bhd) *pv+=bmd;
      while(*pv>=bhd) *pv-=bmd;
    }
  }

  /**
   * @brief compress a Vector object into main region
   *
   * It is implemented with compress operation for array.
   *
   * @param PB [in] the PeriodicBox object
   * @param v [in,out] the Vector object to be operated
   * @return nothing
   */
  void Compress2MainRegion(const PeriodicBox& PB, Vector<double>& v) {
    Compress2MainRegion(PB,v(),v.size);
  }

  /**
   * @brief calculate displacement for arrays with periodic boundary condition
   *
   * Firstly, a displacement is calculated with direct DisplacementFunc
   * operation. This vector is compressed to main regions.
   *
   * @param va, vb [in] the arrays representing the coordinates
   * @param dim [in] the dimension of space
   * @param Dsp [out] the array storing displacement
   * @param PB [in] the PeriodicBox object
   * @param aoff, boff, doff [in] the offsets for the first element in the
   *                              arrays va, vb, and Dsp. They take the
   *                              default value iZero.
   * @param astep, bstep, dstep [in] the separations between used elements in
   *                                 the arrays va, vb, and Dsp. They take the
   *                                 default value lOne.
   * @return nothing.
   */
  void DisplacementFunc(const double* va, const double* vb,
                        const unsigned int dim, double* Dsp,
                        const PeriodicBox& PB,
                        const int aoff=iZero, const long astep=lOne,
                        const int boff=iZero, const long bstep=lOne,
                        const int doff=iZero, const long dstep=lOne) {
    unsigned int n=(dim<PB.size?dim:PB.size);
    DisplacementFunc(va,vb,n,Dsp,aoff,astep,boff,bstep,doff,dstep);
    Compress2MainRegion(PB,Dsp,n,doff,dstep);
  }

  /**
   * @brief calculate displacement for Vector objects with periodic boundary
   *
   * It is implemented with DisplacementFunc operation for array with
   * periodic boundary condition. The number of elements to be operated
   * is the minimum of the sizes of the concerned Vector object.
   *
   * @param va, vb [in] the Vector objects as the coordinates
   * @param Dsp [out] the Vector object storing displacement
   * @param PB [in] the PeriodicBox object
   * @return nothing.
   */
  void DisplacementFunc(const Vector<double>& va, const Vector<double>& vb,
                        Vector<double>& Dsp, const PeriodicBox& PB) {
    unsigned int m;
    m=(va.size<vb.size?va.size:vb.size);
    m=(m<Dsp.size?m:Dsp.size);
    DisplacementFunc(va(),vb(),m,Dsp(),PB);
  }

}

#endif

