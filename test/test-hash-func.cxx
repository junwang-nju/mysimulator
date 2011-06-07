
#include "hash/func.h"
using namespace mysimulator;

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

  return 0;
}

