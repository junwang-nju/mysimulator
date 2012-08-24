
/**
 * @file boundary/free/interface.h
 * @brief boundary condition representing free space
 *
 * The boundary condition with no boundary is popular in model study with no
 * solvent. A data structure is needed to describe this kind of boundary
 * condition. This file implements the data structure.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Boundary_Free_Interface_H_
#define _Boundary_Free_Interface_H_

namespace mysimulator {

  /** @class FreeSpace
   * @brief the data structure defining the condition with no boundary
   *
   * This defines a boundary condition with no boundary. Since this
   * kind of boundary represents a free space, there are no parameters
   * in this data structure.
   */
  class FreeSpace {

    public:

      /** @typedef Type
       * @brief the trait type of \c FreeSpace object
       *
       * This is used for type reflection and abbreviation
       */
      typedef FreeSpace Type;

      /** @brief default initiator
       *
       * There are no contents since there are no data for this object.
       */
      FreeSpace() {}
      /** @brief default destructor
       *
       * There are no operations since there are no data for this object.
       */
      ~FreeSpace() {}

      /** @fn bool IsValid();
       * @brief check the validity of the \c FreeSpace object
       *
       * Since there are no contents in \c FreeSpace object, this object
       * is always available.
       *
       * @return a \c true flag indicating this object is available
       */
      bool IsValid() const { return true; }
      /** @fn void Allocate(unsigned int)
       * @brief allocate \c FreeSpace object
       *
       * This is an interface to allocate \c FreeSpace object. This is used
       * to be compatible with other boundary conditions. Since there are
       * no data members in this object, there are no operations in this
       * function.
       *
       * @param dim [in] the dimension of the concerned space
       */
      void Allocate(unsigned int dim) {}
      /** @fn void Refer(const Type&)
       * @brief refer to another \c FreeSpace object
       *
       * This is an interface to refer to another \c FreeSpace object.
       * This is used to be compatible with other boundary conditions. Since
       * there are no data members in this object, there are no operations
       * in this function.
       *
       * @param B [in] the \c FreeSpace object to be referred to
       */
      void Refer(const Type& B) {}

    private:

      /** @brief disable copy initiator
       *
       * There are no operations for this copy initiator. This is put into
       * the \c private part to disable this operation.
       */
      FreeSpace(const Type&) {}
      /** @fn FreeSpace& operator=(const FreeSpace&)
       * @brief the disabled copier 
       *
       * There are no operations for this copier. This is put into the
       * \c private part to disable this operation.
       *
       * @param B [in] the input \c FreeSpace object
       * @return the reference to present \c FreeSpace object.
       */
      Type& operator=(const Type& B) { return *this; }

  };

  /** @fn void Clear(FreeSpace& B)
   * @brief clear the content of \c FreeSpace object
   *
   * There are no operations since there are no contents for \c FreeSpace
   * object.
   *
   * @param B [in,out] the \c FreeSpace object to be cleared
   */
  void Clear(FreeSpace& B) {}

}

#include "displacement/free/calc.h"

#endif

