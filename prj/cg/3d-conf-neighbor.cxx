
#include "parameter-list.h"
#include <iostream>
#include <fstream>
using namespace std;

void convert(unsigned int* seq, const unsigned int size) {
  unsigned int level=0;
  unsigned int map[6],reg[6]={7,7,7,7,7,7};
  map[seq[0]]=0;  map[5-seq[0]]=5;
  reg[0]=seq[0];  reg[1]=5-seq[0];
  for(unsigned int i=1;i<size;++i)
    if(level==0) {
      if((seq[i]!=reg[0])&&(seq[i]!=reg[1])) {
        map[seq[i]]=1;  map[5-seq[i]]=4;
        reg[2]=seq[i];  reg[3]=5-seq[i];
        level++;
      }
    } else if(level==1) {
      if((seq[i]!=reg[0])&&(seq[i]!=reg[1])&&
         (seq[i]!=reg[2])&&(seq[i]!=reg[3])) {
        map[seq[i]]=2;  map[5-seq[i]]=3;
        break;
      }
    }
  for(unsigned int i=0;i<size;++i)  seq[i]=map[seq[i]];
}

void check_move(unsigned int* seq, const unsigned int size,
                const unsigned int sID,
                ParameterList& PL, Vector<unsigned int>& IDSet) {
  Vector<UniqueParameter>* pID;
  bool fg;
  convert(seq,size);
  pID=const_cast<Vector<UniqueParameter>*>(get(PL,seq,size));
  if(pID!=0) {
    if((*pID)[0].u!=sID) {
      fg=false;
      for(unsigned int z=1;z<=IDSet[0];++z)
        if((*pID)[0].u==IDSet[z]) { fg=true; break; }
      if(!fg) {
        IDSet[0]++;
        IDSet[IDSet[0]]=(*pID)[0].u;
      }
    }
  }
}

int main() {

  ParameterList ConfLib;
  allocate(ConfLib,11,1,885641);

  ifstream ifs;
  ifs.open("12-conf-3d");
  for(unsigned int i=0;i<885641;++i) {
    ifs>>ConfLib.key[i];
    buildhash(ConfLib.key[i]);
    ConfLib.value[i][0].u=i;
  }
  ifs.close();
  updatetree(ConfLib);
  cout<<(*get(ConfLib,ConfLib.key[880901].index,11))[0].u<<endl;

  Vector<unsigned int> rConf;
  Vector<unsigned int> IDSet;
  allocate(rConf,11);
  allocate(IDSet,1+12+6+10);

  for(unsigned int i=0;i<885641;++i) {
    cout<<i;
    IDSet[0]=0;
    assign(rConf.data,ConfLib.key[i].index,11);
    rConf[0]=(rConf[0]+1)%3;
    check_move(rConf.data,11,i,ConfLib,IDSet);
    assign(rConf.data,ConfLib.key[i].index,11);
    rConf[0]=5-(rConf[0]+1)%3;
    check_move(rConf.data,11,i,ConfLib,IDSet);
    assign(rConf.data,ConfLib.key[i].index,11);
    rConf[0]=(rConf[0]+2)%3;
    check_move(rConf.data,11,i,ConfLib,IDSet);
    assign(rConf.data,ConfLib.key[i].index,11);
    rConf[0]=5-(rConf[0]+2)%3;
    check_move(rConf.data,11,i,ConfLib,IDSet);
    for(unsigned int k=1;k<11;++k) {
      assign(rConf.data,ConfLib.key[i].index,11);
      if(rConf[k-1]!=rConf[k]) {
        swap(rConf[k],rConf[k-1]);
        check_move(rConf.data,11,i,ConfLib,IDSet);
      }
    }
    for(unsigned int k=1;k<10;++k) {
      assign(rConf.data,ConfLib.key[i].index,11);
      if(rConf[k-1]+rConf[k+1]==5) {
        swap(rConf[k-1],rConf[k+1]);
        check_move(rConf.data,11,i,ConfLib,IDSet);
      }
    }
    assign(rConf.data,ConfLib.key[i].index,11);
    rConf[10]=(rConf[10]+1)%3;
    check_move(rConf.data,11,i,ConfLib,IDSet);
    assign(rConf.data,ConfLib.key[i].index,11);
    rConf[10]=5-(rConf[10]+1)%3;
    check_move(rConf.data,11,i,ConfLib,IDSet);
    assign(rConf.data,ConfLib.key[i].index,11);
    rConf[10]=(rConf[10]+2)%3;
    check_move(rConf.data,11,i,ConfLib,IDSet);
    assign(rConf.data,ConfLib.key[i].index,11);
    rConf[10]=5-(rConf[10]+2)%3;
    check_move(rConf.data,11,i,ConfLib,IDSet);
    for(unsigned int z=0;z<=IDSet[0];++z)
      cout<<"\t"<<IDSet[z];
    cout<<endl;
  }

  return 1;
}

