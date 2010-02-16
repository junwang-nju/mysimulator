
/**
 * @file hash-func.h
 * @brief Functions to generate hash
 */

#ifndef _Hash_Function_H_
#define _Hash_Function_H_

namespace std {
  unsigned int hash_rs(const char* str, unsigned int nchar);
  unsigned int hash_js(const char* str, unsigned int nchar);
  unsigned int hash_pjw(const char* str, unsigned int nchar);
  unsigned int hash_elf(const char* str, unsigned int nchar);
  unsigned int hash_bkdr(const char* str, unsigned int nchar);
  unsigned int hash_sdbm(const char* str, unsigned int nchar);
  unsigned int hash_djb(const char* str, unsigned int nchar);
  unsigned int hash_dek(const char* str, unsigned int nchar);
  unsigned int hash_bp(const char* str, unsigned int nchar);
  unsigned int hash_fnv(const char* str, unsigned int nchar);
  unsigned int hash_ap(const char* str, unsigned int nchar);
}

#endif

