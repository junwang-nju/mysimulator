
/**
 * @file memory.h
 * @brief Procedures for memory-related operation
 */

#ifndef _Memory_H_
#define _Memory_H_

#include "storage-state-name.h"
#include <cstdlib>

namespace std {

  /**
   * @brief delete allocated memory
   *
   * This is an encapsulation for the regular deletion of allocated memory.
   * The related pointer is checked if it is NULL (which suggested if the
   * pointer related to allocated block of memory. After the delete
   * operation, the related pointer is assigned as NULL to avoid
   * unexpected access.
   *
   * \a T
   *    The type of data pointed by the pointer
   *
   * @param [in,out] ptr
   *        The pointer to the memory to be freed. It would returned
   *        as NULL after this operation.
   *
   * @return 1 indicating the operation is successful.
   */
  template <typename T>
  inline int safe_delete(T*& ptr) {
    if(ptr==NULL)   return 0;
    delete ptr;
    ptr=NULL;
    return 1;
  }

  template <typename T>
  inline int safe_delete_array(T*& ptr) {
    if(ptr==NULL)   return 0;
    delete[] ptr;
    ptr=NULL;
    return 1;
  }

  template <typename T>
  inline void safe_release(T*& ptr, const unsigned int state) {
    if(state==Allocated)  safe_delete_array(ptr);
    else ptr=NULL;
  }

}

#endif
