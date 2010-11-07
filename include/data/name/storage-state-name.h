
/**
 * @file storage-state-name.h
 * @brief the name for states of storage
 *
 * This file defines the names for the states of storage.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Storage_State_Name_H_
#define _Storage_State_Name_H_

namespace std {

  /**
   * @brief the name for the states of various kinds of storages
   *
   * Several names are defined for the states of various storages.
   * These names are used as constants for various applications.
   */
  enum StorageStateName {
    /**
     * @brief the name indicating the storage is unused
     */
    Unused=0,
    /**
     * @brief the name indicating the storage is allocated
     */
    Allocated,
    /**
     * @brief the name indicating the storage is a kind of reference
     */
    Reference,
    /**
     * @brief the name for storage with hybrid types of implementations
     */
    HybridStorage
  };

}

#endif

