
#include "hash-func.h"
#include <iostream>
using namespace std;

int main() {
  const int N=5;
  int a[N];
  for(int i=0;i<N;++i) a[N]=i+1;
  cout<<hash_rs(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_js(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_pjw(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_elf(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_bkdr(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_sdbm(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_djb(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_dek(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_bp(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_fnv(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_ap(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<endl;
  a[4]++;
  cout<<hash_rs(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_js(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_pjw(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_elf(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_bkdr(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_sdbm(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_djb(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_dek(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_bp(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_fnv(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  cout<<hash_ap(reinterpret_cast<const char*>(a),sizeof(int)*N)<<endl;
  /*
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
  */
  return 1;
}

