
#include "property-list.h"
#include "parameter-key.h"
#include "btree.h"
#include <iostream>
#include <fstream>
using namespace std;

bool isSame(const Vector<int>& s1, const Vector<int>& s2,
            PropertyList<int>& flag) {
  assert(s1.size==s2.size);
  assign(flag,0);
  for(unsigned int i=0;i<s1.size;++i) flag[s1[i]][s2[i]]=1;
  int s;
  for(unsigned int i=0;i<4;++i) {
    s=0;
    for(unsigned int j=0;j<4;++j) s+=flag[i][j];
    if(s>1) return false;
  }
  for(unsigned int i=0;i<4;++i) {
    s=0;
    for(unsigned int j=0;j<4;++j) s+=flag[j][i];
    if(s>1) return false;
  }
  return true;
}

struct ConfList {
  typedef BTree<ParameterKey,unsigned int> BTreeType;
  BTreeType hash[0xFFFFU];
  ParameterKey* key;
  unsigned int* value;
};

int main() {

  PropertyList<int> Conf;
  Vector<unsigned int> sz;
  allocate(sz,15037);
  assign(sz,11);
  allocate(Conf,sz);
  ifstream ifs;
  ifs.open("12-conf");
  ifs>>Conf;
  ifs.close();

  PropertyList<int> fg;
  allocate(sz,4);
  assign(sz,4);
  allocate(fg,sz);

  cout<<isSame(Conf[0],Conf[1],fg)<<endl;
  cout<<isSame(Conf[0],Conf[0],fg)<<endl;

  return 1;
}

