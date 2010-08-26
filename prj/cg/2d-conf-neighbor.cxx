
#include "parameter-list.h"
#include <iostream>
#include <fstream>
using namespace std;

void convert(unsigned int* seq, const unsigned int size) {
  unsigned int map[4];
  map[seq[0]]=0; map[3-seq[0]]=3;
  for(unsigned int i=1;i<size;++i)
    if(seq[i]!=seq[0]) {
      map[seq[i]]=1; map[3-seq[i]]=2;
      break;
    }
  for(unsigned int i=0;i<size;++i)  seq[i]=map[seq[i]];
}

void check_move(unsigned int* seq, const unsigned int size,
                ParameterList& PL, Vector<unsigned int>& IDSet) {
  Vector<UniqueParameter>* pID;
  bool fg;
  convert(seq,size);
  pID=const_cast<Vector<UniqueParameter>*>(get(PL,seq,size));
  if(pID!=0) {
    fg=false;
    for(unsigned int z=1;z<=IDSet[0];++z)
      if((*pID)[0].u==IDSet[z]) { fg=true; break; }
    if(!fg) {
      IDSet[0]++;
      IDSet[IDSet[0]]=(*pID)[0].u;
    }
  }
}

int main() {

  ParameterList ConfLib;
  allocate(ConfLib,11,1,15037);

  ifstream ifs;
  ifs.open("12-conf");
  for(unsigned int i=0;i<15037;++i) {
    ifs>>ConfLib.key[i];
    buildhash(ConfLib.key[i]);
    ConfLib.value[i][0].u=i;
  }
  ifs.close();
  updatetree(ConfLib);
  cout<<(*get(ConfLib,ConfLib.key[15035].index,11))[0].u<<endl;

  Vector<unsigned int> rConf;
  Vector<unsigned int> IDSet;
  allocate(rConf,11);
  allocate(IDSet,1+12+2+10);

  for(unsigned int i=0;i<15037;++i) {
    cout<<i;
    IDSet[0]=0;
    assign(rConf.data,ConfLib.key[i].index,11);
    rConf[0]=(rConf[0]+2)%4;
    check_move(rConf.data,11,ConfLib,IDSet);
    assign(rConf.data,ConfLib.key[i].index,11);
    rConf[0]=3-(rConf[0]+2)%4;
    check_move(rConf.data,11,ConfLib,IDSet);
    for(unsigned int k=1;k<11;++k) {
      assign(rConf.data,ConfLib.key[i].index,11);
    }
    assign(rConf.data,ConfLib.key[i].index,11);
    rConf[10]=(rConf[10]+2)%4;
    check_move(rConf.data,11,ConfLib,IDSet);
    assign(rConf.data,ConfLib.key[i].index,11);
    rConf[10]=3-(rConf[10]+2)%4;
    check_move(rConf.data,11,ConfLib,IDSet);
    for(unsigned int z=1;z<=IDSet[0];++z)
      cout<<"\t"<<IDSet[z];
    cout<<endl;
  }

  return 1;
}

